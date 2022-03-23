/*
 * RootWindow.h
 *
 *  Created on: Jan 25, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <chrono>
#include <glez/font.hpp>
#include <glez/color.hpp>

#include "gui/widgets/basewindow.hpp"
#include "gui/tooltip.hpp"

class Canvas : public CBaseWindow {
public:
	Canvas();
	void Setup();

	menu::ncc::Tooltip* tooltip = nullptr;
	void ShowTooltip(const std::string& text); // you have to do this in Update()

	bool m_bPressedState[CatKey::CATKEY_COUNT];
	std::chrono::steady_clock::time_point  m_iPressedFrame[CatKey::CATKEY_COUNT];
	std::chrono::steady_clock::time_point  m_iSentFrame[CatKey::CATKEY_COUNT];
	bool m_bKeysInit = false;
	int  m_iMouseX;
	int  m_iMouseY;
	int  mouse_dx;
	int  mouse_dy;
	bool fake_scroll = false;

	glez::rgba GetColor();
	bool gui_rainbow = true;
	glez::rgba gui_color;

	glez::font& GetFont();

	virtual void Update() override;
	virtual void OnKeyPress(CatKey key, bool repeat) override;
	virtual void Draw(int x, int y) override;
	inline virtual void MoveChildren() override {};
private:
	glez::font font;
};

inline glez::rgba Transparent(glez::rgba base, float mod = 0.5f) {
	return glez::rgba(base.r * 255.0f, base.g * 255.0f, base.b * 255.0f, (base.a * 255.0f) * mod);
}
