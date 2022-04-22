
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

#pragma once

#include "basewidget.hpp"

class CSlider;

typedef std::function<void(CSlider*, float, float)> SliderCallbackFn_t;

class CSlider : public CBaseWidget {
public:
    CSlider(IWidget* parent, std::string name = "");
    CSlider(std::string name = "", IWidget* parent = nullptr)
        : CSlider(parent, name) { }

    void Setup(float min, float max);
    void SetStep(float step);
    float Value();
    void SetValue(float value);
    void SetCallback(SliderCallbackFn_t callback);

    virtual void Update();
    virtual void Draw(int x, int y);

    SliderCallbackFn_t m_pCallback;

    int m_nLastX;
    bool m_bDragInit;
    int m_nSliderPos;

private:
    float value_min, value_max, value, step;
};
