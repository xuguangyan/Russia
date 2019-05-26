#if !defined(AFX_BRICK_H__A5511CEA_94DF_42CA_A3AB_6DE53FCE91D0__INCLUDED_)
#define AFX_BRICK_H__A5511CEA_94DF_42CA_A3AB_6DE53FCE91D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Brick.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBrick window

class CBrick : public CButton
{
// Construction
public:
	CBrick();

// Attributes
public:

// Operations
public:
	void SetBkColor(COLORREF color);//设置背景色
	void SetVisible(BOOL bVisible);//设置窗口隐显
	BOOL GetVisible();//获取窗口隐显信息
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//重载DrawItem函数
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBrick)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBrick();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBrick)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL m_Visible;//窗口是否可视
	COLORREF m_BackColor;//背景色
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRICK_H__A5511CEA_94DF_42CA_A3AB_6DE53FCE91D0__INCLUDED_)
