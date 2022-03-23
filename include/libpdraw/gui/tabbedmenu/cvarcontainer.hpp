/*
 * CCVarContainer.h
 *
 *  Created on: Jan 28, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/basecontainer.hpp"
#include "var.hpp"

class CTextInput;
class CTextLabel;

class CCVarContainer : public CBaseContainer {
public:
	CCVarContainer(IWidget* parent, ui::BaseVar* var);

	virtual void MoveChildren() override;
	virtual void Update() override;

	CTextInput* m_pInput;
	IWidget* m_pControl;
	CTextLabel* m_pLabel;

	ui::BaseVar* m_pVar;
};
