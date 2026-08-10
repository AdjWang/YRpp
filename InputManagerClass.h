#pragma once

#include <GameOptionsClass.h>

#include <Helpers/CompileTime.h>

namespace yrpp {

class InputManagerClass {
public:
	static constexpr reference<InputManagerClass*, 0x87F770u> const Instance{};

	bool HandleKeyboard(uint16_t button, bool is_up)
		{ JMP_THIS(0x54F200); }

	byte DoSomething()
		{ JMP_THIS(0x54F720); }

	bool IsKeyPressed(int key) const
		{ JMP_THIS(0x54F5C0); }

	bool IsForceFireKeyPressed() const {
		return this->IsKeyPressed(GameOptionsClass::Instance->KeyForceFire1)
			|| this->IsKeyPressed(GameOptionsClass::Instance->KeyForceFire2);
	}

	bool IsForceMoveKeyPressed() const {
		return this->IsKeyPressed(GameOptionsClass::Instance->KeyForceMove1)
			|| this->IsKeyPressed(GameOptionsClass::Instance->KeyForceMove2);
	}

	bool IsForceSelectKeyPressed() const {
		return this->IsKeyPressed(GameOptionsClass::Instance->KeyForceSelect1)
			|| this->IsKeyPressed(GameOptionsClass::Instance->KeyForceSelect2);
	}

  int MouseClickPos_x;
  int MouseClickPos_y;
  int field_8;
  int field_C;
  int field_10;
  char KeyState[256];
  wchar_t Buffer[256];
  int Head;
  int Tail;
};

} // namespace yrpp
