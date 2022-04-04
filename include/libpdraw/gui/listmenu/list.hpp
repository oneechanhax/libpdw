/*
 * List.hpp
 *
 *  Created on: Mar 26, 2017
 *      Author: nullifiedcat
 */

#ifndef LIST_HPP_
#define LIST_HPP_

#include <var.hpp>

#include "gui/widgets/basecontainer.hpp"

class Item;

namespace menu {
namespace ncc {

    class List : public CBaseContainer {
    public:
        List(std::string title);
        List();

        void Fill(ui::BaseVar*);
        void Fill(const std::string vec);
        void Fill(const std::vector<ui::BaseVar*>& vec);

        List* ForceGetSublist(std::string_view);
        List* FindSublist(std::string_view);
        List* CreateSublist(std::string_view);

        void OpenSublist(List* sublist, int dy);
        bool ShouldClose();

        static List* FromString(const std::string& string);

        // virtual IWidget* ChildByPoint(int x, int y) override;
        inline virtual void SortByZIndex() override {};
        virtual void Show() override;
        virtual void OnKeyPress(CatKey key, bool repeat) override;
        virtual void OnMouseEnter() override;
        virtual void OnMouseLeave() override;
        virtual void Draw(int x, int y) override;
        virtual void Update() override;
        virtual void MoveChildren() override;
        virtual void SetParent(IWidget* parent) override;

    public:
        void Fill(ui::BaseVar*, int depth);
        List* root_list { nullptr };
        bool got_mouse { false };
        List* open_sublist { nullptr };
        std::string title;
    };

}
}

#endif /* LIST_HPP_ */
