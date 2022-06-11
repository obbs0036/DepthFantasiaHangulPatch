#pragma once
#include <Windows.h>
#include <stdio.h>

void LOG(int nColor, LPCSTR lpszLog, ...);
void LOGW(int nColor, LPWSTR lpszLog, ...);
void LOGHEX(PBYTE pbHex, DWORD dwSize);
int isReadableMemory(LPVOID pMemoryAddr);

//#define TA_CODE_PAGE_KOREAN 1

#ifdef TA_CODE_PAGE_KOREAN
// log.h
#define TMC_LOG_FIXED_MSG "누가 호출 %x\r\n"			// who is called
#else
#define TMC_LOG_FIXED_MSG "CALL %x\r\n"				// who is called
#endif


__forceinline void GetOffset(int depth)
{
	DWORD dwRetn;

	DWORD dwEbp;
	__asm push eax
	__asm mov dwEbp, ebp
	__asm pop eax

	LOG(11, "*S-----------------------------------------\r\n");
	for (int i = 0; i < depth; i++)
	{
		dwEbp = *(DWORD*)dwEbp;
		int b = isReadableMemory((LPVOID)dwEbp);
		if (b != 0)
		{
			continue;
		}
		dwRetn = *(DWORD*)(dwEbp + 4);
		LOG(11, TMC_LOG_FIXED_MSG, dwRetn);
	}
	LOG(11, "*E-----------------------------------------\r\n");
}
