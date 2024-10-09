#pragma once
#ifndef ___YUKI_ATRI_H__
#define ___YUKI_ATRI_H__

#include "YukiCV.h"
#include "YukiMatrixBase.h"
#include "YukiDefault.h"
#include "LayerBase.h"
#include "LayerConv2D.h"
#include "LayerLinear.h"
#include "LayerMaxPool2D.h"
#include "LayerFlatten2D.h"
#include "LayerSoftmax.h"
#include "ActivationFunctions.h"
#include "Lenet5.h"

#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <cmath>
#include <array>
#include <functional>
#include <fstream>
#include <iostream>

using yuki::cv::Image;
using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::array;
using std::sqrt;
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::normal_distribution;
using yuki::Mat;

namespace yuki {
	namespace atri {

		namespace cnn {
			/* 初始化方法 */
			enum InitMethod {
				Xavier = 0,
				He,
				MSRA
			};

			//class ModelBase {
			//protected:
			//	vector<LayerBase*> LayerPointers;

			//};

			//auto LossCrossEntropy(Mat const& label, Mat const& output) -> double {
			//	if (label.rows() != output.rows() || label.cols() != output.cols() || label.cols() != 1)
			//		throw "ERROR: Marching error!";
			//	double loss = 0;
			//	for (SizeType i = 0; i < label.rows(); ++i) {
			//		loss -= label.at(i) * log(output.at(i));
			//	}
			//	return loss;
			//}

			/* 6, 16, 120, 84, 10 */


			///* 层结构 */
			///* 二维卷积层 */
			//class LayerConv2D {
			//private:
			//public:
			//	SizeType _inChannels;
			//	SizeType _kernelSize;
			//	SizeType _stride;
			//	SizeType _padding;
			//	SizeType _outChannels;
			//	vector<vector<Mat>> _kernel;
			//	vector<double> _bias;
			//	vector<Mat> _grad;
			//	double (*_ActivationFunction) (double const&);
			//	vector<Mat> _OutputData;

			//public:
			//	LayerConv2D() {}

			//	LayerConv2D(SizeType const& inChannel, SizeType const& outChannel, double (*ActivationFunction) (double const&), Mat (*Init) (SizeType const&, SizeType const&, SizeType const&), SizeType const& kernelSize = 3, SizeType const& padding = 1, SizeType const& stride = 1);

			//	vector<Mat> forward(const vector<Mat>& InputData);

			//	vector<Mat> backward(const vector<Mat>& InputData);

			//	void step(double const& LearingRate);
			//};

			///* 二维最大池化层 */
			//class LayerMaxPool2D {
			//private:
			//public:
			//	SizeType _inChannels;
			//	SizeType _kernelSize;
			//	vector<Mat> _OutputData;
			//	vector<Image<cv::point>> _MaxLocation;

			//public:
			//	LayerMaxPool2D() {}

			//	LayerMaxPool2D(SizeType const& inChannel, SizeType const& kernelSize = 2);

			//	vector<Mat> forward(const vector<Mat>& InputData);

			//	vector<Mat> backward();

			//	vector<Mat> backward(const vector<Mat> InputData);
			//};

			///* 二维展平层 */
			//class LayerFlatten2D {
			//private:
			//public:
			//	SizeType _inChannels;
			//	SizeType _outChannels;
			//	SizeType _InputDataRow;
			//	SizeType _InputDataCol;
			//	vector<double> _OutputData;

			//public:
			//	LayerFlatten2D() {}

			//	LayerFlatten2D(SizeType const& inChannel, SizeType const& outChannel);

			//	vector<double> forward(const vector<Mat>& InputData);

			//	vector<Mat> backward();

			//};
			//
			///* 全连接层 */
			//class LayerLinear {
			//private:
			//public:
			//	SizeType _inChannels;
			//	SizeType _outChannels;
			//	vector<vector<double>> _weight;
			//	vector<double> _bias;
			//	vector<vector<double>> _grad;
			//	double (*_ActivationFunction) (double const&);
			//	vector<double> _OutputData;

			//public:
			//	LayerLinear() {}

			//	LayerLinear(SizeType const& inChannel, SizeType const& outChannel, double (*ActivationFunction) (double const&), double (*Init) (SizeType const&, SizeType const&));

			//	vector<double> forward(const vector<double>& InputData);

			//	vector<double> backward(const vector<double>& InputData);

			//	void step(double const& LearingRate);
			//};

			///* 6, 16, 120, 84, 10 */
			//class Lenet5 {
			//public:
			//	LayerConv2D conv1;
			//	LayerMaxPool2D pool2;
			//	LayerConv2D conv3;
			//	LayerMaxPool2D pool4;
			//	LayerConv2D conv5;
			//	LayerFlatten2D flatten6;
			//	LayerLinear FullConnect7;
			//	LayerLinear OutputLayer8;

			//	Lenet5();

			//	vector<double> forward(const Mat InputImage);

			//	void bacward(const vector<double> loss);

			//	void step();

			//	//;

			//};




		}
	}
}

#endif // !___YUKI_ATRI_H__
