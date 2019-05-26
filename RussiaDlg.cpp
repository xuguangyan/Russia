// RussiaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Russia.h"
#include "RussiaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussiaDlg dialog

CRussiaDlg::CRussiaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRussiaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRussiaDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//可选砖块颜色
	m_selBrickColor[0]=RGB(239,118,106);//淡红
	m_selBrickColor[1]=RGB(209,131,222);//粉红
	m_selBrickColor[2]=RGB(132,221,127);//淡绿
	m_selBrickColor[3]=RGB(199,206,119);//淡黄
	//等级制度(用毫秒数表示砖块下落速度,速度越快,等级越高)
	m_nLevels[0]=1000;
	m_nLevels[1]=800;
	m_nLevels[2]=500;
	m_nLevels[3]=100;
	//积分制度(一次消行越多,积分越高)
	m_nScores[0]=10;
	m_nScores[1]=20;
	m_nScores[2]=40;
	m_nScores[3]=60;

	m_curBrickStop=TRUE;//砖块到底
	m_nLevel=1;//默认等级
	m_strTime="00:00";//默认时间(CString型)
	m_dwTime=0;//默认时间(int型)
	m_nScore=0;//默认积分为0
	m_nKillLine=0;//默认消行数为0

	m_bGameNet=FALSE;//默认不显示网格
	m_bSetTop=FALSE;//默认窗口不置顶
	m_bGamePause=FALSE;//默认不暂停
	m_bGameStart=FALSE;//默认游戏未开始
	m_bGameSound=FALSE;//默认不播放声音

	m_hStaticBrush=CreateSolidBrush(RGB(132,221,127)); 
	m_hBkBrush=CreateSolidBrush(RGB(143,171,190)); 
}

void CRussiaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRussiaDlg)
	DDX_Control(pDX, IDC_GAME_SOUND, m_btnGameSound);
	DDX_Control(pDX, IDC_SLIDER_LEVEL, m_sliderLevel);
	DDX_Control(pDX, IDC_STATIC_LINEBOX, m_staticLineBox);
	DDX_Control(pDX, IDC_STATIC_SCOREBOX, m_staticScoreBox);
	DDX_Control(pDX, IDC_STATIC_TIMEBOX, m_staticTimeBox);
	DDX_Control(pDX, IDC_SETTOP, m_btnSetTop);
	DDX_Control(pDX, IDC_GAME_PAUSE, m_btnGamePause);
	DDX_Control(pDX, IDC_GAME_NET, m_btnGameNet);
	DDX_Control(pDX, IDC_GAME_START, m_btnGameStart);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRussiaDlg, CDialog)
	//{{AFX_MSG_MAP(CRussiaDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_GAME_START, OnGameStart)
	ON_BN_CLICKED(IDC_GAME_NET, OnGameNet)
	ON_BN_CLICKED(IDC_GAME_PAUSE, OnGamePause)
	ON_BN_CLICKED(IDC_SETTOP, OnSettop)
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_LEVEL, OnCustomdrawSliderLevel)
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_GAME_SOUND, OnGameSound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRussiaDlg message handlers

