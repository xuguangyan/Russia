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
	//��ѡש����ɫ
	m_selBrickColor[0]=RGB(239,118,106);//����
	m_selBrickColor[1]=RGB(209,131,222);//�ۺ�
	m_selBrickColor[2]=RGB(132,221,127);//����
	m_selBrickColor[3]=RGB(199,206,119);//����
	//�ȼ��ƶ�(�ú�������ʾש�������ٶ�,�ٶ�Խ��,�ȼ�Խ��)
	m_nLevels[0]=1000;
	m_nLevels[1]=800;
	m_nLevels[2]=500;
	m_nLevels[3]=100;
	//�����ƶ�(һ������Խ��,����Խ��)
	m_nScores[0]=10;
	m_nScores[1]=20;
	m_nScores[2]=40;
	m_nScores[3]=60;

	m_curBrickStop=TRUE;//ש�鵽��
	m_nLevel=1;//Ĭ�ϵȼ�
	m_strTime="00:00";//Ĭ��ʱ��(CString��)
	m_dwTime=0;//Ĭ��ʱ��(int��)
	m_nScore=0;//Ĭ�ϻ���Ϊ0
	m_nKillLine=0;//Ĭ��������Ϊ0

	m_bGameNet=FALSE;//Ĭ�ϲ���ʾ����
	m_bSetTop=FALSE;//Ĭ�ϴ��ڲ��ö�
	m_bGamePause=FALSE;//Ĭ�ϲ���ͣ
	m_bGameStart=FALSE;//Ĭ����Ϸδ��ʼ
	m_bGameSound=FALSE;//Ĭ�ϲ���������

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

//��ʼ��
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

	//ע����ʼ��
	RegInit();

	//��ʼ���ؼ�λ��
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

	//��ʼ�ؼ�״̬
	m_btnGameSound.UpdatButton("����",FALSE);//����
	m_btnGameNet.UpdatButton("����",FALSE);//����
	m_btnSetTop.UpdatButton("�ö�",FALSE);//����
	m_btnGamePause.UpdatButton("��ͣ",FALSE);//����
	m_btnGameStart.UpdatButton("��ʼ",FALSE);//����
	m_btnGamePause.EnableWindow(FALSE);//������

	//������ɷ������ͺ���ɫ
	srand((unsigned)time(NULL));
	int r=(int)rand();
	m_nextBrickType=r%28;
	m_nextBrickColor=m_selBrickColor[r%4];
	//���û�����(�ȼ�)��Χ
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

//�ػ�
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
		//���ñ���
		CPaintDC dc(this);
		dc.SelectObject(CBrush::FromHandle(m_hBkBrush));
		CRect rect;
		GetWindowRect(&rect);
		dc.Rectangle(0,0,rect.Width(),rect.Height());
		CPen pen;
		pen.CreatePen(PS_SOLID,1,RGB(243,212,212));
		dc.SelectObject(&pen);
		//������
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

		//��next������
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

		//�ײ���Ϣ
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOut(315,502,"2008.10.16 ��ʥ");

		LOGFONT logfont;
		memset(&logfont,0,sizeof(LOGFONT));
		lstrcpy(logfont.lfFaceName,_T("����_GB2312"));
		logfont.lfHeight=30;
		logfont.lfWeight=600;

		CFont font;
		font.CreateFontIndirect(&logfont);
		dc.SelectObject(&font);
		//dc.SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		dc.SetTextColor(RGB(255,255,255));
		dc.TextOut(5,495,"�۶���˹���� v0.1���");
		//dc.SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		dc.SetTextColor(RGB(51,51,51));
		dc.TextOut(4,494,"�۶���˹���� v0.1���");

		//CDialog::OnPaint();
	}
}

//����
int CRussiaDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	//���ô��ڱ���
	SetWindowText("����˹����");
	// TODO: Add your specialized creation code here
	//�������󷽿�
	int xOffset=20;//�������Ͻ�xƫ��
	int yOffset=20;//�������Ͻ�xƫ��
	int brickSize=25;//ש���С(�����Ϊ25)
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
	//������һ������
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

