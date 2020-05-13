#include <Windows.h>
#include "wintools.h"

// print str to the output of VS (for debugging)
void OutputDebugStringA(std::string str)
{
	OutputDebugStringA((LPCSTR)str.c_str());
}
