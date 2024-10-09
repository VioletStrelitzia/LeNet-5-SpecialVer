#ifndef _YUKIMATRIXBASE_H_
#define _YUKIMATRIXBASE_H_

#include "YukiCore.h"
#include "YukiDefault.h"

#include <iostream>
#include <functional>
#include <initializer_list>
#include <iterator>

using std::istream;
using std::ostream;
using std::initializer_list;
using std::function;
using std::copy;

namespace yuki {
	template<class ElemType = double>
	struct Point;
	using point = Point<int>;

	template<class ElemType = double>
	class MatrixBase;
	using Mat = MatrixBase<double>;
	template<class ElemType>
	using Matrix = MatrixBase<ElemType>;

	template<class ElemType>
	struct Point {
		ElemType r, c;

		Point();
		Point(ElemType const& r_, ElemType const& c_);

		auto operator +  (Point const& other) const -> Point;
		auto operator -  (Point const& other) const -> Point;
		auto operator != (Point const& other) const -> bool;
		auto operator == (Point const& other) const -> bool;

		template<class ElemType_>
		friend auto operator << (ostream& os, Point<ElemType_> const& p) -> ostream&;
		template<class ElemType_>
		friend auto operator >> (istream& is, Point<ElemType_>& p) -> istream&;
	};

	template<class ElemType>
	class MatrixBase {
	public:
		using InitFuncType = function<ElemType(SizeType const& row, SizeType const& col, SizeType const& rows, SizeType const& cols)>;

	protected:
		SizeType _rows, _cols;
		ElemType** _data;

	private:
		auto reallocate(SizeType const& NewRows, SizeType const& NewCols) -> void;
		auto deallocate() -> void;
		auto InitDataRowIndex() -> void;

	public:
		MatrixBase();
		MatrixBase(SizeType const& rows, SizeType const& cols);
		MatrixBase(SizeType const& rows, SizeType const& cols, ElemType const& value);
		MatrixBase(SizeType const& rows, SizeType const& cols, InitFuncType InitFunc);
		MatrixBase(initializer_list<initializer_list<ElemType>> const& InitList);
		MatrixBase(initializer_list<ElemType> const& InitList);
		MatrixBase(MatrixBase const& MatB);
		auto operator = (MatrixBase const& MatB) -> void;
		auto operator = (ElemType const& value) -> void;
		MatrixBase(MatrixBase&& MatB);
		auto operator = (MatrixBase&& MatB) -> void {
			ElemType** tmp = _data;
			_data = MatB._data;
			MatB._data = tmp;

			SizeType x = _rows;
			_rows = MatB._rows;
			MatB._rows = x;

			x = _cols;
			_cols = MatB._cols;
			MatB._cols = x;
		}
		~MatrixBase();

		template <typename ElemType_>
		friend auto operator << (ostream& os, MatrixBase<ElemType_> const& MatB) -> ostream&;
		template <typename ElemType_>
		friend auto operator >> (istream& is, MatrixBase<ElemType_>& MatB) -> istream&;

		auto rows() const -> SizeType const&;
		auto cols() const -> SizeType const&;
		auto empty() const -> bool;
		auto resize(SizeType const& NewRows, SizeType const& NewCols) -> void;
		auto transpose() -> MatrixBase<ElemType> const&;

		enum FlipMode {
			AR180 = 0,
			AR90,
			AL90
		};
		auto flip(FlipMode const& mode = FlipMode::AR180) -> MatrixBase<ElemType> const&;

		// 重载[]运算符
		auto operator [] (SizeType const& row) const -> ElemType const*;
		auto operator [] (SizeType const& row) -> ElemType*;

		// at访问函数
		auto at(SizeType const& row, SizeType const& col) const -> ElemType const&;
		auto at(SizeType const& row, SizeType const& col) -> ElemType&;
		auto at(SizeType const& row) const -> ElemType const&;
		auto at(SizeType const& row) -> ElemType&;
		auto at(point const& p) const -> ElemType const&;
		auto at(point const& p) -> ElemType&;

		auto operator +	 (MatrixBase const& MatB) const -> MatrixBase;
		auto operator += (MatrixBase const& MatB) -> MatrixBase&;
		auto operator += (ElemType const& value) -> MatrixBase&;
		auto operator -  (MatrixBase const& MatB) const -> MatrixBase;
		auto operator -= (MatrixBase const& MatB) -> MatrixBase&;
		auto operator *  (MatrixBase const& MatB) const -> MatrixBase;
		auto operator *= (MatrixBase const& MatB) -> MatrixBase&;
	};
}

