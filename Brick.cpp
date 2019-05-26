// Brick.cpp : implementation file
//

#include "stdafx.h"
#include "Russia.h"
#include "Brick.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrick

CBrick::CBrick()
{
	m_BackColor=RGB(0,0,255);//默认背景色
	m_Visible=TRUE;
}

CBrick::~CBrick()
{
}

BEGIN_MESSAGE_MAP(CBrick, CButton)
	//{{AFX_MSG_MAP(CBrick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrick message handlers

//设置背景色
void CBrick::SetBkColor(COLORREF color)
{
	m_BackColor=color;
	Invalidate();
}

//重载DrawItem函数
void CBrick::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// 获取一个CDC指针
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//定义按钮区域并初始化
	CRect rect(lpDrawItemStruct->rcItem);
	//设置按钮样式
	CBrush brush;
	brush.CreateSolidBrush(m_BackColor);
	pDC->FillRect(rect,&brush);
	pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
}

//设置窗口隐显
void CBrick::SetVisible(BOOL bVisible)
{
	if(bVisible)
	{
		ShowWindow(SW_SHOWNORMAL);
		m_Visible=TRUE;
	}
	else
	{
		ShowWindow(SW_HIDE);
		m_Visible=FALSE;
	}
}

//获取窗口隐显信息
BOOL CBrick::GetVisible()
{
	return m_Visible;
}
