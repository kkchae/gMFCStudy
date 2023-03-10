
// Step4ProjectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Step4Project.h"
#include "Step4ProjectDlg.h"
#include "afxdialogex.h"
#include "ImageProcess.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
using namespace chrono;

#ifdef _DEBUG
#define new DEBUG_NEW
#ifdef UNICODE
#pragma comment(linker, "/ENTRY:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/ENTRY:WinMainCRTStartup /subsystem:console")
#endif
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


// CStep4ProjectDlg 대화 상자



CStep4ProjectDlg::CStep4ProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STEP4PROJECT_DIALOG, pParent)
	, m_pDlgImage(NULL)
	, m_pDlgImageResult(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStep4ProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStep4ProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStep4ProjectDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_TEST, &CStep4ProjectDlg::OnBnClickedBtnTest)
	ON_BN_CLICKED(IDC_BTN_IMAGE_PROCESS, &CStep4ProjectDlg::OnBnClickedBtnImageProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CStep4ProjectDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CStep4ProjectDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD_PROCESS, &CStep4ProjectDlg::OnBnClickedBtnThreadProcess)
END_MESSAGE_MAP()


// CStep4ProjectDlg 메시지 처리기

BOOL CStep4ProjectDlg::OnInitDialog()
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
	// TODO 변수 define
	MoveWindow(0, 0, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);


	// 좌측 다이얼로그
	m_pDlgImage = new CDlgImage(this);
	m_pDlgImage->Create(IDD_DLG_IMAGE, NULL);
	m_pDlgImage->ShowWindow(SW_SHOW);

	// 우측 다이얼로그
	m_pDlgImageResult = new CDlgImage(this);
	m_pDlgImageResult->Create(IDD_DLG_IMAGE, NULL);
	m_pDlgImageResult->MoveWindow(INNER_WINDOW_WIDTH, 0, INNER_WINDOW_WIDTH, INNER_WINDOW_HEIGHT);
	m_pDlgImageResult->ShowWindow(SW_SHOW);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStep4ProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStep4ProjectDlg::OnPaint()
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
HCURSOR CStep4ProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStep4ProjectDlg::OnBnClickedOk()
{
	/* Modal */
	//CDlgImage dlgImage;
	//dlgImage.DoModal();

	/* Non Modal */
	//m_pDlgImage->ShowWindow(SW_SHOW);

}


void CStep4ProjectDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pDlgImage)
		delete m_pDlgImage;

	if (m_pDlgImageResult)
		delete m_pDlgImageResult;
}

void CStep4ProjectDlg::PrintMsg(CString& strMsg)
{
	AfxMessageBox(strMsg);
}


void CStep4ProjectDlg::OnBnClickedBtnTest()
{
	if (m_pDlgImage == NULL) {
		cout << "[ERROR] " << "m_pDlgImage : NULL" << endl;
		return;
	}

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	int x, y = 0;

	memset(fm, COLOR_BLACK, INNER_WINDOW_WIDTH * INNER_WINDOW_HEIGHT);

	for (int k = 0; k < MAX_GEN_POINT; k++) {
		x = rand() % nWidth;
		y = rand() % nHeight;
		fm[y * nPitch + x] = rand() % (255 + 1);
	}

	int nIndex = 0;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > COPY_COLOR_THRESHOLD) {
				if (nIndex < MAX_GEN_POINT) {
					m_pDlgImageResult->m_ptCoordData[nIndex].x = i;
					m_pDlgImageResult->m_ptCoordData[nIndex].y = j;
					m_pDlgImageResult->m_nCoordDataSize = ++nIndex;
				}
			}

		}
	}
	cout << "defect count : " << nIndex << endl;

	m_pDlgImage->Invalidate();
	m_pDlgImageResult->Invalidate();
}


