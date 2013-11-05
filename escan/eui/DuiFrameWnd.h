// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Build:   Oct/21/2013
// Author:  Alberl Lee
// Email:   ItsBird@qq.com
// Website: http://www.cnblogs.com/Alberl/p/3381820.html
//
// 温馨提示：
// 此邮箱每天都收到很多垃圾邮件，邮件名请不要随意乱取，应尽量与垃圾邮件区分开来，幸好QQ的过滤功能还算强大~O(∩_∩)O~
// 此邮箱仅供【错误指正和技术交流】，若是技术问题请直接在文章评论区提问，否则恕不回复，这样做是为了让后面的小伙伴也能看到解决方案~O(∩_∩)O~
//
// 使用协议：WTFPL
// 鉴于在天朝神马协议都被无视，甚至很多大公司都不遵守，故索性采用了【DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE】协议~O(∩_∩)O~
//
// 代码安全性：
// 此项目为示例项目，为了方便大家编译，没用三方库，因此写了一些简单的函数，很多逻辑判断也只是保证正常操作，实际使用请自行保证代码安全~O(∩_∩)O~
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