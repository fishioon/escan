// escan.cpp : 定义 DLL 应用程序的导出函数。
//

#include "escan.h"
#include <string.h>
#include <stdlib.h>
#include <process.h>

#include <windows.h>

#define ASIZE(arr) sizeof(arr)/sizeof(arr[0])

static void RecvMsg(void *es)
{
    while (true)
    {
        Sleep(3000);
    }
}

Escan* es_init(char *url, Ecall ecall, void *parm)
{
    Escan *es = (Escan *)malloc(sizeof(Escan));
    strncpy(es->url, url, ASIZE(es->url)-1);
    //escan->timeout = timeout;
    es->ecall = ecall;
    es->parm = parm;
    _beginthread(RecvMsg, 0, (void *)es);
    return es;
}

static int SendFile(Escan *es, MY_CHAR *fname)
{
    
}

//static int HttpHeadPack(Escan *es, )

//static int HttpPost(MY_CHAR *fname, char *md5)
//{

//}
//static int HttpPost(MY_CHAR *fname, char *md5, unsigned char *buf, size_t len)
//{
//    return 0;
//}

int es_send_md5(Escan *es, char *md5);
int es_send_file(Escan *es, MY_CHAR *fname);
//int es_update_md5s(char *md5s[], size_t size);
//int es_update_md5(char *md5);

void es_free(Escan *escan);
