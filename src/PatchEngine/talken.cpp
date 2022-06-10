#include "talken.h"

#ifdef false
//#define TA_CODE_PAGE_KOREAN 1

#ifdef TA_CODE_PAGE_KOREAN
// log.h
#define TM_LOG_FIXED_MSG "누가 호출 %x\r\n"	// who is called

// hook.cpp
#define TN_HOOK_NATIVE_CHARSET   HANGUL_CHARSET
#define TN_HOOK_FONT_NAME_GOTHIC "고딕"	// gothic

#define TM_HOOK_FONT_PATCH_COMPLATE "한글 폰트 패치 완료! %d %d %d %s\n"	// Korean font patch completed! %d %d %d
#define TM_HOOK_FIELD_OBJECT_MSG L"필드 오브젝트 : %s\n"
#define TM_HOOK_MONSTER_APPERANCE "몬스터 외형 : %02x %02x %02x\n"	// Monster Appearance:
#define TM_HOOK_MAX_HP "몬스터 : %s (MAX HP: %d)\n"
#define TM_HOOK_MONSTER_MAX_HP L"(미번역) 몬스터 : %s (MAX HP : %d)\n"	// (Untranslated) Monster: %s (MAX HP: %d)\n"
#define TM_HOOK_OPTION L"선택지 : %s\n"	// option
#define TM_HOOK_DIALOG L"대사 : %s\n"	// Dialogue: %s\n
#define TM_HOOK_SIMPLE_STR L"%s\n"
#define TM_HOOK_SIMPLE_STR2 L">>> %s\n"
#define TM_HOOK_FAILED "후킹 실패!! 프로세스를 강제 종료해주세요.\n"		// Hooking failed!! Please kill the process.

// engine.cpp
#define TM_ENGINE_DIC_NOT_EXIST1		"사전 파일이 존재하지 않습니다. 서버에서 사전 파일을 다운로드 합니다.\n"	// The dictionary file does not exist. Download the dictionary file from the server
#define TM_ENGINE_DIC_NOT_VERSION	"사전 파일에 버전 정보가 없습니다. 서버에서 사전 파일을 갱신합니다.\n"		// The dictionary file does not contain version information. The server will update the dictionary file
#define TM_ENGINE_DIC_CUR_VERSION	"현재 사전 파일 버전 %d\n"				// Current dictionary file version
#define TM_ENGINE_DIC_OTHER1		"사전 서버와의 연결에 실패하였습니다.\n"		// 
#define	TM_ENGINE_DIC_FAILED_CONNECT1	"서버 사전 파일 버전 %d\n"			// Failed to connect to dictionary server
#define	TM_ENGINE_DIC_NEWER_VERSION		"사전 파일이 최신 버전입니다.\n"	// newest version. Skip update
#define	TM_ENGINE_DIC_OTHER2		"사전 파일을 최신 버전으로 갱신합니다.\n"		//
#define	TM_ENGINE_DIC_FAILED_CONNECT2	"사전 서버와의 연결에 실패하였습니다.\n"	// Failed to connect to dictionary server
#define	TM_ENGINE_DIC_DONT_UNPACK	"사전 압축파일을 해제할 수 없습니다.\n"			// Could not unpack the pre-compressed file
#define	TM_ENGINE_DIC_NOT_EXIST2	"사전 파일이 없음. 프로세스를 종료한 후 사전파일을 복사해주세요~\n"	// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TM_ENGINE_DIC_READ			"사전에서 %d 문장 읽음.\n"				// LOG(13, "Read %d sentences from dictionary.\n", nDicCount);
#define	TM_ENGINE_CAPTION			"개발 : codetronik, 초코\n"				// Development: codetronik, Choco\n")
#define	TM_ENGINE_SEARCH			" 검색중..\n"							// Searching..
#define	TM_ENGINE_CONSOLE_MSG		"한글패치 Log Console"					// Korean Patch Log Console

#define	TM_ENGINE_LOCALE_NAME		"korean"								// Korean Locale Name

#define TM_ENGINE_DICVER_API_URL	"http://13.209.144.252/api/v1/dictionary/version"
#define TM_ENGINE_DICT_API_URL	"http://13.209.144.252/api/v1/dict-file"

#define WC_PAGE_CD_NARIVE 949  // Korean CodePage
#define WC_PAGE_CD_BIG5 950    // Traditional Chinese CodePage

#define WToMForNative( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 949, f1, f2, f3, f4, f5, f6, f7) 
#define WToMForBig5( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 950, f1, f2, f3, f4, f5, f6, f7) 

#else

#define TM_LOG_FIXED_MSG "CALL %x\r\n"	// who is called

