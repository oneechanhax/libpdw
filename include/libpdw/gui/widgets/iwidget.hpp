
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

#include <cstring>
#include <functional>
#include <string>
#include <utility>

#include "input.hpp"

enum PositionMode {
    ABSOLUTE = 0,
    INLINE,
    FLOATING
};

class KeyValues;
class Canvas;
class IWidget {
public:
    virtual ~IWidget();

    virtual void Update() = 0;
    virtual void Draw(int x, int y) = 0;
    virtual void DrawBounds(int x, int y) = 0;

    virtual KeyValues* Props() const = 0;

    virtual void OnMouseEnter() = 0;
    virtual void OnMouseLeave() = 0;
    virtual void OnMousePress() = 0;
    virtual void OnMouseRelease() = 0;
    virtual void OnMouseMove(std::pair<int, int>) = 0;
    virtual void OnKeyPress(CatKey key, bool repeat) = 0;
    virtual void OnKeyRelease(CatKey key) = 0;
    virtual void OnFocusGain() = 0;
    virtual void OnFocusLose() = 0;

    virtual void HandleCustomEvent(std::string_view event) = 0;

    virtual bool ConsumesKey(CatKey key) const = 0;

    // Widget will be visible even when gui is turned off
    virtual bool AlwaysVisible() const = 0;
    virtual void Show() = 0;
    virtual void Hide() = 0;
    virtual bool IsVisible() const = 0;

    virtual bool IsHovered() const = 0;
    virtual bool IsFocused() const = 0;
    virtual bool IsPressed() const = 0;

    virtual bool DoesStealFocus() const = 0;

    virtual void SetOffset(int x, int y) = 0;
    virtual void SetMaxSize(int x, int y) = 0;
    virtual void SetSize(int x, int y) = 0;
    virtual std::pair<int, int> GetOffset() const = 0;
    virtual std::pair<int, int> GetSize() const = 0;
    virtual std::pair<int, int> GetMaxSize() const = 0;
    virtual int GetZIndex() const = 0;
    virtual void SetZIndex(int idx) = 0;

    virtual std::string GetTooltip() const = 0;

    virtual PositionMode GetPositionMode() const = 0;
    virtual void SetPositionMode(PositionMode) = 0;

    virtual IWidget* GetParent() const = 0;
    virtual void SetParent(IWidget*) = 0;
    virtual std::string GetName() const = 0;
    virtual const Canvas* GetCanvas() const = 0;
    virtual Canvas* GetCanvas() = 0;
};
