
// MFC_k2.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CMFC_k2App: 
// �аѾ\��@�����O�� MFC_k2.cpp
//

class CMFC_k2App : public CWinApp
{
public:
	CMFC_k2App();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CMFC_k2App theApp;