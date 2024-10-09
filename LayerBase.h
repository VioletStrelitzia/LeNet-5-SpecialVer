#pragma once
#include "DLObject.h"
#include "YukiMatrixBase.h"

#include <fstream>

using std::ofstream;
using std::ifstream;

namespace yuki {
namespace atri {

template<class _InputType, class _OutputType, class _WeightType, class _BiasType>
class LayerBase :
	public DLObject {
public:
	using InputType			  = _InputType;
	using OutputType		  = _OutputType;
	using WeightType		  = _WeightType;
	using LossType			  = _OutputType;
	using LossOutputType	  = _InputType;
	using GradType			  = _WeightType;
	using BiasType			  = _BiasType;

	using InputContainer	  = Matrix<InputType>;
	using OutputContainer	  = Matrix<OutputType>;
	using WeightContainer	  = Matrix<WeightType>;
	using BiasContainer		  = Matrix<BiasType>;
	using LossContainer		  = Matrix<LossType>;
	using LossOutputContainer = Matrix<LossOutputType>;
	using GradWeightContainer = Matrix<GradType>;
	using GradBiasContainer	  = Matrix<BiasType>;

public:
	SizeType const		inChannels;
	SizeType const		outChannels;
	bool				trainable;
	InputContainer		cached_ActivationInput;
	OutputContainer		output;
	WeightContainer		weight;
	BiasContainer		bias;
	LossContainer		delta;
	GradWeightContainer	gradWeight_Current;
	GradWeightContainer	gradWeight_Accumulated;
	GradBiasContainer	gradBias_Current;
	GradBiasContainer	gradBias_Accumulated;

public:
	LayerBase(SizeType const& inChannels_, SizeType const& outChannels_,
		string const& name_ = "",
		bool const& trainable_					= true,
		bool const& UsingCached_ActivationInput = true,
		bool const& UsingWeight					= true,
		bool const& UsingBias					= true,
		bool const& UsingDelta					= true,
		bool const& UsingGradCurrent			= true,
		bool const& UsingGradAccumulated		= true) :
		DLObject(DLObjecType::LAYER, name_),
		inChannels(inChannels_), outChannels(outChannels_), output(outChannels_, 1),
		trainable(trainable_),
		cached_ActivationInput(
			(trainable_ && UsingCached_ActivationInput) ? outChannels_ : 0, (trainable_ && UsingCached_ActivationInput) ? 1 : 0),
		weight(
			(trainable_ && UsingWeight)					? outChannels_ : 0, (trainable_ && UsingWeight)					? inChannels_ : 0),
		bias(
			(trainable_ && UsingBias)					? outChannels_ : 0, (trainable_ && UsingBias)					? 1 : 0),
		delta(
			(trainable_ && UsingDelta)					? outChannels_ : 0, (trainable_ && UsingDelta)					? 1 : 0),
		gradWeight_Current(
			(trainable_ && UsingGradCurrent)			? outChannels_ : 0, (trainable_ && UsingGradCurrent)			? inChannels_ : 0),
		gradWeight_Accumulated(
			(trainable_ && UsingGradAccumulated)		? outChannels_ : 0, (trainable_ && UsingGradAccumulated)		? inChannels_ : 0),
		gradBias_Current(
			(trainable_ && UsingGradCurrent)			? outChannels_ : 0, (trainable_ && UsingGradCurrent)			? 1 : 0),
		gradBias_Accumulated(
			(trainable_ && UsingGradAccumulated)		? outChannels_ : 0, (trainable_ && UsingGradAccumulated)		? 1 : 0) {}

	virtual auto forward(InputContainer const& input_) -> void = 0;

	virtual auto backward(LossOutputContainer& deltaOutput_, InputContainer const& input_) -> void = 0;

	virtual auto update(double const& learningRate = 0.001) -> void {}

	virtual auto save(ofstream& outfile) -> void {}

	virtual auto load(ifstream& infile) -> void {}

	auto Output() const -> OutputContainer const& {
		return output;
	}

	auto GradCurrent() -> GradWeightContainer& {
		return gradWeight_Current;
	}

	auto GradAccumulated() -> GradWeightContainer& {
		return gradWeight_Accumulated;
	}
};


}}
