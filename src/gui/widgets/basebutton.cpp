/*
 * CBaseButton.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/widgets/basebutton.hpp"

#include "gui/gui.hpp"

CBaseButton::CBaseButton(std::string name, IWidget* parent, std::string text, ButtonCallbackFn_t callback) : CTextLabel(name, parent, text) {
	SetPadding(BUTTON_PADDING_W, BUTTON_PADDING_H);
	SetText(text);
	if (callback) SetCallback(callback);
}

void CBaseButton::SetCallback(ButtonCallbackFn_t callback) {
	m_pCallback = callback;
}

void CBaseButton::Draw(int x, int y) {
	glez::rgba textcolor = g_pGUI->GetRootWindow()->GetColor();
	auto size = GetSize();
	if (IsPressed()) {
		glez::draw::rect(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor());
		textcolor = glez::color::white;
	}
	glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	glez::draw::string(x + Props()->GetInt("padding_x"), y + Props()->GetInt("padding_y"), GetText().c_str(), g_pGUI->GetRootWindow()->GetFont(), textcolor, nullptr, nullptr);
}

void CBaseButton::OnMousePress() {
	CBaseWidget::OnMousePress();
	if (m_pCallback) {
		m_pCallback(this);
	}
}
