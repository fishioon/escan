#include "Bssvc.h"

Bssvc::Bssvc(void)
{

}
Bssvc::~Bssvc(void)
{

}

int Bssvc::Init(Ecall ecall, void *parm)
{
	m_es = es_init("www.baidu.com", ecall, parm);
	return 0;
}

int Bssvc::ScanFile(wchar_t filename)
{
	return 0;
}

void Bssvc::Free()
{
	
}