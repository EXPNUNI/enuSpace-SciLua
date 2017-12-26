// enuSpace-SciLua.h : main header file for the enuSpace-SciLua DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CenuSpaceSciLuaApp
// See enuSpace-SciLua.cpp for the implementation of this class
//

class CenuSpaceSciLuaApp : public CWinApp
{
public:
	CenuSpaceSciLuaApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
