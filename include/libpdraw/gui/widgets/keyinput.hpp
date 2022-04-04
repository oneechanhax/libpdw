/*
 * CKey.h
 *
 *  Created on: Feb 1, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "basewidget.hpp"

class CKeyInput;

typedef std::function<void(CKeyInput*, CatKey)> KeyInputCallbackFn_t;

class CKeyInput : public CBaseWidget {
public:
    CKeyInput(std::string name = "unnamed", IWidget* parent = nullptr);

    CatKey Value();
    void SetValue(int value);
    void SetCallback(KeyInputCallbackFn_t callback);

    KeyInputCallbackFn_t m_pCallback;

    virtual void OnKeyPress(CatKey key, bool repeat) override;
    virtual void Draw(int x, int y) override;
    virtual void OnMousePress() override;
    virtual void OnFocusLose() override;
    virtual bool ConsumesKey(CatKey key) override;
};
