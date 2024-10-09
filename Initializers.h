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

double initZero(SizeType const& inChannel, SizeType const& outChannel);

/* Xavier��ʼ�� */
struct InitUniformXavier_ {
public:
	auto operator () (SizeType const& inChannel, SizeType const& outChannel) -> double;
};
struct InitNormalXavier_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel) -> double;
};
double initUniformXavier(SizeType const& inChannel, SizeType const& outChannel);
double initNormalXavier(SizeType const& inChannel, SizeType const& outChannel);

/* ����˵�Xavier��ʼ�� */
class InitNormalXavierKernel_ {
public:
	auto operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat;
};
class InitUniformXavierKernel_ {
public:
	auto operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat;
};
Mat initNormalXavierKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize);
Mat initUniformXavierKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize);

/* ����˵�Kaiming��ʼ�� */
struct InitNormalKaimingKernel_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat;
};
Mat initNormalKaimingKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize);

struct InitNormalKaiming_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel) -> double;
};
double initNormalKaiming(SizeType const& inChannel, SizeType const& outChannel);

/* He��ʼ�� */
struct InitHe_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel) -> double;
};
double initHe(SizeType const& inChannel, SizeType const& outChannel);

/* ����˵�He��ʼ�� */
struct InitHeKernel_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat;
};
Mat initHeKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize);

/* MSRA��ʼ�� */
struct InitMSRA_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel) -> double;
};
double initMSRA(SizeType const& inChannel, SizeType const& outChannel);

/* ����˵�MSRA��ʼ�� */
struct InitMSRAKernel_ {
	auto operator () (SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize) -> Mat;
};
Mat initMSRAKernel(SizeType const& inChannel, SizeType const& outChannel, SizeType const& kernelSize);

}}
