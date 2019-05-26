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
	void SetBricksColor();//设置方块沉淀颜色
	void GameStart();//游戏开始
	BOOL CheckOver();//判断游戏结束
	void KillLine(int nLine);//消行
	void CheckKill();//判断消行
	CString GetTimeStr(DWORD dwTime);//转换时间
	void GameOver();//游戏结束
	void ShowNextBricks();//显示下一个方块
	void ShowBricks(int nHow=0);//显示方块
	void RegInit();//注册表初始化
	void RegRead();//注册表读取
	void RegWrite();//注册表写入

//Attributes
private:
	BOOL m_bGameSound;//播放声音
	int m_nKillLine;//消行数
	int m_nScore;//积分
	int m_nLevel;//等级
	int m_nScores[4];//可选积分
	int m_nLevels[4];//可选等级
	DWORD m_dwTime;//所用时间

	HBRUSH m_hBkBrush;//背景画刷
	HBRUSH m_hStaticBrush;//CStaticCtrl控件画刷

	BOOL m_bGameStart;//是否游戏开始
	BOOL m_bGamePause;//是否游戏暂停
	BOOL m_bSetTop;//是否窗口置顶
	BOOL m_bGameNet;//是否显示网格
	BOOL m_curBrickStop;//是否砖块到底

	CString m_strTime;//所用时间
	COLORREF m_curBrickColor;//当前砖块颜色
	COLORREF m_nextBrickColor;//下一个砖块颜色
	COLORREF m_selBrickColor[4];//可选砖块颜色

	int m_curBrickPosy;//当前砖块x坐标
	int m_curBrickPosx;//当前砖块y坐标
	int m_curBrickType;//当前砖块类型
	int m_nextBrickType;//下一个砖块类型

	CBrick m_arrBricks[12][18];//定义砖块矩阵
	CBrick m_nextBricks[4][4];//定义下一个砖块
};

static const int BRICKS_DATA[4*7][4][4]=
{
    /*“田”字形方块*/
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

    /*“一”字形方块*/
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

    /*“L”形方块*/
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

    /*反“L”形方块*/
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

    /*“Z”形方块*/
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

    /*反“Z”形方块*/
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

    /*“T”形方块*/
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
