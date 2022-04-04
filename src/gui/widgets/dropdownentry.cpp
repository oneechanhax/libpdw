/*
 * CDropdownEntry.cpp
 *
 *  Created on: Jan 31, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/gui.hpp"

#include "dropdownentry.hpp"

CDropdownEntry::CDropdownEntry(std::string name, CDropdownList* parent, std::string text, int value)
    : CBaseButton(name, parent, text) {
    Props()->SetInt("value", value);
    SetCallback([this](CBaseButton*) -> void {
        CDropdownList* parent = dynamic_cast<CDropdownList*>(GetParent());
        if (!parent)
            return;
        parent->SetValue(Props()->GetInt("value"));
    });
}

void CDropdownEntry::Draw(int x, int y) {
    std::pair<float, float> ssize;
    g_pGUI->GetRootWindow()->GetFont().stringSize(GetText(), &ssize.first, &ssize.second);
    auto size = GetSize();
    glez::draw::string(x + (size.first - ssize.first) / 2, y + (size.second - ssize.second) / 2, GetText(), g_pGUI->GetRootWindow()->GetFont(), g_pGUI->GetRootWindow()->GetColor(), nullptr, nullptr);
}

CDropdownEntry::~CDropdownEntry() {
}
