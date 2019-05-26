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
	m_BackColor=RGB(0,0,255);//Ĭ�ϱ���ɫ
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

//���ñ���ɫ
void CBrick::SetBkColor(COLORREF color)
{
	m_BackColor=color;
	Invalidate();
}

//����DrawItem����
void CBrick::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// ��ȡһ��CDCָ��
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//���尴ť���򲢳�ʼ��
	CRect rect(lpDrawItemStruct->rcItem);
	//���ð�ť��ʽ
	CBrush brush;
	brush.CreateSolidBrush(m_BackColor);
	pDC->FillRect(rect,&brush);
	pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
}

//���ô�������
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

//��ȡ����������Ϣ
BOOL CBrick::GetVisible()
{
	return m_Visible;
}
