#pragma once
#include "LayerBase.h"
#include "ActivationFunctions.h"

namespace yuki {
namespace atri {

class LayerSoftmax :
	public LayerBase<double, double, double, double> {
private:
public:
	using base = LayerBase<double, double, double, double>;

public:
	LayerSoftmax(SizeType const& inChannels_, string const& name_ = "", bool const& trainable_ = false) :
		base(inChannels_, inChannels_, name_, trainable_, false, false, false, false, false, false) {
		if (trainable) {
			delta.resize(inChannels_, 1);
		}
	}

	auto forward(InputContainer const& input_) -> void override {
		if (inChannels != input_.rows() || input_.cols() != 1)
			throw "ERROR: Marching error!";
		double sum = 0;
		for (SizeType i = 0; i < inChannels; ++i) {
			output.at(i) = exp(input_.at(i));
			sum += output.at(i);
		}
		for (SizeType o = 0; o < outChannels; ++o) {
			output.at(o) /= sum;
		}
	}

	auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void override {
		// 确保输入和输出的维度匹配
		if (inChannels != deltaOutput_.rows() || deltaOutput_.cols() != 1)
			throw std::runtime_error("ERROR: Dimensions mismatch!");

		for (SizeType i = 0; i < inChannels; ++i) {
			deltaOutput_.at(i) = delta.at(i) * output.at(i) * (1.0 - output.at(i));
		}
	}

};

}}
