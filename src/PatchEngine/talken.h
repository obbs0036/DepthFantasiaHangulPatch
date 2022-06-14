//
// Convert For Korea Message <-> English Message
// (Made it possible to switch messages to avoid garbled characters)
//
#include <windows.h>
#include <tchar.h>

// Environ Id( For All Locale )

// log
#define	TENV_ID_LOG_FIXED_MSG 1001				    // 	"누가 호출 %x\r\n"	// who is called

// hook
#define	TENV_ID_HOOK_FONT_PATCH_COMPLATE    2001	// "한글 폰트 패치 완료! %d %d %d %s\n"	// Korean font patch completed! %d %d %d
#define	TENV_ID_HOOK_FIELD_OBJECT_MSG       2002	// L"필드 오브젝트 : %s\n"
#define	TENV_ID_HOOK_MONSTER_APPERANCE      2003	//  "몬스터 외형 : %02x %02x %02x\n"	// Monster Appearance:
#define	TENV_ID_HOOK_MAX_HP                 2004	//  "몬스터 : %s (MAX HP: %d)\n"
#define	TENV_ID_HOOK_MONSTER_MAX_HP         2005	// L"(미번역) 몬스터 : %s (MAX HP : %d)\n"	// (Untranslated) Monster: %s (MAX HP: %d)\n"
#define	TENV_ID_HOOK_OPTION                 2006	// L"선택지 : %s\n"	// option
#define	TENV_ID_HOOK_DIALOG                 2007	// L"대사 : %s\n"	// Dialogue: %s\n
#define	TENV_ID_HOOK_SIMPLE_STR             2008	// L"%s\n"
#define	TENV_ID_HOOK_SIMPLE_STR2            2009	// L">>> %s\n"
#define	TENV_ID_HOOK_FAILED                 2010	// "후킹 실패!! 프로세스를 강제 종료해주세요.\n"		// Hooking failed!! Please kill the process.
// engine
#define	TENV_ID_ENGINE_DIC_NOT_EXIST1       3001	// "사전 파일이 존재하지 않습니다. 서버에서 사전 파일을 다운로드 합니다.\n"	// The dictionary file does not exist. Download the dictionary file from the server
#define	TENV_ID_ENGINE_DIC_NOT_VERSION      3002	// "사전 파일에 버전 정보가 없습니다. 서버에서 사전 파일을 갱신합니다.\n"		// The dictionary file does not contain version information. The server will update the dictionary file
#define	TENV_ID_ENGINE_DIC_CUR_VERSION      3003	// "현재 사전 파일 버전 %d\n"				// Current dictionary file version
#define	TENV_ID_ENGINE_DIC_OTHER1           3004	// "사전 서버와의 연결에 실패하였습니다.\n"		// 
#define	TENV_ID_ENGINE_DIC_FAILED_CONNECT1  3005	// "서버 사전 파일 버전 %d\n"			// Failed to connect to dictionary server
#define	TENV_ID_ENGINE_DIC_NEWER_VERSION    3006	// "사전 파일이 최신 버전입니다.\n"	// newest version. Skip update
#define	TENV_ID_ENGINE_DIC_OTHER2           3007	// "사전 파일을 최신 버전으로 갱신합니다.\n"		//
#define	TENV_ID_ENGINE_DIC_FAILED_CONNECT2  3008	// "사전 서버와의 연결에 실패하였습니다.\n"	// Failed to connect to dictionary server
#define	TENV_ID_ENGINE_DIC_DONT_UNPACK      3009	// "사전 압축파일을 해제할 수 없습니다.\n"			// Could not unpack the pre-compressed file
#define	TENV_ID_ENGINE_DIC_NOT_EXIST2       3010	// "사전 파일이 없음. 프로세스를 종료한 후 사전파일을 복사해주세요~\n"	// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TENV_ID_ENGINE_DIC_READ             3011	// "사전에서 %d 문장 읽음.\n"				// LOG(13, "Read %d sentences from dictionary.\n", nDicCount);
#define	TENV_ID_ENGINE_CAPTION              3012	// "개발 : codetronik, 초코\n"				// Development: codetronik, Choco\n")
#define	TENV_ID_ENGINE_SEARCH               3013	// " 검색중..\n"							// Searching..
#define	TENV_ID_ENGINE_CONSOLE_MSG          3014    // 	"한글패치 Log Console"					// Korean Patch Log Console


