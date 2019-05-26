#if !defined(AFX_ColorButton_H__B2613FB6_3635_4428_AE89_803379687B91__INCLUDED_)
#define AFX_ColorButton_H__B2613FB6_3635_4428_AE89_803379687B91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorButton window

class CColorButton : public CButton
{
// Construction
public:
	CColorButton();

// Attributes
public:

// Operations
public:
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	void UpdatButton(CString strText,BOOL bLButtonDown);//更新按钮显示样式
	virtual ~CColorButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorButton)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CString m_strText;//标题文字
	BOOL m_bLBtnDown;//按钮是否按下
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ColorButton_H__B2613FB6_3635_4428_AE89_803379687B91__INCLUDED_)
