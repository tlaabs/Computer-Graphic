// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "ImageProc.h"

// ------------------------------------------------------------------------------------------------
// Convert to gray-scale
// ------------------------------------------------------------------------------------------------

void ImageProc::convertToGray()
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			Gray = xClip(0.299*R + 0.587*G + 0.114*B);

			setPixel(x, y, Gray, Gray, Gray);
		}
	}
}

void ImageProc::convertToSepia()
{
	int  x, y;
	byte R, G, B;
	byte _R, _G, _B;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			_R = xClip(0.393*R + 0.769*G + 0.189*B);
			_G = xClip(0.349*R + 0.686*G + 0.168*B);
			_B = xClip(0.272*R + 0.534*G + 0.131*B);
			setPixel(x, y, _R, _G, _B);
		}
	}

}

void ImageProc::samplingBy2()
{
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[(m_iWidth*m_iHeight * 3) / 4];
	for (y = 0; y < m_iHeight / 2; y++)
	{
		for (x = 0; x < m_iWidth / 2; x++)
		{

			getPixel(x * 2, y * 2, R, G, B);
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 0] = R;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 1] = G;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
	m_iWidth /= 2;
	m_iHeight /= 2;
}

void ImageProc::quantization(int step)
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			for (int i = 0; i < 255 / step; i++) {
				if (step * i <= R && R < step * (i + 1)) {
					R = step * i;
				}
				if (step * i <= G && G < step * (i + 1)) {
					G = step * i;
				}
				if (step * i <= B && B < step * (i + 1)) {
					B = step * i;
				}
			}

			setPixel(x, y, R, G, B);
		}
	}
}