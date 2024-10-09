#include "ActivationFunctions.h"

namespace yuki {
namespace atri {

auto ReLU_::operator () (double const& input) -> double {
	return input > 0.0 ? input : 0.0;
}

auto ReLUDeriv_::operator () (double const& input) -> double {
	return input > 0.0 ? 1.0 : 0.0;
}

double ReLU(double const& input) {
	return input > 0.0 ? input : 0.0;
}

double ReLUDeriv(double const& input) {
	return input > 0.0 ? 1.0 : 0.0;
}

double sigmoid(double const& value) {
	return 1.0 / (1 + exp(value));
}

double sigmoidDeriv(double const& value) {
	return exp(value) / pow(1 + exp(value), 2);
}
}}