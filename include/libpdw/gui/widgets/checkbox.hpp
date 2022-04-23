
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

class CCheckbox;

typedef std::function<void(CCheckbox*, bool)> CheckboxCallbackFn_t;

class CCheckbox : public CBaseWidget {
public:
    CCheckbox(IWidget* parent, std::string name = "unnamed", bool checked = false);
    CCheckbox(std::string name = "unnamed", IWidget* parent = nullptr, bool checked = false)
        : CCheckbox(parent, name, checked) { }

    void SetWidth(int width);
    inline bool Value() { return this->checked; }
    inline void SetValue(bool value) { this->checked = value; }
    void SetCallback(CheckboxCallbackFn_t callback);

    virtual void OnMousePress();
    virtual void Draw(ICanvas*);

    CheckboxCallbackFn_t m_pCallback;
    bool checked;
    int width;
};
