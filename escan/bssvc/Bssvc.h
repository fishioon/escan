#pragma once

#include <Windows.h>
#include "escan.h"

using namespace std;

class Bssvc
{
public:
    Bssvc(void);
    ~Bssvc(void);

    int Init(Ecall ecall, void *parm);
	void Free();
	int ScanFile(wchar_t filename);

private:
	Ecall m_ecall;
	Escan *m_es;

};



