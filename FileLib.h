#pragma once
#ifndef ___FILE_LIB_H__
#define ___FILE_LIB_H__

#include <iostream>
#include <string>
#include <fstream>

using std::string;

namespace yuki {
	namespace file {
		// ��ȡ�ļ���׺��
		string GetExta(string const& filename);

		/* BMP�ļ�ͷ�ṹ�� */
		typedef struct BitmapFileHeader {
			/* bmp�ļ�ͷ����Ϣ����#�����ص�!!*/
			unsigned short  bfType;		  /* 0x4D42����BM�ַ�����������bmp��ʽ�ļ� */
			unsigned int    bfSize;		  /* ###�ܵ�bmp�ļ���С ���ֽ�Ϊ��λ */
			unsigned short  bfReserved1;  /* ��������������Ϊ0 */
			unsigned short  bfReserved2;  /* ��������������Ϊ0 */
			unsigned int    bfOffBits;    /* ###�ܵ�bmpͷ���Ĵ�С������λͼ��Ϣͷ���������������ݵ�ƫ�� */

			BitmapFileHeader(unsigned int const& bfSize_ = 54) :
				bfType(0x4D42),
				bfSize(bfSize_),
				bfReserved1(0),
				bfReserved2(0),
				bfOffBits(54) {}

		}BitmapFileHeader;

		/* BMPλͼ��Ϣͷ */
		typedef struct BitmapInfoHeader {
			unsigned int    biSize;             /* λͼ��Ϣͷ�Ĵ�С */
			unsigned int    biWidth;            /* ###ͼ��Ŀ� */
			unsigned int    biHeight;           /* ###ͼ��ĸ� */
			unsigned short  biPlanes;           /* ��ɫƽ����������ɫ�����������1 */
			unsigned short  biBitCount;         /* ###ͼƬ��ɫ��λ����һ��Ϊ32 */
			unsigned int    biCompression;      /* ˵��ͼ������ѹ�������ͣ�0Ϊ��ѹ�� */
			unsigned int    biSizeIMAGE;        /* ����������ռ��С����Ϊʹ��BI_RGB����������Ϊ0 */
			unsigned int    biXPelsPerMeter;    /* ˵��ˮƽ�ֱ��ʣ�ȱʡΪ0 */
			unsigned int    biYPelsPerMeter;    /* ˵����ֱ�ֱ��ʣ�ȱʡΪ0 */
			unsigned int    biClrUsed;          /* ˵����λͼʵ��ʹ�õ�ɫ�̵���ɫ��������0��ʾȫ�� */
			unsigned int    biClrImportant;     /* ˵����λͼ��Ҫ��ɫ�̵���ɫ��������0��ʾȫ����Ҫ */

			BitmapInfoHeader(unsigned int const& biWidth_ = 0, unsigned int const& biHeight_ = 0, unsigned short const& biBitCount_ = 32) :
				biSize(40),
				biWidth(biWidth_),
				biHeight(biHeight_),
				biPlanes(1),
				biBitCount(biBitCount_),
				biCompression(0),
				biSizeIMAGE(0),
				biXPelsPerMeter(0),
				biYPelsPerMeter(0),
				biClrUsed(0),
				biClrImportant(0) {}

		}BitmapInfoHeader;


	}
	
}

#endif // !___FILE_LIB_H__
