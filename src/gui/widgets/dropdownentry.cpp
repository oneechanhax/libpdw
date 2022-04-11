
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

#include <glez/draw.hpp>

#include "gui/canvas.hpp"

#include "dropdownentry.hpp"

CDropdownEntry::CDropdownEntry(std::string name, CDropdownList* parent, std::string text, int _value)
    : CBaseButton(name, parent, text) {
    this->value = _value;
    SetCallback([this](CBaseButton*) -> void {
        CDropdownList* parent = dynamic_cast<CDropdownList*>(GetParent());
        if (!parent)
            return;
        parent->SetValue(this->value);
    });
}

void CDropdownEntry::Draw(int x, int y) {
    std::pair<float, float> ssize;
    this->GetCanvas()->GetFont().stringSize(GetText(), &ssize.first, &ssize.second);
    auto size = GetSize();
    glez::draw::string(x + (size.first - ssize.first) / 2, y + (size.second - ssize.second) / 2, GetText(), this->GetCanvas()->GetFont(), this->GetCanvas()->GetColor(), nullptr, nullptr);
}

CDropdownEntry::~CDropdownEntry() {
}
