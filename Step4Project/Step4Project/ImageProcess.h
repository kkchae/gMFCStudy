#pragma once

class CImageProcess
{
public:
	CImageProcess(void);
	~CImageProcess(void);

	int GetStarInfo(CImage* pImage, int nThreshHold = COPY_COLOR_THRESHOLD);
};

