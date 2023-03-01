#pragma once

class CImageProcess
{
public:
	CImageProcess(void);
	~CImageProcess(void);

	int GetStarInfo(CImage* pImage, int nThreshHold = COPY_COLOR_THRESHOLD);
	int GetStarInfo(CImage* pImage, CRect rect, int nThreshHold = COPY_COLOR_THRESHOLD);
};

