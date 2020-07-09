#pragma once
#include"SingleTon.h"
#include<Windows.h>
class Font : public SingleTon< Font>
{
private:
	HDC m_Fonthdc;
	HFONT hFont, OldFont;
public:
	void Init();
	void Text(int x, int y, LPCSTR text, COLORREF color);
	Font();
	~Font();
};