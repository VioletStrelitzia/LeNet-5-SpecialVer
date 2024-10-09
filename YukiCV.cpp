#include "YukiCV.h"

namespace yuki {


	namespace cv {
		double const PI = 3.141592653;

		/* PixelGray */
		PixelGray::PixelGray(int const& g_) {
			if (g_ > 255) {
				g = 255;
			}
			else if (g_ < 0) {
				g = 0;
			}
			else {
				g = g_;
			}
		}

		PixelGray& PixelGray::operator = (const PixelGray other) {
			g = other.g;
			return *this;
		}

		PixelGray& PixelGray::operator = (int const& other) {
			if (other > 255) {
				g = 255;
			}
			else if (other < 0) {
				g = 0;
			}
			else {
				g = other;
			}
			return *this;
		}

		/* PixelGrayFloat */
		PixelGrayFloat& PixelGrayFloat::operator = (const PixelGrayFloat other) {
			g = other.g;
			return *this;
		}

		/* PixelRGB */
		PixelRGB::PixelRGB(int const& b_, int const& g_, int const& r_) {
			b = truncate<int>(b_, 0, 255);
			g = truncate<int>(g_, 0, 255);
			r = truncate<int>(r_, 0, 255);
		}

		PixelRGB::PixelRGB(initializer_list<int> const& initList) : b(0), g(0), r(0) {
			int i = 0;
			for (auto it = initList.begin(); i < 3 && it != initList.end(); ++i, ++it) {
				switch (i) {
				case 0:
					b = (unsigned char)truncate<int>(*it, 0, 255);
					break;
				case 1:
					g = (unsigned char)truncate<int>(*it, 0, 255);
					break;
				case 2:
					r = (unsigned char)truncate<int>(*it, 0, 255);
					break;
				default:
					break;
				}
			}
		}

		bool PixelRGB::operator > (int const& a) const {
			return r > a && g > a && b > a;
		}

		bool PixelRGB::operator >= (int const& a) const {
			return r >= a && g >= a && b >= a;
		}

		bool PixelRGB::operator < (int const& a) const {
			return r < a && g < a && b < a;
		}

		bool PixelRGB::operator <= (int const& a) const {
			return r <= a && g <= a && b <= a;
		}

		/* PixelRGBA */
		PixelRGBA::PixelRGBA(int const& b_, int const& g_, int const& r_, int const& a_) {
			b = truncate<int>(b_, 0, 255);
			g = truncate<int>(g_, 0, 255);
			r = truncate<int>(r_, 0, 255);
			a = truncate<int>(a_, 0, 255);
		}

		PixelRGBA::PixelRGBA(initializer_list<int> const& init) : b(0), g(0), r(0), a(0) {
			int i = 0;
			for (auto it = init.begin(); i < 4 && it != init.end(); ++i, ++it) {
				switch (i) {
				case 0:
					b = static_cast<unsigned char>(truncate<int>(*it, 0, 255));
					break;
				case 1:
					g = static_cast<unsigned char>(truncate<int>(*it, 0, 255));
					break;
				case 2:
					r = static_cast<unsigned char>(truncate<int>(*it, 0, 255));
					break;
				case 3:
					a = static_cast<unsigned char>(truncate<int>(*it, 0, 255));
					break;
				default:
					break;
				}
			}
		}

		bool PixelRGBA::operator > (int const& a) const {
			return r > a && g > a && b > a;
		}

		bool PixelRGBA::operator >= (int const& a) const {
			return r >= a && g >= a && b >= a;
		}

		bool PixelRGBA::operator < (int const& a) const {
			return r < a && g < a && b < a;
		}

		bool PixelRGBA::operator <= (int const& a) const {
			return r <= a && g <= a && b <= a;
		}

		PixelRGBA& PixelRGBA::operator = (int const& other) {
			b = (unsigned char)truncate<int>(other, 0, 255);
			g = (unsigned char)truncate<int>(other, 0, 255);
			r = (unsigned char)truncate<int>(other, 0, 255);
			return *this;
		}

		/* 图像读入函数 | RGBA edition */
		void imageRead(string const& path, Image<PixelRGBA>& InputImage) {
			string exta = file::GetExta(path);
			if (exta == ".bmp") {
				FILE* fp;

				/*  */
				if (fopen_s(&fp, path.c_str(), "rb")) {
					std::cerr << "ERROR: Failed to open file... | in class BMP void load(const std::string& path)" << std::endl;
				}
				if (fp == NULL) {
					free(fp);
					std::cerr << "ERROR: Empty file... | in class BMP void load(const std::string& path)" << std::endl;
					return;
				}

				file::BitmapFileHeader BMPFileHeader;
				file::BitmapInfoHeader BMPInfoHeader;

				// 读取BMP头部
				// 图像文件头
				fread(&BMPFileHeader.bfType, 2, 1, fp);
				fread(&BMPFileHeader.bfSize, 4, 1, fp);
				fread(&BMPFileHeader.bfReserved1, 2, 1, fp);
				fread(&BMPFileHeader.bfReserved2, 2, 1, fp);
				fread(&BMPFileHeader.bfOffBits, 4, 1, fp);

				// 位图信息头
				fread(&BMPInfoHeader.biSize, 4, 1, fp);
				fread(&BMPInfoHeader.biWidth, 4, 1, fp);
				fread(&BMPInfoHeader.biHeight, 4, 1, fp);
				fread(&BMPInfoHeader.biPlanes, 2, 1, fp);
				fread(&BMPInfoHeader.biBitCount, 2, 1, fp);
				fread(&BMPInfoHeader.biCompression, 4, 1, fp);
				fread(&BMPInfoHeader.biSizeIMAGE, 4, 1, fp);
				fread(&BMPInfoHeader.biXPelsPerMeter, 4, 1, fp);
				fread(&BMPInfoHeader.biYPelsPerMeter, 4, 1, fp);
				fread(&BMPInfoHeader.biClrUsed, 4, 1, fp);
				fread(&BMPInfoHeader.biClrImportant, 4, 1, fp);

				InputImage.resize(BMPInfoHeader.biHeight, BMPInfoHeader.biWidth);
				
				// 读取BMP位图数据
				// RGB数据也是倒着念的，原始数据是按B、G、R的顺序排列的
				fseek(fp, BMPFileHeader.bfOffBits, SEEK_SET);
				unsigned int biByteCount = BMPInfoHeader.biBitCount / 8;
				if (BMPInfoHeader.biBitCount == 32) {
					for (unsigned int h = 0; h < BMPInfoHeader.biHeight; ++h) {
						for (unsigned int w = 0; w < BMPInfoHeader.biWidth; ++w) {
							fread(&InputImage[h][w], biByteCount, 1, fp);
						}
					}
				}
				else if (BMPInfoHeader.biBitCount == 24) {
					unsigned int spaces = 4 * (3 * BMPInfoHeader.biWidth / 4 + 1) - 3 * BMPInfoHeader.biWidth;
					for (unsigned int h = 0; h < BMPInfoHeader.biHeight; ++h) {
						for (unsigned int w = 0; w < BMPInfoHeader.biWidth; ++w) {
							fread(&InputImage[h][w], 1, biByteCount, fp);
							InputImage[h][w].a = 0x00;
						}
						if (spaces != 4 && (ftell(fp) - BMPFileHeader.bfOffBits + spaces) % (3 * BMPInfoHeader.biWidth + spaces) == 0) {
							fseek(fp, ftell(fp) + spaces, SEEK_SET);
						}
					}
				}
				fclose(fp);
			}
			else {
				throw "ERROR: No type avilivlable | in yuki::cv::template <typename T> void ImageRead(const string, Image<T>&)\n";
			}
		}