//初始化
BOOL CRussiaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	//注册表初始化
	RegInit();

	//初始化控件位置
	CStatic *pStatic1=(CStatic *)GetDlgItem(IDC_STATIC_CONTAIN);
	pStatic1->SetWindowPos(NULL,17,11,318,480,SWP_NOZORDER);

	CStatic *pStatic2=(CStatic *)GetDlgItem(IDC_STATIC_VIEW);
	pStatic2->SetWindowPos(NULL,333,11,90,480,SWP_NOZORDER);

	CStatic *pStatic3=(CStatic *)GetDlgItem(IDC_STATIC_NEXT);
	pStatic3->SetWindowPos(NULL,336,21,84,20,SWP_NOZORDER);

	CStatic *pStatic4=(CStatic *)GetDlgItem(IDC_STATIC_LEVEL);
	pStatic4->SetWindowPos(NULL,336,130,84,20,SWP_NOZORDER);
	m_sliderLevel.SetWindowPos(NULL,336,160,84,20,SWP_NOZORDER);

	CStatic *pStatic5=(CStatic *)GetDlgItem(IDC_STATIC_TIME);
	pStatic5->SetWindowPos(NULL,336,190,84,20,SWP_NOZORDER);
	m_staticTimeBox.SetWindowPos(NULL,336,215,84,20,SWP_NOZORDER);

	CStatic *pStatic6=(CStatic *)GetDlgItem(IDC_STATIC_SCORE);
	pStatic6->SetWindowPos(NULL,336,240,84,20,SWP_NOZORDER);
	m_staticScoreBox.SetWindowPos(NULL,336,265,84,20,SWP_NOZORDER);

	CStatic *pStatic7=(CStatic *)GetDlgItem(IDC_STATIC_LINE);
	pStatic7->SetWindowPos(NULL,336,290,84,20,SWP_NOZORDER);
	m_staticLineBox.SetWindowPos(NULL,336,315,84,20,SWP_NOZORDER);

	m_btnGameSound.SetWindowPos(NULL,336,340,84,20,SWP_NOZORDER);
	m_btnGameNet.SetWindowPos(NULL,336,370,84,20,SWP_NOZORDER);
	m_btnSetTop.SetWindowPos(NULL,336,400,84,20,SWP_NOZORDER);
	m_btnGamePause.SetWindowPos(NULL,336,430,84,20,SWP_NOZORDER);
	m_btnGameStart.SetWindowPos(NULL,336,460,84,20,SWP_NOZORDER);

	//初始控件状态
	m_btnGameSound.UpdatButton("声音",FALSE);//弹起
	m_btnGameNet.UpdatButton("网格",FALSE);//弹起
	m_btnSetTop.UpdatButton("置顶",FALSE);//弹起
	m_btnGamePause.UpdatButton("暂停",FALSE);//弹起
	m_btnGameStart.UpdatButton("开始",FALSE);//弹起
	m_btnGamePause.EnableWindow(FALSE);//不可用

	//随机生成方块类型和颜色
	srand((unsigned)time(NULL));
	int r=(int)rand();
	m_nextBrickType=r%28;
	m_nextBrickColor=m_selBrickColor[r%4];
	//设置滑动条(等级)范围
	m_sliderLevel.SetRange(1,4);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CRussiaDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

//重绘
void CRussiaDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//设置背景
		CPaintDC dc(this);
		dc.SelectObject(CBrush::FromHandle(m_hBkBrush));
		CRect rect;
		GetWindowRect(&rect);
		dc.Rectangle(0,0,rect.Width(),rect.Height());
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(243,212,212));
		dc.SelectObject(&pen);
		//画网格
		int i,j;
		if(m_bGameNet)
		{
			for(j=1;j<18;j++)
			{
				dc.MoveTo(20,20+j*25+j);
				dc.LineTo(332,20+j*25+j);
			}
			for(i=1;i<12;i++)
			{
				dc.MoveTo(20+i*25+i,20);
				dc.LineTo(20+i*25+i,490);
			}
		}

		//画next的网格
		for(j=0;j<=4;j++)
		{
			dc.MoveTo(338,45+j*20);
			dc.LineTo(418,45+j*20);
		}
		for(i=0;i<=4;i++)
		{
			dc.MoveTo(338+i*20,45);
			dc.LineTo(338+i*20,125);
		}

		//底部信息
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOut(315,502,"2008.10.16 大圣");

		LOGFONT logfont;
		memset(&logfont,0,sizeof(LOGFONT));
		lstrcpy(logfont.lfFaceName,_T("楷体_GB2312"));
		logfont.lfHeight=30;
		logfont.lfWeight=600;

		CFont font;
		font.CreateFontIndirect(&logfont);
		dc.SelectObject(&font);
		//dc.SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOut(5,495,"［俄罗斯方块 v0.1版］");
		//dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		dc.SetTextColor(RGB(51,51,51));
		dc.TextOut(4,494,"［俄罗斯方块 v0.1版］");

		//CDialog::OnPaint();
	}
}

