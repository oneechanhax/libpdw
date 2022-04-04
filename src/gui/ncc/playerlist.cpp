
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

//#include "menu.hpp"

namespace menu {
namespace ncc {

/*
int size_table_width() {
        int accum = 1;
        for (int i = 0; i < sizeof(size_table) / sizeof(int); i++) {
                accum += (size_table[i] + 1) * (float)scale;
        }
        return accum;
}

PlayerList::PlayerList() : CBaseContainer() {
        for (int i = 0; i <= 32; i++) {
                AddChild(new PlayerListEntry(i));
        }
}

bool PlayerList::IsVisible() {
        return !g_Settings.bInvalid;
}

void PlayerList::Draw(int x, int y) {
        if (g_Settings.bInvalid) return;
        const auto& size = GetSize();
        draw::DrawRect(x, y, size.first, size.second, colors::Create(0, 0, 0, 77));
        draw::OutlineRect(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor());
        for (int i = 0; i < Props()->GetInt("vischildren"); i++) {
                draw::DrawLine(x, y + i * (Item::size_y + 2), size_table_width(), 0, g_pGUI->GetRootWindow()->GetColor());
        }
        int accum = 0;
        for (int i = 0; i < sizeof(size_table) / sizeof(int); i++) {
                draw::DrawLine(x + accum, y, 0, size.second, g_pGUI->GetRootWindow()->GetColor());
                accum += (size_table[i] + 1) * (float)scale;
        }
        CBaseContainer::Draw(x, y);
}

void PlayerList::OnKeyPress(ButtonCode_t key, bool repeat) {
        if (GetHoveredChild()) GetHoveredChild()->OnKeyPress(key, repeat);
}

void PlayerList::Update() {
        if (g_Settings.bInvalid) return;
        if (IsPressed()) {
                auto offset = GetOffset();
                offset.first += g_pGUI->mouse_dx;
                offset.second += g_pGUI->mouse_dy;
                SetOffset(offset.first, offset.second);
        }
        CBaseContainer::Update();
}

void PlayerList::MoveChildren() {
        int visible = 0;
        for (int i = 0; i < ChildCount(); i++) {
                ChildByIndex(i)->SetOffset(0, 1 + visible * (Item::size_y + 2));
                if (ChildByIndex(i)->IsVisible()) visible++;
        }
        SetSize(size_table_width(), visible * (Item::size_y + 2) + 1);
        Props()->SetInt("vischildren", visible);
}*/

}
} // namespace menu::ncc