		/* 图像读入函数 | RGB edition */
		void imageRead(string const& path, Image<PixelRGB>& InputImage) {
			string exta = file::GetExta(path);
			if (exta == ".bmp") {
				FILE* fp;

				if (fopen_s(&fp, path.c_str(), "rb")) {
					std::cerr << "ERROR: Failed to open file... | in class BMP void load(const std::string& path)" << std::endl;
				}
				if (fp == NULL) {
					free(fp);
					std::cerr << "ERROR: Empty file... | in class BMP void load(const std::string& path)" << std::endl;
					return;
				}

				file::BitmapFileHeader BMPFileHeader;
				file::BitmapInfoHeader BMPInfoHeader;

				// 读取BMP头部
				// 图像文件头
				fread(&BMPFileHeader.bfType, 2, 1, fp);
				fread(&BMPFileHeader.bfSize, 4, 1, fp);
				fread(&BMPFileHeader.bfReserved1, 2, 1, fp);
				fread(&BMPFileHeader.bfReserved2, 2, 1, fp);
				fread(&BMPFileHeader.bfOffBits, 4, 1, fp);

				// 位图信息头
				fread(&BMPInfoHeader.biSize, 4, 1, fp);
				fread(&BMPInfoHeader.biWidth, 4, 1, fp);
				fread(&BMPInfoHeader.biHeight, 4, 1, fp);
				fread(&BMPInfoHeader.biPlanes, 2, 1, fp);
				fread(&BMPInfoHeader.biBitCount, 2, 1, fp);
				fread(&BMPInfoHeader.biCompression, 4, 1, fp);
				fread(&BMPInfoHeader.biSizeIMAGE, 4, 1, fp);
				fread(&BMPInfoHeader.biXPelsPerMeter, 4, 1, fp);
				fread(&BMPInfoHeader.biYPelsPerMeter, 4, 1, fp);
				fread(&BMPInfoHeader.biClrUsed, 4, 1, fp);
				fread(&BMPInfoHeader.biClrImportant, 4, 1, fp);

				InputImage.resize(BMPInfoHeader.biHeight, BMPInfoHeader.biWidth);

				// 读取BMP位图数据
				// RGB数据也是倒着念的，原始数据是按B、G、R的顺序排列的
				fseek(fp, BMPFileHeader.bfOffBits, SEEK_SET);
				unsigned int biByteCount = BMPInfoHeader.biBitCount / 8;
				if (BMPInfoHeader.biBitCount == 32) {
					for (unsigned int h = 0; h < BMPInfoHeader.biHeight; ++h) {
						for (unsigned int w = 0; w < BMPInfoHeader.biWidth; ++w) {
							fread(&InputImage[h][w], 3, 1, fp);
							fseek(fp, ftell(fp) + 1, SEEK_SET);
						}
					}
				}
				else if (BMPInfoHeader.biBitCount == 24) {
					unsigned int spaces = 4 * (3 * BMPInfoHeader.biWidth / 4 + 1) - 3 * BMPInfoHeader.biWidth;
					for (unsigned int h = 0; h < BMPInfoHeader.biHeight; ++h) {
						for (unsigned int w = 0; w < BMPInfoHeader.biWidth; ++w) {
							fread(&InputImage[h][w], 3, 1, fp);
						}
						if (spaces != 4 && (ftell(fp) - BMPFileHeader.bfOffBits + spaces) % (3 * BMPInfoHeader.biWidth + spaces) == 0) {
							fseek(fp, ftell(fp) + spaces, SEEK_SET);
						}
					}
				}
				fclose(fp);
			}
			else {
				throw "ERROR: No type avilivlable | in yuki::cv::template <typename T> void ImageRead(const string, Image<T>&)\n";
			}
		}

