
// TextDemoDoc.h: интерфейс класса CTextDemoDoc 
//


#pragma once
const int NUMLINES = 42;	// количество строк, сохраненных
						// в документе и отображенных
						// в окне представления


class CTextDemoDoc : public CDocument
{
public:
	COLORREF m_Color;
	CString m_LineTable[NUMLINES];
	CFont m_Font;

protected: // создать только из сериализации
	CTextDemoDoc() noexcept;
	DECLARE_DYNCREATE(CTextDemoDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CTextDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOptionsFont();
};
