#ifndef _YUKITENSOR_H_
#define _YUKITENSOR_H_
#include <iostream>
#include <vector>

//using std::SizeType;
using std::initializer_list;
using std::vector;

namespace yuki {
	//template <typename ElemType, SizeType Dim, SizeType... Dims>
	//class Tensor {
	//private:
	//	using _InnerTensor = Tensor<ElemType, Dims...>;
	//	using _Container = vector<_InnerTensor>;
	//	_Container _data;

	//public:
	//	Tensor() :
	//		_data(Dim) {};

	//	Tensor(initializer_list<_InnerTensor> const& init) :
	//		_data(init) {}

	//	//auto operator () (SizeType const&& i, SizeType const&&... indices) -> ElemType& {
	//	//	return _data[i](indices);
	//	//}

	//	//auto operator () (SizeType const&& i) -> ElemType& {
	//	//	return _data[i];
	//	//}

	//	//auto operator () (SizeType const&& i, SizeType const&&... indices) const -> ElemType const& {
	//	//	return _data[i](indices);
	//	//}

	//	//auto operator () (SizeType const&& i) const -> ElemType const& {
	//	//	return _data[i];
	//	//}

	//	auto size() const -> SizeType {
	//		return _data.size();
	//	}

	//	auto operator [] (SizeType const&& i) -> _InnerTensor& {
	//		return _data[i];
	//	}

	//	auto operator [] (SizeType const&& i) const -> _InnerTensor const& {
	//		return _data[i];
	//	}
	//};

	//template <typename ElemType, SizeType Dim>
	//class Tensor<ElemType, Dim> {
	//private:
	//	using _Container = vector<ElemType>;
	//	_Container _data;

	//public:
	//	Tensor() :
	//		_data(Dim) {};

	//	Tensor(initializer_list<ElemType> const& init) :
	//		_data(init) {}

	//	auto size() const -> SizeType const&& {
	//		return _data.size();
	//	}

	//	auto operator [] (SizeType const&& i) -> ElemType& {
	//		return _data[i];
	//	}

	//	auto operator [] (SizeType const&& i) const -> ElemType const& {
	//		return _data[i];
	//	}
	//};



}

#endif // !_YUKITENSOR_H_

