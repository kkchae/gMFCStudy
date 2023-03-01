// DlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "Step4Project.h"
#include "afxdialogex.h"
#include "DlgImage.h"
#include "Step4ProjectDlg.h"

// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_IMAGE, pParent)
	, m_pParentWnd(pParent)
	, m_nCoordDataSize(0)
{
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgImage::OnBnClickedOk)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


void CDlgImage::OnBnClickedOk()
{
	/*CStep4ProjectDlg* pDlg = (CStep4ProjectDlg*)m_pParentWnd;
	if (pDlg) {
		CString strMsg("Hello, I'm child dialog");
		pDlg->PrintMsg(strMsg);
	}*/
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 640, 480);
	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}

	DrawData(&dc);
}

void CDlgImage::InitImage(void)
{
	int nWidth = 640;
	int nHeight = 480;
	int nBpp = 8;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nPitch = m_Image.GetPitch();
	//cout << _T("nPitch =") <<  nPitch << endl;

	int nColor = RGB(255, 255, 255); //RGB(0, 0, 0);
	memset(fm, nColor, sizeof(unsigned char) * nWidth * nHeight);
}

void CDlgImage::DrawData(CDC* pDC)
{
	if (pDC) {
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // Red
		CPen* oldPen = pDC->SelectObject(&pen);

		CRect rect;
		for (int i = 0; i < m_nCoordDataSize; i++) {
			rect.SetRect(m_ptCoordData[i], m_ptCoordData[i]);
			rect.InflateRect(3, 3);
			pDC->Ellipse(rect);
		}

		pDC->SelectObject(oldPen);
	}
}