// 
// def TT	for API					TAG
// def TMC_ for LOG()				char *
// def TMW_ for LOGW()				wchar *
// def TT_DIC for LoadDictionary	char *
// 


//#define TT_CODE_PAGE_KOREAN 1

// For Korean(Original Locale)
#ifdef TT_CODE_PAGE_KOREAN
// log.h
#define TMC_LOG_FIXED_MSG "누가 호출 %x\r\n"									// who is called

// hook.cpp
#define TT_HOOK_NATIVE_CHARSET   HANGUL_CHARSET
#define TT_HOOK_FONT_NAME_DEF "고딕"											// gothic

#define TMC_HOOK_FONT_PATCH_IREG "FONT PATCH IREG? %d %d %d %s\n"											// Korean font patch completed! %d %d %d
#define TMC_HOOK_FONT_PATCH_COMPLATE	"한글 폰트 패치 완료! %d %d %d %s\n"	// Korean font patch completed! %d %d %d

#define TMW_HOOK_FIELD_OBJECT_MSG L"필드 오브젝트 : %s\n"

#define TMC_HOOK_MONSTER_APPERANCE "몬스터 외형 : %02x %02x %02x\n"			// Monster Appearance:
#define TMC_HOOK_MAX_HP "몬스터 : %s (MAX HP: %d)\n"

#define TMW_HOOK_MONSTER_MAX_HP L"(미번역) 몬스터 : %s (MAX HP : %d)\n"		// (Untranslated) Monster: %s (MAX HP: %d)\n"
#define TMW_HOOK_OPTION L"선택지 : %s\n"									// option
#define TMW_HOOK_DIALOG L"대사 : %s\n"										// Dialogue: %s\n
#define TMW_HOOK_SIMPLE_STR L"%s\n"											//
#define TMW_HOOK_SIMPLE_STR2 L">>> %s\n"									//

#define TMC_HOOK_FAILED "후킹 실패!! 프로세스를 강제 종료해주세요.\n"		// Hooking failed!! Please kill the process.

#define TT_DIC_DIALOG			"korean_dialogue.txt"						// Dict For Dialog
#define TT_DIC_FIELDOBJECT		"korean_fieldobject.txt"					// Dict For FieldObject
#define TT_DIC_SELECT			"korean_select.txt"							// Dict For Select
#define TT_DIC_MONSTER			"korean_monster.txt"						// Dict For Monster
#define TT_DIC_SKILL_DESC		"korean_skilldescription.txt"				// Dict For SkillDescript
#define TT_DIC_SKILL			"korean_skill.txt"							// Dict For Skill
#define TT_DIC_JOB				"korean_job.txt"							// Dict For Job
#define TT_DIC_ITEM				"korean_item.txt"							// Dict For Item

