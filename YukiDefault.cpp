#include "YukiDefault.h"

namespace yuki {
	auto OutOfRange::DefaultInfo() const -> char const* {
		return "yException: Index out of range!\n����֮�У�Խ�磡";
	}

	auto BadAlloc::DefaultInfo() const -> char const* {
		return "yException: Alloc failed!\n����֮�У������ڴ�ʧ�ܣ�";
	}

	auto DivideByZero::DefaultInfo() const -> char const* {
		return "yException: Divide by zero!\n����֮�У�����Ϊ0��";
	}

	auto UnexpectedEnumParameter::DefaultInfo() const -> char const* {
		return "yException: An unexpected enumeration parameter occurred!\n����֮�У�δ֪��ö�����ͣ�";
	}
		
}
