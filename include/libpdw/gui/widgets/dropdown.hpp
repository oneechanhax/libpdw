
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

#include "basebutton.hpp"
#include "dropdownlist.hpp"

class CDropdown;

typedef std::function<void(CDropdown*, int)> DropdownCallbackFn_t;

class CDropdown : public CBaseButton {
public:
    CDropdown(IWidget* parent = nullptr, std::string name = "unnamed");
    CDropdown(std::string name = "unnamed", IWidget* parent = nullptr)
        : CDropdown(parent, name) { }
    ~CDropdown();

    void AddValue(std::string);
    int ValueCount();
    std::string ValueName(int idx);
    void SetValue(int value);
    void SetValueInternal(int value);
    int Value();

    void ShowList();
    void SetCallback(DropdownCallbackFn_t callback);

    virtual void Draw(ICanvas*);
    virtual void OnFocusLose();

    DropdownCallbackFn_t m_pDropdownCallback;
    CDropdownList* list;
    std::vector<std::string> m_values;
    int value;
    int offset;
};