// hook.cpp
#define TN_HOOK_NATIVE_CHARSET   SHIFTJIS_CHARSET
#define TN_HOOK_FONT_NAME_GOTHIC NULL	// gothic

#define TM_HOOK_FONT_PATCH_COMPLATE "FONT PATCH COMPLATED! %d %d %d %s\n"	// Korean font patch completed! %d %d %d
#define TM_HOOK_FIELD_OBJECT_MSG L"FIELD OBJECT : %s\n"	// Field Object
#define TM_HOOK_MONSTER_APPERANCE "MONSTER_APP : %02x %02x %02x\n"	// Monster Appearance:
#define TM_HOOK_MAX_HP "MAX_HP: %s (MAX HP: %d)\n"
#define TM_HOOK_MONSTER_MAX_HP L"(UNTRANSLATED)MONSTER : %s (MAX HP : %d)\n"	// (Untranslated) Monster: %s (MAX HP: %d)\n"
#define TM_HOOK_OPTION L"OPTION : %s\n"	// option
#define TM_HOOK_DIALOG L"DIALOG: %s\n"	// Dialogue: %s\n
#define TM_HOOK_SIMPLE_STR L"%s\n"
#define TM_HOOK_SIMPLE_STR2 L">>> %s\n"
#define TM_HOOK_FAILED "HOOKING FAILED!! PLEASE KILL THE PROCESS\n"	// Hooking failed!! Please kill the process.

// engine.cpp
#define TM_ENGINE_DIC_NOT_EXIST1		"The dictionary file does not exist. Download the dictionary file from the server.\n"
#define TM_ENGINE_DIC_NOT_VERSION	"The dictionary file does not contain version information. The server will update the dictionary file.\n"
#define TM_ENGINE_DIC_CUR_VERSION	"Current dictionary file version %d\n"
#define TM_ENGINE_DIC_OTHER1		"TM_ENGINE_DIC_OTHER1.\n"		// 
#define	TM_ENGINE_DIC_FAILED_CONNECT1	"TM_ENGINE_DIC_FAILED_CONNECT1 %d\n"			// Failed to connect to dictionary server
#define	TM_ENGINE_DIC_NEWER_VERSION		"newest version. Skip update.\n"	// newest version. Skip update
#define	TM_ENGINE_DIC_OTHER2		"TM_ENGINE_DIC_OTHER2.\n"		//
#define	TM_ENGINE_DIC_FAILED_CONNECT2	"Failed to connect to dictionary server.\n"	// Failed to connect to dictionary server
#define	TM_ENGINE_DIC_DONT_UNPACK	"Could not unpack the pre-compressed file.\n"			// Could not unpack the pre-compressed file
#define	TM_ENGINE_DIC_NOT_EXIST2	"The dictionary file does not exist. Please copy the dictionary file after terminating the process\n"	// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TM_ENGINE_DIC_READ			"Read %d sentences from dictionary.\n"				// LOG(13, "Read %d sentences from dictionary.\n", nDicCount);
#define	TM_ENGINE_CAPTION			"Development: codetronik, Choco\n"				// Development: codetronik, Choco\n
#define	TM_ENGINE_SEARCH			"Searching..\n"							// Searching..
#define	TM_ENGINE_CONSOLE_MSG		_T("Korean Patch Log Console")					// Korean Patch Log Console

#define	TM_ENGINE_LOCALE_NAME		"ja-JP"								// Japanese Locale Name

#define TM_ENGINE_DICVER_API_URL	"http://13.209.144.252/api/v1/dictionary/version"
#define TM_ENGINE_DIC_API_URL	"http://13.209.144.252/api/v1/dict-file"

#define WC_PAGE_CD_NARIVE   932 // Japanese CodePage
#define WC_PAGE_CD_BIG5     950 // Traditional Chinese CodePage

#define WToMForNative( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 932, f1, f2, f3, f4, f5, f6, f7 ) 
#define WToMForBig5( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 950, f1, f2, f3, f4, f5, f6, f7 ) 
/*
    UINT CodePage,         // コードページ
    DWORD dwFlags,         // 処理速度とマッピング方法を決定するフラグ
    LPCWSTR lpWideCharStr, // ワイド文字列のアドレス
    int cchWideChar,       // ワイド文字列の文字数
    LPSTR lpMultiByteStr,  // 新しい文字列を受け取るバッファのアドレス
    int cchMultiByte,      // 新しい文字列を受け取るバッファのサイズ
    LPCSTR lpDefaultChar,  // マップできない文字の既定値のアドレス
    LPBOOL lpUsedDefaultChar   // 既定の文字を使ったときにセットするフラグのアドレス
*/

#endif
#endif