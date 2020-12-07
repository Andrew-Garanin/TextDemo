
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
