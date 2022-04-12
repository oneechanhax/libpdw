
/*
 * Libpdraw: A Versitile GUI for use with a primitive drawing system!
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

class CBaseContainer : public CBaseWidget, public virtual IWidget {
public:
    CBaseContainer(std::string name = "unnamed", IWidget* parent = nullptr);
    virtual ~CBaseContainer();

    template <typename T, class... Args>
    T* Add(Args... args) {
        auto* ret = new T(this, args...);
        this->m_children.push_back(ret);
        return ret;
    };

    void AddChild(IWidget* child);
    int ChildCount();
    virtual IWidget* ChildByIndex(int idx);
    virtual IWidget* ChildByName(std::string name);
    virtual IWidget* ChildByPoint(int x, int y);

    virtual bool ConsumesKey(CatKey key);
    virtual void Draw(int x, int y);
    virtual void DrawBounds(int x, int y);
    virtual void Hide();
    virtual void OnFocusLose();
    virtual void OnKeyPress(CatKey key, bool repeat);
    virtual void OnKeyRelease(CatKey key);
    virtual void OnMouseLeave();
    virtual void OnMousePress();
    virtual void OnMouseRelease();
    virtual void Update();
    virtual void HandleCustomEvent(std::string_view event);

    virtual void SortByZIndex();
    void UpdateHovers();

    virtual void MoveChildren();

    IWidget* GetHoveredChild();
    IWidget* GetFocusedChild();
    IWidget* GetPressedChild();
    void HoverOn(IWidget* child);
    void FocusOn(IWidget* child);
    void PressOn(IWidget* child);

    IWidget* m_pHoveredChild;
    IWidget* m_pFocusedChild;
    IWidget* m_pPressedChild;

    std::vector<IWidget*> m_children;
};
