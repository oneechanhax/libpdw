
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

#include "gui/listmenu/item.hpp"
#include "gui/canvas.hpp"
#include <glez/color.hpp>
#include <glez/draw.hpp>

namespace menu {
namespace ncc {

constexpr auto scale = 1;
int Item::size_x = psize_x * (float)scale;
int Item::size_y = psize_y * (float)scale;

Item::Item(std::string name)
    : CBaseWidget(name, nullptr) {
    SetSize(psize_x, psize_y);
    SetMaxSize(psize_x, psize_y);
}

void Item::Draw(int x, int y) {
    const auto& size = GetSize();
    // draw::DrawRect(x, y, size.first, size.second, colors::red);
    glez::draw::rect(x, y, size.first, size.second, glez::rgba(0, 0, 0, 55));
    if (IsHovered()) {
        glez::draw::rect(x, y, size.first, size.second, Transparent(this->GetCanvas()->GetColor(), 0.32f));
    }
}

void Item::HandleCustomEvent(std::string_view event) {
    if (event == "scale_update") {
        size_x = psize_x * (float)scale;
        size_y = psize_y * (float)scale;
        SetSize(size_x, size_y);
        SetMaxSize(size_x, size_y);
    }
}

}
} // namespace menu::ncc
