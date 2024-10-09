#pragma once

#include <string>

using std::string;

namespace yuki {
namespace atri {

class DLObject {
private:
	static int const typeNum = 4;
	static string const typeNames[typeNum];

public:
	enum DLObjecType {
		VALID = 0,
		LAYER,
		OPTIMIZER,
		MODEL
	};

	DLObjecType type;
	string name;

	DLObject(DLObjecType const& type_ = DLObjecType::VALID, string const& name_ = "");
};

}}