		/* 图像保存函数 | RGBA edition */
		void imageWrite(string const& path, Image<PixelRGBA> const& OutputImage) {
			string exta = file::GetExta(path);
			if (exta == ".bmp") {
				FILE* fp;
				fopen_s(&fp, path.c_str(), "wb");

				if (fp == NULL) {
					free(fp);
					std::cerr << "ERROR: Empty file... | in class BMP void ImageRead(string const&, Image<T> const&)";
					return;
				}

				file::BitmapFileHeader BMPFileHeader((unsigned int)(OutputImage.cols() * (unsigned int)OutputImage.rows() * sizeof(PixelRGBA) + 54));
				file::BitmapInfoHeader BMPInfoHeader((unsigned int)OutputImage.cols(), (unsigned int)OutputImage.rows(), sizeof(PixelRGBA) * 8);

				fwrite(&BMPFileHeader.bfType, 2, 1, fp);
				fwrite(&BMPFileHeader.bfSize, 4, 1, fp);
				fwrite(&BMPFileHeader.bfReserved1, 2, 1, fp);
				fwrite(&BMPFileHeader.bfReserved2, 2, 1, fp);
				fwrite(&BMPFileHeader.bfOffBits, 4, 1, fp);

				fwrite(&BMPInfoHeader.biSize, 4, 1, fp);
				fwrite(&BMPInfoHeader.biWidth, 4, 1, fp);
				fwrite(&BMPInfoHeader.biHeight, 4, 1, fp);
				fwrite(&BMPInfoHeader.biPlanes, 2, 1, fp);
				fwrite(&BMPInfoHeader.biBitCount, 2, 1, fp);
				fwrite(&BMPInfoHeader.biCompression, 4, 1, fp);
				fwrite(&BMPInfoHeader.biSizeIMAGE, 4, 1, fp);
				fwrite(&BMPInfoHeader.biXPelsPerMeter, 4, 1, fp);
				fwrite(&BMPInfoHeader.biYPelsPerMeter, 4, 1, fp);
				fwrite(&BMPInfoHeader.biClrUsed, 4, 1, fp);
				fwrite(&BMPInfoHeader.biClrImportant, 4, 1, fp);

				/*std::cout << std::endl;
				std::cout << BMPFileHeader.bfType << std::endl;
				std::cout << BMPFileHeader.bfSize << std::endl;
				std::cout << BMPFileHeader.bfReserved1 << std::endl;
				std::cout << BMPFileHeader.bfReserved2 << std::endl;
				std::cout << BMPFileHeader.bfOffBits << std::endl;
				std::cout << BMPInfoHeader.biSize << std::endl;
				std::cout << BMPInfoHeader.biWidth << std::endl;
				std::cout << BMPInfoHeader.biHeight << std::endl;
				std::cout << BMPInfoHeader.biPlanes << std::endl;
				std::cout << BMPInfoHeader.biBitCount << std::endl;
				std::cout << BMPInfoHeader.biCompression << std::endl;
				std::cout << BMPInfoHeader.biSizeIMAGE << std::endl;
				std::cout << BMPInfoHeader.biXPelsPerMeter << std::endl;
				std::cout << BMPInfoHeader.biYPelsPerMeter << std::endl;
				std::cout << BMPInfoHeader.biClrUsed << std::endl;
				std::cout << BMPInfoHeader.biClrImportant << std::endl;
				std::cout << std::endl;*/

				for (unsigned int r = 0; r < BMPInfoHeader.biHeight; ++r) {
					fwrite(&OutputImage[r][0], sizeof(PixelRGBA), BMPInfoHeader.biWidth, fp);
				}

				fclose(fp);
			} else {
				throw "ERROR: No type avilivlable | in yuki::cv::template <typename T> void ImageWrite(string const&, Image<T> const&)\n";
			}
		}

		/* 图像保存函数 | RGB edition */
		void imageWrite(string const& path, Image<PixelRGB> const& OutputImage) {
			string exta = file::GetExta(path);
			if (exta == ".bmp") {
				FILE* fp;
				fopen_s(&fp, path.c_str(), "wb");

				if (fp == NULL) {
					free(fp);
					std::cerr << "ERROR: Empty file... | in class BMP void ImageRead(string const&, Image<T> const&)";
					return;
				}

				file::BitmapFileHeader BMPFileHeader((unsigned int)(OutputImage.cols() * OutputImage.rows() * sizeof(PixelRGB) + 54));
				file::BitmapInfoHeader BMPInfoHeader((unsigned int)OutputImage.cols(), (unsigned int)OutputImage.rows(), sizeof(PixelRGB) * 8);

				fwrite(&BMPFileHeader.bfType, 2, 1, fp);
				fwrite(&BMPFileHeader.bfSize, 4, 1, fp);
				fwrite(&BMPFileHeader.bfReserved1, 2, 1, fp);
				fwrite(&BMPFileHeader.bfReserved2, 2, 1, fp);
				fwrite(&BMPFileHeader.bfOffBits, 4, 1, fp);

				fwrite(&BMPInfoHeader.biSize, 4, 1, fp);
				fwrite(&BMPInfoHeader.biWidth, 4, 1, fp);
				fwrite(&BMPInfoHeader.biHeight, 4, 1, fp);
				fwrite(&BMPInfoHeader.biPlanes, 2, 1, fp);
				fwrite(&BMPInfoHeader.biBitCount, 2, 1, fp);
				fwrite(&BMPInfoHeader.biCompression, 4, 1, fp);
				fwrite(&BMPInfoHeader.biSizeIMAGE, 4, 1, fp);
				fwrite(&BMPInfoHeader.biXPelsPerMeter, 4, 1, fp);
				fwrite(&BMPInfoHeader.biYPelsPerMeter, 4, 1, fp);
				fwrite(&BMPInfoHeader.biClrUsed, 4, 1, fp);
				fwrite(&BMPInfoHeader.biClrImportant, 4, 1, fp);

				/*std::cout << std::endl;
				std::cout << BMPFileHeader.bfType << std::endl;
				std::cout << BMPFileHeader.bfSize << std::endl;
				std::cout << BMPFileHeader.bfReserved1 << std::endl;
				std::cout << BMPFileHeader.bfReserved2 << std::endl;
				std::cout << BMPFileHeader.bfOffBits << std::endl;
				std::cout << BMPInfoHeader.biSize << std::endl;
				std::cout << BMPInfoHeader.biWidth << std::endl;
				std::cout << BMPInfoHeader.biHeight << std::endl;
				std::cout << BMPInfoHeader.biPlanes << std::endl;
				std::cout << BMPInfoHeader.biBitCount << std::endl;
				std::cout << BMPInfoHeader.biCompression << std::endl;
				std::cout << BMPInfoHeader.biSizeIMAGE << std::endl;
				std::cout << BMPInfoHeader.biXPelsPerMeter << std::endl;
				std::cout << BMPInfoHeader.biYPelsPerMeter << std::endl;
				std::cout << BMPInfoHeader.biClrUsed << std::endl;
				std::cout << BMPInfoHeader.biClrImportant << std::endl;
				std::cout << std::endl;*/

				unsigned int spaces = 4 * (3 * BMPInfoHeader.biWidth / 4 + 1) - 3 * BMPInfoHeader.biWidth;
				for (unsigned int r = 0; r < BMPInfoHeader.biHeight; ++r) {
					for (unsigned int c = 0; c < BMPInfoHeader.biWidth; ++c) {
						fwrite(&OutputImage[r][c], sizeof(PixelRGB), 1, fp);
					}
					if (spaces != 4 && (ftell(fp) - BMPFileHeader.bfOffBits + spaces) % (3 * BMPInfoHeader.biWidth + spaces) == 0) {
						int tmp = 0;
						fwrite(&tmp, spaces, 1, fp);
					}
				}

				fclose(fp);
			}
			else {
				throw "ERROR: No type avilivlable | in yuki::cv::template <typename T> void ImageWrite(string const&, Image<T> const&)\n";
			}
		}

