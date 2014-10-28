/*
*	ExtraWork - Allows PvPGN clients to load this DLL and executes code for specific clients
*	Copyright (C) 2014  xboi209 (xboi209@gmail.com)
*
*	This program is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	This program is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

//INVESTIGATE: Do expansions have the same class name?
#define SEXP "SWarClass"
#define W3XP "Warcraft III"
#define D2XP "Diablo II"

void sexp();
void w3xp();
void d2xp();

struct EXTRAWORK
{
	WORD GameType;
	WORD Length;
	char OutBuffer[1024];
};

struct data
{
	DWORD pid;
	HANDLE handle;
	HWND hWnd;
	char classname[256];
} game;


BOOL __fastcall ExtraWork(EXTRAWORK *inStruct, int unused);
void sexp();
void w3xp();
void d2xp();
BOOL CALLBACK enumWindowsProc(HWND hWnd, LPARAM lParam);
 
const char *classNames[] =
{
	SEXP,
	W3XP,
	D2XP
};

const int classNameElementSize = sizeof(classNames) / sizeof(classNames[0]);
