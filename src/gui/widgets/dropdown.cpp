
/*
 * Libpdw: Primitives Done Well!
 * Copyright (C) 2022 Rebekah Rowe
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/widgets/dropdown.hpp"
#include "gui/widgets/dropdownlist.hpp"

CDropdown::CDropdown(IWidget* parent, std::string name)
    : CBaseButton(name, parent) {
    list = new CDropdownList(name + "_list", this);
    this->GetCanvas()->AddChild(list);
    SetSize(80, 18);
    list->SetSize(80, 0);
    CBaseButton::SetCallback([this](CBaseButton*) -> void {
        ShowList();
    });
    this->value = 0;
    this->offset = 0;
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
    if (idx < 0 || idx >= m_values.size())
        return "unknown";
    return m_values.at(idx);
}

void CDropdown::Draw(ICanvas* canvas) {
    auto size = GetSize();
    std::pair<float, float> ssize;
    this->GetCanvas()->GetFont().stringSize(ValueName(Value() - this->offset), &ssize.first, &ssize.second);
    canvas->Rect({ { 0, 0 }, { size } }, Transparent(glez::color::black));
    canvas->Rect({ { 0, 0 }, { size } }, this->GetCanvas()->GetColor(), CanvasLayer::RectType::Outline);
    canvas->String({ (size.first - ssize.first) / 2, (size.second - ssize.second) / 2 }, ValueName(Value() - this->offset), this->GetCanvas()->GetColor());
    std::pair<float, float> asize;
    this->GetCanvas()->GetFont().stringSize(">", &asize.first, &asize.second);
    canvas->String({ size.first - asize.first - 2, (size.second - asize.second) / 2 }, ">", this->GetCanvas()->GetColor());
}

void CDropdown::OnFocusLose() {
    list->Hide();
}

void CDropdown::SetValueInternal(int value) {
    this->value = value + this->offset;
    if (m_pDropdownCallback)
        m_pDropdownCallback(this, value + this->offset);
}

void CDropdown::SetValue(int value) {
    this->value = value;
}

void CDropdown::ShowList() {
    auto pos = AbsolutePosition();
    auto size = GetSize();
    list->SetOffset(pos.first + size.first + 3, pos.second);
    list->Show();
}

int CDropdown::Value() {
    return this->value;
}

int CDropdown::ValueCount() {
    return m_values.size();
}
