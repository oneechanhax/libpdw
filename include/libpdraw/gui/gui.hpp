/*
 * GUI.h
 *
 *  Created on: Jan 25, 2017
 *      Author: nullifiedcat
 */

#pragma once

class IWidget;

#include <string>

#include "canvas.hpp"
#include "input.hpp"

class CatGUI {
public:
    CatGUI();
    ~CatGUI();

    void Setup();
    Canvas* GetRootWindow();
    Canvas* m_pRootWindow;
};
extern CatGUI* g_pGUI;
