#pragma once

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <deque>
using namespace std;

enum SampleStatus
{
    kNotScan		= 0,    //表示未知状态，未扫描
    kNormal,		        //表示扫描后没有shellcode
    kShellcode,		        //表示有shellcode
    kWhite,			        //表示添加到白名单
    kDelete			        //表示已经删除
};

enum KernelAction
{
    kAllow = 0,
    kStop,
    kStopAndDeL,
    kDeL
};

struct XYConfig
{
    int port;
    char addr[16];
    bool isUpload;

    TCHAR *exts[50];
    bool isProtect;

    TCHAR curpath[MAX_PATH];
    TCHAR safePath[MAX_PATH];
    TCHAR extbuf[512];
    //vector<wstring> excludeDirs;
};


struct SampleInfo
{
    int result;  
    int uploaded;
    char md5[33];
    TCHAR filename[260]; // 检测文件名
    TCHAR info[260]; // 检测出有问题后的简要内容
};

struct MsgInfo
{
    int id;
    int result;
    int upload;
    TCHAR md5[33];
    TCHAR filename[260];
    TCHAR info[260];
};


class XYSrvc
{
public:
    XYSrvc(void);
    ~XYSrvc(void);

    int Init();
    int UploadFile(SampleInfo *sample);
    int WaitExit();
    int ExitSrvc();

    int WriteMsg(SampleInfo *sample, int msgid, MsgInfo *msg);
    int SendMsgToUi(MsgInfo *msg);
    int SendMsgToUi(SampleInfo *sample, int msgid);

    friend ULONG KernelCall(void *parm, PWCHAR fname, ULONG flen, ULONG ptype);
    friend DWORD WINAPI UploadFileThread(LPVOID parm);
    friend DWORD WINAPI ScanFileThread(LPVOID parm);
    friend int ProcessMsg(void *parm, void *msg);

private:
    void Free();

    int Init2();

    int InitKernel(TCHAR *exts[]);
    int LoadConfig(XYConfig *config);
    int InitCore();

    int AddSample(SampleInfo *sample);
    int ScanFile(SampleInfo *sample);
    int KernelScanFile(SampleInfo *sample);

    int IsExcludeDir(TCHAR *fname, int flen);

    int CopyToSafe(TCHAR *filename, char *md5);
    int SafeToBack(TCHAR *filename, char *md5);

    int SampleToBuf(SampleInfo *sample, void **sendbuf, int *buflen);

    int UpdateSample(SampleInfo *sample);
    int InitDb();
    void FreeDb();
    int DbScanSample(SampleInfo *sample);
    int DbInsertSample(SampleInfo *sample);
    int DbUpdateSample(SampleInfo *sample);
    int DbQueryNotUploadSample(SampleInfo *sample);

    sqlite3 *m_db;
    sqlite3_stmt *m_qurey;
    sqlite3_stmt *m_update;
    sqlite3_stmt *m_insert;
    sqlite3_stmt *m_upload;

    ShareMsg *m_sm;

    CRITICAL_SECTION m_lockdb, m_lockss, m_lockarr;
    XYConfig m_config;
    sample_req *m_req;

    bool m_isUilive;
    bool m_uploading;
    bool m_scaning;

    MsgInfo *m_uimsg;
    MsgInfo *m_coremsg;

    deque<SampleInfo*> m_samples;
    TCHAR m_curpath[MAX_PATH];
};



