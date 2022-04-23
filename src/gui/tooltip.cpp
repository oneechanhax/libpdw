
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

#include <glez/color.hpp>
#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/listmenu/item.hpp"
#include "gui/widgets/textlabel.hpp"
#include "tooltip.hpp"

namespace menu {
namespace ncc {

constexpr auto scale = 1;

Tooltip::Tooltip()
    : CTextLabel("ncc_tooltip") {
    SetZIndex(999);
    SetPadding(3, 2);
    SetMaxSize(220, -1);
    SetAutoSize(false);
    SetSize(220, -1);
    // Props()->SetInt("font", font_item);
}

void Tooltip::HandleCustomEvent(std::string_view event) {
    if (event == "scale_update") {
        SetMaxSize(Item::psize_x * (float)scale, -1);
        SetSize(Item::psize_x * (float)scale, -1);
        SetText(GetText()); // To update word wrapping.
    } /*else if (event == "font_update") {
            Props()->SetInt("font", font_item);
    }*/
}

void Tooltip::Draw(ICanvas* canvas) {
    const auto& size = GetSize();
    auto offset = this->GetOffset();
    int originx = offset.first;
    int originy = offset.second;
    auto root_size = this->GetCanvas()->GetSize();
    if (originx + size.first > root_size.first)
        originx -= size.first;
    if (originx + size.second > root_size.second)
        originy -= size.second;
    static auto bgcolor = glez::rgba(0, 0, 0, 77); // colors::Create(70, 86, 47, 28);
    static auto fgcolor = glez::rgba(200, 200, 190, 255);
    canvas->Rect({ { 0, 0 }, size }, bgcolor);
    canvas->Rect({ { 0, 0 }, size }, this->GetCanvas()->GetColor(), CanvasLayer::RectType::Outline);
    canvas->String(this->padding, GetText(), fgcolor);
}

}
} // namespace menu::ncc
