/*
 * CDropdownEntry.h
 *
 *  Created on: Jan 31, 2017
 *      Author: nullifiedcat
 */

#ifndef CDROPDOWNENTRY_H_
#define CDROPDOWNENTRY_H_

#include "gui/widgets/basebutton.hpp"
#include "gui/widgets/dropdownlist.hpp"

class CDropdownEntry : public CBaseButton {
public:
	CDropdownEntry(std::string name = "unnamed", CDropdownList* parent = nullptr, std::string text = "unset", int value = 0);
	~CDropdownEntry();

	virtual void Draw(int x, int y);
};



#endif /* CDROPDOWNENTRY_H_ */
