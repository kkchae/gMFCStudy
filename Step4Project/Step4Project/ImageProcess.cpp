#include "pch.h"
#include "ImageProcess.h"


CImageProcess::CImageProcess(void)
{
}

CImageProcess::~CImageProcess(void)
{
}

int CImageProcess::GetStarInfo(CImage* pImage, int nThreshHold /*= COPY_COLOR_THRESHOLD*/)
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