//创建
int CRussiaDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	//设置窗口标题
	SetWindowText("俄罗斯方块");
	// TODO: Add your specialized creation code here
	//创建矩阵方块
	int xOffset=20;//容器左上角x偏移
	int yOffset=20;//容器左上角x偏移
	int brickSize=25;//砖块大小(长宽均为25)
	CRect rect;
	int nID,i,j;
	for(j=0;j<18;j++)
	{
		for(i=0;i<12;i++)
		{
			rect.left=xOffset+i*brickSize+i;
			rect.top=yOffset+j*brickSize+j;
			rect.right=xOffset+(i+1)*brickSize+i;
			rect.bottom=yOffset+(j+1)*brickSize+j;
			nID=2000+j*12+i;
			m_arrBricks[i][j].Create("",WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				rect,this,nID);
			m_arrBricks[i][j].SetVisible(FALSE);
		}
	}
	//创建下一个方块
	xOffset=338;
	yOffset=45;
	brickSize=20;
	for(j=0;j<4;j++)
	{
		for(i=0;i<4;i++)
		{
			rect.left=xOffset+i*brickSize;
			rect.top=yOffset+j*brickSize;
			rect.right=xOffset+(i+1)*brickSize;
			rect.bottom=yOffset+(j+1)*brickSize;
			nID=2216+j*4+i;
			m_nextBricks[i][j].Create("",WS_CHILD | WS_VISIBLE | BS_OWNERDRAW,
				rect,this,nID);
			m_nextBricks[i][j].SetVisible(FALSE);
		}
	}
	return 0;
}

//显示方块
void CRussiaDlg::ShowBricks(int nHow)
{
/*显示方式:	
	正常:nHow=0
	变换:nHow=1
	左移:nHow=2
	右移:nHow=3
	下移:nHow=4
*/
	int x,y,i,j,tmpx,tmpy,tmpt,cx=0,cy=0;
	
	//判断如何显示
	switch(nHow)
	{
	case 0:
		tmpx=m_curBrickPosx;
		tmpy=m_curBrickPosy;
		tmpt=m_curBrickType;
		break;
	case 1:
		tmpx=m_curBrickPosx;
		tmpy=m_curBrickPosy;
		tmpt=(m_curBrickType/4)*4+(m_curBrickType+1)%4;
		break;
	case 2:
		tmpx=m_curBrickPosx-1;
		tmpy=m_curBrickPosy;
		tmpt=m_curBrickType;
		cx=-1;
		break;
	case 3:
		tmpx=m_curBrickPosx+1;
		tmpy=m_curBrickPosy;
		tmpt=m_curBrickType;
		cx=1;
		break;
	case 4:
		tmpx=m_curBrickPosx;
		tmpy=m_curBrickPosy+1;
		tmpt=m_curBrickType;
		cy=1;
		break;
	}
	//判断砖块是否可移
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			x=j+tmpx;
			y=i+tmpy-3;
			if(x>=0 && x<12 && y>=0 && y<18)//边界内
			{	
				if(m_arrBricks[x][y].GetVisible()&&BRICKS_DATA[tmpt][i][j])//抽出将要显示并且已经显示的砖块进行判断
					if(i+cy>=0&&i+cy<4&&j+cx>=0&&j+cx<4)
					{
						if(!BRICKS_DATA[m_curBrickType][i+cy][j+cx])//在原可视砖块内出现可视砖块属合法(否则不合法)
						{
							if(nHow==4)//若是下移
								m_curBrickStop=TRUE;
							return ;
						}
					}
					else//在原可视砖块外出现可视砖块属不合法
					{
						if(nHow==4)//若是下移
							m_curBrickStop=TRUE;
						return ;
					}
			}
			else if(BRICKS_DATA[tmpt][i][j])//边界外
			{
				if(x<0 || x>=12 || y>=18)//左、右、下边
				{
					if(y>=18)//若是下边越界
						m_curBrickStop=TRUE;
					return ;
				}
			}
		}
	//擦除旧砖块
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			x=j+m_curBrickPosx;
			y=i+m_curBrickPosy-3;
			if(x>=0 && x<12 && y>=0 && y<18)
			{
				if(BRICKS_DATA[m_curBrickType][i][j])
					m_arrBricks[x][y].SetVisible(FALSE);
			}
		}
	//显示新砖块
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			x=j+tmpx;
			y=i+tmpy-3;
			if(x>=0 && x<12 && y>=0 && y<18)
			{
				if(BRICKS_DATA[tmpt][i][j])
				{
					m_arrBricks[x][y].SetBkColor(m_curBrickColor);
					m_arrBricks[x][y].SetVisible(BRICKS_DATA[tmpt][i][j]);
				}
			}
		}
	//保存新位置及新类型
	m_curBrickPosx=tmpx;
	m_curBrickPosy=tmpy;
	m_curBrickType=tmpt;
}

