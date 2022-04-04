/*
 * ItemTitle.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/color.hpp>
#include <glez/draw.hpp>
#include <glez/font.hpp>

#include "gui/gui.hpp"
#include "gui/listmenu/itemtitle.hpp"

namespace menu {
namespace ncc {

    ItemTitle::ItemTitle(std::string title)
        : Item("ncc_list_title")
        , title(title) {
        Props()->SetBool("brackets3", false);
    }

    void ItemTitle::Draw(int x, int y) {
        Item::Draw(x, y);
        // nailed it
        bool brackets3 = Props()->GetBool("brackets3");
        std::string str = (brackets3 ? ">>> " : ">> ") + title + (brackets3 ? " <<<" : " <<");
        std::pair<float, float> size;
        g_pGUI->GetRootWindow()->GetFont().stringSize(str, &size.first, &size.second);
        glez::draw::string(x + ((Item::size_x - size.first) / 2), y, str, g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
    }

}
}
