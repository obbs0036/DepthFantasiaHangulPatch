#pragma once
#include <Windows.h>
#include <stdio.h>

void LOG(int nColor, LPCSTR lpszLog, ...);
void LOGW(int nColor, LPWSTR lpszLog, ...);
void LOGHEX(PBYTE pbHex, DWORD dwSize);