//��ʾ����
void CRussiaDlg::ShowBricks(int nHow)
{
/*��ʾ��ʽ:	
	����:nHow=0
	�任:nHow=1
	����:nHow=2
	����:nHow=3
	����:nHow=4
*/
	int x,y,i,j,tmpx,tmpy,tmpt,cx=0,cy=0;
	
	//�ж������ʾ
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
	//�ж�ש���Ƿ����
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			x=j+tmpx;
			y=i+tmpy-3;
			if(x>=0 && x<12 && y>=0 && y<18)//�߽���
			{	
				if(m_arrBricks[x][y].GetVisible()&&BRICKS_DATA[tmpt][i][j])//�����Ҫ��ʾ�����Ѿ���ʾ��ש������ж�
					if(i+cy>=0&&i+cy<4&&j+cx>=0&&j+cx<4)
					{
						if(!BRICKS_DATA[m_curBrickType][i+cy][j+cx])//��ԭ����ש���ڳ��ֿ���ש�����Ϸ�(���򲻺Ϸ�)
						{
							if(nHow==4)//��������
								m_curBrickStop=TRUE;
							return ;
						}
					}
					else//��ԭ����ש������ֿ���ש�������Ϸ�
					{
						if(nHow==4)//��������
							m_curBrickStop=TRUE;
						return ;
					}
			}
			else if(BRICKS_DATA[tmpt][i][j])//�߽���
			{
				if(x<0 || x>=12 || y>=18)//���ҡ��±�
				{
					if(y>=18)//�����±�Խ��
						m_curBrickStop=TRUE;
					return ;
				}
			}
		}
	//������ש��
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
	//��ʾ��ש��
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
	//������λ�ü�������
	m_curBrickPosx=tmpx;
	m_curBrickPosy=tmpy;
	m_curBrickType=tmpt;
}

//���񰴼���Ϣ
BOOL CRussiaDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
/*  
ɨ�����:
	VK_BACK      08 BACKSPACE ��(�˸�)
����VK_TAB       09 TAB ��(�л�)
����VK_RETURN    0D ENTER ��(�س�)
����VK_SHIFT     10 SHIFT ��(�ϵ�)
����VK_CONTROL   11 CTRL ��(����)
����VK_MENU      12 ALT ��(���)
����VK_PAUSE     13 PAUSE ��(��ͣ)
����VK_CAPITAL   14 CAPS LOCK ��(��Сд��)
	VK_ESCAPE    1B ESC ��(�˳�)
����VK_SPACE     20 SPACEBAR��(�ո�)
����VK_PRIOR     21 PAGE UP ��(�Ϸ�ҳ)
����VK_NEXT      22 PAGE DOWN ��(�·�ҳ)
����VK_END       23 END ��(����)
����VK_HOME      24 HOME ��(����)
	VK_LEFT      25 ��������ϵ� �� ��
����VK_UP        26 ��������ϵ� �� ��
����VK_RIGHT     27 ��������ϵ� �� ��
����VK_DOWN      28 ��������ϵ� �� ��
����VK_SNAPSHOT  2C PRINT SCREEN��(��ӡ��Ļ)
����VK_INSERT    2D INS ��(����)
����VK_DELETE    2E DEL ��(ɾ��)
����VK_NUMPAD0   60 ����С�����ϵ� 0 ��
����VK_NUMPAD1   61 ����С�����ϵ� 1 ��
����VK_NUMPAD2   62 ����С�����ϵ� 2 ��
����VK_NUMPAD3   63 ����С�����ϵ� 3 ��
����VK_NUMPAD4   64 ����С�����ϵ� 4 ��
����VK_NUMPAD5   65 ����С�����ϵ� 5 ��
����VK_NUMPAD6   66 ����С�����ϵ� 6 ��
����VK_NUMPAD7   67 ����С�����ϵ� 7 ��
����VK_NUMPAD8   68 ����С�����ϵ� 8 ��
����VK_NUMPAD9   69 ����С�����ϵ� 9 ��
	VK_MULTIPLY  6A ����С�����ϵ� * ��
����VK_ADD       6B ����С�����ϵ� + ��
����VK_SEPARATOR 6C ����С�����ϵ� Separator ��
����VK_SUBTRACT  6D ����С�����ϵ� - ��
����VK_DECIMAL   6E ����С�����ϵ� . ��
����VK_DIVIDE    6F ����С�����ϵ� / ��
����VK_F1        70 F1 ��
����VK_F2        71 F2 ��
����VK_F3        72 F3 ��
����VK_F4        73 F4 ��
����VK_F5        74 F5 ��
����VK_F6        75 F6 ��
����VK_F7        76 F7 ��
����VK_F8        77 F8 ��
����VK_F9        78 F9 ��
����VK_F10       79 F10 ��
����VK_F11       7A F11 ��
����VK_F12       7B F12 ��
����VK_NUMLOCK   90 NUM LOCK ��(������)
����VK_SCROLL    91 SCROLL LOCK ��(������)*/
	if(pMsg->message==WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_UP:
			if(!m_bGamePause)
			{
				ShowBricks(1);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_TYPE);//��������
			}
			break;
		case VK_LEFT:
			if(!m_bGamePause)
			{
				ShowBricks(2);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//��������
				}
			break;
		case VK_RIGHT:
			if(!m_bGamePause)
			{
				ShowBricks(3);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//��������
				}
			break;
		case VK_DOWN:
			if(!m_bGamePause)
			{
				ShowBricks(4);
				if(m_bGameSound)
					PlaySound(IDR_WAVE_MOVE);//��������
			}
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
/*		case 'X': //ʾ��
			if(::GetKeyState(VK_CONTROL)<0)
				MessageBox("��ϼ�CTRL+X");
			else
				MessageBox("��ĸ��X");
			break;*/
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

