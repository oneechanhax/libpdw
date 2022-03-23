/*
 * CKeyInput.cpp
 *
 *  Created on: Feb 1, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/gui.hpp"

#include "gui/widgets/keyinput.hpp"

CKeyInput::CKeyInput(std::string name, IWidget* parent) : CBaseWidget(name, parent) {
	Props()->SetInt("value", 0);
	Props()->SetBool("capturing", false);
	Props()->SetBool("focus", false);
}

CatKey CKeyInput::Value() {
	return (CatKey)Props()->GetInt("value");
}

void CKeyInput::SetValue(int value) {
	Props()->SetInt("value", value);
}

void CKeyInput::Draw(int x, int y) {
	std::string key = "";
	glez::rgba color = glez::color::white;
	if (Props()->GetBool("capturing")) {
		key = "< PRESS >";
		color = g_pGUI->GetRootWindow()->GetColor();
	} else {
		if (!Value()) {
			if (!IsFocused()) {
				key = "< CLICK >";
			}
		} else {
			key = input::key_names[Value()];
		}
	}
	auto size = GetSize();
	std::pair<float, float> ss;
	g_pGUI->GetRootWindow()->GetFont().stringSize(key, &ss.first, &ss.second);
	glez::draw::string(x + (size.first - ss.first) / 2, y + (size.second - ss.second) / 2, key, g_pGUI->GetRootWindow()->GetFont(), color, nullptr, nullptr);
}

void CKeyInput::SetCallback(KeyInputCallbackFn_t callback) {
	m_pCallback = callback;
}

void CKeyInput::OnMousePress() {
	if (!Props()->GetBool("capturing"))
		Props()->SetBool("capturing", true);
}

void CKeyInput::OnFocusLose() {
	Props()->SetBool("capturing", false);
}

bool CKeyInput::ConsumesKey(CatKey key) {
	return key != CatKey::CATKEY_MOUSE_1 && Props()->GetBool("capturing");
}

void CKeyInput::OnKeyPress(CatKey key, bool repeat) {
	if (Props()->GetBool("capturing")) {
		if (key == CATKEY_ESCAPE) key = (CatKey)0;
		SetValue(key);
		if (m_pCallback) m_pCallback(this, key);
		Props()->SetBool("capturing", false);
	}
}
