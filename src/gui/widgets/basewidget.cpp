/*
 * CBaseWidget.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/widgets/basewidget.hpp"

#include "gui/gui.hpp"
#include "gui/canvas.hpp"

void CBaseWidget::DrawBounds(int x, int y) {
	if (m_KeyValues->IsEmpty("bounds_color")) {
		m_KeyValues->SetColor("bounds_color", glez::rgba(rand() % 255, rand() % 255, rand() % 255, 255));
	}
	auto size = GetSize();
	glez::draw::rect(x, y, size.first, size.second, Transparent(m_KeyValues->GetColor("bounds_color"), 0.25f));
	glez::draw::rect_outline(x, y, size.first, size.second, m_KeyValues->GetColor("bounds_color"), 1);
}

bool CBaseWidget::IsHovered() {
	return g_pGUI->GetRootWindow()->IsVisible() && m_KeyValues->GetBool("hover");
}

bool CBaseWidget::IsFocused() {
	return g_pGUI->GetRootWindow()->IsVisible() && m_KeyValues->GetBool("focus");
}

bool CBaseWidget::IsPressed() {
	return g_pGUI->GetRootWindow()->IsVisible() && m_KeyValues->GetBool("press");
}

CBaseWidget::CBaseWidget(std::string name, IWidget* parent) : m_KeyValues(new KeyValues(std::string(name + "_kv").c_str())) {
	m_pParent = parent;
	Props()->SetString("name", name.c_str());
	SetPositionMode(INLINE);
	Show();
	SetMaxSize(-1, -1);
	this->SetOffset(0, 0);
	this->Props()->SetBool("hover", false);
	this->Props()->SetBool("press", false);
	this->Props()->SetBool("focus", false);
	this->Props()->SetBool("always_visible", false);
	this->Props()->SetInt("size_y", 0);
	this->Props()->SetInt("size_x", 0);
	this->SetZIndex(-1);
}

void CBaseWidget::Update() {
	if (IsHovered() && IsVisible() && Props()->FindKey("tooltip")) {
		g_pGUI->m_pRootWindow->ShowTooltip(Props()->GetString("tooltip"));
	}
}

std::pair<int, int> CBaseWidget::AbsolutePosition() {
	auto result = GetOffset();
	auto parent = GetParent();
	while (parent) {
		auto poffset = parent->GetOffset();
		result.first += poffset.first;
		result.second += poffset.second;
		parent = parent->GetParent();
	}
	return result;
}
