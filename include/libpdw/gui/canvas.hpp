
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

#include <chrono>
#include <glez/color.hpp>
#include <glez/font.hpp>

#include "gui/icanvas.hpp"
#include "gui/tooltip.hpp"
#include "gui/widgets/basewindow.hpp"

class Canvas : public CBaseWindow, public ICanvas {
public:
    Canvas();
    void Setup();

    menu::ncc::Tooltip* tooltip = nullptr;
    void ShowTooltip(const std::string& text); // you have to do this in Update()

    bool m_bPressedState[CatKey::CATKEY_COUNT];
    std::chrono::steady_clock::time_point m_iPressedFrame[CatKey::CATKEY_COUNT];
    std::chrono::steady_clock::time_point m_iSentFrame[CatKey::CATKEY_COUNT];
    bool m_bKeysInit = false;

    int m_iMouseX;
    int m_iMouseY;
    [[deprecated]] int mouse_dx;
    [[deprecated]] int mouse_dy;
    bool fake_scroll = false;

    glez::rgba GetColor() const override;
    bool gui_rainbow = true;
    glez::rgba gui_color;

    const glez::font& GetFont() const;

    virtual void Update() override;
    virtual void OnKeyPress(CatKey key, bool repeat) override;
    virtual void Draw(ICanvas*) override;
    inline virtual void MoveChildren() override {};

    void Line(TranslationMatrix tm, glez::rgba color) override;
    void Rect(TranslationMatrix tm, glez::rgba color, RectType rt = RectType::Filled) override;
    void Rect(TranslationMatrix tm, glez::rgba color, glez::texture& tx) override;
    void Circle(std::pair<int, int> center, float radius, glez::rgba color, int steps = 16) override;
    std::pair<int, int> String(std::pair<int, int> src, const std::string& str, glez::rgba color, std::optional<glez::rgba> outline = glez::color::black) override;
    std::pair<int, int> StringSize(const std::string& str) override;
    const ICanvas& GetBackground() const override { return *this; }
    const ICanvas& GetForeground() const override { return *this; }

private:
    glez::font font;
};

inline glez::rgba Transparent(glez::rgba base, float mod = 0.5f) {
    return glez::rgba(base.r * 255.0f, base.g * 255.0f, base.b * 255.0f, (base.a * 255.0f) * mod);
}
