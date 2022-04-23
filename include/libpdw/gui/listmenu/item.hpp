
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

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "gui/widgets/basewidget.hpp"

namespace menu {
namespace ncc {

class Item : public CBaseWidget {
public:
    constexpr static int psize_x = 220;
    constexpr static int psize_y = 15;

    static int size_x;
    static int size_y;

    Item(std::string name = "ncc_menu_item");

    virtual void Draw(ICanvas*) override;
    virtual void HandleCustomEvent(std::string_view event) override;
};

}
} // namespace menu::ncc

#endif /* ITEM_HPP_ */
