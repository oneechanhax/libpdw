
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
#include <embed_resources.hpp>
#include <glez/detail/render.hpp>
#include <glez/draw.hpp>
#include <glez/glez.hpp>

// xorg conflict
#undef RootWindow

#include "libpdw/gui/widgets/slider.hpp"
#include "libpdw/gui/widgets/titlebar.hpp"
//#include "gui/csplitcontainer.hpp"
#include "libpdw/gui/canvas.hpp"
#include "libpdw/gui/widgets/basebutton.hpp"
#include "libpdw/gui/widgets/basewindow.hpp"
#include "libpdw/gui/widgets/checkbox.hpp"
#include "libpdw/gui/widgets/dropdown.hpp"
#include "libpdw/gui/widgets/keyinput.hpp"
#include "libpdw/gui/widgets/textinput.hpp"

#include "libpdw/gui/listmenu/itemsublist.hpp"
#include "libpdw/gui/listmenu/itemtitle.hpp"
#include "libpdw/gui/listmenu/itemvariable.hpp"
#include "libpdw/gui/listmenu/list.hpp"
#include "libpdw/gui/tabbedmenu/cvarcontainer.hpp"
#include "libpdw/gui/tabbedmenu/menucontainer.hpp"
#include "libpdw/gui/tabbedmenu/menuwindow.hpp"

#include "libpdw/gui/ncc/background.hpp"
#include "libpdw/gui/ncc/logo.hpp"

#include "input.hpp"

static ui::Var<int> text({ "nonya" }, "Editable Text", 1);

class TestWindow : public CBaseWindow {
public:
    TestWindow(IWidget* parent)
        : CBaseWindow(parent, "root_test") {
        this->always_visible = false;
        this->hover = false;
        this->SetMaxSize(1270, 1000);
        this->SetPositionMode(PositionMode::FLOATING);

        this->Add<CTitleBar>("Test uwu~");
        // this->visible = true;

        this->Add<CTextLabel>("button_label", "Button widget:");
        this->Add<CBaseButton>("button", "I'm Clickable!", [this](CBaseButton*) {
            std::cout << "Hey hey I was pressed!" << std::endl;
            this->button_clicked = !this->button_clicked;
        });

        this->Add<CTextLabel>("checkbox_label", "Checkbox widget:");
        this->Add<CCheckbox>("checkbox", false);

        this->Add<CTextLabel>("slider_label", "Slider widget:");
        this->Add<CSlider>("slider")->SetStep(0.1f);

        this->Add<CTextLabel>("dropdown_label", "Dropdown widget:");
        auto* dropdown = this->Add<CDropdown>("dropdown");
        dropdown->AddValue("Im the cutest princess!");
        dropdown->AddValue("No I am, hmp!");
        dropdown->AddValue("*doomguy noises*");
        dropdown->SetSize(150, 16);

        this->Add<CTextLabel>("text_input_label", "Text input widget:");
        this->Add<CTextInput>("text_input")->SetValue("You can edit me!");

        this->Add<CTextLabel>("key_input_label", "Key widget:");
        this->Add<CKeyInput>("key_input")->SetSize(78, 10);
    }
    virtual void Update() override {
        this->CBaseWindow::Update();
        if (this->button_clicked)
            this->GetCanvas()->ShowTooltip("This is an example of a very long tooltip! You can click me again to hide me from view. Thanks for using libpdw ;)");
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

    Canvas* canvas;
    {
        input::RefreshInput();
        xoverlay_draw_begin();
        glez::begin();

        canvas = new Canvas();
        canvas->Setup();

        glez::end();
        xoverlay_draw_end();
    }
    auto bounds = input::GetBounds();

    auto test_window = canvas->Add<TestWindow>();

    using namespace menu::ncc;
    // auto* list_menu = List::FromString(menu_list);
    auto* list_menu = new List();
    list_menu->Fill(ui::BaseVar::GetList());
    ItemTitle* find = nullptr;
    for (auto* i : list_menu->m_children)
        if ((find = dynamic_cast<ItemTitle*>(i)))
            break;
    if (find)
        find->brackets = true;
    list_menu->SetMaxSize(1000, 1000);
    list_menu->Show();
    canvas->AddChild(list_menu);
    list_menu->SetOffset((bounds.first - 912) / 4, (bounds.second - 410) / 3);

    auto* tabbedmenu = canvas->Add<CMenuWindow>("menu_window");
    tabbedmenu->SetMaxSize(912, 410);

    tabbedmenu->AddTab("aimbot", "Main");
    CMenuContainer* tab = tabbedmenu->GetTab("aimbot");
    tab->Add<CTextLabel>("label", "This is a bool!", true);
    tab->Add<CCVarContainer>(&text);
    tabbedmenu->AddTab("esp", "Sub");
    tabbedmenu->AddTab("esp2", "Sub2");
    tabbedmenu->AddTab("esp3", "Sub3");
    tabbedmenu->SetOffset((bounds.first - 912) / 2, (bounds.second - 410) / 2);

    canvas->Add<ncc::Logo>()->SetOffset(500, 25);

    canvas->AddChild(new ncc::Background());

    /*for (auto& i : ui::BaseVar::GetList())
        printf("ui::BaseVar: %s\n", i->command_name.c_str());*/
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
            canvas->Update();
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
