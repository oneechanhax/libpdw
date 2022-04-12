
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

#include <cmath>
#include <glez/draw.hpp>
#include <stdexcept>

#include "gui/canvas.hpp"
#include "gui/widgets/basebutton.hpp"
#include "gui/widgets/checkbox.hpp"
#include "gui/widgets/textinput.hpp"
#include "gui/widgets/textlabel.hpp"
//#include "splitcontainer.h"
#include "gui/widgets/basecontainer.hpp"
#include "gui/widgets/dropdown.hpp"
#include "gui/widgets/slider.hpp"
#include "tooltip.hpp"
//#include "menucontainer.h"
//#include "cvarcontainer.h"
//#include "menuwindow.h"
#include "var.hpp"

#include "gui/widgets/titlebar.hpp"

ui::Var<bool> gui_draw_bounds({ "Gui", "Debug" }, "Draw Bounds", false);
ui::Var<bool> gui_visible({ "Gui" }, "Visible", true);
Canvas::Canvas()
    : CBaseWindow(nullptr, "root") { }

// Crashes associated with no set root in globals
void Canvas::Setup() {
    gui_visible.Callback = [this](bool v) {
        this->visible = v;
    };
    this->gui_color = glez::rgba(255, 105, 180);
    this->always_visible = true;
    this->hover = true;

    // this->font = new glez::font("../res/opensans.ttf", 10);
    // this->font->load();
    this->font = glez::font::loadFromFile("../res/opensans.ttf", 10);
    if (!this->font.isLoaded())
        throw std::runtime_error("Font loading failed");

    this->tooltip = new menu::ncc::Tooltip();
    AddChild(this->tooltip);

    auto bounds = input::GetBounds();
    SetMaxSize(bounds.first, bounds.second);

    /*CBaseWindow* ws = new CBaseWindow("splitwindow");
    ws->SetPositionMode(ABSOLUTE);
    CTitleBar* wst = new CTitleBar(ws, "Window Layout Test");
    ws->AddChild(wst);
    ws->SetMaxSize(500, 0);*/

    // CMenuWindow* win = new CMenuWindow("menu_window", this);
    // win->SetMaxSize(912, 410);
    // auto ms = GetMaxSize();
    // win->AddElements();
    // win->SetOffset((draw::width - 912) / 2, (draw::height - 410) / 2);
    // AddChild(win);
}

