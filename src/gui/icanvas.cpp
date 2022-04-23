
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

#include <glez/draw.hpp>

#include "gui/icanvas.hpp"
#include "gui/canvas.hpp"

void Canvas::Line(TranslationMatrix tm, glez::rgba color) {
    glez::draw::line(tm.first.first, tm.first.second, tm.second.first, tm.second.second, color, 1);
}
void Canvas::Rect(TranslationMatrix tm, glez::rgba color, RectType rt) {
    if (rt == RectType::Filled)
        glez::draw::rect(tm.first.first, tm.first.second, tm.second.first, tm.second.second, color);
    else if (rt == RectType::Outline)
        glez::draw::rect_outline(tm.first.first, tm.first.second, tm.second.first, tm.second.second, color, 1);
}
void Canvas::Rect(TranslationMatrix tm, glez::rgba color, glez::texture& tx) {
    glez::draw::rect_textured(tm.first.first, tm.first.second, tm.second.first, tm.second.second, color, tx, 0, 0, tx.width, tx.height, 0.0f);
}
void Canvas::Circle(std::pair<int, int> center, float radius, glez::rgba color, int steps) {
    glez::draw::circle(center.first, center.second, radius, color, 1, steps);
}
std::pair<int, int> Canvas::String(std::pair<int, int> src, const std::string& str, glez::rgba color, std::optional<glez::rgba> outline) {
    std::pair<float, float> ret;
    if (outline)
        glez::draw::outlined_string(src.first, src.second, str, this->GetFont(), color, *outline, &ret.first, &ret.second);
    else
        glez::draw::string(src.first, src.second, str, this->GetFont(), color, &ret.first, &ret.second);
    return ret;
}
std::pair<int, int> Canvas::StringSize(const std::string& str) {
    std::pair<float, float> ret;
    this->GetFont().stringSize(str, &ret.first, &ret.second);
    return ret;
}
