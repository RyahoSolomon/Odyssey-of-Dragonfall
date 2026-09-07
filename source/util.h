#ifndef _UTIL_H_
#define _UTIL_H_

#include<graphics.h>
#include<iostream>

#pragma comment(lib, "WINMM.lib")
#pragma comment(lib, "MSIMG32.lib")

struct Rect
{
	int x, y;
	int w, h;
	Rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {};
	Rect() : x(0), y(0), w(0), h(0) {};
};

inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0,
		rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(), blend_func
	);
}

inline void putimage_ex(
	IMAGE* img,
	int dst_x, int dst_y, int dst_w, int dst_h,
	int src_x = -1, int src_y = -1, int src_w = -1, int src_h = -1)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	if (src_x < 0 || src_y < 0 || src_w < 0 || src_h < 0) {
		src_x = 0;
		src_y = 0;
		src_w = img->getwidth();
		src_h = img->getheight();
	}
	AlphaBlend(
		GetImageHDC(GetWorkingImage()), dst_x, dst_y, dst_w, dst_h,
		GetImageHDC(img), src_x, src_y, src_w, src_h, blend_func
	);
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}
inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline int range_random(int min, int max)
{
	return rand() % (max - min + 1) + min;
}



inline void render_text(
	const Rect& rect,
	const wchar_t* text,
	int font_size = 32,
	COLORREF color = BLACK,
	const wchar_t* font_name = _T("IPix")
)
{
	setbkmode(TRANSPARENT);
	settextstyle(font_size, 0, font_name);
	settextcolor(color);

	int text_w = textwidth(text);
	int text_h = textheight(text);
	int draw_x = rect.x + (rect.w - text_w) / 2;
	int draw_y = rect.y + (rect.h - text_h) / 2;

	outtextxy(draw_x, draw_y, text);
}

inline std::wstring string_to_wstring(const std::string& str)
{
	return std::wstring(str.begin(), str.end());
}

#endif