void Canvas::Update() {
    auto curtime = std::chrono::steady_clock::now();

    m_bPressedState[CatKey::CATKEY_M_WHEEL_DOWN] = false;
    m_bPressedState[CatKey::CATKEY_M_WHEEL_UP] = false;

    // last_scroll_value = new_scroll;
    for (int i = 0; i < CatKey::CATKEY_COUNT; i++) {
        bool down = false, changed = false;
        ;
        if ((CatKey)i != CatKey::CATKEY_M_WHEEL_DOWN && (CatKey)i != CatKey::CATKEY_M_WHEEL_UP) {
            down = input::GetKey((CatKey)i);
            changed = m_bPressedState[i] != down;
        } else {
            down = m_bPressedState[i];
            changed = down;
        }

        if (changed && down)
            m_iPressedFrame[i] = curtime;
        m_bPressedState[i] = down;
        if (m_bKeysInit) {
            if (changed) {
                // printf("Key %i changed! Now %i.\n", i, down);
                if (i == CatKey::CATKEY_MOUSE_1) {

                    if (down && input::GetKey(CatKey::CATKEY_LCONTROL)) {
                        this->OnKeyPress(CatKey::CATKEY_M_WHEEL_UP, false);
                        // this->OnKeyRelease(CatKey::CATKEY_M_WHEEL_UP);
                    } else if (down && input::GetKey(CatKey::CATKEY_LSHIFT)) {
                        this->OnKeyPress(CatKey::CATKEY_M_WHEEL_DOWN, false);
                    } else

                        if (this->IsVisible()) {
                        if (down)
                            this->OnMousePress();
                        else
                            this->OnMouseRelease();
                    }
                } else {
                    if ((i == CatKey::CATKEY_INSERT || i == CatKey::CATKEY_F11) && down) {
                        this->visible = !this->visible;
                    }
                    if (this->IsVisible()) {
                        if (down)
                            this->OnKeyPress((CatKey)i, false);
                        else
                            this->OnKeyRelease((CatKey)i);
                        m_iSentFrame[i] = curtime;
                    }
                }
            } else {
                if (down) {
                    auto pressed_time = curtime - m_iPressedFrame[i];
                    bool shouldrepeat = false;
                    if (pressed_time > std::chrono::seconds(1)) {
                        auto time_since_keysend = curtime - m_iSentFrame[i];
                        if (pressed_time > std::chrono::seconds(4)) {
                            if (time_since_keysend > std::chrono::milliseconds(250))
                                ;
                            shouldrepeat = true;
                        } else if (time_since_keysend > std::chrono::milliseconds(400))
                            ;
                        shouldrepeat = true;
                    }
                    if (this->IsVisible() && shouldrepeat)
                        this->OnKeyPress((CatKey)i, true);
                }
            }
        }
    }

    auto nmouse = input::GetMouse();

    mouse_dx = nmouse.first - m_iMouseX;
    mouse_dy = nmouse.second - m_iMouseY;

    m_iMouseX = nmouse.first;
    m_iMouseY = nmouse.second;

    if (!m_bKeysInit)
        m_bKeysInit = 1;
    // if (!this->IsVisible())
    // this->Show();

    tooltip->Hide();
    CBaseWindow::Update();

    this->Draw(0, 0);

    // Draw Mouse
    glez::draw::rect(m_iMouseX - 5, m_iMouseY - 5, 10, 10, Transparent(glez::color::black));
    glez::draw::rect_outline(m_iMouseX - 5, m_iMouseY - 5, 10, 10, GetColor(), 2);

    if (gui_draw_bounds)
        this->DrawBounds(0, 0);
}

void Canvas::Draw(int x, int y) {
    if (tooltip->IsVisible()) {
        tooltip->SetOffset(this->m_iMouseX + 24, this->m_iMouseY + 8);
    }
    CBaseContainer::Draw(x, y);
}

static auto start_time = std::chrono::steady_clock::now();
static glez::rgba RainbowCurrent() {
    auto FromHSL = [](float h, float s, float v) {
        auto ToRGBA8 = [](float r, float g, float b, float a = 1.0f) {
            return glez::rgba(static_cast<int>(r * 255), static_cast<int>(g * 255), static_cast<int>(b * 255), static_cast<int>(a * 255));
        };
        if (s <= 0.0f)
            return ToRGBA8(v, v, v);
        if (h >= 360.0f)
            h = 0.0f;
        h /= 60.0f;
        long i = long(h);
        float ff = h - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - (s * ff));
        float t = v * (1.0f - (s * (1.0f - ff)));

        switch (i) {
        case 0:
            return ToRGBA8(v, t, p);
        case 1:
            return ToRGBA8(q, v, p);
        case 2:
            return ToRGBA8(p, v, t);
        case 3:
            return ToRGBA8(p, q, v);
        case 4:
            return ToRGBA8(t, p, v);
        }
        return ToRGBA8(v, p, q);
    };
    std::chrono::duration<float, std::deca> ctime = std::chrono::steady_clock::now() - start_time;
    return FromHSL(fabs(sin(ctime.count())) * 360.0f, 0.85f, 0.9f);
}

glez::rgba Canvas::GetColor() {
    return gui_rainbow ? RainbowCurrent() : gui_color;
}
glez::font& Canvas::GetFont() {
    return this->font;
}
void Canvas::OnKeyPress(CatKey key, bool repeat) {
    if (GetHoveredChild())
        GetHoveredChild()->OnKeyPress(key, repeat);
}

void Canvas::ShowTooltip(const std::string& text) {
    tooltip->Show();
    tooltip->SetText(text);
}
