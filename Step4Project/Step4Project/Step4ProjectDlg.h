
// Step4ProjectDlg.h: 헤더 파일
//

#pragma once
#include "DlgImage.h"

// CStep4ProjectDlg 대화 상자
class CStep4ProjectDlg : public CDialogEx
{
private:
	CDlgImage* m_pDlgImage;
	CDlgImage* m_pDlgImageResult;

// 생성입니다.
public:
	CStep4ProjectDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STEP4PROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	void PrintMsg(CString& strMsg);
	afx_msg void OnBnClickedBtnTest();
	afx_msg void OnBnClickedBtnImageProcess();
	afx_msg void OnBnClickedBtnMakePattern();
	afx_msg void OnBnClickedBtnGetData();
	afx_msg void OnBnClickedBtnThreadProcess();
	int ProcessImg(CRect rect);
};