//��ʱ��
void CRussiaDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	if(nIDEvent==1)//��������
	{
		if(!m_bGamePause)//����ͣ
		{
			if(m_curBrickStop)//���鵽��
			{
				//CString str;
				//str.Format("%d,%d",m_curBrickPosx,m_curBrickPosy);
				//m_staticScoreBox.SetWindowText(str);
				//����ש�������ɫ
				static bool bSet=false;
				if(bSet) SetBricksColor();
				if(!bSet) bSet=true;

				//����
				if(CheckOver())
				{
					OnGameStart();
					return ;
				}
				//����
				CheckKill();
				//׼����һ��
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
	else if(nIDEvent==2)//ʱ���ۼ�
	{
		if(!m_bGamePause)
		{
			m_dwTime++;
			m_strTime=GetTimeStr(m_dwTime);
			m_staticTimeBox.SetWindowText(m_strTime);
		}
	}
	else if(nIDEvent==3)//����ש��
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
	else if(nIDEvent==4)//����ש��
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

//��ʾ��һ������
void CRussiaDlg::ShowNextBricks()
{
	int i,j;
	//������ש��
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			m_nextBricks[j][i].SetVisible(FALSE);
	//��ʾ��ש��
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

//����
void CRussiaDlg::OnGameSound() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameSound)
	{
		m_btnGameSound.UpdatButton("����",0);
		m_bGameSound=0;
	}
	else
	{
		m_btnGameSound.UpdatButton("����",1);
		m_bGameSound=1;
	}
}

//����
void CRussiaDlg::OnGameNet() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameNet)
	{
		m_btnGameNet.UpdatButton("����",0);
		m_bGameNet=0;
		Invalidate();
	}
	else
	{
		m_btnGameNet.UpdatButton("����",1);
		m_bGameNet=1;
		Invalidate();
	}
}

//�ö�
void CRussiaDlg::OnSettop() 
{
	// TODO: Add your control notification handler code here
	if(m_bSetTop)
	{
		m_btnSetTop.UpdatButton("�ö�",0);
		m_bSetTop=0;
		SetWindowPos(&this->wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE |SWP_NOSIZE);
	}
	else
	{
		m_btnSetTop.UpdatButton("�ö�",1);
		m_bSetTop=1;
		SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE |SWP_NOSIZE);

	}
}

//��ͣ
void CRussiaDlg::OnGamePause() 
{
	// TODO: Add your control notification handler code here
	if(m_bGamePause)
	{
		m_btnGamePause.UpdatButton("��ͣ",0);
		m_bGamePause=0;
	}
	else
	{
		m_btnGamePause.UpdatButton("����",1);
		m_bGamePause=1;
	}
}

