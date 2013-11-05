#ifndef VULNHUNT_ESCAN_H_
#define VULNHUNT_ESCAN_H_

#define MAX_FILE_SIZE 1024*1024*64

#ifdef _MSC_VER
#define MY_CHAR	wchar_t
#define DllExport   __declspec(dllexport) 
#else
#define MY_CHAR char
#define DllExport
#endif

typedef struct _sampleInfo
{
    MY_CHAR fname[260];
    char md5[33];
    char info[256];
    char url[256];

} SampleInfo;

typedef int(*Ecall)(void *parm, SampleInfo *info);

typedef void* escan;

#ifdef __cplusplus  
extern "C" {
#endif  

DllExport escan es_init(char *url, Ecall ecall, void *parm);
DllExport int es_scan_file(escan es, MY_CHAR *fname);
DllExport int es_scan_md5(escan es, char *md5);
DllExport int es_scan_buffer(escan es, unsigned char *buffer, size_t length);
DllExport void es_free(escan es);

#ifdef __cplusplus  
}
#endif



#endif