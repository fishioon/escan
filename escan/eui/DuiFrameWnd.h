// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Build:   Oct/21/2013
// Author:  Alberl Lee
// Email:   ItsBird@qq.com
// Website: http://www.cnblogs.com/Alberl/p/3381820.html
//
// ��ܰ��ʾ��
// ������ÿ�춼�յ��ܶ������ʼ����ʼ����벻Ҫ������ȡ��Ӧ�����������ʼ����ֿ������Һ�QQ�Ĺ��˹��ܻ���ǿ��~O(��_��)O~
// ���������������ָ���ͼ��������������Ǽ���������ֱ�����������������ʣ�����ˡ���ظ�����������Ϊ���ú����С���Ҳ�ܿ����������~O(��_��)O~
//
// ʹ��Э�飺WTFPL
// �������쳯����Э�鶼�����ӣ������ܶ��˾�������أ������Բ����ˡ�DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE��Э��~O(��_��)O~
//
// ���밲ȫ�ԣ�
// ����ĿΪʾ����Ŀ��Ϊ�˷����ұ��룬û�������⣬���д��һЩ�򵥵ĺ������ܶ��߼��ж�Ҳֻ�Ǳ�֤����������ʵ��ʹ�������б�֤���밲ȫ~O(��_��)O~
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------


#pragma once
#include "duilib.h"

class CDuiFrameWnd: public CXMLWnd
{
public:
    explicit CDuiFrameWnd(LPCTSTR pszXMLName);
    ~CDuiFrameWnd();

    DUI_DECLARE_MESSAGE_MAP()
    virtual void InitWindow();
    virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
    virtual void Notify(TNotifyUI& msg);
    virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual void OnClick(TNotifyUI& msg);
    virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam); 

private:
};