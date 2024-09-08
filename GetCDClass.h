#pragma once

#include <Helpers/CompileTime.h>

namespace yrpp {

class GetCDClass
{
public:
	static constexpr reference<GetCDClass, 0xA8E8E8u> const Instance{};

	int Drives[26];
	int Count;
	int unknown_6C;
};

} // namespace yrpp
