
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

#include <iostream>

#include "lib/xoverlay.h"
#include "libpdraw/gui/gui.hpp"
#include <embed_resources.hpp>
#include <glez/detail/render.hpp>
#include <glez/draw.hpp>
#include <glez/glez.hpp>

// xorg conflict
#undef RootWindow

#include "libpdraw/gui/widgets/slider.hpp"
#include "libpdraw/gui/widgets/titlebar.hpp"
//#include "gui/csplitcontainer.hpp"
#include "libpdraw/gui/canvas.hpp"
#include "libpdraw/gui/widgets/basebutton.hpp"
#include "libpdraw/gui/widgets/basewindow.hpp"
#include "libpdraw/gui/widgets/checkbox.hpp"
#include "libpdraw/gui/widgets/dropdown.hpp"
#include "libpdraw/gui/widgets/keyinput.hpp"
#include "libpdraw/gui/widgets/textinput.hpp"

#include "libpdraw/gui/listmenu/itemsublist.hpp"
#include "libpdraw/gui/listmenu/itemtitle.hpp"
#include "libpdraw/gui/listmenu/itemvariable.hpp"
#include "libpdraw/gui/listmenu/list.hpp"
#include "libpdraw/gui/tabbedmenu/cvarcontainer.hpp"
#include "libpdraw/gui/tabbedmenu/menucontainer.hpp"
#include "libpdraw/gui/tabbedmenu/menuwindow.hpp"

#include "input.hpp"

static ui::Var<int> text({ "nonya" }, "Editable Text", 1);

class TestWindow : public CBaseWindow {
public:
    TestWindow()
        : CBaseWindow("root_test", nullptr) {
        Props()->SetBool("always_visible", false);
        Props()->SetBool("hover", false);
        SetMaxSize(1270, 1000);
        SetPositionMode(PositionMode::FLOATING);

        auto* titlebar = new CTitleBar(this, "Test uwu~");
        AddChild(titlebar);
        Props()->SetBool("visable", true);

        AddChild(new CTextLabel("button_label", this, "Button widget:"));
        AddChild(new CBaseButton("button", this, "I'm Clickable!", [this](CBaseButton*) {
            std::cout << "Hey hey I was pressed!" << std::endl;
            this->button_clicked = !this->button_clicked;
        }));

        AddChild(new CTextLabel("checkbox_label", this, "Checkbox widget:"));
        AddChild(new CCheckbox("checkbox", this, false));

        AddChild(new CTextLabel("slider_label", this, "Slider widget:"));
        auto* slider = new CSlider("slider", this);
        slider->SetStep(0.1f);
        AddChild(slider);

        AddChild(new CTextLabel("dropdown_label", this, "Dropdown widget:"));
        auto dropdown = new CDropdown("dropdown", this);
        dropdown->AddValue("Im the cutest princess!");
        dropdown->AddValue("No I am, hmp!");
        dropdown->AddValue("*doomguy noises*");
        dropdown->SetSize(150, 16);
        AddChild(dropdown);

        AddChild(new CTextLabel("text_input_label", this, "Text input widget:"));
        auto* text_input = new CTextInput("text_input", this);
        text_input->SetValue("You can edit me!");
        AddChild(text_input);

        AddChild(new CTextLabel("key_input_label", this, "Key widget:"));
        auto key_input = new CKeyInput("key_input");
        key_input->SetSize(78, 10);
        AddChild(key_input);
    }
    virtual void Update() override {
        this->CBaseWindow::Update();
        if (this->button_clicked)
            g_pGUI->GetRootWindow()->ShowTooltip("This is an example of a very long tooltip! You can click me again to hide me from view. Thanks for using libpdraw ;)");
    }
    CTextInput* text_box = nullptr;
    bool button_clicked = false;
};

static const std::string menu_list = R"(
"Libpdraw"
"GUI" [
	"GUI Menu"
	"n_gui_visible"
	"Particles" [
		"Particle Preferences"
		"n_gui_ncc_particles_enabled"
		"n_gui_ncc_particles_type"
    "n_gui_ncc_particles_chance"
    "n_gui_ncc_particles_pack_size"
    "n_gui_ncc_particles_safe"
    "n_gui_ncc_particles_gravity"
    "n_gui_ncc_particles_jittering"
    "n_gui_ncc_particles_wind"
    "n_gui_ncc_particles_jittering_chance"
	]
  "Debug" [
      "Debug Menu Enjoy"
      "n_gui_debug_draw_bounds"
  ]
]
)";

int main() {
    xoverlay_init();

    glez::init(xoverlay_library.width, xoverlay_library.height);

    {
        input::RefreshInput();
        xoverlay_draw_begin();
        glez::begin();

        g_pGUI = new CatGUI();
        g_pGUI->Setup();

        glez::end();
        xoverlay_draw_end();
    }

    auto test_window = new TestWindow();

    g_pGUI->m_pRootWindow->AddChild(test_window);

    using namespace menu::ncc;
    // auto* list_menu = List::FromString(menu_list);
    auto* list_menu = new List();
    list_menu->Fill(ui::BaseVar::GetList());
    list_menu->Props()->SetBool("brackets3", true);
    list_menu->SetMaxSize(1000, 1000);
    list_menu->Show();
    g_pGUI->m_pRootWindow->AddChild(list_menu);

    auto* tabbedmenu = new CMenuWindow("menu_window", g_pGUI->m_pRootWindow);
    tabbedmenu->SetMaxSize(912, 410);

    tabbedmenu->AddTab("aimbot", "Main");
    CMenuContainer* tab = tabbedmenu->GetTab("aimbot");
    tab->AddChild(new CTextLabel("label", tab, "This is a bool!", true));
    tab->AddChild(new CCVarContainer(tab, &text));
    tabbedmenu->AddTab("esp", "Sub");
    tabbedmenu->AddTab("esp2", "Sub2");
    tabbedmenu->AddTab("esp3", "Sub3");

    // tabbedmenu->SetOffset((draw::width - 912) / 2, (draw::height - 410) / 2);
    g_pGUI->m_pRootWindow->AddChild(tabbedmenu);

    for (auto& i : ui::BaseVar::GetList())
        printf("ui::BaseVar: %s\n", i->command_name.c_str());
    xoverlay_show();
    while (1) {
        input::RefreshInput();
        // Must be called in that order.
        xoverlay_draw_begin();
        glez::begin();
        {

            // glez::draw::rect(100, 300, 200, 100, glez::rgba(255, 0, 128));
            // auto mouse = input::GetMouse();
            // glez::draw::rect(mouse.first - 6, mouse.second - 6, 12, 12, glez::rgba(255, 0, 128));
            g_pGUI->m_pRootWindow->Update();
            // glez::draw::rect_textured(50, 50, 100, 100, g_pGUI->m_pRootWindow->GetColor(), dispenser, 0, 10, 40, 94, 7);
            /*bool pressed = input::GetKey(CatKey::CATKEY_MOUSE_1);
            if (!click) {
                if (pressed) {
                  click = true;
                  auto size = test_window->GetSize();
                  printf("test_window size: %i, %i\n", size.first, size.second);
                  size = test_window->GetMaxSize();
                  printf("test_window max size: %i, %i\n", size.first, size.second);
                }
            } else if (!pressed) {
                click = false;
            }*/
        }
        glez::end();
        xoverlay_draw_end();
    }
    return 0;
}
