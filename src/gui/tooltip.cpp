/*
 * Tooltip.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: nullifiedcat
 */

#include <glez/color.hpp>
#include <glez/draw.hpp>

#include "tooltip.hpp"
#include "gui/widgets/textlabel.hpp"
#include "gui/gui.hpp"
#include "gui/canvas.hpp"
#include "gui/listmenu/item.hpp"

namespace menu { namespace ncc {

constexpr auto scale = 1;

Tooltip::Tooltip() : CTextLabel("ncc_tooltip") {
	SetZIndex(999);
	SetPadding(3, 2);
	SetMaxSize(220, -1);
	SetAutoSize(false);
	SetSize(220, -1);
	//Props()->SetInt("font", font_item);
}

void Tooltip::HandleCustomEvent(std::string_view event) {
	if (event == "scale_update") {
		SetMaxSize(Item::psize_x * (float)scale, -1);
		SetSize(Item::psize_x * (float)scale, -1);
		SetText(GetText()); // To update word wrapping.
	} /*else if (event == "font_update") {
		Props()->SetInt("font", font_item);
	}*/
}

void Tooltip::Draw(int x, int  y) {
	const auto& size = GetSize();
	int originx = x;
	int originy = y;
  auto root_size = g_pGUI->m_pRootWindow->GetSize();
	if (originx + size.first > root_size.first) originx -= size.first;
	if (originx + size.second > root_size.second) originy -= size.second;
	static auto bgcolor = glez::rgba(0, 0, 0, 77); //colors::Create(70, 86, 47, 28);
	static auto fgcolor = glez::rgba(200, 200, 190, 255);
	glez::draw::rect(x, y, size.first, size.second, bgcolor);
	glez::draw::rect_outline(x, y, size.first, size.second, g_pGUI->GetRootWindow()->GetColor(), 1);
	glez::draw::string(x + Props()->GetInt("padding_x"), y + Props()->GetInt("padding_y"), GetText(), g_pGUI->GetRootWindow()->GetFont(), fgcolor, nullptr, nullptr);
}

}}
