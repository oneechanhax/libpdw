
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

#include "gui/tabbedmenu/menuwindow.hpp"
#include "gui/tabbedmenu/cvarcontainer.hpp"
#include "gui/tabbedmenu/menucontainer.hpp"
#include "gui/tabbedmenu/menulist.hpp"
#include "gui/widgets/basebutton.hpp"
#include "gui/widgets/textlabel.hpp"

#include "gui/widgets/titlebar.hpp"

CMenuWindow::CMenuWindow(IWidget* parent, std::string name)
    : CBaseWindow(parent, name) {
    m_pList = new CMenuList("list", this);
    AddChild(m_pList);
    m_pActiveTab = 0;
    AddChild(m_pTitle = new CTitleBar(this, "cathook menu"));
}

#define ADDCVAR(x) tab->AddChild(new CCVarContainer(tab, (x)))
#define ADDLABEL(x) tab->AddChild(new CTextLabel("label", tab, x, true))
#define ADDCVARS(x)                 \
    for (auto var : FindCatVars(x)) \
    ADDCVAR(var)

std::vector<ui::BaseVar*> FindCatVars(const std::string name) {
    std::vector<ui::BaseVar*> result = {};
    for (auto var : ui::BaseVar::GetList()) {
        if (var->command_name.find(name) == 0)
            result.push_back(var);
    }
    return result;
}

void CMenuWindow::AddElements() {
    /// * AddTab("aimbot", "Aimbot");
    /*CMenuContainer* tab = GetTab("aimbot");
    for (auto var : FindCatVars("aimbot_")) ADDCVAR(var);
    AddTab("esp", "ESP");
    tab = GetTab("esp");
    for (auto var : FindCatVars("esp_")) ADDCVAR(var);
    AddTab("triggerbot", "Triggerbot");
    tab = GetTab("triggerbot");
    for (auto var : FindCatVars("triggerbot_")) ADDCVAR(var);
    if (TF) {
            ADDLABEL("AutoSticky");
            for (auto var : FindCatVars("sticky_")) ADDCVAR(var);
            ADDLABEL("AutoReflect");
            for (auto var : FindCatVars("reflect_")) ADDCVAR(var);
    }
    AddTab("misc", "Misc");
    tab = GetTab("misc");
    ADDCVARS("thirdperson");
    ADDCVARS("log");
    ADDCVARS("no_");
    ADDCVARS("fov");
    ADDCVARS("clean_");
    ADDCVARS("tauntslide");
    ADDCVARS("airstuck");
    ADDCVARS("fast_");
    ADDCVARS("ignore_");
    ADDCVARS("rollspeedhack");
    ADDCVARS("minigun");
    ADDCVARS("disconnect");

    if (TF) ADDCVAR(&hacks::tf::autoheal::enabled);
    if (TF) ADDCVAR(&hacks::tf2::antidisguise::enabled);
    if (TF2C) {

    }

    ADDCVAR(&cathook);

    if (TF) {
            ADDLABEL("Spy Alert");
            for (auto var : FindCatVars("spyalert_")) ADDCVAR(var);
    }
    ADDLABEL("Bunnyhop");
    ADDCVARS("bhop");
    AddTab("antiaim", "Anti-Aim");
    tab = GetTab("antiaim");
    for (auto var : FindCatVars("aa_")) ADDCVAR(var);
    AddTab("spam", "Spam/Killsay");
    tab = GetTab("spam");
    ADDLABEL("Spam");
    ADDCVARS("spam");
    tab->AddChild(new CBaseButton("spam_reload", tab, "Reload spam", [this](CBaseButton*) {
            hacks::shared::spam::Reload();
    }));
    ADDLABEL("Killsay");
    ADDCVARS("killsay");
    tab->AddChild(new CBaseButton("killsay_reload", tab, "Reload killsays", [this](CBaseButton*) {
            hacks::shared::killsay::Reload();
    }));
    AddTab("multibox", "Bots");
    tab = GetTab("multibox");
    for (auto var : FindCatVars("ipc_")) ADDCVAR(var);
    for (auto var : FindCatVars("fb_")) ADDCVAR(var);
    ADDLABEL("Stats window/bot management coming soon!"); */
    //
}

CMenuContainer* CMenuWindow::GetTab(std::string tab) {
    return dynamic_cast<CMenuContainer*>(ChildByName("tab_" + tab));
}

void CMenuWindow::AddTab(std::string tab, std::string name) {
    m_pList->AddEntry(tab, name);
    CMenuContainer* container = new CMenuContainer("tab_" + tab, this);
    if (!m_pActiveTab)
        m_pActiveTab = container;
    AddChild(container);
    container->Hide();
}

void CMenuWindow::SelectTab(std::string tab) {
    if (m_pActiveTab)
        m_pActiveTab->Hide();
    m_pActiveTab = GetTab(tab);
    m_pList->SelectEntry(tab);
    if (m_pActiveTab)
        m_pActiveTab->Show();
}

void CMenuWindow::MoveChildren() {
    auto ms = GetMaxSize();
    auto th = m_pTitle->GetSize().second;
    SetSize(ms.first, ms.second);
    m_pList->SetMaxSize(200, ms.second - th);
    m_pList->SetSize(200, ms.second - th);
    m_pList->SetOffset(0, th);
    if (m_pActiveTab) {
        m_pActiveTab->SetOffset(200, th);
        m_pActiveTab->SetMaxSize(ms.first - 200, ms.second - th);
        m_pActiveTab->SetSize(ms.first - 200, ms.second - th);
    }
}
