// enuSpace-SciLua.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "enuSpace-SciLua.h"

#include "GlobalHeader.h"
#include "utility_functions.h"
#include <string>

#include "lua.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CenuSpaceSciLuaApp

BEGIN_MESSAGE_MAP(CenuSpaceSciLuaApp, CWinApp)
END_MESSAGE_MAP()


// CenuSpaceSciLuaApp construction

CenuSpaceSciLuaApp::CenuSpaceSciLuaApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CenuSpaceSciLuaApp object

CenuSpaceSciLuaApp theApp;


// CenuSpaceSciLuaApp initialization


// Catch C++ exceptions and convert them to Lua error messages.
// Customize as needed for your own exception classes.
static int wrap_exceptions(lua_State *L, lua_CFunction f)
{
	try {
		return f(L);  // Call wrapped function and return result.
	}
	catch (const char *s) {  // Catch and convert exceptions.
		lua_pushstring(L, s);
	}
	catch (std::exception& e) {
		lua_pushstring(L, e.what());
	}
	catch (...) {
		lua_pushliteral(L, "caught (...)");
	}
	return lua_error(L);  // Rethrow as a Lua error.
}

static int myinit(lua_State *L)
{
	// Define wrapper function and enable it.
	lua_pushlightuserdata(L, (void *)wrap_exceptions);
	luaJIT_setmode(L, -1, LUAJIT_MODE_WRAPCFUNC | LUAJIT_MODE_ON);
	lua_pop(L, 1);
	return 1;
}

BOOL CenuSpaceSciLuaApp::InitInstance()
{
	CWinApp::InitInstance();

	HINSTANCE hInstance = AfxGetInstanceHandle();
	wchar_t szPath[MAX_PATH];
	GetModuleFileName(hInstance, szPath, MAX_PATH);

	wchar_t drive[MAX_PATH];               // 드라이브 명
	wchar_t dir[MAX_PATH];                 // 디렉토리 경로
	wchar_t fname[MAX_PATH];			   // 파일명
	wchar_t ext[MAX_PATH];                 // 확장자 명

	_wsplitpath_s(szPath, drive, dir, fname, ext);

	std::string strMessage;
	std::string strTenMessage = string_format("SciLua -> %s", strMessage.c_str());

	CString strDllPath;
	strDllPath.Format(L"%s%s", drive, dir);
	g_strDllPath = CStringToString(strDllPath);

	lua_State* dd = luaL_newstate();
	int k = myinit(dd);

	return TRUE;
}
