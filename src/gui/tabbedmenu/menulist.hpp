/*
 * CMenuList.h
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/basecontainer.hpp"

class CMenuWindow;
class CMenuContainer;
class CMenuListEntry;

class CMenuList : public CBaseContainer {
public:
    CMenuList(std::string name, CMenuWindow* parent);

    void SelectEntry(std::string id);
    void AddEntry(std::string id, std::string name);

    virtual void MoveChildren() override;

    CMenuListEntry* m_pSelected;
};