// engine.cpp
#define TMC_ENGINE_DIC_NOT_EXIST1		"사전 파일이 존재하지 않습니다. 서버에서 사전 파일을 다운로드 합니다.\n"	// The dictionary file does not exist. Download the dictionary file from the server
#define TMC_ENGINE_DIC_NOT_VERSION	"사전 파일에 버전 정보가 없습니다. 서버에서 사전 파일을 갱신합니다.\n"			// The dictionary file does not contain version information. The server will update the dictionary file
#define TMC_ENGINE_DIC_CUR_VERSION	"현재 사전 파일 버전 %d\n"														// Current dictionary file version
#define TMC_ENGINE_DIC_OTHER1		"사전 서버와의 연결에 실패하였습니다.\n"										// 
#define	TMC_ENGINE_DIC_FAILED_CONNECT1	"서버 사전 파일 버전 %d\n"													// Failed to connect to dictionary server
#define	TMC_ENGINE_DIC_NEWER_VERSION		"사전 파일이 최신 버전입니다.\n"											// newest version. Skip update
#define	TMC_ENGINE_DIC_OTHER2		"사전 파일을 최신 버전으로 갱신합니다.\n"										//
#define	TMC_ENGINE_DIC_FAILED_CONNECT2	"사전 서버와의 연결에 실패하였습니다.\n"									// Failed to connect to dictionary server
#define	TMC_ENGINE_DIC_DONT_UNPACK	"사전 압축파일을 해제할 수 없습니다.\n"											// Could not unpack the pre-compressed file
#define	TMC_ENGINE_DIC_NOT_EXIST2	"사전 파일이 없음. 프로세스를 종료한 후 사전파일을 복사해주세요~\n"				// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TMC_ENGINE_DIC_READ			"사전에서 %d 문장 읽음.\n"														// LOG(13, "Read %d sentences from dictionary.\n", nDicCount);
#define	TMC_ENGINE_CAPTION			"개발 : codetronik, 초코\n"														// Development: codetronik, Choco\n")
#define	TMC_ENGINE_SEARCH			" 검색중..\n"																	// Searching..

#define	TMW_ENGINE_CONSOLE_MSG		"한글패치 Log Console"															// Korean Patch Log Console


#define	TT_ENGINE_LOCALE_NAME		"korean"																		// Korean Locale Name

#define TT_ENGINE_DICVER_API_URL	"http://13.209.144.252/api/v1/dictionary/version"
#define TT_ENGINE_DIC_API_URL	"http://13.209.144.252/api/v1/dict-file"

// trans.cpp
#define TM_TRANS_AMBASSADOR		"번역 대사 : %s\n"	// translation ambassador


#define WC_PAGE_CD_NATIVE 949  // Korean CodePage
#define WC_PAGE_CD_BIG5 950    // Traditional Chinese CodePage

#define WToMForNative( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 949, f1, f2, f3, f4, f5, f6, f7) 
#define WToMForBig5( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( 950, f1, f2, f3, f4, f5, f6, f7) 

#else

// For Eng(All Locale)
#ifndef TM_LOG_FIXED_MSG 
#define TM_LOG_FIXED_MSG "CALL %x\r\n"	// who is called
#endif

// hook.cpp
extern int TT_HOOK_NATIVE_CHARSET;
extern char TT_HOOK_FONT_NAME_DEF[64];

#define _TT_HOOK_NATIVE_CHARSET   SHIFTJIS_CHARSET
#define _TT_HOOK_FONT_NAME_DEF "MS Gothic"	// gothic

#define TMC_HOOK_FONT_PATCH_IREG "FONT PATCH IREG? %d %d %d %s\n"											// Korean font patch completed! %d %d %d
#define TMC_HOOK_FONT_PATCH_COMPLATE "FONT PATCH COMPLATED! %d %d %d %s\n"											// Korean font patch completed! %d %d %d

#define TMW_HOOK_FIELD_OBJECT_MSG L"FIELD OBJECT : %s\n"															// Field Object

#define TMC_HOOK_MONSTER_APPERANCE "MONSTER_APP : %02x %02x %02x\n"													// Monster Appearance:
#define TMC_HOOK_MAX_HP "MAX_HP: %s (MAX HP: %d)\n"

#define TMW_HOOK_MONSTER_MAX_HP L"(UNTRANSLATED)MONSTER : %s (MAX HP : %d)\n"										// (Untranslated) Monster: %s (MAX HP: %d)\n"
#define TMW_HOOK_OPTION L"OPTION : %s\n"																				// option
#define TMW_HOOK_DIALOG L"DIALOG: %s\n"																				// Dialogue: %s\n
#define TMW_HOOK_SIMPLE_STR L"%s\n"
#define TMW_HOOK_SIMPLE_STR2 L">>> %s\n"

