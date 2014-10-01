/*
*	ExtraWork Client - Loads an ExtraWork DLL for information
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

struct EXTRAWORK
{
	WORD GameType;
	WORD Length;
	char OutBuffer[1024];
};

enum GameType
{
	Diablo2 = 0x1,
	Warcraft3 = 0x2,
	Starcraft = 0x3,
	WorldOfWarcraft = 0x4
};

typedef BOOL(__fastcall *ExtraWorkProc)(void *);