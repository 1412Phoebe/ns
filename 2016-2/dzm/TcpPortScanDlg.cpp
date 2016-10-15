// TcpPortScanDlg.cpp : ʵ���ļ�

#include "stdafx.h"
#include "TcpPortScan.h"
#include "TcpPortScanDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//�Ի�����
class CAboutDlg : public CDialog //CAboutDlg�������public�ķ�ʽ�̳���CDialog
{
public:
	CAboutDlg();

//�Ự����
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };  //enumΪö������
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    //DDX�����ݳ�Ա�����ͶԻ���ģ���ڵĿؼ����ӣ�ʹ�������ڿؼ�֮������׵ش��䡣
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

//�궨���һ��
BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpPortScanDlg dialog

CTcpPortScanDlg::CTcpPortScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpPortScanDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcpPortScanDlg)
	m_Address = _T("");
	m_Port = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTcpPortScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcpPortScanDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_Address);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTcpPortScanDlg, CDialog)
	//{{AFX_MSG_MAP(CTcpPortScanDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnTcpscan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpPortScanDlg message handlers

BOOL CTcpPortScanDlg::OnInitDialog()
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
	LONG lStyle;
	lStyle = GetWindowLong(m_list.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	SetWindowLong(m_list.m_hWnd, GWL_STYLE, lStyle);//����style
	DWORD dwStyle = m_list.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_list.SetExtendedStyle(dwStyle); //������չ���
	CRect rc;
	m_list.GetClientRect(rc);
	int width=rc.Width()/3;
	m_list.InsertColumn(0,"������ַ",LVCFMT_CENTER,width);
	m_list.InsertColumn(1,"�˿ں�",LVCFMT_CENTER,width);
	m_list.InsertColumn(2,"�˿�״̬",LVCFMT_CENTER,width);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTcpPortScanDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcpPortScanDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTcpPortScanDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTcpPortScanDlg::OnTcpscan() 
{
	UpdateData(true);                         //MFC���ں���������ˢ������
	int count=m_list.GetItemCount();          
	WSADATA WSAData;                          //�����洢��WSAStartup�������ú󷵻ص�Windows Sockets����
	if(WSAStartup(MAKEWORD(2,2),&WSAData)!=0) /*�������������Ӧ�ó�����winsock.dll�ĵ�һ������.����,��һ��������WINSOCK �汾��,�ڶ���������ָ��
                                              WSADATA��ָ��.�ú�������һ��INT��ֵ,ͨ��������ֵ��ȷ����ʼ���Ƿ�ɹ�*/
	{
		MessageBox("��ʼ��Winsockʧ��!");
		return;
	}
	Socket=socket(AF_INET,SOCK_STREAM,0);         //���������׽���
	if(Socket==INVALID_SOCKET)
	{
		MessageBox("����Socketʧ��!");
		WSACleanup();                         //�ú���������ֹWinsock.DLL��ʹ��
		return;
	}
	int IpAddress;								  //�ж�������IP��ַ
	IpAddress=inet_addr(m_Address);
	if(IpAddress==INADDR_NONE)
	{
		hostent* pHostent=gethostbyname(m_Address);
		if(pHostent)
			IpAddress=(*(in_addr*)pHostent->h_addr).s_addr;
	}	
	sockaddr_in DestHost;                         //�����׽��ֵ�ַ
	memset(&DestHost,0,sizeof(DestHost));
	DestHost.sin_family=AF_INET;
	DestHost.sin_port=htons(atoi(m_Port));
	DestHost.sin_addr.s_addr=IpAddress;
	int nConnect;                                 //���������������
	nConnect=connect(Socket,(sockaddr*)&DestHost,sizeof(DestHost));  //����connect()
	if(nConnect==SOCKET_ERROR)
	{
		m_list.InsertItem(count,m_Address);
		m_list.SetItemText(count,1,m_Port);
		m_list.SetItemText(count,2,"close");
	}
	else
	{
		m_list.InsertItem(count,m_Address);
		m_list.SetItemText(count,1,m_Port);
		m_list.SetItemText(count,2,"open");
	}
	UpdateData(false);
	closesocket(Socket);
	WSACleanup();                                 //�ͷ��׽��ְ�
}
