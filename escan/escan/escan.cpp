// escan.cpp : 定义 DLL 应用程序的导出函数。
//

#include "escan.h"
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <windows.h>
#include <deque>
#include <string>

#include "db.h"
#include "md5.h"

using namespace std;


#define MAX_ARR_SIZE	100
#define ASIZE(arr) sizeof(arr)/sizeof(arr[0])

static MD5_CTX *m_md5;

struct FileInfo
{
	unsigned char *buf;
	size_t length;
};

struct Esctx
{
	char url[256];
	Ecall ecall;
	void *parm;

	bool scanning;
	deque<FileInfo> files;
	HANDLE scanthd;
};

//static set<string> m_cache;

static CRITICAL_SECTION m_lockarr;

static void GetMd5(unsigned char *buf, size_t len, char *mdstr)
{
	unsigned char md[16];
	MD5Update(m_md5, buf, len);
	MD5Final(m_md5, md);
	for (int i = 0; i < 16; i++)
		sprintf(mdstr + 2 * i, "%02x", md[i]);
	mdstr[32] = 0;
}
static void* GetFileContent(MY_CHAR *fname, size_t *fsize)
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
static void ScanFiles(void *es)
{
	Esctx *e = (Esctx *)es;
    while (e->scanning)
    {
		size_t len = 0;
		char mdstr[33];
		unsigned char *buf = (unsigned char *)GetFileContent(fname, &len);
		GetMd5(buf, len, mdstr);
		if (db_scan(mdstr) == 0)
		{
		}
    }
}

escan es_init(char *url, Ecall ecall, void *parm)
{
	Esctx *es = (Esctx *)calloc(1, sizeof(Esctx));
    strncpy(es->url, url, ASIZE(es->url)-1);
    es->ecall = ecall;
    es->parm = parm;
	m_md5 = (MD5_CTX *)malloc(sizeof(MD5_CTX));
	MD5Init(m_md5);
    _beginthread(ScanFiles, 0, (void *)es);
	
    return es;
}

static int UploadFile(Esctx *es, MY_CHAR *fname)
{
	return 0;
}

int es_send_md5(escan es, char *md5)
{
	return 0;
}

int es_scan_file(escan es, MY_CHAR *fname)
{
	Esctx *e = (Esctx *)es;
	EnterCriticalSection(&m_lockarr);
	FileInfo file;
	e->files.push_back(file);
	LeaveCriticalSection(&m_lockarr);
	return 0;
}
void es_free(escan es)
{

}
