
// OCamViewerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OCamViewer.h"
#include "OCamViewerDlg.h"
#include "ImgProc.h"
#include <mmsystem.h>
#include <string>
#include  <fstream>

// Jens includes
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
//#include <sysinfoapi.h>

#define  WM_CALLBACK		(WM_USER+2)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 
#pragma comment(lib, "winmm.lib")

#define MAX_NUM_LIST_RESOLUTION	32	//by SDKIM ����� DEFINE���� ���� 20�� 32���� ������Ŵ
int g_Resolution[MAX_NUM_LIST_RESOLUTION][3];
//int g_Resolution_Test[MAX_NUM_LIST_RESOLUTION]; //by SDKIM ������� �����Ƿ� ����

int g_5CRO_U3[][3] = {		// default
	{2592, 1944, 375},
	{2592, 1944, 750},
	{1920,1080, 750},
	{1920,1080, 1500},
	{1280,960, 1500},
	{1280,960, 3000},
	{1280,720, 1500},
	{1280,720, 3000},
	{640,480, 3000},
	{640,480, 6000},
	{640,480, 9000},
	{640,480, 12000},
	{320,240, 3000},
	{320,240, 6000},
	{320,240, 9000},
    {320,240, 10000},
	{320,240, 12000},
};
int g_5CRO_U2[][3] = {
	{2592, 1944, 375},
	{1920,1080, 750},
	{1280,960, 1500},
	{1280,720, 1500},
	{640,480, 3000},
	{640,480, 6000},
	{320,240, 3000},
	{320,240, 6000},
	{320,240, 9000},
	{320,240, 10000},
	{320,240, 12000},
};
// by SDKIM 1MCG, 1CGN FPS ����Ʈ ���� 20180221
int g_1MGN_U3[][3] = 
{
	{ 1280,960, 5400 },
	{ 1280,960, 5000 },
	{ 1280,960, 3000 },
	{ 1280,960, 2500 },
	{ 1280,960, 1500 },
	{ 1280,720, 6000 },
	{ 1280,720, 5000 },
	{ 1280,720, 3000 },
	{ 1280,720, 2500 },
	{ 1280,720, 1500 },
	{ 640,480, 10000 },
	{ 640,480,  9000 },
	{ 640,480,  6000 },
	{ 640,480,  5000 },
	{ 640,480,  3000 },
	{ 640,480,  2500 },
	{ 640,480,  1500 },
	{ 320,240, 18000 },
	{ 320,240, 15000 },
	{ 320,240, 12000 },
	{ 320,240, 10000 },
	{ 320,240, 6000 },
	{ 320,240, 5000 },
};

int g_1MGN_U2[][3] = 
{
	{ 1280,960, 3000 },
	{ 1280,960, 2500 },
	{ 1280,960, 1500 },
	{ 1280,720, 3000 },
	{ 1280,720, 2500 },
	{ 1280,720, 1500 },
	{ 640,480, 10000 },
	{ 640,480,  9000 },
	{ 640,480,  6000 },
	{ 640,480,  5000 },
	{ 640,480,  3000 },
	{ 640,480,  2500 },
	{ 640,480,  1500 },
	{ 320,240, 18000 },
	{ 320,240, 15000 },
	{ 320,240, 12000 },
	{ 320,240, 10000 },
	{ 320,240,  6000 },
	{ 320,240,  5000 },
};

int g_1CGN_U3[][3] =
{
	{ 1280,960, 5400 },
	{ 1280,960, 5000 },
	{ 1280,960, 3000 },
	{ 1280,960, 2500 },
	{ 1280,960, 1500 },
	{ 1280,720, 6000 },
	{ 1280,720, 5000 },
	{ 1280,720, 3000 },
	{ 1280,720, 2500 },
	{ 1280,720, 1500 },
	{ 640,480, 10000 },
	{ 640,480,  9000 },
	{ 640,480,  6000 },
	{ 640,480,  5000 },
	{ 640,480,  3000 },
	{ 640,480,  2500 },
	{ 640,480,  1500 },
	{ 320,240, 18000 },
	{ 320,240, 15000 },
	{ 320,240, 12000 },
	{ 320,240, 10000 },
	{ 320,240,  6000 },
	{ 320,240,  5000 },
};

