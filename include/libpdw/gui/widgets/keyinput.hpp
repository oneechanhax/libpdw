
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

class CKeyInput;

typedef std::function<void(CKeyInput*, CatKey)> KeyInputCallbackFn_t;

class CKeyInput : public CBaseWidget {
public:
    CKeyInput(IWidget* parent, std::string name = "unnamed");
    CKeyInput(std::string name = "unnamed", IWidget* parent = nullptr)
        : CKeyInput(parent, name) { }

    CatKey Value();
    void SetValue(int value);
    void SetCallback(KeyInputCallbackFn_t callback);

    KeyInputCallbackFn_t m_pCallback;

    virtual void OnKeyPress(CatKey key, bool repeat) override;
    virtual void Draw(ICanvas*) override;
    virtual void OnMousePress() override;
    virtual void OnFocusLose() override;
    virtual bool ConsumesKey(CatKey key) const override;
    bool capturing;
    int value;
};
