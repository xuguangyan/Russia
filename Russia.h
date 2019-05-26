// Russia.h : main header file for the RUSSIA application
//

#if !defined(AFX_RUSSIA_H__8ADC9FDE_4701_4B0B_A6D0_3738D3092E90__INCLUDED_)
#define AFX_RUSSIA_H__8ADC9FDE_4701_4B0B_A6D0_3738D3092E90__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRussiaApp:
// See Russia.cpp for the implementation of this class
//

class CRussiaApp : public CWinApp
{
public:
	CRussiaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussiaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRussiaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIA_H__8ADC9FDE_4701_4B0B_A6D0_3738D3092E90__INCLUDED_)
