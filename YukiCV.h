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
		/* �ҶȻ����� */
		enum GrayScaleMethod {
			GRAY_MODE_WEIGHT = 0,  /* ��Ȩ�����Ƽ�ʹ�ã� */
			GRAY_MODE_BEST,        /* ��ֵ�� */
			GRAY_MODE_AVERAGE,     /* ��ֵ�� */
			GRAY_MODE_PART_RED,    /* ������_RED */
			GRAY_MODE_PART_GREEN,  /* ������_GREEN */
			GRAY_MODE_PART_BLUE,   /* ������_BLUE */
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

		/* ��Χ�ضϺ��� */
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

		/* �������ݽṹ�� */
		/**********************************************************************************************
		* �Ҷ�ͼ��
		* g - gray �Ҷ�ֵ 0-255
		**********************************************************************************************/
		typedef struct PixelGray {
			unsigned char g;  // �Ҷ�ֵ 0-255

			PixelGray() : g(0) {}

			PixelGray(int const& g_);

			~PixelGray() {}

			PixelGray& operator = (const PixelGray other);

			PixelGray& operator = (int const& other);

		}PixelGray;


		/**********************************************************************************************
		* �Ҷ�ͼ��
		* g - gray  0-1.0 �ĻҶ�ֵ
		**********************************************************************************************/
		typedef struct PixelGrayFloat {
			float g;  // �Ҷ�ֵ 0-1.0

			PixelGrayFloat& operator = (const PixelGrayFloat other);

		}PixelGrayFloat;


		/**********************************************************************************************
		* RGBͼ��
		* r - red	 ��ɫͨ��ֵ��R��
		* g - green  ��ɫͨ��ֵ��G��
		* b - blue   ��ɫͨ��ֵ��B��
		**********************************************************************************************/
		typedef struct PixelRGB {
			unsigned char b;  // blue ��ɫͨ��ֵ��B��
			unsigned char r;  // red ��ɫͨ��ֵ��R��
			unsigned char g;  // green ��ɫͨ��ֵ��G��

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
		* RGBAͼ��
		* b - blue   ��ɫͨ��ֵ��B��
		* g - green  ��ɫͨ��ֵ��G��
		* r - red	 ��ɫͨ��ֵ��R��
		* a - alpha  ͸����ͨ��ֵ��A��
		**********************************************************************************************/
		typedef struct PixelRGBA {
			unsigned char b;  /* blue ��ɫͨ��ֵ��B�� */
			unsigned char g;  /* green ��ɫͨ��ֵ��G�� */
			unsigned char r;  /* red ��ɫͨ��ֵ��R�� */
			unsigned char a;  /* alpha ͸����ͨ��ֵ��A�� */

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
		* CMYKͼ��
		* c - cyan	   ��ɫͨ��ֵ��C��
		* m - magenta  ���ͨ��ֵ��M��
		* y - yellow   ��ɫͨ��ֵ��Y��
		* k - black    ��ɫͨ��ֵ��K��
		**********************************************************************************************/
		typedef struct PixelCMYK {
			unsigned char c;  /* cyan ��ɫͨ��ֵ��C�� */
			unsigned char m;  /* magenta ���ͨ��ֵ��M�� */
			unsigned char y;  /* yellow ��ɫͨ��ֵ��Y�� */
			unsigned char k;  /* black ��ɫͨ��ֵ��K�� */
		}PixelCMYK;


		/**********************************************************************************************
		* HSVͼ�� / HSL
		* h - hue ɫ�ࣨH��
		* s - saturation ���Ͷȣ�S��
		* v - value ���ȣ�V��/��L��
		**********************************************************************************************/
		typedef struct PixelHSV {
			unsigned char h;  /* hue ɫ�ࣨH�� */
			unsigned char s;  /* saturation ���Ͷȣ�S�� */
			unsigned char v;  /* value ���ȣ�V��/��L�� */
		}PixelHSV;


		/**********************************************************************************************
		* YUVͼ��
		**********************************************************************************************/
		typedef struct PixelYUV {
			unsigned char y;  // ���ȷ���
			unsigned char u;  // ɫ�����U
			unsigned char v;  // ɫ�����V
		}PixelYUV;

		/**********************************************************************************************
		* XYZͼ��
		**********************************************************************************************/
		typedef struct PixelXYZ {
			unsigned char x;  // ������X���ϵ�ֵ
			unsigned char w;  // ������Y���ϵ�ֵ
			unsigned char z;  // ������Z���ϵ�ֵ��ͨ��Ϊ��ɫ�����ͶȻ����ȣ�
		}PixelXYZ;


		/**********************************************************************************************
		* HLSͼ��
		**********************************************************************************************/
		typedef struct PixelHLS {
			unsigned char h;  // ɫ������
			unsigned char l;  // �Ӻ�ɫ����ɫ����ɫ������ȡֵ��Χͨ��Ϊ -128~127
			unsigned char s;  // ����ɫ����ɫ����ɫ������ȡֵ��Χͨ��Ϊ -128~127
		}PixelHLS;


		/**********************************************************************************************
		* Labͼ��
		**********************************************************************************************/
		typedef struct PixelLab {
			unsigned char l;  // ���ȷ�����ȡֵ��Χͨ��Ϊ 0-100
			unsigned char a;  // �Ӻ�ɫ����ɫ����ɫ������ȡֵ��Χͨ��Ϊ -128~127
			unsigned char b;  // ����ɫ����ɫ����ɫ������ȡֵ��Χͨ��Ϊ -128~127
		}PixelLab;

		/* ��ά���� */
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

		/* ������ */
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


		/* �ļ�����* /
		/* ���뺯�� */
		/* ͼ����뺯�� | RGBA edition */
		void imageRead(string const& path, Image<PixelRGBA>& InputImage);

		/* ͼ����뺯�� | RGB edition */
		void imageRead(string const& path, Image<PixelRGB>& InputImage);

		/* ���溯�� */
		/* ͼ�񱣴溯�� | RGBA edition */
		void imageWrite(string const& path, Image<PixelRGBA> const& OutputImage);

		/* ͼ�񱣴溯�� | RGB edition */
		void imageWrite(string const& path, Image<PixelRGB> const& OutputImage);


		// ͼ�����

		typedef struct GrayScaleOption {
			GrayScaleMethod mode;

			GrayScaleOption(GrayScaleMethod const& mode_ = GRAY_MODE_WEIGHT) : mode(mode_) {};

		}GrayScaleOption;

		/******************************************************************************************
		* ��ɫͼת�Ҷ�ͼ | RGBA edition
		* 0 GRAY_MODE_WEIGHT      ��Ȩ��(�Ƽ�)
		* 1 GRAY_MODE_BEST        ��ֵ��
		* 2 GRAY_MODE_AVERAGE     ��ֵ��
		* 3 GRAY_MODE_PART_RED    ������_RED
		* 4 GRAY_MODE_PART_GREEN  ������_GREEN
		* 5 GRAY_MODE_PART_BLUE   ������_BLUE
		******************************************************************************************/
		Image<PixelRGBA> transColorGray(Image<PixelRGBA> const& InputImage, GrayScaleMethod const& mode = GRAY_MODE_WEIGHT);
		
		Image<PixelRGBA> transColorGray(Image<PixelRGBA> const& InputImage, GrayScaleOption const& GOption);


		/******************************************************************************************
		* ��ɫͼת�Ҷ�ͼ | RGB edition
		* 0 GRAY_MODE_WEIGHT      ��Ȩ��(�Ƽ�)
		* 1 GRAY_MODE_BEST        ��ֵ��
		* 2 GRAY_MODE_AVERAGE     ��ֵ��
		* 3 GRAY_MODE_PART_RED    ������_RED
		* 4 GRAY_MODE_PART_GREEN  ������_GREEN
		* 5 GRAY_MODE_PART_BLUE   ������_BLUE
		******************************************************************************************/
		Image<PixelRGB> transColorGray(Image<PixelRGB> const& inputImage, GrayScaleMethod const& mode = GRAY_MODE_WEIGHT);

		Image<PixelRGB> transColorGray(Image<PixelRGB> const& InputImage, GrayScaleOption const& GOption);

		/* ��ֵͼ���Զ�����ֵ���� | RGBA edition  */
		Image<PixelRGBA> transColorBWTHR(Image<PixelRGBA> const& InputImage, unsigned char const& Threshold, bool const& IsGray = false);

		/* ��ֵͼ���Զ�����ֵ���� | RGB edition  */
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
		
		/* ����ͼ�����ͨ���ľ�ֵ */
		vector<double> comptAverange(Image<PixelRGBA> const& InputImage);

		/* ����ͼ�����ͨ���ķ��� */
		vector<double> comptVariance(Image<PixelRGBA> const& InputImage);

		/* ���������̬�ֲ��ľ���� */
		Image<double> comptGaussianKernel(double const& mu, double const& sigma2, SizeType const& size = 5);

		/* ����� */
		
		
		typedef MatrixBase<double> Mat;

		typedef struct ConvOption {
			Image<double> kernel;
			SizeType stride;
			BorderOption BOption;

			ConvOption(Image<double> const& kernel_, SizeType const& stride_ = 1, BorderMethod const& mode = BORDER_REFLECT_101) : kernel(kernel_), stride(stride_), BOption(kernel_.rows() / 2, mode) {}

		}ConvOption;

		/* ��˹ģ�� */
		Image<PixelRGBA> blurGaussian(Image<PixelRGBA> const& InputImage, SizeType const& kernelSize = 5);

		/* ������� */
		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage, ConvOption const& COption);

		Image<double> convolute(Image<double> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		//Image<PixelRGB> convolute(Image<PixelRGB> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);

		//Image<double> convolute(Image<double> const& InputImage, Image<double> const& kernel, SizeType const& stride = 1, SizeType const& padding = 0);


		/* �ػ����� */
		Image<double> pool(Image<double> const& InputImage, SizeType const& kernelSize = 2, PoolMethod const& = MAX_POOL);

		// ����ͼƬ(˫���Բ�ֵ��)(�Ƽ�ʹ��)
		Image<PixelRGBA> resize(Image<PixelRGBA> const& im, SizeType const& NewHeight, SizeType const& NewWidth, ResizeMethod const& RMethod = BILINEAR_INTERPOLAYION);

	}

}

#endif // !___YUKI_C_V_H__