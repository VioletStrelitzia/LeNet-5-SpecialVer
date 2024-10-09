#include "DLObject.h"
namespace yuki {
namespace atri {

string const DLObject::typeNames[DLObject::typeNum]{
	"Valid",
	"Layer",
	"Optimizer",
	"Model"
};

DLObject::DLObject(DLObjecType const& type_, string const& name_) :
	type(type_), name(name_) {
	if (name == "") {
		name = typeNames[static_cast<int>(type_)];
	}
}

}}
