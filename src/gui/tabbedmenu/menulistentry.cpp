/*
 * CMenuListEntry.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "menulistentry.hpp"
#include "menulist.hpp"

#include "gui/gui.hpp"

CMenuListEntry::CMenuListEntry(std::string name, CMenuList* parent, std::string entry) : CBaseButton(name, parent, entry) {
	Props()->SetString("entry", entry.c_str());
}

void CMenuListEntry::SetMaxSize(int x, int y) {
	CBaseWidget::SetMaxSize(x, y);
	SetSize(x, y);
}

bool CMenuListEntry::IsSelected() {
	return (dynamic_cast<CMenuList*>(GetParent())->m_pSelected == this);
}

void CMenuListEntry::Draw(int x, int y) {
	std::pair<float, float> texts;
	g_pGUI->GetRootWindow()->GetFont().stringSize(GetText(), &texts.first, &texts.second);
	auto size = GetSize();
	if (IsSelected()) {
		glez::draw::line(x, y, size.first, 0, g_pGUI->GetRootWindow()->GetColor(), 1);
		glez::draw::line(x, y + size.second, size.first, 0, g_pGUI->GetRootWindow()->GetColor(), 1);
		glez::draw::line(x, y, 0, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	} else {
		glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	}
	if (IsHovered()) {
		glez::draw::rect(x, y, size.first, size.second, Transparent(g_pGUI->GetRootWindow()->GetColor(), 0.25));
	}
	glez::draw::string(x + (size.first - texts.first) / 2, y + (size.second - texts.second) / 2, GetText().c_str(), g_pGUI->GetRootWindow()->GetFont(), IsSelected() ? glez::color::white : g_pGUI->GetRootWindow()->GetColor(), nullptr, nullptr);
}
