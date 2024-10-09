#include "Initializers.h"

namespace yuki {
namespace atri {

static random_device AtriRD;
static mt19937 AtriGEN(AtriRD());

double initZero(SizeType const& inChannel, SizeType const& outChannel) {
	return 0.0;
}

auto InitUniformXavier_::operator () (SizeType const& inChannel, SizeType const& outChannel) -> double {
	double edge = sqrt(6) / sqrt(static_cast<double>(inChannel + outChannel));
	uniform_real_distribution<double> distribution(-edge, edge);
	return distribution(AtriGEN);
}

auto InitNormalXavier_::operator () (SizeType const& inChannel, SizeType const& outChannel) -> double {
	normal_distribution<double> dis(0.0, 2.0 / static_cast<double>(inChannel + outChannel));  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */
	return dis(AtriGEN);
}

double initUniformXavier(SizeType const& inChannel, SizeType const& outChannel) {
	double edge = sqrt(6) / sqrt((double)(inChannel + outChannel));
	uniform_real_distribution<double> distribution(-edge, edge);
	return distribution(AtriGEN);
}

double initNormalXavier(SizeType const& inChannel, SizeType const& outChannel) {
	normal_distribution<double> distribution(0.0, 2.0 / (inChannel + outChannel));  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */
	return distribution(AtriGEN);
}

auto InitNormalXavierKernel_::operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat {
	/* 均值为0，标准差为 2.0 / (inChannel + outChannel) */
	normal_distribution<double> dis(0.0, 2.0 / static_cast<double>(inChannel + outChannel));

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c)
			dst[r][c] = dis(AtriGEN);
	}
	return dst;
}

auto InitUniformXavierKernel_::operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat {
	double edge = sqrt(6) / sqrt(static_cast<double>(inChannel + outChannel));
	uniform_real_distribution<double> dis(-edge, edge);

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c)
			dst[r][c] = dis(AtriGEN);
	}
	return dst;
}


Mat initNormalXavierKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) {
	normal_distribution<double> distribution(0.0, 2.0 / (inChannel + outChannel));  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c) {
			dst[r][c] = distribution(AtriGEN);
		}
	}
	return dst;
}

Mat initUniformXavierKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) {
	double edge = sqrt(6) / sqrt((double)(inChannel + outChannel));
	uniform_real_distribution<double> distribution(-edge, edge);

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c) {
			dst[r][c] = distribution(AtriGEN);
		}
	}
	return dst;
}



auto InitNormalKaiming_::operator () (SizeType const& inChannel, SizeType const& outChannel) -> double {
	normal_distribution<double> dis(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */
	return dis(AtriGEN);
}

double initNormalKaiming(SizeType const& inChannel, SizeType const& outChannel) {
	normal_distribution<double> distribution(0.0, 2.0 / inChannel);  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */
	return distribution(AtriGEN);
}

auto InitNormalKaimingKernel_::operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat {
	normal_distribution<double> dis(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c)
			dst[r][c] = dis(AtriGEN);
	}
	return dst;
}
Mat initNormalKaimingKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) {
	normal_distribution<double> distribution(0.0, 2.0 / inChannel);  /* 均值为0，标准差为 2.0 / (inChannel + outChannel) */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c) {
			dst[r][c] = distribution(AtriGEN);
		}
	}
	return dst;
}

auto InitHe_::operator () (SizeType const& inChannel, SizeType const& outChannel) -> double {
	normal_distribution<double> distribution(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 1 / inChannel */
	return distribution(AtriGEN);
}

double initHe(SizeType const& inChannel, SizeType const& outChannel) {
	std::normal_distribution<double> distribution(0.0, 2.0 / inChannel);  /* 均值为0，标准差为 1 / inChannel */
	return distribution(AtriGEN);
}

auto InitHeKernel_::operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat {
	normal_distribution<double> distribution(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 1 / inChannel */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c)
			dst[r][c] = distribution(AtriGEN);
	}
	return dst;
}

Mat initHeKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) {
	normal_distribution<double> distribution(0.0, 2.0 / inChannel);  /* 均值为0，标准差为 1 / inChannel */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c) {
			dst[r][c] = distribution(AtriGEN);
		}
	}
	return dst;
}


auto InitMSRA_::operator () (SizeType const& inChannel, SizeType const& outChannel) -> double {
	normal_distribution<double> distribution(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 1 / inChannel */
	return distribution(AtriGEN) / 2.0;
}

double initMSRA(SizeType const& inChannel, SizeType const& outChannel) {
	normal_distribution<double> distribution(0.0, 2.0 / inChannel + outChannel);  /* 均值为0，标准差为 1 / inChannel */
	return distribution(AtriGEN) / 2;
}


auto InitMSRAKernel_::operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat {
	normal_distribution<double> distribution(0.0, 2.0 / static_cast<double>(inChannel));  /* 均值为0，标准差为 1 / inChannel */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c)
			dst[r][c] = distribution(AtriGEN);
	}
	return dst;
}

Mat initMSRAKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) {
	normal_distribution<double> distribution(0.0, 2.0 / inChannel + outChannel);  /* 均值为0，标准差为 1 / inChannel */

	Mat dst(kernelSize, kernelSize);
	for (SizeType r = 0; r < kernelSize; ++r) {
		for (SizeType c = 0; c < kernelSize; ++c) {
			dst[r][c] = distribution(AtriGEN);
		}
	}
	return dst;
}

}}
