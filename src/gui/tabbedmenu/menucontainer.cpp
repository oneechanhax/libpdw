/*
 * CMenuContainer.cpp
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/tabbedmenu/menucontainer.hpp"
#include "gui/tabbedmenu/menuwindow.hpp"
#include "gui/widgets/basebutton.hpp"

CMenuContainer::CMenuContainer(std::string name, CMenuWindow* parent)
    : CBaseContainer(name, parent) { SetMaxSize(200, 200); }

void CMenuContainer::MoveChildren() {
    int column_size = 350;
    int x = 3, y = 2;
    int columns = 0;
    int my = GetMaxSize().second;
    for (int i = 0; i < ChildCount(); i++) {
        auto c = ChildByIndex(i);
        if (y + c->GetSize().second >= my) {
            y = 2;
            x += column_size + 3;
            columns++;
        }
        c->SetOffset(x, y);
        if (!dynamic_cast<CBaseButton*>(c))
            c->SetSize(column_size, -1);
        c->SetMaxSize(column_size, -1);
        y += c->GetSize().second + 2;
    }
    this->columns = columns;
}

void CMenuContainer::Draw(int x, int y) {
    CBaseContainer::Draw(x, y);
    for (int i = 0; i < this->columns; i++) {
        glez::draw::line(x + (350 + 3) * (i + 1), y, 0, GetMaxSize().second, this->GetCanvas()->GetColor(), 1);
    }
}
