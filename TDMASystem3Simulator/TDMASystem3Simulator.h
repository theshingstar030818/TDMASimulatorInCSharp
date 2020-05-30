
// TDMASystem3Simulator.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTDMASystem3SimulatorApp:
// See TDMASystem3Simulator.cpp for the implementation of this class
//

class CTDMASystem3SimulatorApp : public CWinApp
{
public:
	CTDMASystem3SimulatorApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTDMASystem3SimulatorApp theApp;