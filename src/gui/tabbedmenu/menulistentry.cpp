
/*
 * Libpdraw: A Versitile GUI for use with a primitive drawing system!
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

#include "menulist.hpp"
#include "menulistentry.hpp"

#include "gui/canvas.hpp"

CMenuListEntry::CMenuListEntry(std::string name, CMenuList* parent, std::string entry)
    : CBaseButton(name, parent, entry) {
    this->entry = entry;
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
    this->GetCanvas()->GetFont().stringSize(GetText(), &texts.first, &texts.second);
    auto size = GetSize();
    if (IsSelected()) {
        glez::draw::line(x, y, size.first, 0, this->GetCanvas()->GetColor(), 1);
        glez::draw::line(x, y + size.second, size.first, 0, this->GetCanvas()->GetColor(), 1);
        glez::draw::line(x, y, 0, size.second, this->GetCanvas()->GetColor(), 1);
    } else {
        glez::draw::rect_outline(x, y, size.first, size.second, this->GetCanvas()->GetColor(), 1);
    }
    if (IsHovered()) {
        glez::draw::rect(x, y, size.first, size.second, Transparent(this->GetCanvas()->GetColor(), 0.25));
    }
    glez::draw::string(x + (size.first - texts.first) / 2, y + (size.second - texts.second) / 2, GetText().c_str(), this->GetCanvas()->GetFont(), IsSelected() ? glez::color::white : this->GetCanvas()->GetColor(), nullptr, nullptr);
}
