
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

#include "gui/widgets/basebutton.hpp"

#include "gui/canvas.hpp"

CBaseButton::CBaseButton(IWidget* parent, std::string name, std::string text, ButtonCallbackFn_t callback)
    : CTextLabel(name, parent, text) {
    SetPadding(BUTTON_PADDING_W, BUTTON_PADDING_H);
    SetText(text);
    if (callback)
        SetCallback(callback);
}

void CBaseButton::SetCallback(ButtonCallbackFn_t callback) {
    m_pCallback = callback;
}

void CBaseButton::Draw(ICanvas* canvas) {
    auto gui_color = canvas->GetColor();
    auto textcolor = gui_color;
    auto size = GetSize();
    const auto zero = std::pair<int, int> { 0, 0 };
    if (IsPressed()) {
        canvas->Rect({ zero, size }, gui_color);
        textcolor = glez::color::white;
    }
    canvas->Rect({ zero, size }, gui_color, CanvasLayer::RectType::Outline);
    canvas->String(this->padding, GetText(), textcolor);
}

void CBaseButton::OnMousePress() {
    CBaseWidget::OnMousePress();
    if (m_pCallback) {
        m_pCallback(this);
    }
}
