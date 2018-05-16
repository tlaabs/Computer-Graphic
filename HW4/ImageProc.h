// ------------------------------------------------------------------------------------------------
// Image class Header file
// ------------------------------------------------------------------------------------------------


#ifndef __IMAGEPROC_H
#define __IMAGEPROC_H

#include "Image.h"

// ------------------------------------------------------------------------------------------------
// ImageProc class
// ------------------------------------------------------------------------------------------------

class ImageProc : public Image
{
private:
	byte xClip(double x)
	{
		if (x < 0) return 0;
		if (x > 255) return 255;
		return (byte)x;
	}


public:
	// pixel processing
	void convertToGray();
	void convertToSepia();

	// sampling & quantization
	void samplingBy2();
	void quantization(int step);
};

#endif