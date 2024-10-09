#pragma once
#ifndef ___YUKI_C_V_H__
#define ___YUKI_C_V_H__

#include "YukiMatrixBase.h"
#include "FileLib.h"
#include "YukiDefault.h"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using std::string;
using std::vector;


namespace yuki {
	namespace cv {
		/* 灰度化方法 */
		enum GrayScaleMethod {
			GRAY_MODE_WEIGHT = 0,  /* 加权法（推荐使用） */
			GRAY_MODE_BEST,        /* 最值法 */
			GRAY_MODE_AVERAGE,     /* 均值法 */
			GRAY_MODE_PART_RED,    /* 分量法_RED */
			GRAY_MODE_PART_GREEN,  /* 分量法_GREEN */
			GRAY_MODE_PART_BLUE,   /* 分量法_BLUE */
		};

		enum AdaptiveMethod {
			ADAPTIVE_GAUSSIAN_WEIGHT = 0,
			ADAPTIVE_AVERANGE
		};

		enum BorderMethod {
			BORDER_REFLECT_101 = 0,
			BORDER_CONSTANT,
			BORDER_COMPRESS
		};

		enum PoolMethod {
			MAX_POOL = 0
		};

		enum ResizeMethod {
			BILINEAR_INTERPOLAYION = 0
		};

		/* 范围截断函数 */
		template<typename T>
		T truncate(T const& src, T const& st, T const& en) {
			if (src > en) {
				return en;
			}
			if (src < st) {
				return st;
			}
			return src;
		}

		/* 像素数据结构体 */
		/**********************************************************************************************
		* 灰度图像
		* g - gray 灰度值 0-255
		**********************************************************************************************/
		typedef struct PixelGray {
			unsigned char g;  // 灰度值 0-255

			PixelGray() : g(0) {}

			PixelGray(int const& g_);

			~PixelGray() {}

			PixelGray& operator = (const PixelGray other);

			PixelGray& operator = (int const& other);

		}PixelGray;


		/**********************************************************************************************
		* 灰度图像
		* g - gray  0-1.0 的灰度值
		**********************************************************************************************/
		typedef struct PixelGrayFloat {
			float g;  // 灰度值 0-1.0

			PixelGrayFloat& operator = (const PixelGrayFloat other);

		}PixelGrayFloat;


		/**********************************************************************************************
		* RGB图像
		* r - red	 红色通道值（R）
		* g - green  绿色通道值（G）
		* b - blue   蓝色通道值（B）
		**********************************************************************************************/
		typedef struct PixelRGB {
			unsigned char b;  // blue 蓝色通道值（B）
			unsigned char r;  // red 红色通道值（R）
			unsigned char g;  // green 绿色通道值（G）

			PixelRGB(int const& b_ = 0, int const& g_ = 0, int const& r_ = 0);

			PixelRGB(initializer_list<int> const& initList);

			friend ostream& operator << (ostream& os, PixelRGB const& RGB) {
				os << '[' << static_cast<int>(RGB.r) << ' ' << static_cast<int>(RGB.g) << ' ' << static_cast<int>(RGB.b) << ']';
				return os;
			}

			bool operator > (int const& a) const;

			bool operator >= (int const& a) const;

			bool operator < (int const& a) const;

			bool operator <= (int const& a) const;
		}PixelRGB;


		/**********************************************************************************************
		* RGBA图像
		* b - blue   蓝色通道值（B）
		* g - green  绿色通道值（G）
		* r - red	 红色通道值（R）
		* a - alpha  透明度通道值（A）
		**********************************************************************************************/
		typedef struct PixelRGBA {
			unsigned char b;  /* blue 蓝色通道值（B） */
			unsigned char g;  /* green 绿色通道值（G） */
			unsigned char r;  /* red 红色通道值（R） */
			unsigned char a;  /* alpha 透明度通道值（A） */

			PixelRGBA(int const& b_ = 0, int const& g_ = 0, int const& r_ = 0, int const& a_ = 0);
			PixelRGBA(PixelRGBA const& other) :
				b(other.b), g(other.g), r(other.r), a(other.a) {}
			PixelRGBA(initializer_list<int> const& InitList);

			friend ostream& operator << (ostream& os, PixelRGBA const& RGBA) {
				os << '[' << static_cast<int>(RGBA.r) << ' ' << static_cast<int>(RGBA.g) << ' ' << static_cast<int>(RGBA.b) << ' ' << static_cast<int>(RGBA.a) << ']';
				return os;
			}

			bool operator > (int const& a) const;

			bool operator >= (int const& a) const;

			bool operator < (int const& a) const;

			bool operator <= (int const& a) const;

			PixelRGBA& operator = (PixelRGBA const& other) {
				b = other.b;
				g = other.g;
				r = other.r;
				a = other.a;
				return *this;
			}

			PixelRGBA& operator = (int const& other);
		}PixelRGBA;


