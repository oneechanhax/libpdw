
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

#include "gui/widgets/dropdown.hpp"
#include "gui/widgets/dropdownentry.hpp"
#include "gui/widgets/dropdownlist.hpp"

#include "gui/canvas.hpp"

CDropdownList::CDropdownList(std::string name, CDropdown* menu, int offset)
    : CBaseContainer(name, menu) {
    m_pMenu = menu;
    Hide();
    SetZIndex(5);
}

CDropdownList::~CDropdownList() {
    for (auto entry : m_entries) {
        delete entry;
    }
}

void CDropdownList::AddEntry(std::string name) {
    CDropdownEntry* entry = new CDropdownEntry("entry", this, name, m_entries.size());
    auto size = GetSize();
    entry->SetSize(size.first, 18);
    AddChild(entry);
    m_entries.push_back(entry);
    SetSize(size.first, m_entries.size() * 18);
}

void CDropdownList::SetValue(int value) {
    m_pMenu->SetValueInternal(value);
    Hide();
}

void CDropdownList::Draw(ICanvas* canvas) {
    auto size = GetSize();

    canvas->Rect({ { 0, 0 }, size }, Transparent(glez::color::black, 0.85));
    canvas->Rect({ { 0, 0 }, size }, this->GetCanvas()->GetColor(), CanvasLayer::RectType::Outline);
    CBaseContainer::Draw(canvas);
}

void CDropdownList::MoveChildren() {
    for (int i = 0; i < ChildCount(); i++) {
        auto child = ChildByIndex(i);
        child->SetOffset(0, i * 18);
    }
}
