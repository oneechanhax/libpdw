/*
 * TitleBar.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/widgets/titlebar.hpp"

#include "gui/canvas.hpp"
#include "gui/gui.hpp"

CTitleBar::CTitleBar(IWidget* parent, std::string title) : CBaseWidget("titlebar", parent) {
	m_strTitle = title;
	m_iDraggingStage = 0;
	m_nLastX = 0;
	m_nLastY = 0;
	SetPositionMode(ABSOLUTE);
}

void CTitleBar::Draw(int x, int y) {
	auto size = GetSize();
	glez::draw::rect(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor());
	float l, h;
	g_pGUI->GetRootWindow()->GetFont().stringSize(m_strTitle, &l, &h);
	glez::draw::string(x + (size.first - l) / 2, y + TITLEBAR_PADDING_H, m_strTitle, g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
}

void CTitleBar::Update() {
	auto psize = GetParent()->GetSize();
	float l, h;
	g_pGUI->GetRootWindow()->GetFont().stringSize(m_strTitle, &l, &h);
	SetSize(psize.first, 2 * TITLEBAR_PADDING_H + h);
	if (!IsPressed()) {
		m_iDraggingStage = 0;
		return;
	}
	if (m_iDraggingStage == 0) {
		m_iDraggingStage = 1;
	} else {
		int dx = g_pGUI->GetRootWindow()->m_iMouseX - m_nLastX;
		int dy = g_pGUI->GetRootWindow()->m_iMouseY - m_nLastY;
		auto offset = GetParent()->GetOffset();
		GetParent()->SetOffset(offset.first + dx, offset.second + dy);
	}
	m_nLastX = g_pGUI->GetRootWindow()->m_iMouseX;
	m_nLastY = g_pGUI->GetRootWindow()->m_iMouseY;
}
