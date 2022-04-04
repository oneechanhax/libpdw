
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

#include "splitcontainer.hpp"

// TODO, Unknown purpose

CSplitContainer::CSplitContainer(std::string name, IWidget* parent)
    : CBaseContainer(name, parent) { }

void CSplitContainer::MoveChildren() {
    auto newsize = std::make_pair(GetMaxSize().first, 0);
    auto size = GetSize();
    if (!ChildCount())
        return;
    int width = ((size.first - 4) / ChildCount()) - 2; // TODO padding!
    for (int i = 0; i < ChildCount(); i++) {
        auto child = ChildByIndex(i);
        child->SetOffset(2 + i * width, 2);
        child->SetMaxSize(width, -1);
        auto csize = child->GetSize();
        if (csize.second + 2 > newsize.second)
            newsize.second = csize.second + 2;
    }
    SetSize(-1, newsize.second);
}
