// escan.cpp : 定义 DLL 应用程序的导出函数。
//

#include "escan.h"
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <windows.h>

#include "md5.h"

#define ASIZE(arr) sizeof(arr)/sizeof(arr[0])

static MD5_CTX *m_md5;

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
    while (true)
    {
        Sleep(3000);
    }
}

Escan* es_init(char *url, Ecall ecall, void *parm)
{
    Escan *es = (Escan *)calloc(1, sizeof(Escan));
    strncpy(es->url, url, ASIZE(es->url)-1);
    es->ecall = ecall;
    es->parm = parm;
	m_md5 = (MD5_CTX *)malloc(sizeof(MD5_CTX));
	MD5Init(m_md5);
    _beginthread(ScanFiles, 0, (void *)es);
	
    return es;
}

static int UploadFile(Escan *es, MY_CHAR *fname)
{
	return 0;
}

int es_send_md5(Escan *es, char *md5);
int es_scan_file(Escan *es, MY_CHAR *fname)
{
	size_t len = 0;
	unsigned char md[16];
	char mdstr[33];
	unsigned char *buf = (unsigned char *)GetFileContent(fname, &len);
	MD5Update(m_md5, buf, len);
	MD5Final(m_md5, md);

	for (int i = 0; i < 16; i++)
	{
		sprintf(mdstr+2*i, "%02x", md[i]);
	}
	mdstr[32] = 0;
	printf("%S: %s\n", fname, mdstr);
	return 0;
}
void es_free(Escan *escan);
