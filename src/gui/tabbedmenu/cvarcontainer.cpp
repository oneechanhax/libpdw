
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

#include "gui/tabbedmenu/cvarcontainer.hpp"

#include "gui/widgets/checkbox.hpp"
#include "gui/widgets/dropdown.hpp"
#include "gui/widgets/keyinput.hpp"
#include "gui/widgets/slider.hpp"
#include "gui/widgets/textinput.hpp"
#include "gui/widgets/textlabel.hpp"

CCVarContainer::CCVarContainer(IWidget* parent, ui::BaseVar* var)
    : CBaseContainer("cvc_" + var->command_name, parent) {
    m_pVar = var;
    m_pInput = 0;
    m_pLabel = new CTextLabel(GetName() + "_desc", this, std::string(var->gui_name));
    m_pControl = 0;
    SetMaxSize(200, 200);
    /*if (var->gui_name.length()) {
            Props()->SetString("tooltip", var->desc_long.c_str());
    }*/
    bool needsinput = false;
    switch (var->type) {
    case ui::BaseVar::Type::kBool: { // Label, Checkbox
        CCheckbox* cb = new CCheckbox(GetName() + "_control", this, static_cast<ui::Var<bool>*>(var));
        cb->SetCallback([this](CCheckbox*, bool value) {
            *static_cast<ui::Var<bool>*>(m_pVar) = value;
        });
        m_pControl = cb;
    } break;
    case ui::BaseVar::Type::kEnum: { // Most difficult thing, dropdown menu
        CDropdown* dd = new CDropdown(GetName() + "_control", this);
        for (auto i : static_cast<ui::Var<ui::Enum>*>(var)->internal_enum)
            dd->AddValue(std::string(i));
        dd->SetCallback([this](CDropdown*, int value) {
            *static_cast<ui::Var<ui::Enum>*>(m_pVar) = value;
        });
        dd->Props()->SetInt("offset", 0 /*var->enum_type->Minimum()*/);
        m_pControl = dd;
    } break;
    case ui::BaseVar::Type::kFloat: {
        // if (var->restricted) {
        CSlider* sl = new CSlider(GetName() + "_control", this);
        sl->Setup(static_cast<ui::Var<float>*>(var)->min, static_cast<ui::Var<float>*>(var)->max);
        sl->SetValue(*static_cast<ui::Var<float>*>(var));
        m_pControl = sl;
        sl->SetCallback([this](CSlider*, float oldv, float newv) {
            *static_cast<ui::Var<float>*>(m_pVar) = newv;
        });

        needsinput = true;
    } break;
    case ui::BaseVar::Type::kInt: {
        // if (var->restricted) {
        CSlider* sl = new CSlider(GetName() + "_control", this);
        sl->Setup(static_cast<ui::Var<int>*>(var)->min, static_cast<ui::Var<int>*>(var)->max);
        sl->SetStep(1.0f);
        sl->SetValue(*static_cast<ui::Var<int>*>(var));
        sl->SetCallback([this](CSlider*, float oldv, float newv) {
            *static_cast<ui::Var<int>*>(m_pVar) = newv;
        });
        m_pControl = sl;

        needsinput = true;
    } break;
    case ui::BaseVar::Type::kKey: {
        /*CKeyInput* ki = new CKeyInput(GetName() + "_control", this);
        ki->SetCallback([this](CKeyInput*, CatKey key) {
                m_pVar->SetValue(key);
        });
        ki->SetSize(60, 18);
        m_pControl = ki;*/
    } break;
    case ui::BaseVar::Type::kString: {
        needsinput = true;
    } break;
    }

    if (needsinput) {
        m_pInput = new CTextInput(GetName() + "_input", this);
        m_pInput->SetValue(std::string(var->GetString()));
        m_pInput->SetCallback([this](CTextInput*, std::string old, std::string newv) {
            if (m_pVar->type == ui::BaseVar::Type::kString) {
                *static_cast<ui::Var<std::string>*>(m_pVar) = newv;
            } else {
                try {
                    m_pVar->Call(std::cerr, { newv });
                } catch (...) {
                }
            }
        });
    }

    if (m_pLabel) {
        AddChild(m_pLabel);
    }
    if (m_pControl) {
        AddChild(m_pControl);
    }
    if (m_pInput) {
        m_pInput->SetMaxWidth(10);
        AddChild(m_pInput);
    }
}

void CCVarContainer::MoveChildren() {
    int sy = 0;
    for (auto child : m_children) {
        auto s = child->GetSize();
        if (sy < s.second)
            sy = s.second;
    }
    auto max = GetMaxSize();
    SetSize(max.first, sy + 4);
    auto labels = m_pLabel->GetSize();
    m_pLabel->SetOffset(2, (sy - labels.second) / 2 + 2);
    int x = max.first - 2;
    if (m_pInput) {
        auto inputs = m_pInput->GetSize();
        x -= inputs.first + 2;
        m_pInput->SetOffset(x + 2, (sy - inputs.second) / 2 + 2);
    }
    if (m_pControl) {
        auto controls = m_pControl->GetSize();
        m_pControl->SetMaxSize(x - 4 - labels.first, sy - 4);
        x -= controls.first + 2;
        m_pControl->SetOffset(x + 2, (sy - controls.second) / 2 + 2);
    }
}

void CCVarContainer::Update() {
    static int updticks = 0;
    updticks++;
    if (m_pVar && !(updticks % 30)) {
        updticks = 1;
        if (m_pInput) {
            if (!m_pInput->IsFocused())
                m_pInput->SetValue(m_pVar->GetString());
        }
        if (m_pControl && !m_pControl->IsFocused()) {
            switch (m_pVar->type) {
            case ui::BaseVar::Type::kEnum: {
                dynamic_cast<CDropdown*>(m_pControl)->SetValue(*static_cast<ui::Var<int>*>(m_pVar));
            } break;
            case ui::BaseVar::Type::kFloat:
            case ui::BaseVar::Type::kInt: {
                dynamic_cast<CSlider*>(m_pControl)->SetValue(*static_cast<ui::Var<float>*>(m_pVar));
            } break;
            case ui::BaseVar::Type::kKey: {
                dynamic_cast<CKeyInput*>(m_pControl)->SetValue(*dynamic_cast<ui::Var<int>*>(m_pVar));
            } break;
            case ui::BaseVar::Type::kBool: {
                dynamic_cast<CCheckbox*>(m_pControl)->SetValue(*static_cast<ui::Var<bool>*>(m_pVar));
            } break;
            }
        }
    }
    CBaseContainer::Update();
}
