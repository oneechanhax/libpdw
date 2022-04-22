
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

#include <functional>

#include "textlabel.hpp"

#define BUTTON_PADDING_W 3
#define BUTTON_PADDING_H 2

class CBaseButton;

typedef std::function<void(CBaseButton*)> ButtonCallbackFn_t;

class CBaseButton : public CTextLabel {
public:
    CBaseButton(IWidget* parent, std::string name = "unnamed", std::string text = "", ButtonCallbackFn_t callback = nullptr);
    CBaseButton(std::string name = "unnamed", IWidget* parent = nullptr, std::string text = "", ButtonCallbackFn_t callback = nullptr)
        : CBaseButton(parent, name, text, callback) { }

    virtual void Draw(int x, int y) override;
    virtual void OnMousePress() override;

    void SetCallback(ButtonCallbackFn_t callback);

    ButtonCallbackFn_t m_pCallback;
    std::pair<int, int> padding;
};
