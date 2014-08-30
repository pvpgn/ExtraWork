//INVESTIGATE: Do expansions have the same class name?
#define SEXP "SWarClass"
#define W3XP "Warcraft III"
#define D2XP "Diablo II"

void sexp();
void w3xp();
void d2xp();

extern "C"
{
	__declspec(dllexport) bool __cdecl ExtraWork(void *_params);
}

struct data
{
	DWORD pid;
	HANDLE handle;
	HWND hWnd;
	char classname[256];
} game;

const char *classNames[] =
{
	"SWarClass",
	"Warcraft III",
	"Diablo II"
};

const int classNameElementSize = sizeof(classNames) / sizeof(classNames[0]);