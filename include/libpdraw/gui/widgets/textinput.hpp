
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

#pragma once

#include "basewidget.hpp"

class CTextInput;

typedef std::function<void(CTextInput*, std::string, std::string)> TextInputCallbackFn_t;

class CTextInput : public CBaseWidget {
public:
    CTextInput(std::string name = "unnamed", IWidget* parent = nullptr);

    virtual void OnKeyPress(CatKey key, bool repeat);
    virtual void Draw(int x, int y);
    virtual bool ConsumesKey(CatKey key);

    void PutChar(char ch);
    void SetLength(int newlength);
    void SetMaxWidth(int width);
    void SetCallback(TextInputCallbackFn_t callback);
    std::string Value();
    void SetValue(std::string value);

    TextInputCallbackFn_t m_pCallback;
};
