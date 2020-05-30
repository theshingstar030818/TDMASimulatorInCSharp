
// TDMASystem3SimulatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TDMASystem3Simulator.h"
#include "TDMASystem3SimulatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTDMASystem3SimulatorDlg dialog



CTDMASystem3SimulatorDlg::CTDMASystem3SimulatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TDMASYSTEM3SIMULATOR_DIALOG, pParent)
	, status_N(8)
	, status_W(4)
	, status_Li(4)
	, status_SlotLen(1000)
	, m_sSrcN1(_T(""))
	, m_sSrcN2(_T(""))
	, m_sSrcN3(_T(""))
	, m_sSrcN4(_T(""))
	, m_sSrcN5(_T(""))
	, m_sSrcN6(_T(""))
	, m_sSrcN7(_T(""))
	, m_sSrcN8(_T(""))
	, m_sDstN1(_T(""))
	, m_sDstN2(_T(""))
	, m_sDstN3(_T(""))
	, m_sDstN4(_T(""))
	, m_sDstN5(_T(""))
	, m_sDstN6(_T(""))
	, m_sDstN7(_T(""))
	, m_sDstN8(_T(""))
	, status_bVal(1)
	, m_strAnalyze(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTDMASystem3SimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_N, status_N);
	DDX_Text(pDX, IDC_EDIT_W, status_W);
	DDX_Text(pDX, IDC_EDIT_Li, status_Li);
	DDX_Text(pDX, IDC_EDIT_SLOT_LEN, status_SlotLen);
	DDX_Text(pDX, IDC_EDIT_SRC_N1, m_sSrcN1);
	DDX_Text(pDX, IDC_EDIT_SRC_N2, m_sSrcN2);
	DDX_Text(pDX, IDC_EDIT_SRC_N3, m_sSrcN3);
	DDX_Text(pDX, IDC_EDIT_SRC_N4, m_sSrcN4);
	DDX_Text(pDX, IDC_EDIT_SRC_N5, m_sSrcN5);
	DDX_Text(pDX, IDC_EDIT_SRC_N6, m_sSrcN6);
	DDX_Text(pDX, IDC_EDIT_SRC_N7, m_sSrcN7);
	DDX_Text(pDX, IDC_EDIT_SRC_N8, m_sSrcN8);
	DDX_Text(pDX, IDC_EDIT_DST_N1, m_sDstN1);
	DDX_Text(pDX, IDC_EDIT_DST_N2, m_sDstN2);
	DDX_Text(pDX, IDC_EDIT_DST_N3, m_sDstN3);
	DDX_Text(pDX, IDC_EDIT_DST_N4, m_sDstN4);
	DDX_Text(pDX, IDC_EDIT_DST_N5, m_sDstN5);
	DDX_Text(pDX, IDC_EDIT_DST_N6, m_sDstN6);
	DDX_Text(pDX, IDC_EDIT_DST_N7, m_sDstN7);
	DDX_Text(pDX, IDC_EDIT_DST_N8, m_sDstN8);
	DDX_Control(pDX, IDC_LIST_SLOT_LOG, m_ctrlLstSlotLog);
	DDX_Text(pDX, IDC_EDIT1, status_bVal);
	DDV_MinMaxInt(pDX, status_bVal, 1, 8);
	DDX_Text(pDX, IDC_STATIC_ANALYZE, m_strAnalyze);
}

BEGIN_MESSAGE_MAP(CTDMASystem3SimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, &CTDMASystem3SimulatorDlg::OnBnClickedBtnStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_STOP, &CTDMASystem3SimulatorDlg::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CTDMASystem3SimulatorDlg::OnBnClickedBtnPause)
END_MESSAGE_MAP()


// CTDMASystem3SimulatorDlg message handlers

BOOL CTDMASystem3SimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTDMASystem3SimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTDMASystem3SimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTDMASystem3SimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTDMASystem3SimulatorDlg::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CTDMASystem3SimulatorDlg::OnLbnSelchangeList1()
{
	// TODO: Add your control notification handler code here
}


