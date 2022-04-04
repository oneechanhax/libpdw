
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

#include "gui/widgets/basewindow.hpp"

#include "gui/gui.hpp"

void CBaseWindow::MoveChildren() {
    int mx = 0, my = 2;
    for (auto c : m_children) {
        if (!c->IsVisible())
            continue;
        auto off = c->GetOffset();
        auto size = c->GetSize();
        if (c->GetPositionMode() != ABSOLUTE && c->GetPositionMode() != FLOATING)
            c->SetOffset(2, my);
        else {
            size.first += off.first;
            size.second += off.second;
        }
        if (c->GetPositionMode() != FLOATING && c->GetPositionMode() != ABSOLUTE)
            if (size.first > mx)
                mx = size.first;
        if (c->GetPositionMode() != FLOATING)
            my += (size.second + 2);
    }
    if (GetParent()) {
        SetSize(mx + 4, my + 2);
    }
}

void CBaseWindow::OnFocusGain() {
    SetZIndex(GetZIndex() + 1);
    CBaseContainer::OnFocusGain();
}

void CBaseWindow::OnFocusLose() {
    SetZIndex(GetZIndex() - 1);
    CBaseContainer::OnFocusLose();
}

void CBaseWindow::Draw(int x, int y) {
    auto abs = AbsolutePosition();
    auto size = GetSize();
    glez::draw::rect(abs.first, abs.second, size.first, size.second, Transparent(glez::color::black, 0.9));
    glez::draw::rect_outline(abs.first, abs.second, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
    CBaseContainer::Draw(x, y);
}
