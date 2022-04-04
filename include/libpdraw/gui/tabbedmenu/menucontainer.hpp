/*
 * CMenuContainer.h
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/basecontainer.hpp"

class CMenuWindow;

class CMenuContainer : public CBaseContainer {
public:
    CMenuContainer(std::string name, CMenuWindow* parent);

    virtual inline void SortByZIndex() override {};
    virtual void MoveChildren() override;
    virtual void Draw(int x, int y) override;
};
