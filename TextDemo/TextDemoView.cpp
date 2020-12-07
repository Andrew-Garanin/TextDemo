
// TextDemoView.cpp: реализация класса CTextDemoView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "TextDemo.h"
#endif

#include "TextDemoDoc.h"
#include "TextDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTextDemoView

IMPLEMENT_DYNCREATE(CTextDemoView, CScrollView)

BEGIN_MESSAGE_MAP(CTextDemoView, CScrollView)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CTextDemoView

CTextDemoView::CTextDemoView() noexcept
{
	// TODO: добавьте код создания

}

CTextDemoView::~CTextDemoView()
{
}

BOOL CTextDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

// Рисование CTextDemoView

void CTextDemoView::OnDraw(CDC* pDC)
{
	CTextDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	// возврат, если шрифт не создан: 
	if (pDoc->m_Font.m_hObject == NULL)
		return;

	RECT ClipRect;
	int LineHeight;
	TEXTMETRIC TM;
	int Y = MARGIN;

	// выбор шрифта в объект контекста устройства: 
	pDC->SelectObject(&pDoc->m_Font);

	// получение метрики текста: 
	pDC->GetTextMetrics(&TM);
	LineHeight = TM.tmHeight + TM.tmExternalLeading;

	// установка атрибутов текста: 
	pDC->SetTextColor(pDoc->m_Color);
	pDC->SetBkMode(TRANSPARENT);

	// получение координат недействительной области: 
	pDC->GetClipBox(&ClipRect);

	// отображение строки заголовка: 
	pDC->TextOut(MARGIN, Y, _T("FONT PROPERTIES"));
	// отображение строк текста: 
	for (int Line = 0; Line < NUMLINES; ++Line)
	{
		Y += LineHeight;
		if (Y + LineHeight >= ClipRect.top && Y <=
			ClipRect.bottom)
			pDC->TextOut(MARGIN, Y,
				pDoc->m_LineTable[Line]);
	}

}

//void CTextDemoView::OnInitialUpdate()
//{
//	CScrollView::OnInitialUpdate();
//
//	CSize sizeTotal;
//	// TODO: рассчитайте полный размер этого представления
//	sizeTotal.cx = sizeTotal.cy = 100;
//	SetScrollSizes(MM_TEXT, sizeTotal);
//}


// Диагностика CTextDemoView

#ifdef _DEBUG
void CTextDemoView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTextDemoView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTextDemoDoc* CTextDemoView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTextDemoDoc)));
	return (CTextDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CTextDemoView


void CTextDemoView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	// TODO: добавьте специализированный код или вызов базового класса
	CTextDemoDoc* PDoc = GetDocument();

	if (PDoc->m_Font.m_hObject == NULL)  // шрифт не создан 
		SetScrollSizes(MM_TEXT, CSize(0, 0));
	else                                 // шрифт создан
	{
		CClientDC ClientDC(this);
		int LineWidth = 0;
		SIZE Size;
		TEXTMETRIC TM;

		ClientDC.SelectObject(&PDoc->m_Font);
		ClientDC.GetTextMetrics(&TM);
		for (int Line = 0; Line < NUMLINES; ++Line)
		{
			Size = ClientDC.GetTextExtent
			(PDoc->m_LineTable[Line],
				PDoc->m_LineTable[Line].GetLength());
			if (Size.cx > LineWidth)
				LineWidth = Size.cx;
		}

		Size.cx = LineWidth + MARGIN;
		Size.cy = (TM.tmHeight + TM.tmExternalLeading) *
			(NUMLINES + 1) + MARGIN;
		SetScrollSizes(MM_TEXT, Size);
		ScrollToPosition(CPoint(0, 0));
	}
	CScrollView::OnUpdate(pSender, lHint, pHint);

}


void CTextDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	// TODO: Добавьте собственный код обработчика
	CSize DocSize = GetTotalSize();
	RECT ClientRect;
	GetClientRect(&ClientRect);

	switch (nChar)
	{
	case VK_LEFT:     // стрелка влево
		if (ClientRect.right < DocSize.cx)
			SendMessage(WM_HSCROLL, SB_LINELEFT);
		break;
	case VK_RIGHT:    // стрелка вправо
		if (ClientRect.right < DocSize.cx)
			SendMessage(WM_HSCROLL, SB_LINERIGHT);
		break;
	case VK_UP:       // стрелка вверх
		if (ClientRect.bottom < DocSize.cy)
			SendMessage(WM_VSCROLL, SB_LINEUP);
		break;
	case VK_DOWN:     // стрелка вниз
		if (ClientRect.bottom < DocSize.cy)
			SendMessage(WM_VSCROLL, SB_LINEDOWN);
		break;
	case VK_HOME:     // клавиша Home
		if (::GetKeyState(VK_CONTROL) & 0x8000)
			// Ctrl+Home 
		{
			if (ClientRect.bottom < DocSize.cy)
				SendMessage(WM_VSCROLL, SB_TOP);
		}
		else            // Home без Ctrl
		{
			if (ClientRect.right < DocSize.cx)
				SendMessage(WM_HSCROLL, SB_LEFT);
		}
		break;
	case VK_END:      // клавиша End 
		if (::GetKeyState(VK_CONTROL) & 0x8000)
			// Ctrl+End
		{
			if (ClientRect.bottom < DocSize.cy)
				SendMessage(WM_VSCROLL, SB_BOTTOM);
		}
		else          // End без Ctrl
		{
			if (ClientRect.right < DocSize.cx)
				SendMessage(WM_HSCROLL, SB_RIGHT);
		}
		break;
	case VK_PRIOR:    // клавиша PgUp 
		if (ClientRect.bottom < DocSize.cy)
			SendMessage(WM_VSCROLL, SB_PAGEUP);
		break;
	case VK_NEXT:     // клавиша PgDn
		if (ClientRect.bottom < DocSize.cy)
			SendMessage(WM_VSCROLL, SB_PAGEDOWN);
		break;
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}
