#pragma once
#ifndef ___FILE_LIB_H__
#define ___FILE_LIB_H__

#include <iostream>
#include <string>
#include <fstream>

using std::string;

namespace yuki {
	namespace file {
		// 获取文件后缀名
		string GetExta(string const& filename);

		/* BMP文件头结构体 */
		typedef struct BitmapFileHeader {
			/* bmp文件头的信息，有#的是重点!!*/
			unsigned short  bfType;		  /* 0x4D42，即BM字符串，表明是bmp格式文件 */
			unsigned int    bfSize;		  /* ###总的bmp文件大小 以字节为单位 */
			unsigned short  bfReserved1;  /* 保留，必须设置为0 */
			unsigned short  bfReserved2;  /* 保留，必须设置为0 */
			unsigned int    bfOffBits;    /* ###总的bmp头部的大小（包括位图信息头），即到像素数据的偏移 */

			BitmapFileHeader(unsigned int const& bfSize_ = 54) :
				bfType(0x4D42),
				bfSize(bfSize_),
				bfReserved1(0),
				bfReserved2(0),
				bfOffBits(54) {}

		}BitmapFileHeader;

		/* BMP位图信息头 */
		typedef struct BitmapInfoHeader {
			unsigned int    biSize;             /* 位图信息头的大小 */
			unsigned int    biWidth;            /* ###图像的宽 */
			unsigned int    biHeight;           /* ###图像的高 */
			unsigned short  biPlanes;           /* 颜色平面数，即调色盘数，恒等于1 */
			unsigned short  biBitCount;         /* ###图片颜色的位数，一般为32 */
			unsigned int    biCompression;      /* 说明图象数据压缩的类型，0为不压缩 */
			unsigned int    biSizeIMAGE;        /* 像素数据所占大小，因为使用BI_RGB，所以设置为0 */
			unsigned int    biXPelsPerMeter;    /* 说明水平分辨率，缺省为0 */
			unsigned int    biYPelsPerMeter;    /* 说明垂直分辨率，缺省为0 */
			unsigned int    biClrUsed;          /* 说明本位图实际使用调色盘的颜色索引数，0表示全部 */
			unsigned int    biClrImportant;     /* 说明本位图重要调色盘的颜色索引数，0表示全都重要 */

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
