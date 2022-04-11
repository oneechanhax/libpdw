
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

#include "gui/widgets/basewidget.hpp"

#include "gui/canvas.hpp"
#include "gui/gui.hpp"

void CBaseWidget::DrawBounds(int x, int y) {
    if (!this->bounds_color)
        this->bounds_color = glez::rgba(rand() % 255, rand() % 255, rand() % 255, 255);
    auto size = GetSize();
    glez::draw::rect(x, y, size.first, size.second, Transparent(*this->bounds_color, 0.25f));
    glez::draw::rect_outline(x, y, size.first, size.second, *this->bounds_color, 1);
}

bool CBaseWidget::IsHovered() {
    return g_pGUI->GetRootWindow()->IsVisible() && this->hover;
}

bool CBaseWidget::IsFocused() {
    return g_pGUI->GetRootWindow()->IsVisible() && this->focus;
}

bool CBaseWidget::IsPressed() {
    return g_pGUI->GetRootWindow()->IsVisible() && this->press;
}

CBaseWidget::CBaseWidget(std::string _name, IWidget* parent)
    : m_KeyValues(new KeyValues(std::string(_name + "_kv").c_str())) {
    m_pParent = parent;
    this->name = _name;
    SetPositionMode(INLINE);
    Show();
    this->max_size = { -1, -1 };
    this->SetOffset(0, 0);
    this->hover = false;
    this->press = false;
    this->focus = false;
    this->always_visible = false;
    this->SetZIndex(-1);
}

void CBaseWidget::Update() {
    if (IsHovered() && IsVisible() && !this->tooltip.empty()) {
        g_pGUI->m_pRootWindow->ShowTooltip(tooltip);
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