int g_1CGN_U2[][3] =
{
	{ 1280,960, 3000 },
	{ 1280,960, 2500 },
	{ 1280,960, 1500 },
	{ 1280,720, 3000 },
	{ 1280,720, 2500 },
	{ 1280,720, 1500 },
	{ 640,480, 10000 },
	{ 640,480,  9000 },
	{ 640,480,  6000 },
	{ 640,480,  5000 },
	{ 640,480,  3000 },
	{ 640,480,  2500 },
	{ 640,480,  1500 },
	{ 320,240, 18000 },
	{ 320,240, 15000 },
	{ 320,240, 12000 },
	{ 320,240, 10000 },
	{ 320,240,  6000 },
	{ 320,240,  5000 },
};
// by SDKIM 1MCG, 1CGN FPS ����Ʈ ���� 20180221

// sdkim 2WRS �߰� 20180220
int g_2WRS_U3[][3] =
{
	{ 1920,1080, 3000 },
    { 1920,1080, 1500 },
	{ 1280,720, 6000 },
	{ 1280,720, 1500 },
	{ 960,540, 10000 },
	{ 960,540, 1500 },
	{ 640,360, 20000 },
	{ 640,360, 1500 },
};

int g_2WRS_U2[][3] =
{
	{ 0, 0, 0 },
};
int g_2WRS_Flag = 0;
// sdkim 2WRS �߰� 20180220

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// COCamViewerDlg dialog
COCamViewerDlg::COCamViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COCamViewerDlg::IDD, pParent)
	, m_Width(640)
	, m_Height(480)
    , m_FPS(30)
    , m_pCam(NULL)
{
	m_CurrFPS	= 0;
	m_Count		= 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	init_dirImSeq();

}

void COCamViewerDlg::init_dirImSeq()
{
	// Set up dir for sequence of images
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);

	std::string month = std::to_string(sysTime.wMonth);
	month = std::string(2- month.length(), '0') + month;

	std::string day = std::to_string(sysTime.wDay);
	day = std::string(2 - day.length(), '0') + day;

	std::string hour = std::to_string(sysTime.wHour);
	hour = std::string(2 - hour.length(), '0') + hour;

	std::string minute = std::to_string(sysTime.wMinute);
	minute = std::string(2 - minute.length(), '0') + minute;

	std::string second = std::to_string(sysTime.wSecond);
	second = std::string(2 - second.length(), '0') + second;

	std::string ms = std::to_string(sysTime.wMilliseconds);
	ms = std::string(3 - ms.length(), '0') + ms;


	std::string t_str_noMs = std::to_string(sysTime.wYear) + '-' + month + '-' +
		day	+ '-' + hour + '-' + 	minute + '-' + second;
	m_dirImgSeq =  "img_seq_" + t_str_noMs + "\\";
	std::string cmd = "mkdir " + m_dirImgSeq;
	system(cmd.c_str());

	std::ofstream f_tInfo;
	std::string n_tInfo = m_dirImgSeq + "_timeRelaion.txt";
	f_tInfo.open(n_tInfo.c_str());
	f_tInfo << "ms_system_time: " << std::to_string(timeGetTime()) << "\n\n";
	f_tInfo << "year: " << std::to_string(sysTime.wYear) << "\n";
	f_tInfo << "month: " << month << "\n";
	f_tInfo << "day: " << day << "\n";
	f_tInfo << "hour: " << hour << "\n";
	f_tInfo << "minute: " << minute << "\n";
	f_tInfo << "second: " << second << "\n";
	f_tInfo << "ms: " << ms << "\n";
	f_tInfo.close();

}
void COCamViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_Width);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_Height);
	DDX_Control(pDX, IDC_COMBO_CAM, m_cbCam);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_cbResolution);
}

BEGIN_MESSAGE_MAP(COCamViewerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &COCamViewerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &COCamViewerDlg::OnBnClickedButtonStop)

	ON_BN_CLICKED(IDC_BUTTON_SAVE_VIDEO, &COCamViewerDlg::OnBnClickedButtonSaveVideo)
	ON_BN_CLICKED(IDC_BUTTON_STOP_VIDEO, &COCamViewerDlg::OnBnClickedButtonStopVideo)
	
	ON_CBN_SELCHANGE(IDC_COMBO_CAM, &COCamViewerDlg::OnCbnSelchangeComboCam)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, &COCamViewerDlg::OnCbnSelchangeComboResolution)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_IMAGE, &COCamViewerDlg::OnBnClickedButtonSaveImage)
	ON_BN_CLICKED(IDC_BUTTON_CAM_CTRL, &COCamViewerDlg::OnBnClickedButtonCamCtrl)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_MESSAGE(WM_CALLBACK, &COCamViewerDlg::CallbackProc)