void CStep4ProjectDlg::OnBnClickedBtnImageProcess()
{
	CImageProcess process;

	steady_clock::time_point beginTime = steady_clock::now();
	int nRet = process.GetStarInfo(&(m_pDlgImage->m_Image), COPY_COLOR_THRESHOLD);
	steady_clock::time_point endTime = steady_clock::now();

	milliseconds millisec = duration_cast<milliseconds>(endTime - beginTime); // ms(milli seconds) : 1 / 1,000 sec
	if (millisec > steady_clock::duration::zero()) {
		cout << "Star count :" << nRet << ", process time : " << millisec.count() << " milli seconds" << endl;
	}
	else {
		microseconds microsec = duration_cast<microseconds>(endTime - beginTime); // us(micro seconds) : 1 / 1,000,000 sec
		if (microsec > steady_clock::duration::zero()) {
			cout << "Star count :" << nRet << ", process time : " << microsec.count() << " micro seconds" << endl;
		}
		else {
			nanoseconds nanosec = duration_cast<nanoseconds>(endTime - beginTime); // ns(nano seconds) : 1 / 10^9 sec
			cout << "Star count :" << nRet << ", process time : " << nanosec.count() << " nano seconds" << endl;
		}

	}
}


void CStep4ProjectDlg::OnBnClickedBtnMakePattern()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	memset(fm, COLOR_BLACK, INNER_WINDOW_WIDTH * INNER_WINDOW_HEIGHT);

	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand() % 256;
		}

	}

	m_pDlgImage->Invalidate();
}


void CStep4ProjectDlg::OnBnClickedBtnGetData()
{
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();

	int nTh = 0x80;
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << "Center : " << dCenterX << ", " << dCenterY << endl;
}

void ThreadProcess(CWnd* pParent, CRect rect, int* nRet)
{
	CStep4ProjectDlg* pWnd = (CStep4ProjectDlg*)pParent;
	if (pWnd) {
		*nRet = pWnd->ProcessImg(rect);
	}
}

void CStep4ProjectDlg::OnBnClickedBtnThreadProcess()
{
	steady_clock::time_point beginTime = steady_clock::now();

	int nWidth = m_pDlgImage->m_Image.GetWidth() / 2;
	int nHeight = m_pDlgImage->m_Image.GetHeight() / 2;
	CRect rect(0, 0, nWidth, nHeight);
	CRect rt[4];
	int nRet[4] = {0, };

	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(nWidth * (k % 2), nHeight * int(k / 2));
	}

	thread _thread0(ThreadProcess, this, rt[0], &nRet[0]);
	thread _thread1(ThreadProcess, this, rt[1], &nRet[1]);
	thread _thread2(ThreadProcess, this, rt[2], &nRet[2]);
	thread _thread3(ThreadProcess, this, rt[3], &nRet[3]);

	_thread0.join();
	_thread1.join();
	_thread2.join();
	_thread3.join();

	int nSum = 0;
	for (int k = 0; k < 4; k++)
		nSum += nRet[k];

	steady_clock::time_point endTime = steady_clock::now();

	microseconds microsec = duration_cast<microseconds>(endTime - beginTime); // us(micro seconds) : 1 / 1,000,000 sec
	if (microsec > steady_clock::duration::zero()) {
		cout << "Total star count :" << nSum << ", process time : " << microsec.count() << " micro seconds" << endl << endl;
	}
	else {
		nanoseconds nanosec = duration_cast<nanoseconds>(endTime - beginTime); // ns(nano seconds) : 1 / 10^9 sec
		cout << "Total star count :" << nSum << ", process time : " << nanosec.count() << " nano seconds" << endl << endl;
	}
}
mutex mtxProcessPrint;
int CStep4ProjectDlg::ProcessImg(CRect rect)
{
	CImageProcess process;

	steady_clock::time_point beginTime = steady_clock::now();
	int nRet = process.GetStarInfo(&(m_pDlgImage->m_Image), rect, COPY_COLOR_THRESHOLD);
	steady_clock::time_point endTime = steady_clock::now();

	microseconds microsec = duration_cast<microseconds>(endTime - beginTime); // us(micro seconds) : 1 / 1,000,000 sec
	if (microsec > steady_clock::duration::zero()) {
		mtxProcessPrint.lock();
		cout << "Star count :" << nRet << ", process time : " << microsec.count() << " micro seconds" << endl;
		mtxProcessPrint.unlock();
	}
	else {
		nanoseconds nanosec = duration_cast<nanoseconds>(endTime - beginTime); // ns(nano seconds) : 1 / 10^9 sec
		mtxProcessPrint.lock();
		cout << "Star count :" << nRet << ", process time : " << nanosec.count() << " nano seconds" << endl;
		mtxProcessPrint.unlock();
	}

	return nRet;
}
