
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

#pragma once

#include "basewidget.hpp"

class CTextLabel : public CBaseWidget {
public:
    CTextLabel(IWidget* parent, std::string name, std::string text = "", bool centered = false);
    CTextLabel(std::string name, IWidget* parent, std::string text = "", bool centered = false)
        : CTextLabel(parent, name, text, centered) { }
    CTextLabel(std::string name = "unnamed", bool centered = false);

    void SetText(std::string text);
    std::string GetText();
    void SetPadding(int x, int y);
    void SetAutoSize(bool autosize);
    void SetCentered(bool centered);

    virtual void Draw(int x, int y);

private:
    bool autosize;
    bool centered;
    std::pair<int, int> padding;
    std::string text;
};
