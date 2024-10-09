#pragma once
#include "LayerBase.h"
#include "ActivationFunctions.h"

namespace yuki {
namespace atri {

class LayerFlatten2D : public LayerBase<Mat, double, Mat, double> {
private:
public:
	SizeType const InputRows;
	SizeType const InputCols;
	using base = LayerBase<Mat, double, Mat, double>;

public:
	LayerFlatten2D(SizeType const& inChannels_, SizeType const& InputRows_, SizeType const& InputCols_,
		string const& name_ = "", bool const& trainable_ = false) :
		base(inChannels_, 1, name_, trainable_, false, false, false, false, false, false), InputRows(InputRows_), InputCols(InputCols_) {
		if (trainable) {
			delta.resize(inChannels, 1);
		}
	}

	auto forward(InputContainer const& input_) -> void override {
		if (InputRows * InputCols * inChannels != output.rows()) {
			output.resize(InputRows * InputCols * inChannels, 1);
		}

		for (SizeType i = 0, j = 0; i < inChannels; ++i) {
			for (SizeType r = 0; r < input_.at(i).rows(); ++r) {
				for (SizeType c = 0; c < input_.at(i).cols(); ++c) {
					output.at(j++) = input_.at(i)[r][c];
				}
			}
		}
	}

	auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void override {
		for (SizeType i = 0, j = 0; i < inChannels; ++i) {
			deltaOutput_.at(i) = 0;
			for (SizeType r = 0; r < InputRows; ++r) {
				for (SizeType c = 0; c < InputCols; ++c) {
					deltaOutput_.at(i)[r][c] = delta.at(j++);
				}
			}
		}
	}

};

}}
