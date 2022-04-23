
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

#include <cmath>
#include <glez/draw.hpp>

#include "gui/canvas.hpp"

#include "gui/widgets/slider.hpp"

CSlider::CSlider(IWidget* parent, std::string name)
    : CBaseWidget(name, parent) {
    Setup(0.0f, 1.0f);
    SetSize(80, 16);
    m_nLastX = 0;
    m_nSliderPos = 40;
    m_bDragInit = false;
    m_pCallback = 0;
}

void CSlider::Setup(float min, float max) {
    this->value_min = min;
    this->value_max = max;
    this->value = 0;
    this->step = 0;
    SetValue((min + max) / 2.0f);
}

void CSlider::SetStep(float _step) {
    this->step = _step;
}

void CSlider::SetCallback(SliderCallbackFn_t callback) {
    m_pCallback = callback;
}

void CSlider::SetValue(float value) {
    float old = Value();
    if (this->step) {
        value -= fmod(value, this->step);
    }
    this->value = value;
    if (old != value) {
        if (m_pCallback) {
            m_pCallback(this, old, value);
        }
    }
    m_nSliderPos = (GetSize().first) * (float)(value - this->value_min) / (float)(this->value_max - this->value_min);
}

float CSlider::Value() {
    return this->value;
}

void CSlider::Update() {
    if (IsPressed()) {
        if (m_bDragInit) {
            int delta = m_nLastX - this->GetCanvas()->m_iMouseX;
            if (delta) {
                auto abs = AbsolutePosition();
                auto size = GetSize();
                int mv = this->GetCanvas()->m_iMouseX - abs.first;
                if (mv < 0)
                    mv = 0;
                if (mv > size.first)
                    mv = size.first;
                SetValue(((float)mv / (float)size.first) * (this->value_max - this->value_min) + this->value_min);
                m_nSliderPos = mv;
            }
        }
        m_nLastX = this->GetCanvas()->m_iMouseX;
        m_bDragInit = true;
    } else
        m_bDragInit = false;
}

void CSlider::Draw(ICanvas* canvas) {
    auto size = GetSize();
    canvas->Rect({ { 0, 0 }, size }, glez::color::black);
    canvas->Rect({ { 0, 0 }, { m_nSliderPos, size.second } }, this->GetCanvas()->GetColor());
    char s[256];
    snprintf(s, sizeof(s), "%.2f", Value());
    std::string str(s);
    std::pair<float, float> sl;
    this->GetCanvas()->GetFont().stringSize(str, &sl.first, &sl.second);
    canvas->String({ (size.first - sl.first) / 2, (size.second - sl.second) / 2 }, str, glez::color::white);
}
