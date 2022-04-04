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
