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
	void SetBkColor(COLORREF color);//���ñ���ɫ
	void SetVisible(BOOL bVisible);//���ô�������
	BOOL GetVisible();//��ȡ����������Ϣ
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);//����DrawItem����
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
	BOOL m_Visible;//�����Ƿ����
	COLORREF m_BackColor;//����ɫ
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRICK_H__A5511CEA_94DF_42CA_A3AB_6DE53FCE91D0__INCLUDED_)
