// escan.cpp : 定义 DLL 应用程序的导出函数。
//

#include "escan.h"
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <tchar.h>

#include "db.h"
#include "md5.h"
#include "queue.h"
#include <deque>
#include <string>
using namespace std;

#define MAX_ARR_SIZE	100
#define ASIZE(arr) sizeof(arr)/sizeof(arr[0])

static MD5_CTX *m_md5;
static bool m_uploading;

struct FileInfo
{
    TCHAR fname[260];
    char md5[33];
};

typedef struct _escan
{
	char url[256];
	Ecall ecall;
	void *parm;

	bool scanning;
	Queue *que_scan;
    deque<SampleInfo> que_upload;
} Escan;

//static set<string> m_cache;

static CRITICAL_SECTION m_lockarr;
static bool m_upload;

static void GetMd5(unsigned char *buf, size_t len, char *mdstr)
{
	unsigned char md[16];
	MD5Update(m_md5, buf, len);
	MD5Final(m_md5, md);
	for (int i = 0; i < 16; i++)
		sprintf(mdstr + 2 * i, "%02x", md[i]);
	mdstr[32] = 0;
}
static void* GetFileData(TCHAR *fname, size_t *fsize)
{
	HANDLE hfile = CreateFile(fname, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hfile)
	{
		printf("'%S' open failed.\n", fname);
		return NULL;
	}
	size_t usize = GetFileSize(hfile, 0);
	if (usize == 0)
	{
		printf("file size = 0.\n");
		CloseHandle(hfile);
		return NULL;
	}
	HANDLE hmap = CreateFileMapping(hfile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (INVALID_HANDLE_VALUE == hmap)
	{
		printf("create file map failed.\n");
		CloseHandle(hfile);
		return NULL;
	}
	void *pbuf = MapViewOfFile(hmap, FILE_MAP_READ, 0, 0, 0);
	if (NULL == pbuf)
	{
		CloseHandle(hfile);
		CloseHandle(hmap);
		return NULL;
	}
	*fsize = usize;
	return pbuf;
}

//返回值：-1无法连通网络 0正常 1威胁 2表示需要上传
static int ScanOnline(Escan *es, SampleInfo *sample)
{
    //TODO: 
    return 0;
}


void UploadThread(void *es)
{
    Escan *e = (Escan *)es;
    m_uploading = true;
    SampleInfo sample;
    while (m_uploading)
    {
        EnterCriticalSection(&m_lockarr);
        if (e->que_upload.size())
        {
            sample = e->que_upload.front();
            e->que_upload.pop_front();
            LeaveCriticalSection(&m_lockarr);
            //TODO:
            //http_post()
        }
        else
        {
            LeaveCriticalSection(&m_lockarr);
            m_uploading = false;
        }
    }
}

static int UploadFile(Escan *es, SampleInfo *sample)
{
    if (!m_uploading)
    {
        _beginthread(UploadThread, 0, es);
    }

    EnterCriticalSection(&m_lockarr);
    es->que_upload.push_back(*sample);
    LeaveCriticalSection(&m_lockarr);
    return 0;
}
static int ExitScan()
{
    return 0;
}

static void ScanFiles(void *es)
{
    int res;
    size_t flen;
	Escan *e = (Escan *)es;
    SampleInfo sample = { 0 };
    while (e->scanning)
    {
        //队列出列失败，表示队列为空，sleep 1 秒
        if (QueuePop(e->que_scan, sample.fname) == -1)
        {
            Sleep(1000);
            continue;
        }
        unsigned char *buf = (unsigned char *)GetFileData(sample.fname, &flen);
        GetMd5(buf, flen, sample.md5);

        //本地白名单数据库查找
        if (db_scan(sample.md5) == 0)
        {
            sample.result = kNormal;
        }
        else
        {
            res = ScanOnline(e, &sample);
            if (res == 2)
            {
                UploadFile(e, &sample);
            }
        }
        if (sample.result != kUnknow)
        {
            e->ecall(e->parm, &sample);
        }
        sample.result = kUnknow;
    }
}

Escan* es_init(char *url, Ecall ecall, void *parm)
{
	Escan *es = (Escan *)calloc(1, sizeof(Escan));
    strncpy(es->url, url, ASIZE(es->url)-1);
    es->ecall = ecall;
    es->parm = parm;
    es->que_scan = QueueInit(10, sizeof(TCHAR[260]));
	m_md5 = (MD5_CTX *)malloc(sizeof(MD5_CTX));
	MD5Init(m_md5);
    _beginthread(ScanFiles, 0, (void *)es);
	
    return es;
}

int es_send_md5(Escan *es, char *md5)
{
	return 0;
}

int es_scan_file(Escan *es, TCHAR *fname)
{
    TCHAR name[260];
    name[260-1] = _T('\0');
    _tcsncpy(name, fname, _countof(name)-1);
	return QueuePush(es->que_scan, fname);
}
void es_free(Escan *es)
{
    if (es->scanning)
    {
        ExitScan();
    }
    if (es->que_scan)
    {
        QueueFree(es->que_scan);
    }
    free(es);
}
