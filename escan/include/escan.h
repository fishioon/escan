#ifndef VULNHUNT_ESCAN_H_
#define VULNHUNT_ESCAN_H_

#define MAX_FILE_SIZE 1024*1024*64

#ifdef _MSC_VER
#define DllExport   __declspec(dllexport) 
#else
#define DllExport
#endif

#include <tchar.h>

typedef enum _scanResult
{
    kUnknow = 0,
    kNormal,
    kRisk
} ScanResult;

typedef struct _sampleInfo
{
    int result;
    TCHAR fname[260];
    char md5[33];
    char info[256];

} SampleInfo;

typedef int(*Ecall)(void *parm, SampleInfo *info);

typedef struct _escan Escan;

#ifdef __cplusplus  
extern "C" {
#endif  

DllExport Escan* es_init(char *url, Ecall ecall, void *parm);
DllExport int es_scan_file(Escan *es, TCHAR *fname);
DllExport int es_scan_md5(Escan *es, char *md5);
DllExport int es_scan_buffer(Escan *es, unsigned char *buffer, size_t length);
DllExport void es_free(Escan *es);

#ifdef __cplusplus  
}
#endif



#endif