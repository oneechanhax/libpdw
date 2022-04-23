
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

void CMenuListEntry::Draw(ICanvas* canvas) {
    std::pair<float, float> texts;
    this->GetCanvas()->GetFont().stringSize(GetText(), &texts.first, &texts.second);
    auto size = GetSize();
    auto gui_color = canvas->GetColor();
    const auto zero = std::pair<int, int> { 0, 0 };
    if (IsSelected()) {
        canvas->Line({ zero, { size.first, 0 } }, gui_color);
        canvas->Line({ { 0, size.second }, { size.first, 0 } }, gui_color);
        canvas->Line({ zero, { 0, size.second } }, gui_color);
    } else {
        canvas->Rect({ zero, size }, gui_color, CanvasLayer::RectType::Outline);
    }
    if (IsHovered()) {
        canvas->Rect({ zero, size }, Transparent(gui_color, 0.25));
    }
    canvas->String({ (size.first - texts.first) / 2, (size.second - texts.second) / 2 }, GetText(), IsSelected() ? glez::color::white : gui_color);
}