		/******************************************************************************************
		* 彩色图转灰度图
		* 0 GRAY_MODE_WEIGHT      加权法(推荐)
		* 1 GRAY_MODE_BEST        最值法
		* 2 GRAY_MODE_AVERAGE     均值法
		* 3 GRAY_MODE_PART_RED    分量法_RED
		* 4 GRAY_MODE_PART_GREEN  分量法_GREEN
		* 5 GRAY_MODE_PART_BLUE   分量法_BLUE
		******************************************************************************************/
		Image<PixelRGBA> transColorGray(Image<PixelRGBA> const& InputImage, GrayScaleMethod const& mode) {
			Image<PixelRGBA> OutputImage(InputImage.rows(), InputImage.cols());
			switch (mode) {
			case GRAY_MODE_WEIGHT: {
				int BlueWeight = 144, GreenWeight = 587, RedWeight = 299, total = BlueWeight + GreenWeight + RedWeight;
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = truncate<int>(((int)InputImage[row][col].b * BlueWeight + (int)InputImage[row][col].g * GreenWeight + (int)InputImage[row][col].r * RedWeight) / total, 0, 255);
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_BEST: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].b;
						gray = gray < InputImage[row][col].g ? InputImage[row][col].g : gray;
						gray = gray < InputImage[row][col].r ? InputImage[row][col].r : gray;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_AVERAGE: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = ((int)InputImage[row][col].b + (int)InputImage[row][col].g + (int)InputImage[row][col].r) / 3;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_RED: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].r;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_GREEN: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].g;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_BLUE: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].b;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			default:
				throw "ERROR: No type avilivlable | in yuki::cv::void TfmColorGray(Image<PixelRGBA> const&, Image<PixelRGBA>&, GrayScaleMethod const&)";
				break;
			}
			return OutputImage;
		}

		/******************************************************************************************
		* 彩色图转灰度图
		* 0 GRAY_MODE_WEIGHT      加权法(推荐)
		* 1 GRAY_MODE_BEST        最值法
		* 2 GRAY_MODE_AVERAGE     均值法
		* 3 GRAY_MODE_PART_RED    分量法_RED
		* 4 GRAY_MODE_PART_GREEN  分量法_GREEN
		* 5 GRAY_MODE_PART_BLUE   分量法_BLUE
		******************************************************************************************/
		Image<PixelRGB> transColorGray(Image<PixelRGB> const& InputImage, GrayScaleMethod const& mode) {
			Image<PixelRGB> OutputImage(InputImage.rows(), InputImage.cols());
			switch (mode) {
			case GRAY_MODE_WEIGHT: {
				int BlueWeight = 144, GreenWeight = 587, RedWeight = 299, total = BlueWeight + GreenWeight + RedWeight;
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = truncate<int>(((int)InputImage[row][col].b * BlueWeight + (int)InputImage[row][col].g * GreenWeight + (int)InputImage[row][col].r * RedWeight) / total, 0, 255);
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_BEST: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].b;
						gray = gray < InputImage[row][col].g ? InputImage[row][col].g : gray;
						gray = gray < InputImage[row][col].r ? InputImage[row][col].r : gray;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_AVERAGE: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = ((int)InputImage[row][col].b + (int)InputImage[row][col].g + (int)InputImage[row][col].r) / 3;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_RED: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].r;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_GREEN: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].g;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			case GRAY_MODE_PART_BLUE: {
				for (SizeType row = 0; row < InputImage.rows(); ++row) {
					for (SizeType col = 0; col < InputImage.cols(); ++col) {
						unsigned char gray = InputImage[row][col].b;
						OutputImage[row][col].b = OutputImage[row][col].g = OutputImage[row][col].r = gray;
					}
				}
				break;
			}
			default:
				throw "ERROR: No type avilivlable | in yuki::cv::void TfmColorGray(Image<PixelRGB> const&, Image<PixelRGB>&, GrayScaleMethod const&)";
				break;
			}
			return OutputImage;
		}

		/* 二值图（自定义阈值法） | RGBA edition */
		Image<PixelRGBA> transColorBWTHR(Image<PixelRGBA> const& InputImage, unsigned char const& Threshold, bool const& IsGray) {
			Image<PixelRGBA> OutputImage(InputImage.rows(), InputImage.cols());
			if (!IsGray) {
				OutputImage = transColorGray(InputImage);
			}
			unsigned char color = 0;
			for (SizeType r = 0; r < OutputImage.rows(); ++r) {
				for (SizeType c = 0; c < OutputImage.cols(); ++c) {
					/* Threshold的值在不同的图片中是不同的 */
					color = (OutputImage[r][c].b >= Threshold) ? 255 : 0;
					OutputImage[r][c].b = OutputImage[r][c].g = OutputImage[r][c].r = color;
				}
			}
			return OutputImage;
		}

		/* 二值图（自定义阈值法） | RGB edition */
		Image<PixelRGB> transColorBWTHR(Image<PixelRGB> const& InputImage, unsigned char const& Threshold, bool const& IsGray) {
			Image<PixelRGB> OutputImage(InputImage.rows(), InputImage.cols());
			if (!IsGray) {
				OutputImage = transColorGray(InputImage);
			}
			unsigned char color = 0;
			for (SizeType r = 0; r < OutputImage.rows(); ++r) {
				for (SizeType c = 0; c < OutputImage.cols(); ++c) {
					/* Threshold的值在不同的图片中是不同的 */
					color = (OutputImage[r][c].b >= Threshold) ? 255 : 0;
					OutputImage[r][c].b = OutputImage[r][c].g = OutputImage[r][c].r = color;
				}
			}
			return OutputImage;
		}

		/* 二值图（大津法OSTU，适用双峰直方图。当图像的整体颜色差别不大时，不推荐使用 */
		Image<PixelRGBA> transColorBWOSTU(Image<PixelRGBA> const& InputImage, bool const& IsGray) {
			Image<PixelRGBA> OutputImage(InputImage);
			if (!IsGray) {
				OutputImage = transColorGray(InputImage);
			}

			// 公式：g = w0 / (1 - w0) * (u0 - u)* (u0 - u) 当g最大时取到阈值T
			SizeType ColorMap[256] = { 0 }, total = OutputImage.rows() * OutputImage.cols();
			double w0 = 0;  /* 前景像素数的占比 */
			SizeType u0 = 0;  /* 前景的平局灰度（灰度值*其对应的素数个数）的累加/前景的像素个数 */
			SizeType u = 0;  /* 图像的平局灰度（灰度值*其对应的素数个数）的累加/总的像素个数 */
			double g = 0;  /* 方差 */
			unsigned char T = 0;  /* 阈值 */

			// 创建灰度直方图
			for (SizeType r = 0; r < OutputImage.rows(); ++r) {
				for (SizeType c = 0; c < OutputImage.cols(); ++c) {
					ColorMap[(int)OutputImage[r][c].b] += 1;
				}
			}

			for (int i = 0; i < 256; ++i) {
				/* u暂时计算累加 */
				u += ColorMap[i] * i;
			}
			u /= total;

			/* 遍历 0-255 寻找合适的阈值 */
			for (unsigned short int m = 0; m < 256; ++m) {
				for (unsigned short int n = m; n < 256; ++n) {
					w0 += ColorMap[n];  /* w0暂时计算，保存前景的所有像素个数 */
					u0 += ColorMap[n] * n;  /* u0暂时计算累加 */
				}

				u0 = (SizeType)(u0 / w0);
				w0 /= total;

				if ((w0 / (1 - w0) * (u0 - u) * (u0 - u)) > g) {
					g = w0 / (1 - w0) * (u0 - u) * (u0 - u);
					T = (unsigned char)m;
				}
			}
			OutputImage = transColorBWTHR(OutputImage, T);
			return OutputImage;
		}

		/* 原理：在以一个像素为中心，边长为SideLength（奇数）的区域内求像素的平均值 */
		/* 二值图（自适应阈值法，AreaSize = 25较合适，当图片线条多且密时，不推荐使用） */
		Image<PixelRGBA> transColorBWAdaptive(Image<PixelRGBA> const& InputImage, SizeType const& SideLength, bool const& IsGray, GrayScaleMethod const& GMethod, BorderMethod const& BMethod, unsigned char const& sample, AdaptiveMethod const& AMethod) {
			SizeType HalfSideLength = SideLength / 2, AreaSize = SideLength * SideLength;
			Image<PixelRGBA> tmp(InputImage), Gray(InputImage), OutputImage(InputImage.rows(), InputImage.cols());
			if (!IsGray) {
				tmp = transColorGray(InputImage, GMethod);
				Gray = transColorGray(InputImage, GMethod);
			}
			tmp = transShapeBoeder(tmp, SideLength / 2, BMethod, sample);
			SizeType gray = 0;
			switch (AMethod) {
			case ADAPTIVE_GAUSSIAN_WEIGHT:

				break;
			case ADAPTIVE_AVERANGE:
				for (SizeType r = HalfSideLength; r < InputImage.rows() + HalfSideLength; ++r) {
					for (SizeType c = HalfSideLength; c < InputImage.cols() + HalfSideLength; ++c) {
						gray = 0;
						for (SizeType i = -HalfSideLength; i <= HalfSideLength; ++i) {
							for (SizeType j = -HalfSideLength; j <= HalfSideLength; ++j) {
								gray += static_cast<SizeType>(tmp[r + i][c + j].b);
							}
						}
						gray /= AreaSize;
						OutputImage[r - HalfSideLength][c - HalfSideLength].b = OutputImage[r - HalfSideLength][c - HalfSideLength].g = OutputImage[r - HalfSideLength][c - HalfSideLength].r = Gray[r - HalfSideLength][c - HalfSideLength].b >= gray ? 255 : 0;
					}
				}
				break;
			default:
				break;
			}

			return OutputImage;
		}

		template <typename T>
		Image<T> transShapeBoeder(Image<T> const& InputImage, SizeType const& padding, BorderMethod const& mode, unsigned char const& sample) {
			if (padding == 0) {
				return Image<T>(InputImage);
			}
			Image<T> OutputImage(InputImage.rows() + padding * 2, InputImage.cols() + padding * 2);
			/* 复制中间 */
			for (SizeType r = padding; r < OutputImage.rows() - padding; ++r) {
				for (SizeType c = padding; c < OutputImage.cols() - padding; ++c) {
					OutputImage[r][c] = InputImage[r - padding][c - padding];
				}
			}

			/* 处理pad的区域 */
			switch (mode) {
			case yuki::cv::BORDER_REFLECT_101:
				/* 中上 */
				for (SizeType r = 0; r < padding; ++r) {
					for (SizeType c = padding; c < OutputImage.cols() - padding; ++c) {
						OutputImage[r][c] = InputImage[padding - r][c - padding];
					}
				}
				/* 左上 */
				for (SizeType r = 0; r < padding; ++r) {
					for (SizeType c = 0; c < padding; ++c) {
						OutputImage[r][c] = InputImage[padding - r][padding - c];
					}
				}
				/* 右上 */
				for (SizeType r = 0; r < padding; ++r) {
					for (SizeType c = OutputImage.cols() - padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[padding - r][InputImage.cols() + OutputImage.cols() - padding - c - 2];
					}
				}
				/* 中下 */
				for (SizeType r = OutputImage.rows() - padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = padding; c < OutputImage.cols() - padding; ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - padding - r - 2][c - padding];
					}
				}
				/* 左下 */
				for (SizeType r = OutputImage.rows() - padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = 0; c < padding; ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - padding - r - 2][padding - c];
					}
				}
				/* 右下 */
				for (SizeType r = OutputImage.rows() - padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = OutputImage.cols() - padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - padding - r - 2][InputImage.cols() + OutputImage.cols() - padding - c - 2];
					}
				}
				/* 中左 */
				for (SizeType r = padding; r < OutputImage.rows() - padding; ++r) {
					for (SizeType c = 0; c < padding; ++c) {
					OutputImage[r][c] = InputImage[r - padding][padding - c];
					}
				}
				/* 中右 */
				for (SizeType r = padding; r < OutputImage.rows() - padding; ++r) {
					for (SizeType c = OutputImage.cols() - padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[r - padding][InputImage.cols() + OutputImage.cols() - padding - c - 2];
					}
				}
				break;
			case yuki::cv::BORDER_CONSTANT:
				/* （左、中、右）上 */
				for (SizeType r = 0; r < padding; ++r) {
					for (SizeType c = 0; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = sample;
					}
				}
				/* （左、中、右）下 */
				for (SizeType r = OutputImage.rows() - padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = 0; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = sample;
					}
				}
				/* （中）左 */
				for (SizeType c = 0; c < padding; ++c) {
					for (SizeType r = padding; r < OutputImage.rows() - padding; ++r) {
						OutputImage[r][c] = sample;
					}
				}
				/* （中）右 */
				for (SizeType c = OutputImage.cols() - padding; c < OutputImage.cols(); ++c) {
					for (SizeType r = padding; r < OutputImage.rows() - padding; ++r) {
						OutputImage[r][c] = sample;
					}
				}
				break;
			case yuki::cv::BORDER_COMPRESS:
				break;
			default:
				break;
			}
			return OutputImage;
		}

		Image<PixelRGBA> transShapeBoeder(Image<PixelRGBA> const& InputImage, BorderOption const& BOption) {
			Image<PixelRGBA> OutputImage(InputImage.rows() + BOption.padding * 2, InputImage.cols() + BOption.padding * 2);
			/* 复制中间 */
			for (SizeType r = BOption.padding; r < OutputImage.rows() - BOption.padding; ++r) {
				for (SizeType c = BOption.padding; c < OutputImage.cols() - BOption.padding; ++c) {
					OutputImage[r][c] = InputImage[r - BOption.padding][c - BOption.padding];
				}
			}

			/* 处理pad的区域 */
			switch (BOption.mode) {
			case yuki::cv::BORDER_REFLECT_101:
				/* 中上 */
				for (SizeType r = 0; r < BOption.padding; ++r) {
					for (SizeType c = BOption.padding; c < OutputImage.cols() - BOption.padding; ++c) {
						OutputImage[r][c] = InputImage[BOption.padding - r][c - BOption.padding];
					}
				}
				/* 左上 */
				for (SizeType r = 0; r < BOption.padding; ++r) {
					for (SizeType c = 0; c < BOption.padding; ++c) {
						OutputImage[r][c] = InputImage[BOption.padding - r][BOption.padding - c];
					}
				}
				/* 右上 */
				for (SizeType r = 0; r < BOption.padding; ++r) {
					for (SizeType c = OutputImage.cols() - BOption.padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[BOption.padding - r][InputImage.cols() + OutputImage.cols() - BOption.padding - c - 2];
					}
				}
				/* 中下 */
				for (SizeType r = OutputImage.rows() - BOption.padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = BOption.padding; c < OutputImage.cols() - BOption.padding; ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - BOption.padding - r - 2][c - BOption.padding];
					}
				}
				/* 左下 */
				for (SizeType r = OutputImage.rows() - BOption.padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = 0; c < BOption.padding; ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - BOption.padding - r - 2][BOption.padding - c];
					}
				}
				/* 右下 */
				for (SizeType r = OutputImage.rows() - BOption.padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = OutputImage.cols() - BOption.padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[InputImage.rows() + OutputImage.rows() - BOption.padding - r - 2][InputImage.cols() + OutputImage.cols() - BOption.padding - c - 2];
					}
				}
				/* 中左 */
				for (SizeType r = BOption.padding; r < OutputImage.rows() - BOption.padding; ++r) {
					for (SizeType c = 0; c < BOption.padding; ++c) {
						OutputImage[r][c] = InputImage[r - BOption.padding][BOption.padding - c];
					}
				}
				/* 中右 */
				for (SizeType r = BOption.padding; r < OutputImage.rows() - BOption.padding; ++r) {
					for (SizeType c = OutputImage.cols() - BOption.padding; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = InputImage[r - BOption.padding][InputImage.cols() + OutputImage.cols() - BOption.padding - c - 2];
					}
				}
				break;
			case yuki::cv::BORDER_CONSTANT:
				/* （左、中、右）上 */
				for (SizeType r = 0; r < BOption.padding; ++r) {
					for (SizeType c = 0; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = BOption.sample;
					}
				}
				/* （左、中、右）下 */
				for (SizeType r = OutputImage.rows() - BOption.padding; r < OutputImage.rows(); ++r) {
					for (SizeType c = 0; c < OutputImage.cols(); ++c) {
						OutputImage[r][c] = BOption.sample;
					}
				}
				/* （中）左 */
				for (SizeType c = 0; c < BOption.padding; ++c) {
					for (SizeType r = BOption.padding; r < OutputImage.rows() - BOption.padding; ++r) {
						OutputImage[r][c] = BOption.sample;
					}
				}
				/* （中）右 */
				for (SizeType c = OutputImage.cols() - BOption.padding; c < OutputImage.cols(); ++c) {
					for (SizeType r = BOption.padding; r < OutputImage.rows() - BOption.padding; ++r) {
						OutputImage[r][c] = BOption.sample;
					}
				}
				break;
			case yuki::cv::BORDER_COMPRESS:
				break;
			default:
				break;
			}
			return OutputImage;
		}

		vector<double> comptAverange(Image<PixelRGBA> const& InputImage) {
			vector<double> averange = {0, 0, 0};
			for (SizeType r = 0; r < InputImage.rows(); ++r) {
				for (SizeType c = 0; c < InputImage.cols(); ++c) {
					averange[0] += (double)InputImage[r][c].b;
					averange[1] += (double)InputImage[r][c].g;
					averange[2] += (double)InputImage[r][c].r;
				}
			}
			averange[0] /= InputImage.rows() * InputImage.cols();
			averange[1] /= InputImage.rows() * InputImage.cols();
			averange[2] /= InputImage.rows() * InputImage.cols();
			return averange;
		}

		vector<double> comptVariance(Image<PixelRGBA> const& InputImage) {
			vector<double> variance = { 0, 0, 0 }, averange = comptAverange(InputImage);
			for (SizeType r = 0; r < InputImage.rows(); ++r) {
				for (SizeType c = 0; c < InputImage.cols(); ++c) {
					variance[0] += ((double)InputImage[r][c].b - averange[0]) * ((double)InputImage[r][c].b - averange[0]);
					variance[1] += ((double)InputImage[r][c].g - averange[1]) * ((double)InputImage[r][c].g - averange[1]);
					variance[2] += ((double)InputImage[r][c].r - averange[2]) * ((double)InputImage[r][c].r - averange[2]);
				}
			}
			variance[0] /= InputImage.rows() * InputImage.cols();
			variance[1] /= InputImage.rows() * InputImage.cols();
			variance[2] /= InputImage.rows() * InputImage.cols();
			return variance;
		}

		/* 计算服从正态分布的卷积核 */
		Image<double> comptGaussianKernel(double const& mu, double const& sigma2, SizeType const& size) {
			Image<double> GaussianKernel(size, size);
			SizeType HalfSize = size / 2;
			double k1 = 1 / (PI * sigma2 * 2), k2 = sigma2 * 2;
			for (SizeType r = 0; r <= HalfSize; ++r) {
				for (SizeType c = r; c <= HalfSize; ++c) {
					GaussianKernel[r][c] = k1 * exp(-(long double)((HalfSize - r) * (HalfSize - r) + (HalfSize - c) * (HalfSize - c)) / sigma2 * 2);
				}
			}
			for (SizeType r = 0; r < HalfSize; ++r) {
				for (SizeType c = 0; c < r; ++c) {
					GaussianKernel[r][c] = GaussianKernel[c][r];
				}
			}

			long double sum = 0;
			for (SizeType r = 0; r < HalfSize; ++r) {
				for (SizeType c = r; c <= HalfSize; ++c) {
					sum += GaussianKernel[r][c];
				}
			}
			sum = sum * 4 + GaussianKernel[HalfSize][HalfSize];
			for (SizeType r = 0; r < HalfSize; ++r) {
				for (SizeType c = r; c <= HalfSize; ++c) {
					GaussianKernel[r][c] /= sum;
				}
			}
			GaussianKernel[HalfSize][HalfSize] /= sum;

			for (SizeType r = 0; r <= HalfSize; ++r) {
				for (SizeType c = HalfSize + 1; c < size; ++c) {
					GaussianKernel[r][c] = GaussianKernel[c - HalfSize - 1][r];
				}
			}
			for (SizeType r = HalfSize + 1; r < size; ++r) {
				for (SizeType c = HalfSize; c < size; ++c) {
					GaussianKernel[r][c] = GaussianKernel[size - r - 1][size - c - 1];
				}
			}
			for (SizeType r = size - 1; r >= HalfSize; --r) {
				for (SizeType c = 0; c < HalfSize; ++c) {
					GaussianKernel[r][c] = GaussianKernel[c][size - r - 1];
				}
			}
			return GaussianKernel;
		}

		/* 高斯模糊 */
		Image<PixelRGBA> blurGaussian(Image<PixelRGBA> const& InputImage_, SizeType const& kernelSize) {
			SizeType HalfkernelSize = kernelSize / 2;
			vector<double> mu = comptAverange(InputImage_), sigma = comptAverange(InputImage_);
			Image<double> BKernel = comptGaussianKernel(mu[0], sigma[0], kernelSize),
						   GKernel = comptGaussianKernel(mu[1], sigma[1], kernelSize),
						   RKernel = comptGaussianKernel(mu[2], sigma[2], kernelSize);

			/* copy InputImage */
			Image<PixelRGBA> InputImage(InputImage_);
			InputImage = transShapeBoeder(InputImage, HalfkernelSize, yuki::cv::BORDER_REFLECT_101);
			Image<PixelRGBA> OutputImage(InputImage.rows() - HalfkernelSize * 2, InputImage.cols() - HalfkernelSize * 2);

			for (SizeType r = HalfkernelSize; r < InputImage.rows() - HalfkernelSize; ++r) {
				for (SizeType c = HalfkernelSize; c < InputImage.cols() - HalfkernelSize; ++c) {
					SizeType ROut = r - HalfkernelSize, COut = c - HalfkernelSize;
					double SumB = 0, SumG = 0, SumR = 0;

					for (SizeType i = ROut; i <= r + HalfkernelSize; ++i) {
						for (SizeType j = COut; j <= c + HalfkernelSize; ++j) {
							SumB += (double)InputImage[i][j].b * BKernel[i - ROut][j - COut];
							SumG += (double)InputImage[i][j].g * GKernel[i - ROut][j - COut];
							SumR += (double)InputImage[i][j].r * RKernel[i - ROut][j - COut];
						}
					}

					OutputImage[ROut][COut].b = (unsigned char)truncate<double>(SumB, 0, 255);
					OutputImage[ROut][COut].g = (unsigned char)truncate<double>(SumG, 0, 255);
					OutputImage[ROut][COut].r = (unsigned char)truncate<double>(SumR, 0, 255);
				}
			}
			return OutputImage;
		}

		/* 卷积操作 */
		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage_, Image<double> const& kernel, SizeType const& stride, SizeType const& padding) {
			SizeType HalfKernelRow = kernel.rows() / 2, HalfKernelCol = kernel.cols() / 2;
			/* copy InputImage */
			Image<PixelRGBA> InputImage(InputImage_);
			InputImage = transShapeBoeder(InputImage, padding, yuki::cv::BORDER_CONSTANT, 0);
			Image<PixelRGBA> OutputImage((InputImage.rows() - HalfKernelRow * 2) / stride, (InputImage.cols() - HalfKernelCol * 2) / stride);

			for (SizeType r = HalfKernelRow; r < InputImage.rows() - HalfKernelRow; r += stride) {
				for (SizeType c = HalfKernelCol; c < InputImage.cols() - HalfKernelCol; c += stride) {
					SizeType ROut = r - HalfKernelRow, COut = c - HalfKernelCol;
					double SumB = 0, SumG = 0, SumR = 0;

					for (SizeType i = ROut; i <= r + HalfKernelRow; ++i) {
						for (SizeType j = COut; j <= c + HalfKernelCol; ++j) {
							SumB += (double)InputImage[i][j].b * kernel[i - ROut][j - COut];
							SumG += (double)InputImage[i][j].g * kernel[i - ROut][j - COut];
							SumR += (double)InputImage[i][j].r * kernel[i - ROut][j - COut];
						}
					}

					OutputImage[ROut][COut].b = (unsigned char)truncate<double>(SumB, 0, 255);
					OutputImage[ROut][COut].g = (unsigned char)truncate<double>(SumG, 0, 255);
					OutputImage[ROut][COut].r = (unsigned char)truncate<double>(SumR, 0, 255);
				}
			}
			return OutputImage;
		}

		Image<PixelRGBA> convolute(Image<PixelRGBA> const& InputImage_, ConvOption const& COption) {
			SizeType HalfKernelRow = COption.kernel.rows() / 2, HalfKernelCol = COption.kernel.cols() / 2;
			/* copy InputImage */
			Image<PixelRGBA> InputImage(InputImage_);
			InputImage = transShapeBoeder(InputImage, COption.BOption);
			Image<PixelRGBA> OutputImage((InputImage.rows() - HalfKernelRow * 2) / COption.stride, (InputImage.cols() - HalfKernelCol * 2) / COption.stride);

			for (SizeType r = HalfKernelRow; r < InputImage.rows() - HalfKernelRow; r += COption.stride) {
				for (SizeType c = HalfKernelCol; c < InputImage.cols() - HalfKernelCol; c += COption.stride) {
					SizeType ROut = r - HalfKernelRow, COut = c - HalfKernelCol;
					double SumB = 0, SumG = 0, SumR = 0;

					for (SizeType i = ROut; i <= r + HalfKernelRow; ++i) {
						for (SizeType j = COut; j <= c + HalfKernelCol; ++j) {
							SumB += (double)InputImage[i][j].b * COption.kernel[i - ROut][j - COut];
							SumG += (double)InputImage[i][j].g * COption.kernel[i - ROut][j - COut];
							SumR += (double)InputImage[i][j].r * COption.kernel[i - ROut][j - COut];
						}
					}

					OutputImage[ROut][COut].b = (unsigned char)truncate<double>(SumB, 0, 255);
					OutputImage[ROut][COut].g = (unsigned char)truncate<double>(SumG, 0, 255);
					OutputImage[ROut][COut].r = (unsigned char)truncate<double>(SumR, 0, 255);
				}
			}
			return OutputImage;
		}

		Image<double> convolute(Image<double> const& InputImage_, Image<double> const& kernel, SizeType const& stride, SizeType const& padding) {
			SizeType HalfKernelRow = kernel.rows() / 2, HalfKernelCol = kernel.cols() / 2;
			/* copy InputImage */
			Image<double> InputImage(InputImage_);
			InputImage = transShapeBoeder(InputImage, padding, yuki::cv::BORDER_CONSTANT, 0);
			Image<double> OutputImage((InputImage.rows() - HalfKernelRow * 2) / stride, (InputImage.cols() - HalfKernelCol * 2) / stride, 0);

			for (SizeType r = HalfKernelRow; r < InputImage.rows() - HalfKernelRow; r += stride) {
				for (SizeType c = HalfKernelCol; c < InputImage.cols() - HalfKernelCol; c += stride) {
					SizeType ROut = r - HalfKernelRow, COut = c - HalfKernelCol;

					for (SizeType i = ROut; i <= r + HalfKernelRow; ++i) {
						for (SizeType j = COut; j <= c + HalfKernelCol; ++j) {
							OutputImage[ROut][COut] += InputImage[i][j] * kernel[i - ROut][j - COut];
						}
					}

				}
			}
			return OutputImage;
		}

		/*Image<PixelRGB> convolute(Image<PixelRGB> const& InputImage, Image<double> const& kernel, SizeType const& stride, SizeType const& padding) {

		}

		Image<double> convolute(Image<double> const& InputImage, Image<double> const& kernel, SizeType const& stride, SizeType const& padding) {

		}*/

		Image<double> pool(Image<double> const& InputImage, SizeType const& kernelSize, PoolMethod const& PMtd) {
			Image<double> OutputImage(InputImage.rows() / kernelSize, InputImage.cols() / kernelSize);
			switch (PMtd) {
			case yuki::cv::MAX_POOL: {
				for (SizeType r = 0, R = 0; r < InputImage.rows(); r += kernelSize, ++R) {
					for (SizeType c = 0, C = 0; c < InputImage.cols(); c += kernelSize, ++C) {
						double max = InputImage[r][c];
						for (SizeType i = r; i < r + kernelSize; ++i) {
							for (SizeType j = c; j < c + kernelSize; ++j) {
								max = InputImage[i][j] > max ? InputImage[r][c] : max;
							}
						}
						OutputImage[R][C] = max;
					}
				}
				break;
			}
			default:
				break;
			}

			return OutputImage;
		}

		/* 缩放图片（双线性插值法）（推荐使用） */
		Image<PixelRGBA> resize(Image<PixelRGBA> const& InputImage, SizeType const& NewHeight, SizeType const& NewWidth, ResizeMethod const& RMethod) {
			Image<PixelRGBA> OutputImage(NewHeight, NewWidth);
			switch (RMethod) {
			case BILINEAR_INTERPOLAYION: {
				point p[4];
				double r, c, dr, dc;
				for (SizeType R = 0; R < NewHeight; ++R) {
					for (SizeType C = 0; C < NewWidth; ++C) {
						/* 通过新图的坐标计算原图的坐标 */
						r = ((double)R + 0.5) * (double)InputImage.rows() / (double)NewHeight - 0.5;
						c = ((double)C + 0.5) * (double)InputImage.cols() / (double)NewWidth - 0.5;

						dr = r - floor(r);
						dc = c - floor(c);

						/* 分别计算四个角上点的坐标同时判断是否越界 */
						p[0] = point(truncate<point::ElemType>((point::ElemType)floor(r), 0, InputImage.rows() - 1), truncate<point::ElemType>((point::ElemType)floor(c), 0, InputImage.cols() - 1));  /* 左上角 */
						p[1] = point(truncate<point::ElemType>((point::ElemType)(floor(r) + 1), 0, InputImage.rows() - 1), truncate<point::ElemType>((point::ElemType)floor(c), 0, InputImage.cols() - 1));  /* 右上角 */
						p[2] = point(truncate<point::ElemType>((point::ElemType)floor(r), 0, InputImage.rows() - 1), truncate<point::ElemType>((point::ElemType)(floor(c) + 1), 0, InputImage.cols() - 1));  /* 左下角 */
						p[3] = point(truncate<point::ElemType>((point::ElemType)(floor(r) + 1), 0, InputImage.rows() - 1), truncate<point::ElemType>((point::ElemType)(floor(c) + 1), 0, InputImage.cols() - 1));   /* 右下角 */

						OutputImage[R][C].b = (unsigned char)truncate<double>(((double)InputImage[p[0].row][p[0].col].b * dr + (double)InputImage[p[1].row][p[1].col].b * (1 - dr)) * dc +
							((double)InputImage[p[2].row][p[2].col].b * dr + (double)InputImage[p[3].row][p[3].col].b * (1 - dr)) * (1 - dc), 0, 255);
						
						OutputImage[R][C].g = (unsigned char)truncate<double>(((double)InputImage[p[0].row][p[0].col].g * dr + (double)InputImage[p[1].row][p[1].col].g * (1 - dr)) * dc +
							((double)InputImage[p[2].row][p[2].col].g * dr + (double)InputImage[p[3].row][p[3].col].g * (1 - dr)) * (1 - dc), 0, 255);

						OutputImage[R][C].r = (unsigned char)truncate<double>(((double)InputImage[p[0].row][p[0].col].r * dr + (double)InputImage[p[1].row][p[1].col].r * (1 - dr)) * dc +
							((double)InputImage[p[2].row][p[2].col].r * dr + (double)InputImage[p[3].row][p[3].col].r * (1 - dr)) * (1 - dc), 0, 255);

						OutputImage[R][C].a = 0;

					}
				}
			}
				break;
			default:
				break;
			}
			
			return OutputImage;
		}


	}
}
