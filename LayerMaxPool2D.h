#pragma once
#include "LayerBase.h"
#include "ActivationFunctions.h"

namespace yuki {
namespace atri {

class LayerMaxPool2D : public LayerBase<Mat, Mat, Mat, double> {
private:
public:
	SizeType const kernelSize;
	vector<Matrix<point>> MaxLocation;
	using base = LayerBase<Mat, Mat, Mat, double>;


public:
	LayerMaxPool2D(SizeType const& inChannels_, SizeType const& InputMatRows_, SizeType const& InputMatCols_,
		SizeType const& kernelSize_ = 2,
		string const& name_ = "",
		bool const& trainable_ = false) :
		base(inChannels_, inChannels_, name_, trainable_, false, false, false, false, false, false), kernelSize(kernelSize_), MaxLocation() {
		if (trainable_) {
			delta.resize(outChannels, 1);
			for (SizeType o = 0; o < inChannels_; ++o) {
				delta.at(o).resize(InputMatRows_ / kernelSize_, InputMatCols_ / kernelSize_);
			}
		}
	}

	auto forward(InputContainer const& input_) -> void override {
		MaxLocation.clear();

		for (SizeType o = 0; o < inChannels; ++o) {
			Mat TmpMax(input_.at(o).rows() / kernelSize, input_.at(o).cols() / kernelSize);
			Matrix<point> TmpLoc(input_.at(o).rows() / kernelSize, input_.at(o).cols() / kernelSize);

			/* r, c是在输入图的行、列，R, C是在输出图的行、列 */
			for (SizeType r = 0, R = 0; R < TmpMax.rows(); r += kernelSize, ++R) {
				for (SizeType c = 0, C = 0; C < TmpMax.cols(); c += kernelSize, ++C) {
					auto max = input_.at(o)[r][c];
					point loc(static_cast<int>(r), static_cast<int>(c));

					for (SizeType i = r; i < r + kernelSize; ++i) {
						for (SizeType j = c; j < c + kernelSize; ++j) {
							if (input_.at(o)[i][j] > max) {
								max = input_.at(o)[i][j];
								loc.r = static_cast<int>(i);
								loc.c = static_cast<int>(j);
							}
						}
					}

					TmpMax[R][C] = max;
					TmpLoc[R][C] = loc;
				}
			}

			output.at(o) = TmpMax;
			MaxLocation.push_back(TmpLoc);
		}

	}

	auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void override {
		for (SizeType o = 0; o < MaxLocation.size(); ++o) {
			deltaOutput_.at(o) = 0;
			for (SizeType r = 0; r < MaxLocation[o].rows(); ++r) {
				for (SizeType c = 0; c < MaxLocation[o].cols(); ++c) {
					deltaOutput_.at(o)[MaxLocation[o][r][c].r][MaxLocation[o][r][c].c] = delta.at(o)[r][c];
				}
			}
		}

	}
};
}}


