
// MFCTest02Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCTest02.h"
#include "MFCTest02Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMFCTest02Dlg 대화 상자(dialog class)



CMFCTest02Dlg::CMFCTest02Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST02_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCTest02Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDYES, btnTest);
	DDX_Control(pDX, IDC_EDIT1, Memo);
}

BEGIN_MESSAGE_MAP(CMFCTest02Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDYES, &CMFCTest02Dlg::TestFunc)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCTest02Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCTest02Dlg 메시지 처리기

BOOL CMFCTest02Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCTest02Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCTest02Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCTest02Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//소문자를 대문자로 변환(6번째 비트를 0으로 만들어 줌) 
// ex) xx1x xxxx => xx0x xxxx
//	   1101 1111 DFh	(&)
CString ToUpper(CString s)	
{
	CString t;

	for (int i = 0; i < s.GetLength(); i++) {
		WCHAR w = s[i];
		if (w >= 'a' && w <= 'z') {
			w &= 0xdf;
		}
		t += w;
	}

	return t;
}

//대문자를 소문자로 변환(6번째 비트를 1으로 만들어 줌) 
// ex) xx0x xxxx => xx1x xxxx
//	   0010 0000 20h	(|)
CString ToLower(CString s)
{
	CString t;

	for (int i = 0; i < s.GetLength(); i++) {
		WCHAR w = s[i];
		if (w >= 'A' && w <= 'Z') {
			w |= 0x20;
		}
		t += w;
	}

	return t;
}

void CMFCTest02Dlg::TestFunc()		//Button1 Clicked
{
	static bool change = false;
	CString message;

	if (change) {	// 첫번째 클릭

		char* s1 = "문자열 예시";
		WCHAR* s2 = L"WIDE String Sample";
		CString str = L"문자열 예시";
		((CEdit*)(GetDlgItem(IDC_EDIT1)))->GetWindowTextW(str);
		//Memo.GetWindowTextW(str);	//읽어올 때

		str = ToUpper(str);
		Memo.SetWindowTextW(str);	//쓸 때

		change = false;
	}
	else {			// 두번째 클릭
		CString str = L"문자열 예시";
		((CEdit*)(GetDlgItem(IDC_EDIT1)))->GetWindowTextW(str);
		
		str = ToLower(str);
		Memo.SetWindowTextW(str);	//쓸 때
		change = true;
	}
}


void CMFCTest02Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
