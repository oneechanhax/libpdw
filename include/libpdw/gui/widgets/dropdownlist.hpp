
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

#include "basecontainer.hpp"

class CDropdown;
class CDropdownEntry;

class CDropdownList : public CBaseContainer {
public:
    CDropdownList(std::string name = "unnamed", CDropdown* menu = nullptr, int offset = 0);
    ~CDropdownList();

    virtual void Draw(ICanvas*);
    virtual void MoveChildren();
    inline virtual void SortByZIndex() override {};
    inline virtual bool DoesStealFocus() { return false; }

    void AddEntry(std::string name);
    void SetValue(int value);

    CDropdown* m_pMenu;
    std::vector<CDropdownEntry*> m_entries;
};
