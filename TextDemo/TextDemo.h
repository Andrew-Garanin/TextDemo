
// TextDemo.h: основной файл заголовка для приложения TextDemo
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CTextDemoApp:
// Сведения о реализации этого класса: TextDemo.cpp
//

class CTextDemoApp : public CWinApp
{
public:
	CTextDemoApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTextDemoApp theApp;
