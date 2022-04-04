
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

#pragma once

class IWidget;

#include <string>

#include "canvas.hpp"
#include "input.hpp"

/// Main root object of libpdraw
/**
 * The main required global of the library.
 * You MUST set g_pGUI to a valid pointer and run Setup() afterwards for anything to function.
 */
class CatGUI {
public:
    CatGUI();
    ~CatGUI();

    void Setup();
    Canvas* GetRootWindow(); /**< Use to get a container you can add widgets to. */
    Canvas* m_pRootWindow;
};
/** Must be a valid pointer for library to function. */
extern CatGUI* g_pGUI;
