#pragma once

#include "LayerConv2D.h"
#include "LayerLinear.h"
#include "LayerMaxPool2D.h"
#include "LayerFlatten2D.h"
#include "LayerSoftmax.h"

namespace yuki {
namespace atri {

class Lenet5 {
private:
	using SizeType   = SizeType;
	using InputType  = Mat;
	using OutputType = Mat;
	Mat& output;

	function<double(Mat const& label, Mat const& output)> LossFunc;

public:
	LayerConv2D		conv1;
	LayerMaxPool2D  pool2;
	LayerConv2D		conv3;
	LayerMaxPool2D  pool4;
	LayerConv2D		conv5;
	LayerFlatten2D  flatten6;
	LayerLinear		fullConnect7;
	LayerLinear		fullConnect8;
	LayerSoftmax	outputLayer9;

	Lenet5(bool const& IsInit_ = false);

	auto forward(InputType const& InputImage) -> OutputType;

	auto backward(InputType const& InputImage, Mat const& label) -> void;

	auto update(double const& learningRate = 0.001) -> void;

	auto save(string const& filename) -> void;

	auto load(string const& filename) -> void;

};

}}
