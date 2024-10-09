#pragma once

#include "YukiMatrixBase.h"
#include "LayerBase.h"
#include "ActivationFunctions.h"
#include "Initializers.h"

namespace yuki {
namespace atri {

class LayerLinear : public LayerBase<double, double, double, double> {
private:
	using WeightInitFuncType	  = function<double(SizeType const& inChannels_, SizeType const& outChannels_)>;
	using BiasInitFuncType		  = function<double(SizeType const& inChannels_, SizeType const& outChannels_)>;
	using ActivationFuncType	  = function<double(double const&)>;
	using ActivationDerivFuncType = function<double(double const&)>;

	WeightInitFuncType		WeightInitFunc;
	BiasInitFuncType		BiasInitFunc;
	ActivationFuncType		ActivationFunc;
	ActivationDerivFuncType ActivationDerivFunc;

	using base = LayerBase<double, double, double, double>;
public:
	LayerLinear(SizeType const&				inChannels_,
				SizeType const&				outChannels_,
				ActivationFuncType			ActivationFunc_		= ReLU,
				string const&				name_				= "",
				bool						isInit_				= false,
				bool const&					trainable_			= false,
				WeightInitFuncType const&	WeightInitFunc_		= initNormalKaiming,
				BiasInitFuncType const&		BiasInitFunc_		= initNormalKaiming,
				ActivationDerivFuncType ActivationDerivFunc_	= ReLUDeriv) :
		base(inChannels_, outChannels_, name_, trainable_, true, true, true, true, true, true),
		WeightInitFunc(WeightInitFunc_), BiasInitFunc(BiasInitFunc_),
		ActivationFunc(ActivationFunc_), ActivationDerivFunc(ActivationDerivFunc_) {
		if (isInit_) {
			for (SizeType o = 0; o < outChannels_; ++o) {
				for (SizeType i = 0; i < inChannels_; ++i) {
					weight.at(o, i) = WeightInitFunc(inChannels_, outChannels_);
				}
			}
			for (SizeType o = 0; o < outChannels_; ++o) {
				bias.at(o, 0) = BiasInitFunc(inChannels_, outChannels_);
			}
		}
		if (trainable) {
			gradWeight_Accumulated = 0;
			gradBias_Accumulated = 0;
		}
	}

	auto forward(InputContainer const& input_) -> void override {
		output = weight * input_ + bias;
		cached_ActivationInput = output;
		// 通过激活函数
		for (SizeType o = 0; o < outChannels; ++o) {
			output.at(o) = ActivationFunc(output.at(o));
		}
	}

	auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void override {
		if (!deltaOutput_.empty()) {
			deltaOutput_ = weight.transpose() * delta;
			weight.transpose();
		}

		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {
				gradWeight_Current.at(o, i) = delta.at(o) * ActivationDerivFunc(cached_ActivationInput.at(o)) * input_.at(i);
				gradWeight_Accumulated.at(o, i) += gradWeight_Current.at(o, i);
			}

			gradBias_Current.at(o) = ActivationDerivFunc(cached_ActivationInput.at(o)) * delta.at(o);
			gradBias_Accumulated.at(o) += gradBias_Current.at(o);
		}
	}

	auto update(double const& learningRate) -> void {
		for (SizeType o = 0; o < outChannels; ++o) {

			for (SizeType i = 0; i < inChannels; ++i) {
				weight.at(o, i) -= learningRate * gradWeight_Accumulated.at(o, i);
				gradWeight_Accumulated.at(o, i) = 0;
			}

			bias.at(o) -= learningRate * gradBias_Accumulated.at(o);
			gradBias_Accumulated.at(o) = 0;
		}
	}

	auto save(ofstream& outfile) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {
				outfile.write(reinterpret_cast<char*>(&weight.at(o, i)), sizeof(double));
			}
		}

		for (SizeType o = 0; o < outChannels; ++o) {
			outfile.write(reinterpret_cast<char*>(&bias.at(o)), sizeof(double));
		}

	}

	auto load(ifstream& infile) -> void override {
		for (SizeType o = 0; o < outChannels; ++o) {
			for (SizeType i = 0; i < inChannels; ++i) {
				infile.read(reinterpret_cast<char*>(&weight.at(o, i)), sizeof(double));
			}
		}

		for (SizeType o = 0; o < outChannels; ++o) {
			infile.read(reinterpret_cast<char*>(&bias.at(o)), sizeof(double));
		}
	}

};

}}
