
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

#include "gui/widgets/basewindow.hpp"

class CMenuList;
class CMenuContainer;
class CTitleBar;

class CMenuWindow : public CBaseWindow {
public:
    CMenuWindow(IWidget* parent, std::string name);
    CMenuWindow(std::string name, IWidget* parent)
        : CMenuWindow(parent, name) { }

    void AddElements();

    void SelectTab(std::string tab);
    void AddTab(std::string tab, std::string name);
    CMenuContainer* GetTab(std::string tab);

    virtual void MoveChildren() override;

    CMenuList* m_pList;
    CTitleBar* m_pTitle;
    CMenuContainer* m_pActiveTab;
};
