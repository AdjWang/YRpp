#pragma once

#include <ControlClass.h>

namespace yrpp {

class NOVTABLE ToggleClass : public ControlClass
{
public:
	//Non virtual
	void TurnOn() { JMP_THIS(0x723EA0); }
	void TurnOff() { JMP_THIS(0x723EB0); }

	//Statics

	//Constructors
	ToggleClass(unsigned int nID, int nX, int nY, int nWidth, int nHeight) noexcept
		: ToggleClass(noinit_t()) { JMP_THIS(0x723E60); }

protected:
	explicit __forceinline ToggleClass(noinit_t)  noexcept
		: ControlClass(noinit_t())
	{
	}

	//Properties
public:

	bool IsPressed;
	bool IsOn;
	DWORD ToggleType;
};
} // namespace yrpp
