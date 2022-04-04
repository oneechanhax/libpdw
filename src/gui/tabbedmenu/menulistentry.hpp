/*
 * CMenuListEntry.h
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/basebutton.hpp"

class CMenuList;

class CMenuListEntry : public CBaseButton {
public:
    CMenuListEntry(std::string name, CMenuList* parent, std::string entry);

    bool IsSelected();

    virtual void SetMaxSize(int x, int y) override;
    virtual void Draw(int x, int y) override;
};