//捕获按键消息
BOOL CRussiaDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
/*  
扫描码表:
	VK_BACK      08 BACKSPACE 键(退格)
　　VK_TAB       09 TAB 键(切换)
　　VK_RETURN    0D ENTER 键(回车)
　　VK_SHIFT     10 SHIFT 键(上档)
　　VK_CONTROL   11 CTRL 键(控制)
　　VK_MENU      12 ALT 键(组合)
　　VK_PAUSE     13 PAUSE 键(暂停)
　　VK_CAPITAL   14 CAPS LOCK 键(大小写锁)
	VK_ESCAPE    1B ESC 键(退出)
　　VK_SPACE     20 SPACEBAR键(空格)
　　VK_PRIOR     21 PAGE UP 键(上翻页)
　　VK_NEXT      22 PAGE DOWN 键(下翻页)
　　VK_END       23 END 键(结束)
　　VK_HOME      24 HOME 键(主层)
	VK_LEFT      25 方向键盘上的 ← 键
　　VK_UP        26 方向键盘上的 ↑ 键
　　VK_RIGHT     27 方向键盘上的 → 键
　　VK_DOWN      28 方向键盘上的 ↓ 键
　　VK_SNAPSHOT  2C PRINT SCREEN键(打印屏幕)
　　VK_INSERT    2D INS 键(插入)
　　VK_DELETE    2E DEL 键(删除)
　　VK_NUMPAD0   60 数字小键盘上的 0 键
　　VK_NUMPAD1   61 数字小键盘上的 1 键
　　VK_NUMPAD2   62 数字小键盘上的 2 键
　　VK_NUMPAD3   63 数字小键盘上的 3 键
　　VK_NUMPAD4   64 数字小键盘上的 4 键
　　VK_NUMPAD5   65 数字小键盘上的 5 键
　　VK_NUMPAD6   66 数字小键盘上的 6 键
　　VK_NUMPAD7   67 数字小键盘上的 7 键
　　VK_NUMPAD8   68 数字小键盘上的 8 键
　　VK_NUMPAD9   69 数字小键盘上的 9 键
	VK_MULTIPLY  6A 数字小键盘上的 * 键
　　VK_ADD       6B 数字小键盘上的 + 键
　　VK_SEPARATOR 6C 数字小键盘上的 Separator 键
　　VK_SUBTRACT  6D 数字小键盘上的 - 键
　　VK_DECIMAL   6E 数字小键盘上的 . 键
　　VK_DIVIDE    6F 数字小键盘上的 / 键
　　VK_F1        70 F1 键
　　VK_F2        71 F2 键
　　VK_F3        72 F3 键
　　VK_F4        73 F4 键
　　VK_F5        74 F5 键
　　VK_F6        75 F6 键
　　VK_F7        76 F7 键
　　VK_F8        77 F8 键
　　VK_F9        78 F9 键
　　VK_F10       79 F10 键
　　VK_F11       7A F11 键
　　VK_F12       7B F12 键
　　VK_NUMLOCK   90 NUM LOCK 键(数字锁)
　　VK_SCROLL    91 SCROLL LOCK 键(滚动锁)*/
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_UP:
			if(!m_bGamePause)
			{
				ShowBricks(1);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_TYPE);//播放声音
			}
			break;
		case VK_LEFT:
			if(!m_bGamePause)
			{
				ShowBricks(2);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//播放声音
				}
			break;
		case VK_RIGHT:
			if(!m_bGamePause)
			{
				ShowBricks(3);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//播放声音
				}
			break;
		case VK_DOWN:
			if(!m_bGamePause)
			{
				ShowBricks(4);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//播放声音
			}
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
/*		case 'X': //示例
			if(::GetKeyState(VK_CONTROL)<0)
				MessageBox("组合键CTRL+X");
			else
				MessageBox("字母键X");
			break;*/
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

