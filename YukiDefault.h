#pragma once
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

namespace yuki {
	struct DefaultBase : public std::exception {
		virtual auto DefaultInfo() const -> char const* = 0;
	};

	struct OutOfRange : public DefaultBase {
		auto DefaultInfo() const -> char const* override;
	};

	struct BadAlloc : public DefaultBase {
		auto DefaultInfo() const -> char const* override;
	};

	struct DivideByZero : public DefaultBase {
		auto DefaultInfo() const -> char const* override;
	};

	struct UnexpectedEnumParameter : public DefaultBase {
		auto DefaultInfo() const -> char const* override;
	};
	
	
}

