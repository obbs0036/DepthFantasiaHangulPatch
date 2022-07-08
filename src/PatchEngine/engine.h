#pragma once

typedef struct _DIC
{
	/*
	original mean:
	Chinese -> Korean Dictionary

	char szChinese[512];
	int nChineseLen;
	char szKorean[512];

	Changed by obbs0036g
	universal dictionary : src word -> dst word

	(Language convert and Initialize dictionary)

	*/
	char szSrcword[512];	// from Chinese (and initialize settings)
	int nSrcwordLen;
	char szDstword[512];	// to Korean or Japanese or other parameters
	int nDstwordLen;
	int nValue;
	int nItemType;
} DIC;

int LoadDictionary(char* szFileName, DIC *dic, BOOL bNeedBlank);
