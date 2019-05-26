// RussiaDlg.h : header file
//

#if !defined(AFX_RUSSIADLG_H__2F9BD3D7_B651_4A69_9E94_042A3CAD6DAB__INCLUDED_)
#define AFX_RUSSIADLG_H__2F9BD3D7_B651_4A69_9E94_042A3CAD6DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "brick.h"
#include "ColorButton.h"
#include <mmsystem.h>
#pragma comment(lib,"WINMM.LIB")

/////////////////////////////////////////////////////////////////////////////
// CRussiaDlg dialog

class CRussiaDlg : public CDialog
{
// Construction
public:
	CRussiaDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRussiaDlg)
	enum { IDD = IDD_RUSSIA_DIALOG };
	CColorButton	m_btnGameSound;
	CSliderCtrl	m_sliderLevel;
	CStatic	m_staticLineBox;
	CStatic	m_staticScoreBox;
	CStatic	m_staticTimeBox;
	CColorButton	m_btnSetTop;
	CColorButton	m_btnGamePause;
	CColorButton	m_btnGameNet;
	CColorButton	m_btnGameStart;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRussiaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRussiaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGameStart();
	afx_msg void OnGameNet();
	afx_msg void OnGamePause();
	afx_msg void OnSettop();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawSliderLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnGameSound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

//Operations
private:
	bool PlaySound(int nID);
	void SetBricksColor();//���÷��������ɫ
	void GameStart();//��Ϸ��ʼ
	BOOL CheckOver();//�ж���Ϸ����
	void KillLine(int nLine);//����
	void CheckKill();//�ж�����
	CString GetTimeStr(DWORD dwTime);//ת��ʱ��
	void GameOver();//��Ϸ����
	void ShowNextBricks();//��ʾ��һ������
	void ShowBricks(int nHow=0);//��ʾ����
	void RegInit();//ע����ʼ��
	void RegRead();//ע����ȡ
	void RegWrite();//ע���д��

//Attributes
private:
	BOOL m_bGameSound;//��������
	int m_nKillLine;//������
	int m_nScore;//����
	int m_nLevel;//�ȼ�
	int m_nScores[4];//��ѡ����
	int m_nLevels[4];//��ѡ�ȼ�
	DWORD m_dwTime;//����ʱ��

	HBRUSH m_hBkBrush;//������ˢ
	HBRUSH m_hStaticBrush;//CStaticCtrl�ؼ���ˢ

	BOOL m_bGameStart;//�Ƿ���Ϸ��ʼ
	BOOL m_bGamePause;//�Ƿ���Ϸ��ͣ
	BOOL m_bSetTop;//�Ƿ񴰿��ö�
	BOOL m_bGameNet;//�Ƿ���ʾ����
	BOOL m_curBrickStop;//�Ƿ�ש�鵽��

	CString m_strTime;//����ʱ��
	COLORREF m_curBrickColor;//��ǰש����ɫ
	COLORREF m_nextBrickColor;//��һ��ש����ɫ
	COLORREF m_selBrickColor[4];//��ѡש����ɫ

	int m_curBrickPosy;//��ǰש��x����
	int m_curBrickPosx;//��ǰש��y����
	int m_curBrickType;//��ǰש������
	int m_nextBrickType;//��һ��ש������

	CBrick m_arrBricks[12][18];//����ש�����
	CBrick m_nextBricks[4][4];//������һ��ש��
};

static const int BRICKS_DATA[4*7][4][4]=
{
    /*������η���*/
    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,1,0,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    /*��һ�����η���*/
    1,1,1,1,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,

    1,1,1,1,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,1,0,0,

    /*��L���η���*/
    1,0,0,0,
    1,0,0,0,
    1,1,0,0,
    0,0,0,0,

    1,1,1,0,
    1,0,0,0,
    0,0,0,0,
    0,0,0,0,

    1,1,0,0,
    0,1,0,0,
    0,1,0,0,
    0,0,0,0,

    0,0,1,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0,

    /*����L���η���*/
    0,1,0,0,
    0,1,0,0,
    1,1,0,0,
    0,0,0,0,

    1,0,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0,

    1,1,0,0,
    1,0,0,0,
    1,0,0,0,
    0,0,0,0,

    1,1,1,0,
    0,0,1,0,
    0,0,0,0,
    0,0,0,0,

    /*��Z���η���*/
    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0,

    1,1,0,0,
    0,1,1,0,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0,

    /*����Z���η���*/
    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,

    0,1,1,0,
    1,1,0,0,
    0,0,0,0,
    0,0,0,0,

    1,0,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,

    /*��T���η���*/
    0,1,0,0,
    1,1,1,0,
    0,0,0,0,
    0,0,0,0,

    1,0,0,0,
    1,1,0,0,
    1,0,0,0,
    0,0,0,0,

    1,1,1,0,
    0,1,0,0,
    0,0,0,0,
    0,0,0,0,

    0,1,0,0,
    1,1,0,0,
    0,1,0,0,
    0,0,0,0,
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUSSIADLG_H__2F9BD3D7_B651_4A69_9E94_042A3CAD6DAB__INCLUDED_)
