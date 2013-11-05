#include "DuiFrameWnd.h"

CDuiFrameWnd::CDuiFrameWnd( LPCTSTR pszXMLName )
    : CXMLWnd(pszXMLName)
{
}

CDuiFrameWnd::~CDuiFrameWnd()
{
}

DUI_BEGIN_MESSAGE_MAP(CDuiFrameWnd, CNotifyPump)
    DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
    DUI_END_MESSAGE_MAP()

    void CDuiFrameWnd::InitWindow()
{
    CControlUI *btn = m_PaintManager.FindControl(_T("dangerous_HorizontalLayoutUI9"));
    btn->SetVisible(false);
    btn = m_PaintManager.FindControl(_T("window_VerticalLayout"));
    btn->SetBkImage(_T("skin_1.png"));
//    CControlUI *btn = m_PaintManager.FindControl(_T("danerous2_HorizontalLayoutUI10"));

}

CControlUI* CDuiFrameWnd::CreateControl( LPCTSTR pstrClassName )
{
    return NULL;
}

void CDuiFrameWnd::OnClick(TNotifyUI& msg)
{
    __super::OnClick(msg);
}

void CDuiFrameWnd::Notify(TNotifyUI& msg)
{
    __super::Notify(msg);
}

LRESULT CDuiFrameWnd::OnNcHitTest( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
    return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
}
LRESULT CDuiFrameWnd::ResponseDefaultKeyEvent(WPARAM wParam)
{
    return __super::ResponseDefaultKeyEvent(wParam);
}
LRESULT CDuiFrameWnd::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
    return lRes;
}