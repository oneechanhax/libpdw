
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

#include "gui/widgets/keyinput.hpp"

CKeyInput::CKeyInput(IWidget* parent, std::string name)
    : CBaseWidget(name, parent) {
    this->value = 0;
    this->capturing = false;
    this->focus = false;
}

CatKey CKeyInput::Value() {
    return (CatKey)this->value;
}

void CKeyInput::SetValue(int value) {
    this->value = value;
}

void CKeyInput::Draw(ICanvas* canvas) {
    std::string key = "";
    glez::rgba color = glez::color::white;
    if (this->capturing) {
        key = "< PRESS >";
        color = this->GetCanvas()->GetColor();
    } else {
        if (!Value()) {
            if (!IsFocused()) {
                key = "< CLICK >";
            }
        } else {
            key = input::key_names[Value()];
        }
    }
    auto size = GetSize();
    std::pair<float, float> ss;
    this->GetCanvas()->GetFont().stringSize(key, &ss.first, &ss.second);
    canvas->String({ (size.first - ss.first) / 2, (size.second - ss.second) / 2 }, key, color);
}

void CKeyInput::SetCallback(KeyInputCallbackFn_t callback) {
    m_pCallback = callback;
}

void CKeyInput::OnMousePress() {
    if (!this->capturing)
        this->capturing = true;
}

void CKeyInput::OnFocusLose() {
    this->capturing = false;
}

bool CKeyInput::ConsumesKey(CatKey key) const {
    return key != CatKey::CATKEY_MOUSE_1 && this->capturing;
}

void CKeyInput::OnKeyPress(CatKey key, bool repeat) {
    if (this->capturing) {
        if (key == CATKEY_ESCAPE)
            key = (CatKey)0;
        SetValue(key);
        if (m_pCallback)
            m_pCallback(this, key);
        this->capturing = false;
    }
}
