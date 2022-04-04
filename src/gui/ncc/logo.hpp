/*
 * Logo.hpp
 *
 *  Created on: Apr 28, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <glez/texture.hpp>

#include "gui/widgets/basewidget.hpp"

namespace ncc {

class Logo : public CBaseWidget {
public:
    Logo();
    virtual bool AlwaysVisible() override;
    virtual void Draw(int x, int y) override;
    virtual void Update() override;
    glez::texture texture;
};

}