#define TMC_HOOK_FAILED "HOOKING FAILED!! PLEASE KILL THE PROCESS\n"													// Hooking failed!! Please kill the process.

#define TT_DIC_NATIVE			"dic_native.txt"						// korean.txt Or Jp.txt
#define TT_DIC_DIALOG			"dic_dialogue.txt"						// Dict For Dialog
#define TT_DIC_FIELDOBJECT		"dic_fieldobject.txt"					// Dict For FieldObject
#define TT_DIC_SELECT			"dic_select.txt"						// Dict For Select
#define TT_DIC_MONSTER			"dic_monster.txt"						// Dict For Monster
#define TT_DIC_SKILL_DESC		"dic_skilldescription.txt"				// Dict For SkillDescript
#define TT_DIC_SKILL			"dic_skill.txt"							// Dict For Skill
#define TT_DIC_JOB				"dic_job.txt"							// Dict For Job
#define TT_DIC_ITEM				"dic_item.txt"							// Dict For Item

// engine.cpp
#define TMC_ENGINE_DIC_NOT_EXIST1		"The dictionary file does not exist. Download the dictionary file from the server.\n"
#define TMC_ENGINE_DIC_NOT_VERSION		"The dictionary file does not contain version information. The server will update the dictionary file.\n"
#define TMC_ENGINE_DIC_CUR_VERSION		"Current dictionary file version %d\n"
#define TMC_ENGINE_DIC_OTHER1			"TM_ENGINE_DIC_OTHER1.\n"													// 
#define	TMC_ENGINE_DIC_FAILED_CONNECT1	"TM_ENGINE_DIC_FAILED_CONNECT1 %d\n"										// Failed to connect to dictionary server
#define	TMC_ENGINE_DIC_NEWER_VERSION		"newest version. Skip update.\n"											// newest version. Skip update
#define	TMC_ENGINE_DIC_OTHER2			"TM_ENGINE_DIC_OTHER2.\n"													//
#define	TMC_ENGINE_DIC_FAILED_CONNECT2	"Failed to connect to dictionary server.\n"									// Failed to connect to dictionary server
#define	TMC_ENGINE_DIC_DONT_UNPACK		"Could not unpack the pre-compressed file.\n"								// Could not unpack the pre-compressed file#define	TMW_ENGINE_DIC_NOT_EXIST2		"The dictionary file does not exist. Please copy the dictionary file after terminating the process\n"	// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TMC_ENGINE_DIC_READ				"Read %d sentences from dictionary.\n"										// LOG(13, "Read %d sentences from dictionary.\n", nDicCount);
#define	TMC_ENGINE_DIC_NOT_EXIST2		"The dictionary file does not exist. Please copy the dictionary file after terminating the process\n"				// The dictionary file does not exist. Please copy the dictionary file after terminating the process
#define	TMC_ENGINE_CAPTION				"Development: codetronik, Choco\n"											// Development: codetronik, Choco\n
#define	TMC_ENGINE_SEARCH				"Searching..\n"																// Searching..

#define	TMW_ENGINE_CONSOLE_MSG			_T("Korean Patch Log Console(for jp-mode)")									// Korean Patch Log Console

extern char TT_ENGINE_LOCALE_NAME[64];

#define TT_ENGINE_DICVER_API_URL	"http://13.209.144.252/api/v1/dictionary/version"
#define TT_ENGINE_DIC_API_URL	"http://13.209.144.252/api/v1/dict-file"

// trans.cpp
#define TM_TRANS_AMBASSADOR		"translation ambassador: %s\n"	// translation ambassador

extern UINT WC_PAGE_CD_NATIVE;
extern UINT WC_PAGE_CD_BIG5;

#define WToMForNative( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( WC_PAGE_CD_NATIVE, f1, f2, f3, f4, f5, f6, f7 ) 
#define WToMForBig5( f1, f2, f3, f4, f5, f6, f7 ) WideCharToMultiByte( WC_PAGE_CD_BIG5, f1, f2, f3, f4, f5, f6, f7 ) 
#endif

void initTalken(void);
