
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

#include "gui/widgets/checkbox.hpp"

CCheckbox::CCheckbox(IWidget* parent, std::string name, bool checked)
    : CBaseWidget(name, parent) {
    SetWidth(16);
    SetValue(checked);
}

void CCheckbox::SetWidth(int _width) {
    this->width = _width;
    SetSize(_width, _width);
}

void CCheckbox::Draw(int x, int y) {
    auto size = GetSize();
    glez::draw::rect_outline(x, y, size.first, size.second, this->GetCanvas()->GetColor(), 1);
    if (Value()) {
        glez::draw::rect(x + 3, y + 3, size.first - 6, size.second - 6, this->GetCanvas()->GetColor());
    }
}

void CCheckbox::OnMousePress() {
    SetValue(!Value());
    if (m_pCallback) {
        m_pCallback(this, Value());
    }
}

void CCheckbox::SetCallback(CheckboxCallbackFn_t callback) {
    m_pCallback = callback;
}
