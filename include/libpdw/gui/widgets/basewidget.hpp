
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

//#include <memory>
#include <algorithm>
#include <cstring>
#include <optional>
#include <vector>

#include "iwidget.hpp"
#include "keyvalues.hpp"

class CBaseWidget : public virtual IWidget {
public:
    inline ~CBaseWidget() { }
    CBaseWidget(std::string name = "unnamed", IWidget* parent = nullptr);

    virtual void Update();
    virtual void Draw(ICanvas*) { }
    virtual void DrawBounds(int x, int y);

    inline virtual KeyValues* Props() const {
        return m_KeyValues;
    }

    inline virtual void OnMouseEnter() { this->hover = true; }
    inline virtual void OnMouseLeave() { this->hover = false; }
    inline virtual void OnMousePress() { this->press = true; }
    inline virtual void OnMouseRelease() { this->press = false; }
    inline virtual void OnMouseMove(std::pair<int, int>) { }
    inline virtual void OnKeyPress(CatKey key, bool repeat) {};
    inline virtual void OnKeyRelease(CatKey key) {};
    inline virtual void OnFocusGain() { this->focus = true; }
    inline virtual void OnFocusLose() { this->focus = false; }

    inline virtual void HandleCustomEvent(std::string_view event) {};

    inline virtual bool ConsumesKey(CatKey key) const { return false; }

    inline virtual bool AlwaysVisible() const { return this->always_visible; }

    inline virtual void Show() { this->visible = true; }
    inline virtual void Hide() { this->visible = false; }
    virtual bool IsVisible() const;

    virtual bool IsHovered() const;
    virtual bool IsFocused() const;
    virtual bool IsPressed() const;

    inline virtual bool DoesStealFocus() const { return true; }

    inline virtual void SetOffset(int x, int y) {
        if (x >= 0)
            this->offset.first = x;
        if (y >= 0)
            this->offset.second = y;
    }
    inline virtual void SetMaxSize(int x, int y) {
        if (x >= 0)
            this->max_size.first = x;
        if (y >= 0)
            this->max_size.second = y;
    }
    inline virtual std::pair<int, int> GetOffset() const {
        return this->offset;
    }
    inline virtual std::pair<int, int> GetSize() const {
        return this->size;
    }
    inline virtual std::pair<int, int> GetMaxSize() const {
        return this->max_size;
    }
    inline virtual int GetZIndex() const { return this->zindex; }
    inline virtual void SetZIndex(int idx) { this->zindex = idx; }

    inline virtual std::string GetTooltip() const { return this->tooltip; }

    inline virtual PositionMode GetPositionMode() const { return this->positionmode; }
    inline virtual void SetPositionMode(PositionMode mode) { this->positionmode = mode; };

    inline virtual IWidget* GetParent() const { return m_pParent; }
    inline virtual void SetParent(IWidget* parent) { m_pParent = parent; }
    inline virtual std::string GetName() const { return this->name; }
    virtual const Canvas* GetCanvas() const;
    virtual Canvas* GetCanvas();
    std::pair<int, int> AbsolutePosition() const;
    inline void SetSize(int x, int y) {
        if (x >= 0)
            this->size.first = x;
        if (y >= 0)
            this->size.second = y;
    }

    KeyValues* m_KeyValues;
    IWidget* m_pParent;
    std::pair<int, int> offset;
    std::pair<int, int> size;
    std::pair<int, int> max_size;
    std::string name;
    std::string tooltip;
    std::optional<glez::rgba> bounds_color;
    int zindex;
    PositionMode positionmode;
    bool visible;
    bool always_visible;

    bool hover;
    bool press;
    bool focus;
};