//定时器
void CRussiaDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent==1)//方块下落
	{
		if(!m_bGamePause)//不暂停
		{
			if(m_curBrickStop)//方块到底
			{
				//CString str;
				//str.Format("%d,%d",m_curBrickPosx,m_curBrickPosy);
				//m_staticScoreBox.SetWindowText(str);
				//设置砖块沉淀颜色
				static bool bSet=false;
				if(bSet) SetBricksColor();
				if(!bSet) bSet=true;

				//结束
				if(CheckOver())
				{
					OnGameStart();
					return ;
				}
				//消行
				CheckKill();
				//准备下一个
				m_curBrickType=m_nextBrickType;
				m_curBrickColor=m_nextBrickColor;
				m_curBrickPosx=6;
				m_curBrickPosy=0;
				m_curBrickStop=FALSE;

				srand((unsigned)time(NULL));
				int r=(int)rand();
				m_nextBrickType=r%28;
				m_nextBrickColor=m_selBrickColor[r%4];
				ShowNextBricks();
			}
			ShowBricks(4);
			
		}
	}
	else if(nIDEvent==2)//时间累加
	{
		if(!m_bGamePause)
		{
			m_dwTime++;
			m_strTime=GetTimeStr(m_dwTime);
			m_staticTimeBox.SetWindowText(m_strTime);
		}
	}
	else if(nIDEvent==3)//铺满砖块
	{
		static int j=18;
		j--;
		if(j<0)
		{
			KillTimer(3);
			j=18;
			return ;
		}
		for(int i=0;i<12;i++)
		if(!m_arrBricks[i][j].GetVisible())
		{
				m_arrBricks[i][j].SetBkColor(RGB(135,142,208));
				m_arrBricks[i][j].SetVisible(TRUE);
		}
	}
	else if(nIDEvent==4)//擦除砖块
	{
		static int n=-1;
		n++;
		if(n>17)
		{
			KillTimer(4);
			n=-1;
			SetTimer(1,m_nLevels[m_nLevel-1],NULL);
			SetTimer(2,1000,NULL);
			return ;
		}
		for(int m=0;m<12;m++)
			m_arrBricks[m][n].SetVisible(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

//显示下一个方块
void CRussiaDlg::ShowNextBricks()
{
	int i,j;
	//擦除旧砖块
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			m_nextBricks[j][i].SetVisible(FALSE);
	//显示新砖块
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(BRICKS_DATA[m_nextBrickType][i][j])
			{
				m_nextBricks[j][i].SetBkColor(m_nextBrickColor);
				m_nextBricks[j][i].SetVisible(TRUE);
			}
		}
}

//声音
void CRussiaDlg::OnGameSound() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameSound)
	{
		m_btnGameSound.UpdatButton("声音",0);
		m_bGameSound=0;
	}
	else
	{
		m_btnGameSound.UpdatButton("声音",1);
		m_bGameSound=1;
	}
}

