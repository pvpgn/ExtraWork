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
	char OutBuffer[4096];
} extrawork;

struct data
{
	DWORD pid;
	HANDLE handle;
	HWND hWnd;
	char classname[256];
} game;

extern "C"
{
	__declspec(dllexport) BOOL __cdecl ExtraWork(EXTRAWORK inStruct);
}

const char *classNames[] =
{
	"SWarClass",
	"Warcraft III",
	"Diablo II"
};

const int classNameElementSize = sizeof(classNames) / sizeof(classNames[0]);