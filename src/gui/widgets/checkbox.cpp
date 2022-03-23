/*
 * CCheckbox.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/gui.hpp"

#include "gui/widgets/checkbox.hpp"

CCheckbox::CCheckbox(std::string name, IWidget* parent, bool checked) : CBaseWidget(name, parent) {
	SetWidth(16);
	SetValue(checked);
}

void CCheckbox::SetWidth(int width) {
	Props()->SetInt("width", width);
	SetSize(width, width);
}

void CCheckbox::Draw(int x, int y) {
	auto size = GetSize();
	glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	if (Value()) {
		glez::draw::rect(x + 3, y + 3, size.first - 6, size.second - 6, g_pGUI->GetRootWindow()->GetColor());
	}
}

void CCheckbox::OnMousePress() {
	SetValue(!Value());
	if (m_pCallback) {
		m_pCallback(this, Value());
	}
}

void CCheckbox::SetCallback(CheckboxCallbackFn_t callback) {
	m_pCallback = callback;
}
