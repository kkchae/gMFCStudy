#include "pch.h"
#include "ImageProcess.h"


CImageProcess::CImageProcess(void)
{
}

CImageProcess::~CImageProcess(void)
{
}

int CImageProcess::GetStarInfo(CImage* pImage, int nThreshHold)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	if (fm)
	{
		int nWidth = pImage->GetWidth();
		int nHeight = pImage->GetHeight();
		int nPitch = pImage->GetPitch();

		int nIndex = 0;
		for (int k = 0; k < nWidth * nHeight; k++)
		{
			if (fm[k] > nThreshHold) {
				nIndex++;
			}
		}
		return nIndex;
	}
	return -1;
}

int CImageProcess::GetStarInfo(CImage* pImage, CRect rect, int nThreshHold)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	int nSum = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nThreshHold) {
				nSum++;
			}
		}
	}
	return nSum;
}
