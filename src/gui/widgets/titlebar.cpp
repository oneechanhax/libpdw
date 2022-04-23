
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

#include "gui/widgets/titlebar.hpp"

#include "gui/canvas.hpp"

CTitleBar::CTitleBar(IWidget* parent, std::string title)
    : CBaseWidget("titlebar", parent) {
    m_strTitle = title;
    SetPositionMode(ABSOLUTE);
}

void CTitleBar::Draw(int x, int y) {
    auto size = GetSize();
    glez::draw::rect(x, y, size.first, size.second, this->GetCanvas()->GetColor());
    float l, h;
    this->GetCanvas()->GetFont().stringSize(m_strTitle, &l, &h);
    glez::draw::string(x + (size.first - l) / 2, y + TITLEBAR_PADDING_H, m_strTitle, this->GetCanvas()->GetFont(), glez::color::white, nullptr, nullptr);
}

void CTitleBar::OnMouseMove(std::pair<int, int> delta) {
    if (this->IsPressed()) {
        auto offset = GetParent()->GetOffset();
        GetParent()->SetOffset(offset.first + delta.first, offset.second + delta.second);
    }
}

void CTitleBar::Update() {
    auto psize = GetParent()->GetSize();
    float l, h;
    this->GetCanvas()->GetFont().stringSize(m_strTitle, &l, &h);
    SetSize(psize.first, 2 * TITLEBAR_PADDING_H + h);
}