//网格
void CRussiaDlg::OnGameNet() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameNet)
	{
		m_btnGameNet.UpdatButton("网格",0);
		m_bGameNet=0;
		Invalidate();
	}
	else
	{
		m_btnGameNet.UpdatButton("网格",1);
		m_bGameNet=1;
		Invalidate();
	}
}

//置顶
void CRussiaDlg::OnSettop() 
{
	// TODO: Add your control notification handler code here
	if(m_bSetTop)
	{
		m_btnSetTop.UpdatButton("置顶",0);
		m_bSetTop=0;
		SetWindowPos(&this->wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE |SWP_NOSIZE);
	}
	else
	{
		m_btnSetTop.UpdatButton("置顶",1);
		m_bSetTop=1;
		SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE |SWP_NOSIZE);

	}
}

//暂停
void CRussiaDlg::OnGamePause() 
{
	// TODO: Add your control notification handler code here
	if(m_bGamePause)
	{
		m_btnGamePause.UpdatButton("暂停",0);
		m_bGamePause=0;
	}
	else
	{
		m_btnGamePause.UpdatButton("继续",1);
		m_bGamePause=1;
	}
}

//游戏开始
void CRussiaDlg::OnGameStart() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameStart)
	{
		m_btnGameStart.UpdatButton("开始",0);
		m_bGameStart=0;
		KillTimer(1);
		KillTimer(2);
		m_sliderLevel.EnableWindow(TRUE);
		m_btnGamePause.EnableWindow(FALSE);
		m_btnGamePause.UpdatButton("暂停",0);
		m_bGamePause=0;
		GameOver();
	}
	else
	{
		m_btnGameStart.UpdatButton("结束",1);
		m_bGameStart=1;
		GameStart();
		m_sliderLevel.EnableWindow(FALSE);
		m_btnGamePause.EnableWindow(TRUE);
		m_btnGamePause.SetFocus();//主要为了能接收空格键以实现暂停
	}
}

//游戏结束
void CRussiaDlg::GameOver()
{
	SetTimer(3,30,NULL);
}

//控件更新
HBRUSH CRussiaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	int nID=pWnd->GetDlgCtrlID();
	switch(nID)
	{
	case IDC_STATIC_NEXT:
	case IDC_STATIC_LEVEL:
	case IDC_STATIC_TIME:
	case IDC_STATIC_SCORE:
	case IDC_STATIC_LINE:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,255));
		return m_hStaticBrush;
		break;
	case IDC_SLIDER_LEVEL:
	case IDC_STATIC_TIMEBOX:
	case IDC_STATIC_SCOREBOX:
	case IDC_STATIC_LINEBOX:
		CFont font;
		font.CreatePointFont(150,"宋体",NULL);
		pDC->SelectObject(&font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(205,12,67));
		return m_hBkBrush;
		break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

//转换时间
CString CRussiaDlg::GetTimeStr(DWORD dwTime)
{

	DWORD nHour,nSecond;
	nHour=dwTime/60;
	nSecond=dwTime%60;
	CString str;
	if(nHour<10&&nSecond>9)
		str.Format("0%d:%d",nHour,nSecond);
	else if(nHour>9&&nSecond<10)
		str.Format("%d:0%d",nHour,nSecond);
	else if(nHour<10&&nSecond<10)
		str.Format("0%d:0%d",nHour,nSecond);
	else
		str.Format("%d:%d",nHour,nSecond);
	return str;
}

//滑动条滑动
void CRussiaDlg::OnCustomdrawSliderLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_nLevel=m_sliderLevel.GetPos();
	*pResult = 0;
}

//判断游戏结束
BOOL CRussiaDlg::CheckOver()
{
	for(int i=0;i<12;i++)
		if(m_arrBricks[i][0].GetVisible())
			return TRUE;
	return FALSE;
}

