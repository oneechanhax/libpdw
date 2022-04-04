/*
 * CTextInput.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>

#include "gui/canvas.hpp"
#include "gui/gui.hpp"

#include "gui/widgets/textinput.hpp"

CTextInput::CTextInput(std::string name, IWidget* parent)
    : CBaseWidget(name, parent) {
    this->Props()->SetString("value", "");
    this->Props()->SetBool("focus", false);
    this->SetMaxWidth(8);
}

bool CTextInput::ConsumesKey(CatKey key) {
    return key >= CatKey::CATKEY_NONE && key <= CatKey::CATKEY_BACKSPACE;
}

void CTextInput::SetMaxWidth(int width) {
    std::pair<float, float> length;
    g_pGUI->GetRootWindow()->GetFont().stringSize("W", &length.first, &length.second);
    SetSize(length.first * width + 4, length.second + 4); // TODO PADDING
}

std::string CTextInput::Value() {
    return std::string(Props()->GetString("value"));
}

void CTextInput::SetValue(std::string value) {
    std::string oldv = Value();
    if (m_pCallback)
        m_pCallback(this, oldv, value);
    Props()->SetString("value", value.c_str());
}

void CTextInput::Draw(int x, int y) {
    std::pair<float, float> wsize;
    g_pGUI->GetRootWindow()->GetFont().stringSize("W", &wsize.first, &wsize.second);
    auto size = GetSize();
    auto color = glez::rgba(0, 0, 0, 80);
    if (IsFocused())
        color = Transparent(g_pGUI->GetRootWindow()->GetColor(), 0.25);
    glez::draw::rect(x, y, size.first, size.second, color);
    glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
    int ml = 0;
    int md = 0;
    std::pair<float, float> dotssize; // TODO static?
    g_pGUI->GetRootWindow()->GetFont().stringSize("...", &dotssize.first, &dotssize.second);
    std::string value = Value();
    for (int i = 0; i < value.length(); i++) {
        std::pair<float, float> strsize;
        g_pGUI->GetRootWindow()->GetFont().stringSize(value.substr(i), &strsize.first, &strsize.second);
        if (strsize.first + 10 + dotssize.first >= size.first)
            md = i;
        if (strsize.first + 8 > size.first)
            ml = i;
    }
    if (ml) {
        glez::draw::string(x + 2, y + 2, "..." + value.substr(md), g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr);
    } else {
        glez::draw::string(x + 2, y + 2, value, g_pGUI->GetRootWindow()->GetFont(), glez::color::white, nullptr, nullptr); // TODO recalc on update
    }
}

void CTextInput::SetCallback(TextInputCallbackFn_t callback) {
    m_pCallback = callback;
}

void CTextInput::PutChar(char ch) {
    SetValue(Value() + std::string(1, ch));
}

void CTextInput::OnKeyPress(CatKey key, bool repeat) {
    if (key == CatKey::CATKEY_BACKSPACE) {
        std::string val = Value();
        if (val.length() > 0) {
            SetValue(val.substr(0, val.length() - 1));
        }
        return;
    } else if (key == CatKey::CATKEY_SPACE) {
        PutChar(' ');
        return;
    } else {
        char ch = 0;
        if (g_pGUI->GetRootWindow()->m_bPressedState[CatKey::CATKEY_LSHIFT] || g_pGUI->GetRootWindow()->m_bPressedState[CatKey::CATKEY_RSHIFT]) {
            ch = toupper(input::key_names[key][0]);
        } else {
            ch = input::key_names[key][0];
        }
        if (ch) {
            PutChar(ch);
        }
    }
}