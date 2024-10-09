#include "YukiDefault.h"

namespace yuki {
	auto OutOfRange::DefaultInfo() const -> char const* {
		return "yException: Index out of range!\n意料之中：越界！";
	}

	auto BadAlloc::DefaultInfo() const -> char const* {
		return "yException: Alloc failed!\n意料之中：申请内存失败！";
	}

	auto DivideByZero::DefaultInfo() const -> char const* {
		return "yException: Divide by zero!\n意料之中：除数为0！";
	}

	auto UnexpectedEnumParameter::DefaultInfo() const -> char const* {
		return "yException: An unexpected enumeration parameter occurred!\n意料之中：未知的枚举类型！";
	}
		
}
