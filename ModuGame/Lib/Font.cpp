#include "Font.h"
#include"ResoucesManager.h"

Font::Font()
{
}

void Font::Init()
{
	
}

void Font::Text(int x, int y, LPCSTR text, COLORREF color)
{
	m_Fonthdc = JEngine::ResoucesManager::GetInstance()->GetBackDC();
	hFont = CreateFont(0, 0, 0, 0, 0, 0, 0, 0, OEM_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Terminal"));
	OldFont = (HFONT)SelectObject(m_Fonthdc, hFont);

	TCHAR str[128];

	wsprintf(str, text);

	SetBkMode(m_Fonthdc, TRANSPARENT);
	SetTextColor(m_Fonthdc, color);


	TextOut(m_Fonthdc, x, y, str, lstrlen(str));

	SelectObject(m_Fonthdc, OldFont);
	DeleteObject(hFont);
}


Font::~Font()
{
}