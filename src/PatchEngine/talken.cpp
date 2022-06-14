//
// Korean And English And Japanese Code Talken Switcher Module
//

#include "talken.h"

char TT_ENGINE_LOCALE_NAME[64] = { 0x00 };
UINT WC_PAGE_CD_NATIVE = 932;
UINT WC_PAGE_CD_BIG5 = 950;

int TT_HOOK_NATIVE_CHARSET = 128;
char TT_HOOK_FONT_NAME_DEF[64] = { 0x00 };

#define	_TT_ENGINE_LOCALE_NAME		"ja-JP"		// Japanese Locale Name
#define _WC_PAGE_CD_NATIVE   932	// Japanese CodePage
#define _WC_PAGE_CD_BIG5     950	// Traditional Chinese CodePage


void initTalken()
{
	strcat(TT_ENGINE_LOCALE_NAME, _TT_ENGINE_LOCALE_NAME);
	WC_PAGE_CD_NATIVE = _WC_PAGE_CD_NATIVE;
	WC_PAGE_CD_BIG5 = _WC_PAGE_CD_BIG5;

	int TT_HOOK_NATIVE_CHARSET = _TT_HOOK_NATIVE_CHARSET;
	memset(TT_HOOK_FONT_NAME_DEF, 0x00, 64);
	strcat(TT_HOOK_FONT_NAME_DEF, _TT_HOOK_FONT_NAME_DEF);

}