/*
 * GUI.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: nullifiedcat
 */

#include <cmath>
#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/gui.hpp"
#include "gui/listmenu/itemsublist.hpp"
#include "gui/listmenu/itemtitle.hpp"
#include "gui/listmenu/itemvariable.hpp"
#include "gui/listmenu/list.hpp"
#include "gui/ncc/background.hpp"
#include "gui/ncc/logo.hpp"
#include "gui/tabbedmenu/cvarcontainer.hpp"
#include "gui/tabbedmenu/menucontainer.hpp"
#include "gui/tabbedmenu/menuwindow.hpp"
#include "gui/widgets/iwidget.hpp"
#include "tooltip.hpp"

CatGUI::CatGUI() {
    m_pRootWindow = nullptr;
}
void CatGUI::Setup() {
    m_pRootWindow = new Canvas();
    m_pRootWindow->Setup();

    auto* logo = new ncc::Logo();
    logo->SetOffset(500, 25);
    m_pRootWindow->AddChild(logo);

    m_pRootWindow->AddChild(new ncc::Background());
}

CatGUI::~CatGUI() {
    delete m_pRootWindow;
}

/*bool CatGUI::ConsumesKey(CatKey key) {
        CBaseWindow* root =  dynamic_cast<CBaseWindow*>(m_pRootWindow);
        if (root->Isgui_visible)
                return root->ConsumesKey(key);
        else return false;
}*/

Canvas* CatGUI::GetRootWindow() {
    return m_pRootWindow;
}

CatGUI* g_pGUI = 0;
