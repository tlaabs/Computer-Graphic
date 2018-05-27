// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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

void ImageProc::kuwahara() {    // 5*5 Mask, 3*3 block
	int x, y, count = 9;
	int vr = 0, vg = 0, vb = 0;
	int sumr = 0, sumg = 0, sumb = 0; //RGB SUM
	double vrr = 0, vgg = 0, vbb = 0; //분산
	double minr, ming, minb;
	double avg_r, avg_g, avg_b; // average r g b

	byte R, G, B;
	byte *temp = new byte[m_iHeight*m_iWidth * 3];

	for (y = 2; y < m_iHeight - 2; y++)
	{
		for (x = 2; x < m_iWidth - 2; x++)
		{
			minr = 9999999; ming = 9999999; minb = 9999999;
			for (int q = 0; q < 2; q++)
			{
				for (int w = 0; w < 2; w++)
				{
					sumr = 0; sumg = 0; sumb = 0;
					vr = 0; vg = 0; vb = 0;

					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							getPixel(x - 2 + l + q * 2, y - 2 + k + w * 2, R, G, B);
				
							vr += R * R; vg += G * G; vb += B * B;
							sumr += R; sumg += G; sumb += B;
						}
					}
					//V(X) = E(X^2) - E(X)^2
					vrr = (double)(vr / count) - ((double)(sumr / count)*(double)(sumr / count));
					vgg = (double)(vg / count) - ((double)(sumg / count)*(double)(sumg / count));
					vbb = (double)(vb / count) - ((double)(sumb / count)*(double)(sumb / count));
					
					//분산값이 최소일 때만 RGB의 평균값을 계산.
					if (vrr < minr) {
						minr = vrr;
						avg_r = sumr / count;
					}
					if (vgg < ming) {
						ming = vgg;
						avg_g = sumg / count;
					}
					if (vbb < minb) {
						minb = vbb;
						avg_b = sumb / count;
					}
				}
			}
			temp[getAddr(x, y) + 0] = xClip(avg_r);
			temp[getAddr(x, y) + 1] = xClip(avg_g);
			temp[getAddr(x, y) + 2] = xClip(avg_b);
		}
	}
	m_pRGB = temp;
}