END_MESSAGE_MAP()

// COCamViewerDlg message handlers
void CallbackFunction(void *Para, void *Data) 
{
    if (Para != NULL)
	{
		((COCamViewerDlg *)Para)->CopyImage(Data);
		((COCamViewerDlg *)Para)->PostMessage(WM_CALLBACK, (WPARAM)0, (LPARAM)0);
	}
}

BOOL COCamViewerDlg::OnInitDialog()
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

#ifdef _DEBUG
	AllocConsole();
    freopen("CONOUT$", "wt", stdout);   // stdout redirection
#endif

	int camNum = GetConnectedCamNumber();
	for (int i=0; i<camNum; i++)
	{
		CString str;

		str.Format("Cam%d", i);
		m_cbCam.AddString(str);
	}
	m_cbCam.SetCurSel(0);
	OnCbnSelchangeComboCam();

	CWinApp* pApp = AfxGetApp();
	int sel = pApp->GetProfileInt("Set", "Sel", 0);

	if (sel>=m_cbCam.GetCount() || sel<0)
		sel = 0;
	
	m_cbResolution.SetCurSel(sel);
	OnCbnSelchangeComboResolution();

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CAM_CTRL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE_IMAGE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SAVE_VIDEO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_VIDEO)->EnableWindow(FALSE);

	m_StartTime = timeGetTime();

	SetTimer(1, 1000, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COCamViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void COCamViewerDlg::OnPaint()
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
HCURSOR COCamViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COCamViewerDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	KillTimer(1);
    CamStop(m_pCam);
    CamClose(m_pCam);

	int sel = m_cbResolution.GetCurSel();

	CWinApp* pApp = AfxGetApp();
	pApp->WriteProfileInt("Set", "Sel", sel);

#ifdef _DEBUG
	FreeConsole(); 
#endif
}

void COCamViewerDlg::UpdateFPS()
{
    static DWORD t = 0;
	DWORD	current_time;

	current_time = timeGetTime();
	m_CurrFPS = (double)m_Count*1000/(current_time -t);
	t = current_time;

	m_Count = 0;
}


void COCamViewerDlg::CopyImage(void *Data)
{
	BYTE* img = (BYTE*)m_ImageSrc.GetPtr1D();
	memcpy(img, Data, m_ImageSrc.GetSize());
}
//#define FOR_LOWSPEED_MACHINE_BY_SDKIM
#ifdef FOR_LOWSPEED_MACHINE_BY_SDKIM
int m_forLowSpeedMachine_Devide = 0;
int m_forLowSpeedMachine_DevideCnt = 0;
#endif

LRESULT COCamViewerDlg::CallbackProc(WPARAM wParam, LPARAM lParam)
{
	//************ �̹��� ȹ���� ���� Callback �Լ� **************************
	m_Count++;

#ifdef FOR_LOWSPEED_MACHINE_BY_SDKIM
	if (m_forLowSpeedMachine_DevideCnt > 0)
	{
		m_forLowSpeedMachine_DevideCnt--;
		return 0;
	}
	else {
		m_forLowSpeedMachine_DevideCnt = m_forLowSpeedMachine_Devide;
	}
#endif

	
	BYTE* src = (BYTE*)m_ImageSrc.GetPtr1D();
	BYTE* dst = (BYTE*)m_Image.GetPtr1D();

	if (m_CamModel == "oCam-1CGN-U") {
		Bayer2RGB((char*)src, (char*)dst, m_Width, m_Height, BayerGR2RGB);
		m_Display.Display(m_Image);
		
	}
	else if (m_CamModel == "oCam-1MGN-U") {
		m_Display.Display(m_ImageSrc);
	}
	else {
		YUV2RGB(src, dst, m_Image.GetNumPixels(), 0, 1, 2, 3);
		m_Display.Display(m_Image);
	}

	if (isRecording)
	{
		SaveSequenceInstance();
	}
	return 0;
}


