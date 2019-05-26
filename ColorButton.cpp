// ColorButton.cpp : implementation file
//

#include "stdafx.h"
#include "ColorButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorButton

CColorButton::CColorButton()
{
	m_bLBtnDown=FALSE;
	m_strText="";
}

CColorButton::~CColorButton()
{
}


BEGIN_MESSAGE_MAP(CColorButton, CButton)
	//{{AFX_MSG_MAP(CColorButton)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorButton message handlers
void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 获取一个CDC指针
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//定义按钮区域并初始化
	UINT state = lpDrawItemStruct->itemState;
	CRect rect(lpDrawItemStruct->rcItem);
	//设置背景模式
	int iObk = pDC->SetBkMode(TRANSPARENT);
	if (state & ODS_DISABLED)
	{
		//按钮置灰（DISABLED）
		CBrush brush;
		brush.CreateSolidBrush (GetSysColor(COLOR_3DFACE));
		pDC->FillRect(rect,&brush);
		pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));

		pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->DrawText(m_strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rect.top -= 2;
		rect.left -= 2;
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		pDC->DrawText(m_strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		return ;
	}

	//初始化按钮状态
	if (m_bLBtnDown)//按钮按下
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(204,204,204));
		pDC->FillRect(rect,&brush);
		pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
		rect.top += 2;
		rect.left += 2;
		pDC->SetTextColor(RGB(255,0,0));
		pDC->DrawText(m_strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else//按钮弹起
	{
		CBrush brush;
		brush.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
		pDC->FillRect(rect,&brush);	
		pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
		pDC->SetTextColor(RGB(0,0,255));
		pDC->DrawText(m_strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
}

//更新按钮显示样式
void CColorButton::UpdatButton(CString strText, BOOL bLButtonDown)
{
	
	m_strText=strText;
	m_bLBtnDown=bLButtonDown;
	Invalidate();
}

//设置光标
BOOL CColorButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	//SetClassLong(m_hWnd,GCL_HCURSOR,(long)LoadCursorFromFile("res/hand.cur"));
	::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
	return TRUE;
	//return CButton::OnSetCursor(pWnd, nHitTest, message);
}
