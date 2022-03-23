/*
 * Logo.cpp
 *
 *  Created on: Apr 28, 2017
 *      Author: nullifiedcat
 */

#include <glez/draw.hpp>
#include <embed_resources.hpp>

#include <var.hpp>
#include "gui/gui.hpp"
#include "logo.hpp"

namespace ncc {

static ui::Enum logo_enum({"NEVER", "MENU", "ALWAYS"});
static ui::Var<ui::Enum> logo({"Gui"}, "Logo", 1, logo_enum);

Logo::Logo() : CBaseWidget("nc_logo") {
  this->texture = glez::texture::loadFromMemory(embeded_logo_png_rgba.data.begin, embeded_logo_png_rgba.data.size, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height);
	SetSize(576, 288);
}

bool Logo::AlwaysVisible() {
	return (int)logo == 2;
}

void Logo::Draw(int x, int y) {
	if (logo)
    glez::draw::rect_textured(x, y, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height, g_pGUI->m_pRootWindow->GetColor(), this->texture, 0, 0, embeded_logo_png_rgba.width, embeded_logo_png_rgba.height, 0.0f);
}

void Logo::Update() {
	if (IsPressed()) {
		auto offset = GetOffset();
		offset.first += g_pGUI->GetRootWindow()->mouse_dx;
		offset.second += g_pGUI->GetRootWindow()->mouse_dy;
		SetOffset(offset.first, offset.second);
	}
}

}
