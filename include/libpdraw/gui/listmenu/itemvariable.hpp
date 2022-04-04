/*
 * ItemVariable.hpp
 *
 *  Created on: Mar 26, 2017
 *      Author: nullifiedcat
 */

#ifndef ITEMVARIABLE_HPP_
#define ITEMVARIABLE_HPP_

#include <var.hpp>

#include "item.hpp"

namespace menu {
namespace ncc {

    class ItemVariable : public Item {
    public:
        ItemVariable(ui::BaseVar& variable);

        void Change(float amount);

        virtual void Update() override;
        virtual bool ConsumesKey(CatKey key) override;
        virtual void OnMousePress() override;
        virtual void OnFocusLose() override;
        virtual void OnKeyPress(CatKey key, bool repeat) override;
        virtual void Draw(int x, int y) override;

    public:
        ui::BaseVar& catvar;
        bool capturing { false };
    };

}
}

#endif /* ITEMVARIABLE_HPP_ */
