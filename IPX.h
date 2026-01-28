#pragma once

namespace yrpp {

class IPXAddressClass
{
	unsigned char NetworkNumber[4];
	unsigned char NodeAddress[6];
	char fieldA;
	char fieldB;
};
static_assert(sizeof(IPXAddressClass) == 0xC);

} // namespace yrpp
