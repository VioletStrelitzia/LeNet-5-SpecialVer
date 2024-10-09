#pragma once
#include "LayerBase.h"
#include "ActivationFunctions.h"
#include "Initializers.h"

namespace yuki {
namespace atri {

class LayerConv2D :
	public LayerBase<Mat, Mat, Mat, double> {
private:
	using WeightInitFuncType	  = function<Mat(SizeType const& inChannels_, SizeType const& outChannels_, SizeType const& kernelSize_)>;
	using BiasInitFuncType		  = function<double(SizeType const& inChannels_, SizeType const& outChannels_)>;
	using ActivationFuncType	  = function<double(double const&)>;
	using ActivationDerivFuncType = function<double(double const&)>;

	SizeType const			kernelSize;
	bool const				IsPadding;
	WeightInitFuncType		weightInitFunc;
	BiasInitFuncType		BiasInit;
	ActivationFuncType		ActivationFunc;
	ActivationDerivFuncType ActivationDerivFunc;

	using base = LayerBase<Mat, Mat, Mat, double>;
public:
	LayerConv2D(SizeType const& inChannels_, SizeType const& outChannels_,
		SizeType const& inputMatRows_, SizeType const& inputMatCols_,
		SizeType const& kernelSize_ = 5, bool const& IsPadding_ = false,
		ActivationFuncType ActivationFunc_ = ReLU,
		string const& name_ = "",
		bool const& IsInit_ = false,
		bool const& trainable_ = false,
		WeightInitFuncType const& weightInitFunc_ = initNormalKaimingKernel,
		BiasInitFuncType const& BiasInit_ = initNormalKaiming,
		ActivationDerivFuncType ActivationDerivFunc_ = ReLUDeriv) :
		base(inChannels_, outChannels_, name_, trainable_, true, true, true, true, true, true), kernelSize(kernelSize_), IsPadding(IsPadding_),
		weightInitFunc(weightInitFunc_), BiasInit(BiasInit_), ActivationFunc(ActivationFunc_), ActivationDerivFunc(ActivationDerivFunc_) {
		if (IsInit_) {
			for (SizeType o = 0; o < outChannels_; ++o) {
				for (SizeType i = 0; i < inChannels_; ++i) {
					weight.at(o, i) = weightInitFunc(inChannels_, outChannels_, kernelSize_);
				}
			}
			for (SizeType o = 0; o < outChannels_; ++o) {
				bias.at(o) = BiasInit(inChannels_, outChannels_);
			}
		}
		else {
			for (SizeType o = 0; o < outChannels_; ++o) {
				for (SizeType i = 0; i < inChannels_; ++i) {
					weight.at(o, i).resize(kernelSize, kernelSize_);
				}
			}
		}
		if (trainable_) {
			for (SizeType o = 0; o < outChannels_; ++o) {
				for (SizeType i = 0; i < inChannels_; ++i) {
					delta.at(o).resize(inputMatRows_ - (IsPadding_ ? 0 : ((kernelSize_ >> 1) << 1)), inputMatCols_ - (IsPadding_ ? 0 : ((kernelSize_ >> 1) << 1)));
					gradWeight_Current.at(o, i).resize(kernelSize_, kernelSize_);
					gradWeight_Accumulated.at(o, i).resize(kernelSize_, kernelSize_);
					gradWeight_Accumulated.at(o, i) = 0;
				}
			}
			for (SizeType o = 0; o < outChannels_; ++o) {
				gradBias_Accumulated.at(o) = 0;
			}
		}
	}

	auto forward(InputContainer const& input_) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			// 进行卷积
			output.at(o).resize(input_.at(0).rows() - (IsPadding ? 0 : ((kernelSize >> 1) << 1)), input_.at(0).cols() - (IsPadding ? 0 : ((kernelSize >> 1) << 1)));
			output.at(o) = 0;
			SizeType rows = output.at(o).rows(), cols = output.at(o).cols();

			if (IsPadding) {
				SizeType padding = kernelSize >> 1;
				for (SizeType i = 0; i < inChannels; ++i) {
					for (SizeType r = 0; r < rows; ++r) {
						for (SizeType c = 0; c < cols; ++c) {

							for (SizeType dr = -padding; dr <= padding; ++dr) {
								SizeType valid_r = r + dr;
								for (SizeType dc = -padding; dc <= padding; ++dc) {
									// 注意这里需要处理边界条件，因为输入可能小于kernelSize
									SizeType valid_c = c + dc;

									if (valid_r >= 0 && valid_r < input_.at(i).rows() &&
										valid_c >= 0 && valid_c < input_.at(i).cols()) {
										output.at(o)[r][c] += input_.at(i)[valid_r][valid_c] * weight.at(o, i)[dr + padding][dc + padding];
									}
								}
							}

						}
					}
				}
			} else {
				for (SizeType i = 0; i < inChannels; ++i) {
					for (SizeType r = 0; r < rows; ++r) {
						for (SizeType c = 0; c < cols; ++c) {

							for (SizeType dr = 0; dr < kernelSize; ++dr) {
								for (SizeType dc = 0; dc < kernelSize; ++dc) {
									output.at(o)[r][c] += input_.at(i)[r + dr][c + dc] * weight.at(o, i)[dr][dc];
								}
							}

						}
					}
				}
			}

			//output.at(o) = cv::convolute(input_.at(0), weight.at(o, 0), 1, IsPadding ? kernelSize / 2 : 0);
			//for (SizeType i = 1; i < inChannels; ++i) {
			//	output.at(o) += cv::convolute(input_.at(i), weight.at(o, i), 1, IsPadding ? kernelSize / 2 : 0);
			//}

			// +偏置
			output.at(o) += bias.at(o);
			cached_ActivationInput.at(o) = output.at(o);

			// 通过激活函数
			for (SizeType r = 0; r < rows; ++r) {
				for (SizeType c = 0; c < cols; ++c) {
					output.at(o)[r][c] = ActivationFunc(output.at(o)[r][c]);
				}
			}
		}
	}

	auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void override {
		if (!deltaOutput_.empty()) {
			for (SizeType i = 0; i < inChannels; ++i) {
				deltaOutput_.at(i) = 0;
				for (SizeType o = 0; o < outChannels; ++o) {
					SizeType rows = output.at(o).rows(),
						cols = output.at(o).cols(),
						padding = kernelSize >> 1;
					deltaOutput_.at(i).resize(rows + (padding << 1), rows + (padding << 1));
					deltaOutput_.at(i) = 0;
					weight.at(o, i).flip(Mat::AR180);

					// 遍历输出特征图的每个位置  
					for (SizeType r = -padding; r < rows + padding; ++r) {
						for (SizeType c = -padding; c < cols + padding; ++c) {
							// 遍历输入通道和卷积核  

							for (SizeType dr = -padding; dr <= padding; ++dr) {
								SizeType valid_r = r + dr;
								for (SizeType dc = -padding; dc <= padding; ++dc) {
									// 注意这里需要处理边界条件，因为输入可能小于kernelSize
									SizeType valid_c = c + dc;

									if (valid_r >= 0 && valid_r < delta.at(i).rows() &&
										valid_c >= 0 && valid_c < delta.at(i).cols()) {
										deltaOutput_.at(i)[r + padding][c + padding] +=
											weight.at(o, i)[dr + padding][dc + padding] * delta.at(i)[valid_r][valid_c];
									}
								}
							}

						}
					}
					weight.at(o, i).flip(Mat::AR180);

				}
			}

		}

		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {
				gradWeight_Current.at(o, i) = 0;

				for (SizeType dr = 0; dr < gradWeight_Current.at(o, i).rows(); ++dr) {
					for (SizeType dc = 0; dc < gradWeight_Current.at(o, i).cols(); ++dc) {

						for (SizeType ur = 0; ur < cached_ActivationInput.at(o).rows(); ++ur) {
							for (SizeType uc = 0; uc < cached_ActivationInput.at(o).cols(); ++uc) {
								if (ur + dr < input_.at(i).rows() && uc + dc < input_.at(i).cols())
									gradWeight_Current.at(o, i)[dr][dc] += delta.at(o)[ur][uc] * ActivationDerivFunc(cached_ActivationInput.at(o)[ur][uc]) * input_.at(i)[ur + dr][uc + dc];
							}
						}
						gradWeight_Accumulated.at(o, i)[dr][dc] += gradWeight_Current.at(o, i)[dr][dc];

					}
				}

			}

			gradBias_Current.at(o) = 0;
			for (SizeType ur = 0; ur < cached_ActivationInput.at(o).rows(); ++ur) {
				for (SizeType uc = 0; uc < cached_ActivationInput.at(o).cols(); ++uc) {
					gradBias_Current.at(o) += delta.at(o)[ur][uc] * ActivationDerivFunc(cached_ActivationInput.at(o)[ur][uc]);
				}
			}
			gradBias_Accumulated.at(o) += gradBias_Current.at(o);
		}

	}

	auto update(double const& learningRate) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {

				for (SizeType r = 0; r < kernelSize; ++r) {
					for (SizeType c = 0; c < kernelSize; ++c) {
						weight.at(o, i)[r][c] -= learningRate * gradWeight_Accumulated.at(o, i)[r][c];
					}
				}

				gradWeight_Accumulated.at(o, i) = 0;

			}

			bias.at(o) -= learningRate * gradBias_Accumulated.at(o);
			gradBias_Accumulated.at(o) = 0;
		}
	}

	auto save(ofstream& outfile) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {

				for (SizeType r = 0; r < weight.at(o, i).rows(); ++r) {
					for (SizeType c = 0; c < weight.at(o, i).cols(); ++c) {
						outfile.write(reinterpret_cast<char*>(&weight.at(o, i)[r][c]), sizeof(double));
					}
				}

			}
		}

		for (SizeType o = 0; o < outChannels; ++o) {
			outfile.write(reinterpret_cast<char*>(&bias.at(o)), sizeof(double));
		}

	}

	auto load(ifstream& infile) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {

				for (SizeType r = 0; r < weight.at(o, i).rows(); ++r) {
					for (SizeType c = 0; c < weight.at(o, i).cols(); ++c) {
						infile.read(reinterpret_cast<char*>(&weight.at(o, i)[r][c]), sizeof(double));
					}
				}

			}
		}

		for (SizeType o = 0; o < outChannels; ++o) {
			infile.read(reinterpret_cast<char*>(&bias.at(o)), sizeof(double));
		}
	}

};

}}