//判断消行
void CRussiaDlg::CheckKill()
{
	int nLine=0;
	for(int i=0;i<18;i++)
	{
		BOOL bKill=TRUE;
		for(int j=0;j<12;j++)
		{
			if(!m_arrBricks[j][i].GetVisible())
			{
				bKill=FALSE;
				break;
			}
		}
		if(bKill)
		{
			KillLine(i);
			if(m_bGameSound)
				PlaySound(IDR_WAVE_KILL);//播放声音
			nLine++;
		}
	}
	if(nLine>0)
	{
		m_nScore+=m_nScores[nLine-1];
		m_nKillLine+=nLine;
		//显示新成绩
		CString str;
		str.Format("%d",m_nScore);
		m_staticScoreBox.SetWindowText(str);
		str.Format("%d",m_nKillLine);
		m_staticLineBox.SetWindowText(str);
	}
}

//消行
void CRussiaDlg::KillLine(int nLine)
{
	for(int i=nLine;i>0;i--)
		for(int j=0;j<12;j++)
			m_arrBricks[j][i].SetVisible(m_arrBricks[j][i-1].GetVisible());
}

//设置砖块沉淀颜色
void CRussiaDlg::SetBricksColor()
{
	for(int j=0;j<18;j++)
	{
		for(int i=0;i<12;i++)
			if(m_arrBricks[i][j].GetVisible())
			{
				m_arrBricks[i][j].SetBkColor(RGB(89,104,244));
			}
	}
}
//游戏结束
void CRussiaDlg::GameStart()
{

	m_curBrickStop=TRUE;
	m_strTime="00:00";
	m_dwTime=0;
	m_nScore=0;
	m_nKillLine=0;

	SetTimer(4,30,NULL);
}

//设置光标
BOOL CRussiaDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	int nID=pWnd->GetDlgCtrlID();
	if(nID==IDC_SLIDER_LEVEL)
	{
		::SetCursor(AfxGetApp()->LoadStandardCursor(MAKEINTRESOURCE(32649)));
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

bool CRussiaDlg::PlaySound(int nID)
{
	//1．获得包含资源的模块句柄：
	HMODULE hmod=AfxGetResourceHandle(); 
	//2．检索资源块信息：
	HRSRC hSndResource=FindResource(hmod,MAKEINTRESOURCE(nID),_T("WAVE"));
	//3. 装载资源数据并加锁：
	HGLOBAL hGlobalMem=LoadResource(hmod,hSndResource);
	LPCTSTR lpMemSound=(LPCSTR)LockResource(hGlobalMem);
	//4．播放声音文件：
	sndPlaySound(lpMemSound,SND_MEMORY);
	//5．释放资源句柄：
	FreeResource(hGlobalMem);
	return true;
}

//注册表初始化
void CRussiaDlg::RegInit()
{
	HKEY hKey;
	LONG result=RegOpenKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia",&hKey);
	if(result==ERROR_SUCCESS)
		RegRead();
	else
		RegWrite();
}

//注册表读取
void CRussiaDlg::RegRead()
{
	//HKEY hKey;
	//DWORD len,type;

	//RegOpenKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppParam",&hKey);

	//read something...

	//RegCloseKey(hKey);
}
//注册表写入
void CRussiaDlg::RegWrite()
{
	HKEY hKey;
	//DWORD len;

	RegCreateKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppInfo",&hKey);
	RegSetValueEx(hKey,"AppName",0,REG_SZ,(CONST BYTE*)"俄罗斯方块游戏",strlen("俄罗斯方块游戏"));
	RegSetValueEx(hKey,"Author",0,REG_SZ,(CONST BYTE*)"大圣",strlen("大圣"));
	RegSetValueEx(hKey,"Version",0,REG_SZ,(CONST BYTE*)"v0.1版",strlen("v0.1版"));
	RegSetValueEx(hKey,"Date",0,REG_SZ,(CONST BYTE*)"2008.10.16",strlen("2008.10.16"));

	RegCreateKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppParam",&hKey);
	
	RegCloseKey(hKey);
}
