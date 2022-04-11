
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

#include "menulist.hpp"

#include "gui/tabbedmenu/menuwindow.hpp"
#include "menulistentry.hpp"

CMenuList::CMenuList(std::string name, CMenuWindow* parent)
    : CBaseContainer(name, parent) {
}

void CMenuList::AddEntry(std::string id, std::string name) {
    CMenuListEntry* entry = new CMenuListEntry("entry_" + id, this, id);
    entry->SetText(name);
    entry->SetCallback([entry](CBaseButton* thisptr) {
        CMenuWindow* window = dynamic_cast<CMenuWindow*>(thisptr->GetParent()->GetParent());
        window->SelectTab(entry->entry);
    });
    AddChild(entry);
}

void CMenuList::SelectEntry(std::string id) {
    m_pSelected = dynamic_cast<CMenuListEntry*>(ChildByName("entry_" + id));
}

void CMenuList::MoveChildren() {
    int cc = ChildCount();
    auto ms = GetMaxSize();
    for (int i = 0; i < cc; i++) {
        auto child = ChildByIndex(i);
        child->SetMaxSize(ms.first, ms.second / cc);
        child->SetOffset(0, (ms.second / cc) * i);
    }
}
