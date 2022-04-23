
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

#include <embed_resources.hpp>
#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/ncc/logo.hpp"
#include <var.hpp>

namespace ncc {

static ui::Enum logo_enum({ "NEVER", "MENU", "ALWAYS" });
static ui::Var<ui::Enum> logo({ "Gui" }, "Logo", 1, logo_enum);

Logo::Logo(IWidget* parent)
    : CBaseWidget("nc_logo", parent) {
    this->texture = glez::texture::loadFromMemory(embeded_logo_png_rgba.data.begin, embeded_logo_png_rgba.data.size, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height);
    SetSize(576, 288);
}

bool Logo::AlwaysVisible() {
    return (int)logo == 2;
}

void Logo::Draw(int x, int y) {
    if (logo)
        glez::draw::rect_textured(x, y, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height, this->GetCanvas()->GetColor(), this->texture, 0, 0, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height, 0.0f);
}

void Logo::OnMouseMove(std::pair<int, int> delta) {
    if (this->IsPressed()) {
        auto offset = GetOffset();
        offset.first += delta.first;
        offset.second += delta.second;
        SetOffset(offset.first, offset.second);
    }
}

} // namespace ncc
