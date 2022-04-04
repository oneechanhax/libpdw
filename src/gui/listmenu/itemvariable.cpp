/*
 * ItemVariable.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/color.hpp>
#include <glez/draw.hpp>
#include <stdexcept>
#include <var.hpp>

#include "gui/gui.hpp"
#include "gui/listmenu/item.hpp"
#include "gui/listmenu/itemvariable.hpp"

namespace menu {
namespace ncc {

    ItemVariable::ItemVariable(ui::BaseVar& variable)
        : Item("ncc_item_variable_" + variable.command_name)
        , catvar(variable) {
    }

    void ItemVariable::Update() {
        Item::Update();
        /*if (catvar.desc_long.length() && IsHovered() && catvar.desc_long != "no description")
                ShowTooltip(catvar.desc_long);*/
        // if (IsHovered())
        // g_pGUI->GetRootWindow()->ShowTooltip("no description");
    }

    void ItemVariable::Change(float amount) {
        if (!amount)
            return;
        switch (catvar.type) {
        case ui::BaseVar::Type::kBool: {
            static_cast<ui::Var<bool>&>(catvar) = !static_cast<ui::Var<bool>&>(catvar);
        } break;
        case ui::BaseVar::Type::kEnum:
        case ui::BaseVar::Type::kInt: {
            static_cast<ui::Var<int>&>(catvar) = static_cast<ui::Var<int>&>(catvar) + amount;
        } break;
        case ui::BaseVar::Type::kFloat: {
            static_cast<ui::Var<float>&>(catvar) = static_cast<ui::Var<float>&>(catvar) + amount;
        } break;
        }
    }

    bool ItemVariable::ConsumesKey(CatKey key) {
        if (capturing)
            return true;
        if (key == CatKey::CATKEY_M_WHEEL_DOWN || key == CatKey::CATKEY_M_WHEEL_UP || key == CatKey::CATKEY_MOUSE_1)
            return true;
        return false;
    }

    void ItemVariable::OnMousePress() {
        if (catvar.type == ui::BaseVar::Type::kKey)
            capturing = true;
        if (catvar.type == ui::BaseVar::Type::kBool)
            static_cast<ui::Var<bool>&>(catvar) = !static_cast<ui::Var<bool>&>(catvar);
    }

    void ItemVariable::OnFocusLose() {
        capturing = false;
    }

    void ItemVariable::OnKeyPress(CatKey key, bool repeat) {
        if (capturing) {
            static_cast<ui::Var<CatKey>&>(catvar) = key;
            capturing = false;
            return;
        }

        float change = 0.0f;

        switch (catvar.type) {
        case ui::BaseVar::Type::kEnum:
        case ui::BaseVar::Type::kBool:
            change = 1.0f;
            break;
        case ui::BaseVar::Type::kInt:
        case ui::BaseVar::Type::kFloat: {
            auto float_var = static_cast<ui::Var<float>&>(catvar);
            if (float_var.min != 0 || float_var.max != 100) {
                change = float(float_var.max - float_var.min) / 50.0f;
            } else {
                change = 1.0f;
            }
        }
        }

        if (change < 1.0f && catvar.type == ui::BaseVar::Type::kInt)
            change = 1.0f;

        if ((catvar.type == ui::BaseVar::Type::kBool && key == CatKey::CATKEY_MOUSE_1) || key == CatKey::CATKEY_M_WHEEL_UP) {
            Change(change);
        } else if (key == CatKey::CATKEY_M_WHEEL_DOWN) {
            Change(-change);
        }
    }

    void ItemVariable::Draw(int x, int y) {
        Item::Draw(x, y);
        std::string val = "[UNDEFINED]";
        switch (catvar.type) {
        case ui::BaseVar::Type::kBool:
        case ui::BaseVar::Type::kInt:
        case ui::BaseVar::Type::kFloat:
        case ui::BaseVar::Type::kEnum:
        case ui::BaseVar::Type::kString:
            val = catvar.GetString();
            break;
        case ui::BaseVar::Type::kKey: {
            if (capturing) {
                val = "[PRESS A KEY]";
            } else {
                if (static_cast<ui::Var<CatKey>&>(catvar) != CATKEY_NONE) {
                    val = input::key_names[static_cast<CatKey>(static_cast<ui::Var<CatKey>&>(catvar))];
                } else {
                    val = "[CLICK TO SET]";
                }
            }
        } break;
        }
        glez::draw::string(x + 2, y, (std::string(catvar.gui_name) + ": " + val), g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
    }

}
}