		/**********************************************************************************************
		* CMYK图像
		* c - cyan	   青色通道值（C）
		* m - magenta  洋红通道值（M）
		* y - yellow   黄色通道值（Y）
		* k - black    黑色通道值（K）
		**********************************************************************************************/
		typedef struct PixelCMYK {
			unsigned char c;  /* cyan 青色通道值（C） */
			unsigned char m;  /* magenta 洋红通道值（M） */
			unsigned char y;  /* yellow 黄色通道值（Y） */
			unsigned char k;  /* black 黑色通道值（K） */
		}PixelCMYK;


		/**********************************************************************************************
		* HSV图像 / HSL
		* h - hue 色相（H）
		* s - saturation 饱和度（S）
		* v - value 亮度（V）/（L）
		**********************************************************************************************/
		typedef struct PixelHSV {
			unsigned char h;  /* hue 色相（H） */
			unsigned char s;  /* saturation 饱和度（S） */
			unsigned char v;  /* value 亮度（V）/（L） */
		}PixelHSV;


		/**********************************************************************************************
		* YUV图像
		**********************************************************************************************/
		typedef struct PixelYUV {
			unsigned char y;  // 亮度分量
			unsigned char u;  // 色差分量U
			unsigned char v;  // 色差分量V
		}PixelYUV;

		/**********************************************************************************************
		* XYZ图像
		**********************************************************************************************/
		typedef struct PixelXYZ {
			unsigned char x;  // 像素在X轴上的值
			unsigned char w;  // 像素在Y轴上的值
			unsigned char z;  // 像素在Z轴上的值（通常为颜色不饱和度或亮度）
		}PixelXYZ;


		/**********************************************************************************************
		* HLS图像
		**********************************************************************************************/
		typedef struct PixelHLS {
			unsigned char h;  // 色调分量
			unsigned char l;  // 从红色到绿色的颜色分量，取值范围通常为 -128~127
			unsigned char s;  // 从蓝色到黄色的颜色分量，取值范围通常为 -128~127
		}PixelHLS;


		/**********************************************************************************************
		* Lab图像
		**********************************************************************************************/
		typedef struct PixelLab {
			unsigned char l;  // 亮度分量，取值范围通常为 0-100
			unsigned char a;  // 从红色到绿色的颜色分量，取值范围通常为 -128~127
			unsigned char b;  // 从蓝色到黄色的颜色分量，取值范围通常为 -128~127
		}PixelLab;

		/* 二维点类 */
		typedef struct point {
			using ElemType = SizeType;
			ElemType row;
			ElemType col;

			point(ElemType const& row_ = 0, ElemType const& col_ = 0) {
				this->row = row_;
				this->col = col_;
			}

			~point() {}

		}point;

		template<class ElemType = PixelRGBA>
		using Image = MatrixBase<ElemType>;

		/* 矩形类 */
		typedef struct rect {
			using SizeType = int;
			SizeType row_st;
			SizeType row_en;
			SizeType col_st;
			SizeType col_en;

			rect(SizeType const& row_st_ = 0, SizeType const& row_en_ = 0, SizeType const& col_st_ = 0, SizeType const& col_en_ = 0) {
				if (row_st_ > row_en_) {
					this->row_st = row_st_;
					this->row_en = row_en_;
				} else {
					this->row_st = row_en_;
					this->row_en = row_st_;
				}
				if (col_st_ > col_en_) {
					this->col_st = col_st_;
					this->col_en = col_en_;
				} else {
					this->col_st = col_en_;
					this->col_en = col_st_;
				}
			}

			rect(const point& vertex1, const point& vertex2) {
				this->row_st = vertex1.row < vertex2.row ? vertex1.row : vertex2.row;
				this->row_en = vertex1.row > vertex2.row ? vertex1.row : vertex2.row;
				this->col_st = vertex1.col < vertex2.col ? vertex1.col : vertex2.col;
				this->col_en = vertex1.col > vertex2.col ? vertex1.col : vertex2.col;
			}

			~rect() {}

		}rect;


		/* 文件操作* /
		/* 读入函数 */
		/* 图像读入函数 | RGBA edition */
		void imageRead(string const& path, Image<PixelRGBA>& InputImage);

		/* 图像读入函数 | RGB edition */
		void imageRead(string const& path, Image<PixelRGB>& InputImage);

		/* 保存函数 */
		/* 图像保存函数 | RGBA edition */
		void imageWrite(string const& path, Image<PixelRGBA> const& OutputImage);

		/* 图像保存函数 | RGB edition */
		void imageWrite(string const& path, Image<PixelRGB> const& OutputImage);


		// 图像操作

		typedef struct GrayScaleOption {
			GrayScaleMethod mode;

			GrayScaleOption(GrayScaleMethod const& mode_ = GRAY_MODE_WEIGHT) : mode(mode_) {};

		}GrayScaleOption;

		/******************************************************************************************
		* 彩色图转灰度图 | RGBA edition
		* 0 GRAY_MODE_WEIGHT      加权法(推荐)
		* 1 GRAY_MODE_BEST        最值法
		* 2 GRAY_MODE_AVERAGE     均值法
		* 3 GRAY_MODE_PART_RED    分量法_RED
		* 4 GRAY_MODE_PART_GREEN  分量法_GREEN
		* 5 GRAY_MODE_PART_BLUE   分量法_BLUE
		******************************************************************************************/
		Image<PixelRGBA> transColorGray(Image<PixelRGBA> const& InputImage, GrayScaleMethod const& mode = GRAY_MODE_WEIGHT);
		
