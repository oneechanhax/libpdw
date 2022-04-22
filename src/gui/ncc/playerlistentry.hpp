
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

//#include <gui/widgets/basecontainer.hpp>
//#include "menu.hpp"

/*namespace menu { namespace ncc {

class PlayerListEntry : public CBaseContainer {
public:
        PlayerListEntry(int eid);
        inline virtual void SortByZIndex() override {};
        virtual void Draw(int x, int y) override;
        virtual void MoveChildren() override;
        virtual void Update() override;
        virtual void OnKeyPress(CatKey key, bool repeat) override;
public:
        const int idx;
};

namespace entrysubs {

class SubBase : public CBaseWidget {
public:
        SubBase(PlayerListEntry&);
        virtual void Draw(int x, int y) override;
public:
        PlayerListEntry& parent;
        int color_fg { 0 };
        int color_bg { 0 };
        std::string text { "" };
};
class SubTitle : public SubBase {
public:
        SubTitle(PlayerListEntry& parent, const std::string& title);
        virtual void Draw(int x, int y) override;
};
class SubState : public SubBase {
public:
        inline SubState(PlayerListEntry& parent) : SubBase(parent) {};
        virtual void Update() override;
        virtual bool ConsumesKey(CatKey key) override;
        virtual void OnKeyPress(CatKey key, bool repeat) override;
};
class SubColorComponent : public SubBase {
public:
        enum class Component {
                R,
                G,
                B
        };
        SubColorComponent(PlayerListEntry&, Component);
        virtual void Update() override;
        virtual bool ConsumesKey(CatKey key) override;
        virtual void OnKeyPress(CatKey key, bool repeat) override;
public:
        const Component component;
};

}

}}*/