void COCamViewerDlg::OnBnClickedButtonPlay()
{
#ifdef FOR_LOWSPEED_MACHINE_BY_SDKIM
	m_forLowSpeedMachine_Devide = (int)(m_FPS / 30.0);
#endif

    // TODO: Add your control notification handler code here
	if(GetConnectedCamNumber() > 0)
	{
		//m_pCam = CamOpen(m_CamSel, m_Width, m_Height, m_FPS, CallbackFunction, this);
		m_pCam = CamOpen(m_CamSel, m_Width, m_Height, 5, CallbackFunction, this);
	} else
	{
		m_Image.Alloc(600,600, MV_Y8);
		RECT rct = RECT{ 150, 150, 250,250 };
		COLORREF clr = 0x778877;
		m_Display.Display(m_Image);
		m_Display.DrawRect(rct, clr);
		HWND wrnWnd = NULL;
		LPCSTR txt = "No camera connected";
		LPCSTR cpt = "Camera issue";
		MessageBoxA(txt, cpt, MB_OK);

		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CAM_CTRL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_CAM)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_TEST)->EnableWindow(TRUE);
		return;
	}
	m_DlgCamCtrl.UpdateCamCtrl(m_pCam, m_Width, m_Height);

	if (m_CamModel == "oCam-1MGN-U" || m_CamModel == "oCam-1CGN-U")
	{
	    m_ImageSrc.Alloc(m_Width, m_Height, MV_Y8);
	}
	else
	{
	    m_ImageSrc.Alloc(m_Width, m_Height, MV_YUV422);
	}

	m_Image.Alloc(m_Width, m_Height, MV_RGB24);

	Sleep(50);

	if (CamStart(m_pCam) == 0) 
        return;

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CAM_CTRL)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_CAM)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_SAVE_IMAGE)->EnableWindow(TRUE);
	
	m_CurrFPS = 0;
	m_StartTime = timeGetTime();
}

void COCamViewerDlg::OnBnClickedButtonStop()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CAM_CTRL)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_CAM)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_SAVE_IMAGE)->EnableWindow(FALSE);
	

    CamStop(m_pCam);
    CamClose(m_pCam);

	m_DlgCamCtrl.ShowWindow(SW_HIDE);
	m_CurrFPS = 0;
}

void COCamViewerDlg::OnBnClickedButtonSaveVideo()
{
	//GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	//GetDlgItem(IDC_BUTTON_CAM_CTRL)->EnableWindow(TRUE);
	//GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
	//GetDlgItem(IDC_COMBO_CAM)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_SAVE_VIDEO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP_VIDEO)->EnableWindow(TRUE);
	
	isRecording = true;
}

void COCamViewerDlg::OnBnClickedButtonStopVideo()
{
	GetDlgItem(IDC_BUTTON_SAVE_VIDEO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP_VIDEO)->EnableWindow(FALSE);


	isRecording = false;
}

void COCamViewerDlg::SaveSequenceInstance()
{
	DWORD t_save_frame = timeGetTime();

	std::ostringstream save_name;
	save_name << m_dirImgSeq << "im_" << std::setw(10) << std::setfill('0') << t_save_frame << ".bmp";
	std::string name_str = save_name.str();
	CString fName(name_str.c_str());

	if (m_CamModel == "oCam-1MGN-U") {
		m_ImageSrc.Save(fName);
	}
	else {
		m_Image.Save(fName);
	}
}