		Image<PixelRGBA> transColorGray(Image<PixelRGBA> const& InputImage, GrayScaleOption const& GOption);


		/******************************************************************************************
		* 彩色图转灰度图 | RGB edition
		* 0 GRAY_MODE_WEIGHT      加权法(推荐)
		* 1 GRAY_MODE_BEST        最值法
		* 2 GRAY_MODE_AVERAGE     均值法
		* 3 GRAY_MODE_PART_RED    分量法_RED
		* 4 GRAY_MODE_PART_GREEN  分量法_GREEN
		* 5 GRAY_MODE_PART_BLUE   分量法_BLUE
		******************************************************************************************/
		Image<PixelRGB> transColorGray(Image<PixelRGB> const& inputImage, GrayScaleMethod const& mode = GRAY_MODE_WEIGHT);

		Image<PixelRGB> transColorGray(Image<PixelRGB> const& InputImage, GrayScaleOption const& GOption);

		/* 二值图（自定义阈值法） | RGBA edition  */
		Image<PixelRGBA> transColorBWTHR(Image<PixelRGBA> const& InputImage, unsigned char const& Threshold, bool const& IsGray = false);

		/* 二值图（自定义阈值法） | RGB edition  */
		Image<PixelRGB> transColorBWTHR(Image<PixelRGB> const& InputImage, unsigned char const& Threshold, bool const& IsGray = false);

		Image<PixelRGBA> transColorBWOSTU(Image<PixelRGBA> const& InputImage, bool const& IsGray = false);



		typedef struct BorderOption {
			SizeType padding;
			BorderMethod mode;
			unsigned char sample;

			BorderOption(SizeType const& padding_ = 0, BorderMethod const& mode_ = BORDER_CONSTANT, unsigned char const& sample_ = 0) :
				padding(padding_), mode(mode_), sample(sample_) {}

		}BorderOption;

		Image<PixelRGBA> transColorBWAdaptive(Image<PixelRGBA> const& InputImage, SizeType const& SideLength = 5, bool const& IsGray = false,
			GrayScaleMethod const& GMethod = GRAY_MODE_WEIGHT,
			BorderMethod const& BMethod = BORDER_CONSTANT, unsigned char const& sample = 0,
			AdaptiveMethod const& AMethod = ADAPTIVE_AVERANGE);

		//Image<PixelRGBA> TfmColorBWAdaptive(Image<PixelRGBA> const& InputImage, SizeType const& SideLength = 5, bool const& IsGray = false,
		//	GrayScaleOption const& GOption = GrayScaleOption(GRAY_MODE_WEIGHT), BorderOption const& BOption = BorderOption(5 / 2, BORDER_CONSTANT, 0));

		template <typename T>
		Image<T> transShapeBoeder(Image<T> const& InputImage, SizeType const& padding = 3, BorderMethod const& mode = BORDER_REFLECT_101, unsigned char const& sample = 0);

		Image<PixelRGBA> transShapeBoeder(Image<PixelRGBA> const& InputImage, BorderOption const& BOption = BorderOption(3, BORDER_REFLECT_101 , 0));
		
		/* 计算图像各个通道的均值 */
		vector<double> comptAverange(Image<PixelRGBA> const& InputImage);

		/* 计算图像各个通道的方差 */
		vector<double> comptVariance(Image<PixelRGBA> const& InputImage);

		/* 计算服从正态分布的卷积核 */
		Image<double> comptGaussianKernel(double const& mu, double const& sigma2, SizeType const& size = 5);

		/* 卷积核 */
		
		
		typedef MatrixBase<double> Mat;

		typedef struct ConvOption {
			Image<double> kernel;
			SizeType stride;
			BorderOption BOption;

			ConvOption(Image<double> const& kernel_, SizeType const& stride_ = 1, BorderMethod const& mode = BORDER_REFLECT_101) : kernel(kernel_), stride(stride_), BOption(kernel_.rows() / 2, mode) {}

		}ConvOption;

		/* 高斯模糊 */
		Image<PixelRGBA> blurGaussian(Image<PixelRGBA> const& InputImage, SizeType const& kernelSize = 5);

		/* 卷积操作 */
		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage, ConvOption const& COption);

		Image<double> convolute(Image<double> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		//Image<PixelRGB> convolute(Image<PixelRGB> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		//Image<double> convolute(Image<double> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);


		/* 池化操作 */
		Image<double> pool(Image<double> const& InputImage, SizeType const& kernelSize = 2, PoolMethod const& = MAX_POOL);

		// 缩放图片(双线性插值法)(推荐使用)
		Image<PixelRGBA> resize(Image<PixelRGBA> const& im, SizeType const& NewHeight, SizeType const& NewWidth, ResizeMethod const& RMethod = BILINEAR_INTERPOLAYION);

	}

}

#endif // !___YUKI_C_V_H__