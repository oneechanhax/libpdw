
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

#include <glez/draw.hpp>
#include <sstream>

#include "gui/gui.hpp"

#include "gui/widgets/textlabel.hpp"

static std::string WordWrap(std::string& in, int max, glez::font& font) {
    std::stringstream result, line, wordstream, next;
    std::string word;
    char ch;
    for (int i = 0; i < in.size(); i++) {
        ch = in.at(i);
        if (ch == ' ' || ch == '\n') {
            word = wordstream.str();
            // logging::Info("got word: '%s'", word.c_str());
            wordstream.str("");
            std::pair<float, float> size;
            font.stringSize(line.str() + word, &size.first, &size.second);
            if (size.first >= max) {
                // logging::Info("wrapping: '%s'", line.str().c_str());
                result << line.str() << '\n';
                line.str("");
            }
            line << word << ch;
        } else {
            wordstream << ch;
        }
    }
    word = wordstream.str();
    wordstream.str("");
    std::pair<float, float> size;
    font.stringSize(line.str() + word, &size.first, &size.second);
    if (size.first >= max) {
        result << line.str() << '\n';
        line.str(word);
    } else {
        line << word;
    }
    result << line.str();
    return result.str();
}

CTextLabel::CTextLabel(std::string name, IWidget* parent, std::string text, bool centered)
    : CBaseWidget(name, parent) {
    this->max_size.first = 50;
    this->SetPadding(3, 3);
    if (centered) {
        SetAutoSize(false);
        SetCentered(true);
    } else {
        SetAutoSize(true);
        SetCentered(false);
    }
    SetText(text);
}

void CTextLabel::SetAutoSize(bool _autosize) {
    this->autosize = _autosize;
}

void CTextLabel::SetCentered(bool _centered) {
    this->centered = _centered;
}

void CTextLabel::SetPadding(int x, int y) {
    Props()->SetInt("padding_x", x);
    Props()->SetInt("padding_y", y);
}

void CTextLabel::SetText(std::string text) {
    // unsigned long font_handle = Props()->GetInt("font", fonts::MENU);
    Props()->SetString("text", text.c_str());
    auto padding = std::make_pair(Props()->GetInt("padding_x"), Props()->GetInt("padding_y"));
    std::pair<float, float> size;
    g_pGUI->GetRootWindow()->GetFont().stringSize(text, &size.first, &size.second);
    if (this->autosize) {
        SetSize(size.first + padding.first * 2, size.second + padding.second * 2);
    } else {
        // auto ms = GetMaxSize();
        auto ms = this->max_size.first;
        SetSize(-1, size.second + padding.second * 2);
        if (ms /*.first*/ > 0) {
            std::string txt = WordWrap(text, ms /*.first*/ - 2 * padding.first, g_pGUI->GetRootWindow()->GetFont());
            std::pair<float, float> size2;
            g_pGUI->GetRootWindow()->GetFont().stringSize(txt, &size2.first, &size2.second);
            SetSize(size2.first + padding.first * 2, size2.second + padding.second * 2);
            Props()->SetString("text", txt);
        }
    }
}

std::string CTextLabel::GetText() {
    // return std::string(Props()->GetString("text", ""));
    return std::string(Props()->GetString("text"));
}

void CTextLabel::Draw(int x, int y) {
    if (this->centered) {
        auto size = GetSize();
        std::pair<float, float> ssize;
        g_pGUI->GetRootWindow()->GetFont().stringSize(GetText(), &ssize.first, &ssize.second);
        glez::draw::string(x + (size.first - ssize.first) / 2, y + (size.second - ssize.second) / 2, GetText(), g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
    } else
        glez::draw::string(x, y, GetText(), g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
}
