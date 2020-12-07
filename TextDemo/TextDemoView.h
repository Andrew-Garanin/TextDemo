
// TextDemoView.h: интерфейс класса CTextDemoView
//

#pragma once

const int MARGIN = 10; 	// расстояние от текста до верхней и 
					// левой границы окна представления

class CTextDemoView : public CScrollView
{
protected: // создать только из сериализации
	CTextDemoView() noexcept;
	DECLARE_DYNCREATE(CTextDemoView)

// Атрибуты
public:
	CTextDemoDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
//	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора

// Реализация
public:
	virtual ~CTextDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};

#ifndef _DEBUG  // версия отладки в TextDemoView.cpp
inline CTextDemoDoc* CTextDemoView::GetDocument() const
   { return reinterpret_cast<CTextDemoDoc*>(m_pDocument); }
#endif

