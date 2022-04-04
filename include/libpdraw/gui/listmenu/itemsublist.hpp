
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

#ifndef ITEMSUBLIST_HPP_
#define ITEMSUBLIST_HPP_

#include "gui/listmenu/list.hpp"
#include "item.hpp"

namespace menu {
namespace ncc {

class List; // ????

class ItemSublist : public Item {
public:
    ItemSublist(std::string title, List* list);

    virtual void SetParent(IWidget*) override;
    virtual bool IsHovered() override;
    virtual void Update() override;
    virtual void Draw(int x, int y) override;
    virtual void OnKeyPress(CatKey code, bool repeated) override;
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();

public:
    List* const list;
    const std::string title;
};

}
} // namespace menu::ncc

#endif /* ITEMSUBLIST_HPP_ */