namespace yuki {
	template<class ElemType>
	Point<ElemType>::Point() :
		r(), c() {}

	template<class ElemType>
	Point<ElemType>::Point(ElemType const& r_, ElemType const& c_) :
		r(r_), c(c_) {}

	template<class ElemType>
	auto Point<ElemType>::operator + (Point const& other) const -> Point {
		return Point(r + other.r, c + other.c);
	}

	template<class ElemType>
	auto Point<ElemType>::operator - (Point const& other) const -> Point {
		return Point(r - other.r, c - other.c);
	}

	template<class ElemType>
	auto Point<ElemType>::operator != (Point const& other) const -> bool {
		return r != other.r || c != other.c;
	}

	template<class ElemType>
	auto Point<ElemType>::operator == (Point const& other) const -> bool {
		return r == other.r && c == other.c;
	}

	template<class ElemType>
	auto operator << (ostream& os, Point<ElemType> const& p) -> ostream& {
		os << '(' << p.r << ", " << p.c << ')';
		return os;
	}

	template<class ElemType>
	auto operator >> (istream& is, Point<ElemType>& p) -> istream& {
		is >> p.r >> p.c;
		return is;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::reallocate(SizeType const& NewRows, SizeType const& NewCols) -> void {
		if (_rows == NewRows && _cols == NewCols) return;
		if (_data == nullptr) {
			if (NewRows == 0 || NewCols == 0) {
				_rows = 0;
				_cols = 0;
				return;
			}
			_data = new ElemType* [NewRows]; if (_data == nullptr) throw BadAlloc();
			*_data = new ElemType[NewRows * NewCols]; if (*_data == nullptr) throw BadAlloc();
		} else {
			if (NewRows * NewCols > _rows * _cols && NewRows > _rows) {
				delete[] *_data;
				delete[] _data;
				_data = new ElemType* [NewRows]; if (_data == nullptr) throw BadAlloc();
				*_data = new ElemType[NewRows * NewCols]; if (*_data == nullptr) throw BadAlloc();
			} else if (NewRows * NewCols > _rows * _cols) {
				delete[] *_data;
				*_data = new ElemType[NewRows * NewCols]; if (*_data == nullptr) throw BadAlloc();
			} else if (NewRows > _rows) {
				ElemType* ptr = *_data;
				delete[] _data;
				_data = new ElemType* [NewRows]; if (_data == nullptr) throw BadAlloc();
				*_data = ptr;
			}
		}
		_rows = NewRows;
		_cols = NewCols;
		InitDataRowIndex();
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::deallocate() -> void {
		if (_data == nullptr) return;
		delete[] *_data;
		delete[] _data;
		_data = nullptr;
		
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::InitDataRowIndex() -> void {
		for (SizeType r = 1, i = _cols; r < _rows; ++r, i += _cols)
			_data[r] = *_data + i;
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase() :
		_rows(0), _cols(0), _data(nullptr) {}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(SizeType const& rows, SizeType const& cols) :
		_rows(rows), _cols(cols), _data(nullptr) {
		if (rows != 0 && cols != 0) {
			_data = new ElemType * [rows];
			if (_data == nullptr) throw BadAlloc();
			*_data = new ElemType[rows * cols];
			if (*_data == nullptr) throw BadAlloc();
			InitDataRowIndex();
		}
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(SizeType const& rows, SizeType const& cols, ElemType const& value) :
		_rows(rows), _cols(cols), _data(nullptr) {
		if (rows != 0 && cols != 0) {
			_data = new ElemType * [rows];
			if (_data == nullptr) throw BadAlloc();
			*_data = new ElemType[rows * cols];
			if (*_data == nullptr) throw BadAlloc();
			InitDataRowIndex();
			for (SizeType r = 0; r < _rows; ++r) {
				for (SizeType c = 0; c < _cols; ++c) {
					_data[r][c] = value;
				}
			}
		}
		//ElemType tmpv = value;
		//SizeType i = 1, j = 2, sizei = sizeof(ElemType);

		//memcpy(*_data, &tmpv, sizei);
		//for (; j < size; i += i, j += j, sizei += sizei)
		//	memcpy(*_data + i, *_data, sizei);
		//memcpy(*_data + i, *_data, (size - i) * sizeof(ElemType));
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(SizeType const& rows, SizeType const& cols, InitFuncType InitFunc) :
		_rows(rows), _cols(cols), _data(nullptr) {
		if (rows != 0 && cols != 0) {
			_data = new ElemType * [rows];
			if (_data == nullptr) throw BadAlloc();
			*_data = new ElemType[rows * cols];
			if (*_data == nullptr) throw BadAlloc();
			InitDataRowIndex();
			for (SizeType r = 0; r < _rows; ++r) {
				for (SizeType c = 0; c < _cols; ++c) {
					_data[r][c] = InitFunc(r, c, _rows, _cols);
				}
			}
		}

	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(initializer_list<initializer_list<ElemType>> const& InitList) :
		_rows(static_cast<int>(InitList.size())), _cols(0), _data(new ElemType* [_rows]) { if (_data == nullptr) throw BadAlloc();
		for (auto const& list : InitList) {
			if (_cols < static_cast<int>(list.size()))
				_cols = static_cast<int>(list.size());
		}
		*_data = new ElemType[_rows * _cols]; if (*_data == nullptr) throw BadAlloc();
		InitDataRowIndex();

		SizeType r = 0;
		for (auto const& list : InitList) {
			SizeType c = 0;
			for (auto const& it : list) _data[r][c++] = it;
			while (c < _cols) _data[r][c++] = 0;
			++r;
		}
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(initializer_list<ElemType> const& InitList) :
		_rows(InitList.size()), _cols(1), _data(new ElemType* [_rows]) { if (_data == nullptr) throw BadAlloc();
		*_data = new ElemType[_rows]; if (*_data == nullptr) throw BadAlloc();
		InitDataRowIndex();
		SizeType r = 0;
		for (auto const& it : InitList) {
			_data[r++][0] = it;
		}
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(MatrixBase const& MatB) :
		_rows(MatB._rows), _cols(MatB._cols), _data(new ElemType* [_rows]) {
		if (_data == nullptr) throw BadAlloc();
		*_data = new ElemType[_rows * _cols];
		if (*_data == nullptr) throw BadAlloc();
		InitDataRowIndex();
		for (SizeType r = 0; r < _rows; ++r) {
			for (SizeType c = 0; c < _cols; ++c) {
				_data[r][c] = MatB._data[r][c];
			}
		}
		//copy(*MatB._data, *MatB._data + (MatB._rows * MatB._cols), _data);
		//memcpy(*_data, *MatB._data, _rows * _cols * sizeof(ElemType));
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator = (MatrixBase const& MatB) -> void {
		reallocate(MatB._rows, MatB._cols);
		for (SizeType r = 0; r < _rows; ++r) {
			for (SizeType c = 0; c < _cols; ++c) {
				_data[r][c] = MatB._data[r][c];
			}
		}
		//copy(*MatB._data, *MatB._data + MatB._rows * MatB._cols, _data);
		//memcpy(*_data, *MatB._data, size * sizeof(ElemType));
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator = (ElemType const& value) -> void {
		for (SizeType r = 0; r < _rows; ++r) {
			for (SizeType c = 0; c < _cols; ++c) {
				_data[r][c] = value;
			}
		}
	}

	template<class ElemType>
	MatrixBase<ElemType>::MatrixBase(MatrixBase&& MatB) {
		ElemType** tmp = _data;
		_data = MatB._data;
		MatB._data = tmp;

		SizeType x = _rows;
		_rows = MatB._rows;
		MatB._rows = x;

		x = _cols;
		_cols = MatB._cols;
		MatB._cols = x;
	}

	template<class ElemType>
	MatrixBase<ElemType>::~MatrixBase() {
		deallocate();
	}

	template<class ElemType>
	auto operator << (ostream& os, MatrixBase<ElemType> const& MatB) -> ostream& {
		for (SizeType r = 0; r < MatB._rows; ++r) {
			for (SizeType c = 0; c < MatB._cols; ++c)
				os << MatB._data[r][c] << ' ';
			os << "\n";
		}
		os << typeid(MatB).name() << " (" << MatB._rows << ", " << MatB._cols << ")";
		return os;
	}

	template<class ElemType>
	auto operator >> (istream& is, MatrixBase<ElemType>& MatB) -> istream& {
		SizeType size = MatB._rows * MatB._cols;
		for (SizeType i = 0; i < size; ++i)
			is >> *MatB._data[i];
		return is;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::rows() const -> SizeType const& { return _rows; }

	template<class ElemType>
	auto MatrixBase<ElemType>::cols() const -> SizeType const& { return _cols; }

	template<class ElemType>
	auto MatrixBase<ElemType>::empty() const -> bool { return _rows == 0 || _cols == 0; }

	template<class ElemType>
	auto MatrixBase<ElemType>::resize(SizeType const& NewRows, SizeType const& NewCols) -> void {
		reallocate(NewRows, NewCols);
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::transpose() -> MatrixBase<ElemType> const& {
		if (_rows < _cols) {
			ElemType* data = *_data;
			delete[] _data;
			_data = new ElemType*[_cols];
			*_data = data;
		}
		SizeType tmp = _rows;
		_rows = _cols;
		_cols = tmp;
		InitDataRowIndex();
		return *this;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::flip(FlipMode const& mode) -> MatrixBase<ElemType> const& {
		switch (mode) {
		case FlipMode::AR180:
			for (SizeType r = 0; r < (_rows >> 1); ++r) {
				for (SizeType c = 0; c < _cols; ++c) {
					std::swap(_data[r][c], _data[_rows - 1 - r][_cols - 1 - c]);
				}
			}
			if (_rows & 1) {
				for (SizeType c = 0; c < _cols; ++c) {
					std::swap(_data[_rows >> 1][c], _data[_rows >> 1][_cols - 1 - c]);
				}
			}
		break;
		case FlipMode::AR90:
			break;
		case FlipMode::AL90:
			break;
		default:
			break;
		}
		return *this;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator [] (SizeType const& row) const -> ElemType const* {
		return _data[row];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator [] (SizeType const& row) -> ElemType* {
		return _data[row];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(SizeType const& row, SizeType const& col) const -> ElemType const& {
		return _data[row][col];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(SizeType const& row, SizeType const& col) -> ElemType& {
		return _data[row][col];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(SizeType const& row) const->ElemType const& {
		
		return _data[row][0];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(SizeType const& row) -> ElemType& {
		
		return _data[row][0];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(point const& p) const -> ElemType const& {
		return _data[p.r][p.c];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::at(point const& p) -> ElemType& {
		return _data[p.r][p.c];
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator + (MatrixBase const& MatB) const -> MatrixBase {
		MatrixBase<ElemType> dst(*this);
		SizeType size = _rows * _cols;
		for (SizeType i = 0; i < size; ++i) (*dst._data)[i] += (*MatB._data)[i];
		return dst;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator += (MatrixBase const& MatB) -> MatrixBase& {
		SizeType size = _rows * _cols;
		for (SizeType i = 0; i < size; ++i) (*_data)[i] += (*MatB._data)[i];
		return *this;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator += (ElemType const& value)->MatrixBase& {
		SizeType size = _rows * _cols;
		for (SizeType i = 0; i < size; ++i) (*_data)[i] += value;
		return *this;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator - (MatrixBase const& MatB) const -> MatrixBase {
		MatrixBase<ElemType> dst(*this);
		SizeType size = _rows * _cols;
		for (SizeType i = 0; i < size; ++i) (*dst._data)[i] -= (*MatB._data)[i];
		return dst;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator -= (MatrixBase const& MatB) -> MatrixBase& {
		SizeType size = _rows * _cols;
		for (SizeType i = 0; i < size; ++i) (*_data)[i] -= (*MatB._data)[i];
		return *this;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator * (MatrixBase const& MatB) const -> MatrixBase {
		MatrixBase<ElemType> dst(_rows, MatB._cols, 0);
		for (SizeType r = 0; r < dst._rows; ++r) {
			for (SizeType c = 0; c < dst._cols; ++c) {
				for (SizeType i = 0; i < _cols; ++i)
					dst._data[r][c] += _data[r][i] * MatB._data[i][c];
			}
		}
		return dst;
	}

	template<class ElemType>
	auto MatrixBase<ElemType>::operator *= (MatrixBase const& MatB) -> MatrixBase& {
		for (SizeType r = 0; r < _rows; ++r) {
			for (SizeType c = 0; c < MatB._cols; ++c) {
				_data[r][c] = 0;
				for (SizeType i = 0; i < _cols; ++i)
					_data[r][c] += _data[r][i] * MatB._data[i][c];
			}
		}
		return *this;
	}

}

#endif // !_YUKIMATRIXBASE_H_
