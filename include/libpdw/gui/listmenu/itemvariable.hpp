
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

#ifndef ITEMVARIABLE_HPP_
#define ITEMVARIABLE_HPP_

#include <var.hpp>

#include "item.hpp"

namespace menu {
namespace ncc {

class ItemVariable : public Item {
public:
    ItemVariable(ui::BaseVar& variable);

    void Change(float amount);

    virtual void Update() override;
    virtual bool ConsumesKey(CatKey key) const override;
    virtual void OnMousePress() override;
    virtual void OnFocusLose() override;
    virtual void OnKeyPress(CatKey key, bool repeat) override;
    virtual void Draw(int x, int y) override;

public:
    ui::BaseVar& catvar;
    bool capturing { false };
};

}
} // namespace menu::ncc

#endif /* ITEMVARIABLE_HPP_ */
