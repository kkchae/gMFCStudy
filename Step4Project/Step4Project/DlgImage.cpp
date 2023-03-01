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
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기


void CDlgImage::OnBnClickedOk()
{
	CStep4ProjectDlg* pDlg = (CStep4ProjectDlg*)m_pParentWnd;
	if (pDlg) {
		CString strMsg("Hello, I'm child dialog");
		pDlg->PrintMsg(strMsg);
	}
}
