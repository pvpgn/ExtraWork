/*
*	See UNLICENSE file for license details
*	Refer to <http://unlicense.org/> if you have not received a copy of UNLICENSE
*/
#include "ExtraWork.h"

EXPORT BOOL __fastcall ExtraWork(EXTRAWORK *ExtraWork, int)
{
	if (ExtraWork == nullptr)
		return FALSE;

	switch (ExtraWork->Game)
	{
	case 0x01:
	case 0x02:
	case 0x03:
	case 0x04:
		break;
	default:
		return FALSE;
	}

	return TRUE;
}