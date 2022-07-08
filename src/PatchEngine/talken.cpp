//
// Korean And English And Japanese Code Talken Switcher Module
//

#include "talken.h"
#include "engine.h"
#include "log.h"

DIC* initial_dic;
int initial_nDicCount;

char TT_ENGINE_LOCALE_NAME[64] = { 0x00 };
UINT WC_PAGE_CD_NATIVE = 932;
UINT WC_PAGE_CD_BIG5 = 950;

int TT_HOOK_NATIVE_CHARSET = 128;
char TT_HOOK_FONT_NAME_DEF[64] = { 0x00 };

#define	_TT_ENGINE_LOCALE_NAME		"ja-JP"		// Japanese Locale Name
#define _WC_PAGE_CD_NATIVE   932	// Japanese CodePage
#define _WC_PAGE_CD_BIG5     950	// Traditional Chinese CodePage

UINT TI_HOOK_FONT_H10 = 10;
UINT TI_HOOK_FONT_H12 = 12;
UINT TI_HOOK_FONT_H14 = 14;
UINT TI_HOOK_FONT_H16 = 16;

BOOLEAN initTalken()
{
	DIC* initial_dic = (DIC*)malloc(sizeof(DIC) * 100);
	ZeroMemory(initial_dic, sizeof(DIC) * 100);

	initial_nDicCount = LoadDictionary(TT_DIC_INITIAL, initial_dic, FALSE);	// not added blank(set false is)

	strcat(TT_ENGINE_LOCALE_NAME, _TT_ENGINE_LOCALE_NAME);
	WC_PAGE_CD_NATIVE = _WC_PAGE_CD_NATIVE;
	WC_PAGE_CD_BIG5 = _WC_PAGE_CD_BIG5;

	int TT_HOOK_NATIVE_CHARSET = _TT_HOOK_NATIVE_CHARSET;
	memset(TT_HOOK_FONT_NAME_DEF, 0x00, 64);
	strcat(TT_HOOK_FONT_NAME_DEF, _TT_HOOK_FONT_NAME_DEF);

	TI_HOOK_FONT_H10 = _TI_HOOK_FONT_H10_DEF;
	TI_HOOK_FONT_H12 = _TI_HOOK_FONT_H12_DEF;
	TI_HOOK_FONT_H14 = _TI_HOOK_FONT_H14_DEF;
	TI_HOOK_FONT_H16 = _TI_HOOK_FONT_H16_DEF;

/*
	token list

	CI_PAGE_CD_BIG5 = 950
	CI_PAGE_CD_NATIVE = 932
	CI_HOOK_NATIVE_CHARSET = 128
	CS_ENGINE_LOCALE_NAME = ja - JP
	CS_HOOK_FONT_NAME_DEF = Noto Sans CJK HK
	CI_LOG_LEVEL = 0
*/

	UINT idx;
	for (idx = 0; idx < initial_nDicCount; idx++ ) {
		if ( initial_dic[idx].nSrcwordLen > 0 ) {
			if (initial_dic[idx].nItemType == 0) {
				// string talken
				if (strcmp(initial_dic[idx].szSrcword, "_CS_HOOK_FONT_NAME_DEF") == 0) {
					memset(TT_HOOK_FONT_NAME_DEF, 0x00, 64);
					strcat(TT_HOOK_FONT_NAME_DEF, initial_dic[idx].szDstword);
				}
				if (strcmp(initial_dic[idx].szSrcword, "_CS_ENGINE_LOCALE_NAME") == 0) {
					memset(TT_ENGINE_LOCALE_NAME, 0x00, 64);
					strcat(TT_ENGINE_LOCALE_NAME, initial_dic[idx].szDstword);
				}
			}
			if (initial_dic[idx].nItemType == 1) {
				//
				if (strcmp(initial_dic[idx].szSrcword, "_CI_LOG_LEVEL") == 0) {
					logLevel = initial_dic[idx].nValue;
				}

				//
				if (strcmp(initial_dic[idx].szSrcword, "_CI_HOOK_FONT_H10") == 0) {
					TI_HOOK_FONT_H10 = initial_dic[idx].nValue;
				}
				if (strcmp(initial_dic[idx].szSrcword, "_CI_HOOK_FONT_H12") == 0) {
					TI_HOOK_FONT_H12 = initial_dic[idx].nValue;
				}
				if (strcmp(initial_dic[idx].szSrcword, "_CI_HOOK_FONT_H14") == 0) {
					TI_HOOK_FONT_H14 = initial_dic[idx].nValue;
				}
				if (strcmp(initial_dic[idx].szSrcword, "_CI_HOOK_FONT_H16") == 0) {
					TI_HOOK_FONT_H16 = initial_dic[idx].nValue;
				}

				// Change Code page For Universal Dictionary
				if (strcmp(initial_dic[idx].szSrcword, "_CI_PAGE_CD_NATIVE") == 0) {
					WC_PAGE_CD_NATIVE = initial_dic[idx].nValue;
				}
				if (strcmp(initial_dic[idx].szSrcword, "_CI_HOOK_NATIVE_CHARSET") == 0) {
					TT_HOOK_NATIVE_CHARSET = initial_dic[idx].nValue;
				}
			}
		}
	}

	BOOL result = false;
	result = AllocConsole();
	return result;
}