//��Ϸ��ʼ
void CRussiaDlg::OnGameStart() 
{
	// TODO: Add your control notification handler code here
	if(m_bGameStart)
	{
		m_btnGameStart.UpdatButton("��ʼ",0);
		m_bGameStart=0;
		KillTimer(1);
		KillTimer(2);
		m_sliderLevel.EnableWindow(TRUE);
		m_btnGamePause.EnableWindow(FALSE);
		m_btnGamePause.UpdatButton("��ͣ",0);
		m_bGamePause=0;
		GameOver();
	}
	else
	{
		m_btnGameStart.UpdatButton("����",1);
		m_bGameStart=1;
		GameStart();
		m_sliderLevel.EnableWindow(FALSE);
		m_btnGamePause.EnableWindow(TRUE);
		m_btnGamePause.SetFocus();//��ҪΪ���ܽ��տո����ʵ����ͣ
	}
}

//��Ϸ����
void CRussiaDlg::GameOver()
{
	SetTimer(3,30,NULL);
}

//�ؼ�����
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
		font.CreatePointFont(150,"����",NULL);
		pDC->SelectObject(&font);
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(205,12,67));
		return m_hBkBrush;
		break;
	}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

//ת��ʱ��
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

//����������
void CRussiaDlg::OnCustomdrawSliderLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_nLevel=m_sliderLevel.GetPos();
	*pResult = 0;
}

//�ж���Ϸ����
BOOL CRussiaDlg::CheckOver()
{
	for(int i=0;i<12;i++)
		if(m_arrBricks[i][0].GetVisible())
			return TRUE;
	return FALSE;
}

//�ж�����
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
				PlaySound(IDR_WAVE_KILL);//��������
			nLine++;
		}
	}
	if(nLine>0)
	{
		m_nScore+=m_nScores[nLine-1];
		m_nKillLine+=nLine;
		//��ʾ�³ɼ�
		CString str;
		str.Format("%d",m_nScore);
		m_staticScoreBox.SetWindowText(str);
		str.Format("%d",m_nKillLine);
		m_staticLineBox.SetWindowText(str);
	}
}

//����
void CRussiaDlg::KillLine(int nLine)
{
	for(int i=nLine;i>0;i--)
		for(int j=0;j<12;j++)
			m_arrBricks[j][i].SetVisible(m_arrBricks[j][i-1].GetVisible());
}

//����ש�������ɫ
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
//��Ϸ����
void CRussiaDlg::GameStart()
{

	m_curBrickStop=TRUE;
	m_strTime="00:00";
	m_dwTime=0;
	m_nScore=0;
	m_nKillLine=0;

	SetTimer(4,30,NULL);
}

//���ù��
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
	//1����ð�����Դ��ģ������
	HMODULE hmod=AfxGetResourceHandle(); 
	//2��������Դ����Ϣ��
	HRSRC hSndResource=FindResource(hmod,MAKEINTRESOURCE(nID),_T("WAVE"));
	//3. װ����Դ���ݲ�������
	HGLOBAL hGlobalMem=LoadResource(hmod,hSndResource);
	LPCTSTR lpMemSound=(LPCSTR)LockResource(hGlobalMem);
	//4�����������ļ���
	sndPlaySound(lpMemSound,SND_MEMORY);
	//5���ͷ���Դ�����
	FreeResource(hGlobalMem);
	return true;
}

//ע����ʼ��
void CRussiaDlg::RegInit()
{
	HKEY hKey;
	LONG result=RegOpenKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia",&hKey);
	if(result==ERROR_SUCCESS)
		RegRead();
	else
		RegWrite();
}

//ע����ȡ
void CRussiaDlg::RegRead()
{
	//HKEY hKey;
	//DWORD len,type;

	//RegOpenKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppParam",&hKey);

	//read something...

	//RegCloseKey(hKey);
}
//ע���д��
void CRussiaDlg::RegWrite()
{
	HKEY hKey;
	//DWORD len;

	RegCreateKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppInfo",&hKey);
	RegSetValueEx(hKey,"AppName",0,REG_SZ,(CONST BYTE*)"����˹������Ϸ",strlen("����˹������Ϸ"));
	RegSetValueEx(hKey,"Author",0,REG_SZ,(CONST BYTE*)"��ʥ",strlen("��ʥ"));
	RegSetValueEx(hKey,"Version",0,REG_SZ,(CONST BYTE*)"v0.1��",strlen("v0.1��"));
	RegSetValueEx(hKey,"Date",0,REG_SZ,(CONST BYTE*)"2008.10.16",strlen("2008.10.16"));

	RegCreateKey(HKEY_LOCAL_MACHINE,"software\\DashengSoft\\Russia\\AppParam",&hKey);
	
	RegCloseKey(hKey);
}
