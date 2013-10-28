#ifndef VULNHUNT_ESCAN_H_
#define VULNHUNT_ESCAN_H_

#define MAX_FILE_SIZE 1024*1024*64

#define MY_CHAR wchar_t

typedef struct _fileinfo
{
    MY_CHAR fname[260];
    char md5[33];
    char info[256];
    char url[256];

} FileInfo;

typedef int(*Ecall)(void *parm, FileInfo *info);

typedef struct _escan
{
    char url[256];
    //int timeout;
    Ecall ecall;
    void *parm;

} Escan;

Escan* es_init(char *url, Ecall ecall, void *parm);

int es_send_md5(Escan *es, char *md5);
int es_send_file(Escan *es, MY_CHAR *fname);
//int es_update_db(char *md5s[], size_t size);

void es_free(Escan *es);

#endif