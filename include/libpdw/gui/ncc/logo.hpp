
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

#include <glez/texture.hpp>

#include "gui/widgets/basewidget.hpp"

namespace ncc {

class Logo : public CBaseWidget {
public:
    Logo(IWidget*);
    virtual bool AlwaysVisible() override;
    virtual void Draw(int x, int y) override;
    virtual void Update() override;
    glez::texture texture;
};

} // namespace ncc
