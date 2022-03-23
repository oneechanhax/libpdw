/*
 * CDropdown.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/gui.hpp"

#include "gui/widgets/dropdown.hpp"
#include "gui/widgets/dropdownlist.hpp"
#include "gui/canvas.hpp"

CDropdown::CDropdown(std::string name, IWidget* parent) : CBaseButton(name, parent) {
	list = new CDropdownList(name + "_list", this);
	g_pGUI->GetRootWindow()->AddChild(list);
	SetSize(80, 18);
	list->SetSize(80, 0);
	CBaseButton::SetCallback([this](CBaseButton*) -> void {
		ShowList();
	});
	this->Props()->SetInt("value", 0);
	this->Props()->SetInt("offset", 0);
}

CDropdown::~CDropdown() {
	delete list;
}

void CDropdown::SetCallback(DropdownCallbackFn_t callback) {
	m_pDropdownCallback = callback;
}

void CDropdown::AddValue(std::string string) {
	list->AddEntry(string);
	m_values.push_back(string);
}

std::string CDropdown::ValueName(int idx) {
	if (idx < 0 || idx >= m_values.size()) return "unknown";
	return m_values.at(idx);
}

void CDropdown::Draw(int x, int y) {
	auto size = GetSize();
	std::pair<float, float> ssize;
	g_pGUI->GetRootWindow()->GetFont().stringSize(ValueName(Value() - Props()->GetInt("offset")), &ssize.first, &ssize.second);
	glez::draw::rect(x, y, size.first, size.second, Transparent(glez::color::black));
	glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	glez::draw::string(x + (size.first - ssize.first) / 2, y + (size.second - ssize.second) / 2, ValueName(Value() - Props()->GetInt("offset")), g_pGUI->GetRootWindow()->GetFont(), g_pGUI->GetRootWindow()->GetColor(), nullptr, nullptr);
	std::pair<float, float> asize;
	g_pGUI->GetRootWindow()->GetFont().stringSize(">", &asize.first, &asize.second);
	glez::draw::string(x + size.first - asize.first - 2, y + (size.second - asize.second) / 2, ">", g_pGUI->GetRootWindow()->GetFont(), g_pGUI->GetRootWindow()->GetColor(), nullptr, nullptr);
}

void CDropdown::OnFocusLose() {
	list->Hide();
}

void CDropdown::SetValueInternal(int value) {
	Props()->SetInt("value", value + Props()->GetInt("offset"));
	if (m_pDropdownCallback)
		m_pDropdownCallback(this, value + Props()->GetInt("offset"));
}

void CDropdown::SetValue(int value) {
	Props()->SetInt("value", value);
}

void CDropdown::ShowList() {
	auto pos = AbsolutePosition();
	auto size = GetSize();
	list->SetOffset(pos.first + size.first + 3, pos.second);
	list->Show();
}

int CDropdown::Value() {
	return Props()->GetInt("value");
}

int CDropdown::ValueCount() {
	return m_values.size();
}
