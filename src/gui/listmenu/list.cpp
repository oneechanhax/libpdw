
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

#include <glez/draw.hpp>
#include <sstream>
#include <stdexcept>

#include "gui/canvas.hpp"
#include "gui/listmenu/item.hpp"
#include "gui/listmenu/itemsublist.hpp"
#include "gui/listmenu/itemtitle.hpp"
#include "gui/listmenu/itemvariable.hpp"
#include "gui/listmenu/list.hpp"

namespace menu {
namespace ncc {

List::List(std::string title)
    : open_sublist(nullptr)
    , title(title)
    , got_mouse(false)
    , CBaseContainer("ncc_list") {
    AddChild(new ItemTitle(title));
    Hide();
    root_list = this;
}

List::List()
    : open_sublist(nullptr)
    , title("")
    , got_mouse(false)
    , CBaseContainer("ncc_list") {
    Hide();
    root_list = this;
}

void List::Show() {
    CBaseContainer::Show();
    got_mouse = false;
}

void List::Fill(ui::BaseVar* var) {
    this->Fill(var, 1);
}
void List::Fill(ui::BaseVar* var, int depth) {

    if (depth > var->gui_map.size()) {
        this->AddChild(new ItemVariable(*var));
        return;
    }
    auto namedepth = depth - 1;
    auto next_depth = depth + 1;
    auto find = std::find_if(this->m_children.begin(), this->m_children.end(), [&](auto i) { return i->GetName() == "ncc_item_sublist" && dynamic_cast<ItemSublist*>(i)->title == var->gui_map[namedepth]; });
    if (find != this->m_children.end()) {
        dynamic_cast<ItemSublist*>(*find)->list->Fill(var, next_depth);
    } else {
        auto* new_list = new List(std::string(var->gui_map[namedepth]));
        new_list->Fill(var, next_depth);
        this->AddChild(new ItemSublist(std::string(var->gui_map[namedepth]), new_list));
    }
}
void List::Fill(const std::vector<ui::BaseVar*>& vec) {
    for (auto var : vec) {
        this->Fill(var, 1);
    }
}

void List::OnKeyPress(CatKey key, bool repeat) {
    if (GetHoveredChild())
        GetHoveredChild()->OnKeyPress(key, repeat);
}

void List::OpenSublist(List* sublist, int dy) {
    if (open_sublist)
        open_sublist->Hide();
    open_sublist = sublist;
    if (sublist) {
        sublist->SetOffset(Item::size_x + 1, dy);
        sublist->Show();
    }
}

List* List::FindSublist(std::string_view name) {
    auto find = std::find_if(this->m_children.begin(), this->m_children.end(), [&](auto i) { return i->GetName() == "ncc_item_sublist" && dynamic_cast<ItemSublist*>(i)->title == name; });
    return find != this->m_children.end() ? dynamic_cast<ItemSublist*>(*find)->list : nullptr;
}
List* List::CreateSublist(std::string_view name) {
    assert(this->FindSublist(name) == nullptr);
    auto* list = new List(std::string(name));
    this->AddChild(new ItemSublist(std::string(name), list));
    return list;
}
List* List::ForceGetSublist(std::string_view name) {
    if (auto find = this->FindSublist(name))
        return find;
    return this->CreateSublist(name);
}

bool List::ShouldClose() {
    if (open_sublist) {
        if (!open_sublist->ShouldClose())
            return false;
    }
    return !IsHovered() && !got_mouse;
}
/*
/// *IWidget* List::ChildByPoint(int x, int y) {
        IWidget* rr = CBaseContainer::ChildByPoint(x, y);
        if (rr) return rr;
        List* list = dynamic_cast<List*>(open_sublist);
        if (list) {
                auto co = list->GetOffset();
                auto cs = list->GetSize();
                if (x >= co.first && x <= co.first + cs.first &&
                        y >= co.second && y <= co.second + cs.second) {
                        return list;
                }
        }
        return nullptr;
} */
// */

ui::BaseVar* FindCatVar(const std::string name) {
    for (auto var : ui::BaseVar::GetList()) {
        if (var->command_name == name)
            return var;
    }
    printf("can't find %s\n", name.c_str());
    throw std::runtime_error("can't find catvar " + name);
}

std::vector<std::string> ParseTokens(const std::string& string) {
    bool readingkey = false;
    std::string last_read_key = "";
    std::stringstream readkey("");
    std::vector<std::string> tokens = {};
    int brackets = 0;
    for (const auto& c : string) {
        if (c == '[') {
            brackets++;
            if (brackets == 1) {
                tokens.push_back("[");
                readkey.str("");
                readkey.clear();
                continue;
            }
        } else if (c == ']') {
            brackets--;
            if (!brackets) {
                tokens.push_back(readkey.str());
                tokens.push_back("]");
                readkey.str("");
                readkey.clear();
                continue;
            }
        }
        if (!brackets) {
            if (c == '"') {
                readingkey = !readingkey;
                if (!readingkey) {
                    tokens.push_back(readkey.str());
                    readkey.str("");
                    readkey.clear();
                }
            } else {
                if (readingkey)
                    readkey << c;
            }
        } else {
            readkey << c;
        }
    }
    return tokens;
}

// This is how it generates menues and submenues of menues
// abc def, ghj, [, fdg sgf saqw rter, ], gs
void FillFromTokens(List* list, const std::vector<std::string>& tokens) {
    list->title = tokens[0];
    list->AddChild(new ItemTitle(tokens[0]));
    for (int i = 1; i < tokens.size(); i++) {
        const std::string& str = tokens.at(i);
        if (i == tokens.size() - 1 || tokens[i + 1] != "[") {
            list->AddChild(new ItemVariable(*FindCatVar(str)));
        } else {
            list->AddChild(new ItemSublist(str, List::FromString(tokens[i + 2])));
            i += 3;
        }
    }
}

// Cool string parser
List* List::FromString(const std::string& string) {
    List* result = new List();
    FillFromTokens(result, ParseTokens(string));
    printf("done making list %s - has %i children.\n", result->title.c_str(), result->ChildCount());
    return result;
}

/*
void List::FillWithCatVars(std::vector<std::string> vec) {
        for (const auto& string : vec) {
                AddChild(new ItemVariable(*FindCatVar(string)));
        }
}*/

void List::OnMouseLeave() {
    CBaseContainer::OnMouseLeave();
    if (ShouldClose()) {
        List* parent_list = dynamic_cast<List*>(GetParent());
        if (parent_list) {
            parent_list->OpenSublist(nullptr, 0);
        }
    }
}

void List::Draw(int x, int y) {
    // const auto& size = GetSize();
    glez::draw::rect_outline(x, y, 2 + Item::size_x, this->items * Item::size_y + 2, this->GetCanvas()->GetColor(), 1);
    for (int i = 1; i < this->items; i++) {
        glez::draw::line(x + 1, y + Item::size_y * i, Item::size_x, 0, this->GetCanvas()->GetColor(), 1);
    }
    // CBaseContainer::Draw(x, y);
    for (int i = 0; i < ChildCount(); i++) {
        Item* item = dynamic_cast<Item*>(ChildByIndex(i));
        if (!item) {
            if (ChildByIndex(i)->GetName().find("ncc_list") == 0)
                continue;
            throw std::runtime_error("Invalid cast in NCC-List:Draw!");
        }
        const auto& offset = item->GetOffset();
        item->Draw(x + offset.first, y + offset.second);
    }
    if (dynamic_cast<List*>(open_sublist)) {
        const auto& offset = open_sublist->GetOffset();
        open_sublist->Draw(x + offset.first, y + offset.second);
    }
}

void List::OnMouseEnter() {
    CBaseContainer::OnMouseEnter();
    got_mouse = true;
}

void List::SetParent(IWidget* parent) {
    CBaseContainer::SetParent(parent);
    List* parent_list = dynamic_cast<List*>(parent);
    if (parent_list) {
        root_list = parent_list->root_list;
    } else
        root_list = this;
}

void List::OnMouseMove(std::pair<int, int> delta) {
    if (IsPressed() && root_list == this) {
        const auto& offset = root_list->GetOffset();
        root_list->SetOffset(offset.first + delta.first, offset.second + delta.second);
    }
}

void List::Update() {
    CBaseContainer::Update();
}

void List::MoveChildren() {
    int accy = 2;
    int j = 0;
    for (int i = 0; i < ChildCount(); i++) {
        Item* item = dynamic_cast<Item*>(ChildByIndex(i));
        if (!item) {
            if (ChildByIndex(i)->GetName().find("ncc_list") == 0)
                continue;
            throw std::runtime_error("Invalid cast in NCC-List:MoveChildren! Offender " + ChildByIndex(i)->GetName());
        }
        item->SetOffset(1, j * Item::size_y + 1);
        accy += Item::size_y;
        j++;
    }
    this->items = j;
    List* list = dynamic_cast<List*>(open_sublist);
    if (list) {
        const auto& size = list->GetSize();
        const auto& offset = list->GetOffset();
        SetSize(Item::size_x + 2 + size.first, std::max(accy, offset.second + size.second));
    } else {
        SetSize(Item::size_x + 2, accy);
    }
}

}
} // namespace menu::ncc