void COCamViewerDlg::OnCbnSelchangeComboCam()
{
	// TODO: Add your control notification handler code here
	m_CamSel = m_cbCam.GetCurSel();

	m_CamModel = CamGetDeviceInfo(m_CamSel, INFO_MODEL_NAME);
	m_CamSN	   = CamGetDeviceInfo(m_CamSel, INFO_SERIAL_NUM);
	m_UsbType  = CamGetDeviceInfo(m_CamSel, INFO_USB_TYPE);
	m_FW       = CamGetDeviceInfo(m_CamSel, INFO_DATE_TIME);

	SetDlgItemText(IDC_STATIC_MODEL, m_CamModel);
	SetDlgItemText(IDC_STATIC_SN, m_CamSN);
	SetDlgItemText(IDC_STATIC_USB_TYPE, m_UsbType);
	SetDlgItemText(IDC_STATIC_FW, m_FW);

	int num_list;
	if (m_CamModel == "oCam-1CGN-U") {
		if (m_UsbType == "USB2")
		{
			memcpy(g_Resolution, g_1CGN_U2, sizeof(g_1CGN_U2));
			num_list = sizeof(g_1CGN_U2) / 12;
		}
		else
		{
			memcpy(g_Resolution, g_1CGN_U3, sizeof(g_1CGN_U3));
			num_list = sizeof(g_1CGN_U3) / 12;
		}
	}
	else if (m_CamModel == "oCam-1MGN-U") {
		if (m_UsbType == "USB2")
		{
			memcpy(g_Resolution, g_1MGN_U2, sizeof(g_1MGN_U2));
			num_list = sizeof(g_1MGN_U2) / 12;
		}
		else
		{
			memcpy(g_Resolution, g_1MGN_U3, sizeof(g_1MGN_U3));
			num_list = sizeof(g_1MGN_U3) / 12;
		}
	}
	// sdkim 2WRS �߰� 20180220
	else if (m_CamModel == "oCam-2WRS-U") { 
		g_2WRS_Flag = 1;
		if (m_UsbType == "USB2")
		{
			memcpy(g_Resolution, g_2WRS_U2, sizeof(g_2WRS_U2));
			num_list = sizeof(g_2WRS_U2) / 12;
			num_list = 0;
		}
		else
		{
			memcpy(g_Resolution, g_2WRS_U3, sizeof(g_2WRS_U3));
			num_list = sizeof(g_2WRS_U3) / 12;
		}
	}
	// sdkim 2WRS �߰� 20180220
	else {		// oCam-5CRO-U
		if (m_UsbType == "USB2")
		{
			memcpy(g_Resolution, g_5CRO_U2, sizeof(g_5CRO_U2));
			num_list = sizeof(g_5CRO_U2) / 12;
		}
		else
		{
			memcpy(g_Resolution, g_5CRO_U3, sizeof(g_5CRO_U3));
			num_list = sizeof(g_5CRO_U3) / 12;
		}
	}

	m_cbResolution.ResetContent();
	if (num_list == 0)
	{
		m_cbResolution.AddString("Not Supported.");
	}

	for (int i=0; i<num_list; i++)
	{
		CString str;
		if (g_Resolution[i][2]%100 == 0)
			str.Format("%4d x%4d %3.00ffps", g_Resolution[i][0], g_Resolution[i][1], g_Resolution[i][2]/100.0);
		else
			str.Format("%4d x%4d %3.02ffps", g_Resolution[i][0], g_Resolution[i][1], g_Resolution[i][2]/100.0);
		m_cbResolution.AddString(str);
	}

	m_cbResolution.SetCurSel(0);
	OnCbnSelchangeComboResolution();
}

void COCamViewerDlg::OnCbnSelchangeComboResolution()
{
	// TODO: Add your control notification handler code here
	int num = m_cbResolution.GetCurSel();

	m_Width  = g_Resolution[num][0];
	m_Height = g_Resolution[num][1];
	m_FPS    = static_cast<double>(g_Resolution[num][2]) / 100.0;

	UpdateData(FALSE);
}

void COCamViewerDlg::OnBnClickedButtonSaveImage()
{
	// TODO: Add your control notification handler code here
	wImage image;
	if (m_CamModel == "oCam-1MGN-U") {
		image = m_ImageSrc;
	}
	else {
		image = m_Image;
	}


	CFileDialog dlg(FALSE, _T("bmp"),_T("image"),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
	_T("bmp FILE (*.bmp)|*.bmp|ALL FILE (*.*)|*.*|") );

	if (dlg.DoModal() == IDOK) 
	{
		CString file = dlg.GetPathName();
		image.Save(file);
	}
}


void COCamViewerDlg::OnBnClickedButtonCamCtrl()
{
	// TODO: Add your control notification handler code here
	m_DlgCamCtrl.ShowWindow(SW_SHOW);
}


void COCamViewerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	UpdateFPS();

	SetDlgItemInt(IDC_STATIC_FPS, (int)(m_CurrFPS+0.5));

	CDialogEx::OnTimer(nIDEvent);
}
