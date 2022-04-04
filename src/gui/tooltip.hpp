/*
 * Tooltip.hpp
 *
 *  Created on: Mar 27, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include "gui/widgets/textlabel.hpp"

namespace menu {
namespace ncc {

    class Tooltip : public CTextLabel {
    public:
        Tooltip();

        virtual void Draw(int x, int y) override;
        virtual void HandleCustomEvent(std::string_view event) override;
        inline virtual PositionMode GetPositionMode() override { return PositionMode::FLOATING; }
    };

}
}
