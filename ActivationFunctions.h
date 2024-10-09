#pragma once
#include "YukiMatrixBase.h"
#include "YukiCV.h"
#include "YukiDefault.h"

#include <random>
#include <cmath>

using std::sqrt;
using std::random_device;
using std::mt19937;
using std::uniform_real_distribution;
using std::normal_distribution;

namespace yuki {
namespace atri {

using SizeType = SizeType;

struct ReLU_ {
	auto operator () (double const& input) -> double;
};
/* ReLU激活函数 */
auto ReLU(double const& input) -> double;


struct ReLUDeriv_ {
	auto operator () (double const& input) -> double;
};
/* ReLU激活函数的导数 */
auto ReLUDeriv(double const& input) -> double;

auto sigmoid(double const& value) -> double;

auto sigmoidDeriv(double const& value) -> double;

}}