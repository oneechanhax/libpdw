/*
 * CMenuWindow.h
 *
 *  Created on: Feb 3, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/basewindow.hpp"

class CMenuList;
class CMenuContainer;
class CTitleBar;

class CMenuWindow : public CBaseWindow {
public:
	CMenuWindow(std::string name, IWidget* parent);

	void AddElements();

	void SelectTab(std::string tab);
	void AddTab(std::string tab, std::string name);
	CMenuContainer* GetTab(std::string tab);

	virtual void MoveChildren() override;

	CMenuList* m_pList;
	CTitleBar* m_pTitle;
	CMenuContainer* m_pActiveTab;
};
