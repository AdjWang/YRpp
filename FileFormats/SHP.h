#ifndef SHP_H_
#define SHP_H_

struct RectangleStruct;

//SHP file stuff
struct SHPStruct
{
	WORD		unknown_0;
	short		Width;
	short		Height;
	short		Frames;
	DWORD		unknown_8;
	DWORD		unknown_C;
	//linked list of all SHPStructs
	SHPStruct*	Next;
	SHPStruct*	Prev;

	RectangleStruct *GetFrameHeader(RectangleStruct *buf, int FrameIndex)
		JMP_THIS(0x69E7E0);
};

//=== GLOBAL LINKED LIST OF ALL LOADED SHP FILES
// defined but not used
// static SHPStruct* SHPStruct_first=(SHPStruct*)0xB077B0;
//==============================================

#endif