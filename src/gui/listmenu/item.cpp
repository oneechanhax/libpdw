/*
 * Item.cpp
 *
 *  Created on: Mar 26, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>
#include <glez/color.hpp>
#include "gui/listmenu/item.hpp"
#include "gui/canvas.hpp"
#include "gui/gui.hpp"

namespace menu { namespace ncc {

constexpr auto scale =  1;
int Item::size_x = psize_x * (float)scale;
int Item::size_y = psize_y * (float)scale;

Item::Item(std::string name) : CBaseWidget(name, nullptr) {
	SetSize(psize_x, psize_y);
	SetMaxSize(psize_x, psize_y);
}

void Item::Draw(int x, int y) {
	const auto& size = GetSize();
	//draw::DrawRect(x, y, size.first, size.second, colors::red);
	glez::draw::rect(x, y, size.first, size.second, glez::rgba(0, 0, 0, 55));
	if (IsHovered()) {
		glez::draw::rect(x, y, size.first, size.second, Transparent(g_pGUI->GetRootWindow()->GetColor(), 0.32f));
	}
}

void Item::HandleCustomEvent(std::string_view event) {
	if (event == "scale_update") {
		size_x = psize_x * (float)scale;
		size_y = psize_y * (float)scale;
		SetSize(size_x, size_y);
		SetMaxSize(size_x, size_y);
	}
}

}}