void CTDMASystem3SimulatorDlg::OnBnClickedBtnStart()
{
	// TODO: Add your control notification handler code here
	m_objTDMASimulator.initialize();
	UpdateData(TRUE);
	int nIntervalForPacketGen = 1800 - status_bVal * 200;
	SetTimer(1, nIntervalForPacketGen, NULL);
	SetTimer(2, status_SlotLen, NULL);

	m_sSrcN1 = _T("");
	m_sSrcN2 = _T("");
	m_sSrcN3 = _T("");
	m_sSrcN4 = _T("");
	m_sSrcN5 = _T("");
	m_sSrcN6 = _T("");
	m_sSrcN7 = _T("");
	m_sSrcN8 = _T("");
	m_sDstN1 = _T("");
	m_sDstN2 = _T("");
	m_sDstN3 = _T("");
	m_sDstN4 = _T("");
	m_sDstN5 = _T("");
	m_sDstN6 = _T("");
	m_sDstN7 = _T("");
	m_sDstN8 = _T("");

	UpdateData(FALSE);

	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	m_ctrlLstSlotLog.ResetContent();
}


void CTDMASystem3SimulatorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1)
	{ // this is timer thread for random integer generator
		while (m_fMutex)
			Sleep(1);
		m_fMutex = true;

		//Generate a Packet to send
		int nNodeNO = m_objTDMASimulator.GenerateAPacket();
	
		//updated dlg content
		UpdateDlgContentOfSendParty(nNodeNO);

		m_fMutex = false;
	}
	else if (nIDEvent == 2)
	{
		while (m_fMutex)
			Sleep(1);
		m_fMutex = true;

		//Process a packet
		CString strtmp = m_objTDMASimulator.ProcessASlot();
		//Updated slot log list
		if(strtmp.GetLength() > 0)
			m_ctrlLstSlotLog.InsertString(0, strtmp);
		//Update Dlg content
		for (int i = 0; i < TDMA_STATUS_N; i++)
		{
			UpdateDlgContentOfSendParty(i);
			UpdateDlgContentOfReceiveParty(i);
		}

		m_strAnalyze = m_objTDMASimulator.GetAverageDelay();

		UpdateData(FALSE);
		m_fMutex = false;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CTDMASystem3SimulatorDlg::UpdateDlgContentOfSendParty(int nNodeNO)
{
	if (nNodeNO >= 0)
	{//show updated data to Dlg
		CString strtmp = m_objTDMASimulator.GetNodeToSendString(nNodeNO);
		if (nNodeNO == 0)
			m_sSrcN1 = strtmp;
		else if (nNodeNO == 1)
			m_sSrcN2 = strtmp;
		else if (nNodeNO == 2)
			m_sSrcN3 = strtmp;
		else if (nNodeNO == 3)
			m_sSrcN4 = strtmp;
		else if (nNodeNO == 4)
			m_sSrcN5 = strtmp;
		else if (nNodeNO == 5)
			m_sSrcN6 = strtmp;
		else if (nNodeNO == 6)
			m_sSrcN7 = strtmp;
		else if (nNodeNO == 7)
			m_sSrcN8 = strtmp;
		UpdateData(FALSE);
	}
}


void CTDMASystem3SimulatorDlg::UpdateDlgContentOfReceiveParty(int nNodeNO)
{
	if (nNodeNO >= 0)
	{//show updated data to Dlg
		CString strtmp = m_objTDMASimulator.GetNodeReceivedString(nNodeNO);
		if (nNodeNO == 0)
			m_sDstN1 = strtmp;
		else if (nNodeNO == 1)
			m_sDstN2 = strtmp;
		else if (nNodeNO == 2)
			m_sDstN3 = strtmp;
		else if (nNodeNO == 3)
			m_sDstN4 = strtmp;
		else if (nNodeNO == 4)
			m_sDstN5 = strtmp;
		else if (nNodeNO == 5)
			m_sDstN6 = strtmp;
		else if (nNodeNO == 6)
			m_sDstN7 = strtmp;
		else if (nNodeNO == 7)
			m_sDstN8 = strtmp;
		UpdateData(FALSE);
	}
}


void CTDMASystem3SimulatorDlg::OnBnClickedBtnStop()
{
	// TODO: Add your control notification handler code here
	KillTimer(1);
	KillTimer(2);

	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
}


void CTDMASystem3SimulatorDlg::OnBnClickedBtnPause()
{
	// TODO: Add your control notification handler code here
	m_isPaused = !m_isPaused;
	if (m_isPaused)
	{
		KillTimer(1);
		KillTimer(2);
	}
	else
	{
		int nIntervalForPacketGen = 1800 - status_bVal * 200;
		SetTimer(1, nIntervalForPacketGen, NULL);
		SetTimer(2, status_SlotLen, NULL);
	}
}
