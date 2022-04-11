
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

#include <glez/color.hpp>
#include <glez/draw.hpp>
#include <glez/font.hpp>

#include "gui/canvas.hpp"
#include "gui/listmenu/itemtitle.hpp"

namespace menu {
namespace ncc {

ItemTitle::ItemTitle(std::string title)
    : Item("ncc_list_title")
    , title(title) {
    this->brackets = false;
}

void ItemTitle::Draw(int x, int y) {
    Item::Draw(x, y);
    // nailed it
    bool brackets3 = this->brackets;
    std::string str = (brackets3 ? ">>> " : ">> ") + title + (brackets3 ? " <<<" : " <<");
    std::pair<float, float> size;
    this->GetCanvas()->GetFont().stringSize(str, &size.first, &size.second);
    glez::draw::string(x + ((Item::size_x - size.first) / 2), y, str, this->GetCanvas()->GetFont(), glez::color::white, nullptr, nullptr);
}

}
} // namespace menu::ncc
