
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

#include <embed_resources.hpp>

#include <glez/color.hpp>
#include <glez/draw.hpp>

#include "gui/gui.hpp"
#include "gui/widgets/basewidget.hpp"
#include "input.hpp"
#include "var.hpp"

#include "background.hpp"

namespace ncc {

static ui::TreeMap tm({ "Gui", "NCC", "Particles" });
static ui::Var<ui::Enum> particles(tm, "Enabled", 1, { "NEVER", "MENU", "ALWAYS" });
static ui::Enum particle_type_enum({ "Snowflake", "Raindrop", "Flame", "Heart", "Raindrop 2", "Random" });
static ui::Var<ui::Enum> particle_type(tm, "Type", 1, particle_type_enum);
static ui::Var<int> particle_chance(tm, "Chance", 1);
static ui::Var<int> particle_pack_size(tm, "Pack Size", 10);
static ui::Var<int> particle_safe(tm, "Safe", 400);
static ui::Var<float> particle_gravity(tm, "Gravity", 700);
static ui::Var<int> particle_jittering(tm, "Jittering", 2);
static ui::Var<int> particle_wind(tm, "Wind", 4);
static ui::Var<int> particle_jittering_chance(tm, "Jittering Chance", 60);

Background::Background()
    : CBaseWidget("nc_background") {
    tx_snowflake = glez::texture::loadFromMemory(embeded_snowflake_png_rgba.data.begin, embeded_snowflake_png_rgba.data.size, embeded_snowflake_png_rgba.width, embeded_snowflake_png_rgba.height);
    tx_raindrop = glez::texture::loadFromMemory(embeded_raindrop_png_rgba.data.begin, embeded_raindrop_png_rgba.data.size, embeded_raindrop_png_rgba.width, embeded_raindrop_png_rgba.height);
    tx_flame = glez::texture::loadFromMemory(embeded_flame_png_rgba.data.begin, embeded_flame_png_rgba.data.size, embeded_flame_png_rgba.width, embeded_flame_png_rgba.height);
    tx_heart = glez::texture::loadFromMemory(embeded_heart_png_rgba.data.begin, embeded_heart_png_rgba.data.size, embeded_heart_png_rgba.width, embeded_heart_png_rgba.height);
    tx_raindrop2 = glez::texture::loadFromMemory(embeded_raindrop2_png_rgba.data.begin, embeded_raindrop2_png_rgba.data.size, embeded_raindrop2_png_rgba.width, embeded_raindrop2_png_rgba.height);
    auto bounds = input::GetBounds();
    SetSize(bounds.first, bounds.second);
}

bool Background::AlwaysVisible() {
    return (int)particles == 2;
}

void Background::Update() {
    if (!(bool)particles)
        return;
    auto newtime = std::chrono::system_clock::now();
    std::chrono::duration<float> dt = newtime - last_update;
    Particle* current = list;
    while (current) {
        Particle* next = current->next;
        current->Update(dt.count());
        if (current->dead) {
            KillParticle(current);
        }
        current = next;
    }
    if (!(rand() % (int)particle_chance)) {
        for (int i = 0; i < rand() % (int)particle_pack_size; i++)
            MakeParticle();
    }
    last_update = newtime;
}

Background::~Background() {
    Particle* current = list;
    while (current) {
        Particle* next = current->next;
        delete current;
        current = next;
    }
}

void Background::Draw(int x, int y) {
    if (!particles)
        return;
    Particle* current = list;
    while (current) {
        Particle* next = current->next;
        if (!current->show_in) {
            glez::rgba color = glez::color::white;
            if (current->y > (int)particle_safe) {
                color = glez::rgba(255, 255, 255, ((int)particle_safe + 255) - current->y);
            }
            glez::draw::rect_textured((int)current->x, (int)current->y, current->texture->width, current->texture->height, color, *current->texture, 0, 0, current->texture->width, current->texture->height, 0.0f);
        }
        current = next;
    }
}
static float RandFloatRange(float min, float max) {
    return (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1));
}
void Background::MakeParticle() {
    auto bounds = input::GetBounds();
    Particle* flake = new Particle();
    flake->x = RandFloatRange(0, bounds.first);
    flake->y = 3 - (rand() % 6);
    flake->vx = 0;
    flake->vy = 0;
    flake->dead = false;
    flake->next = nullptr;
    flake->show_in = rand() % 4;
    switch (((int)particle_type == 5) ? (rand() % 5) : (int)particle_type) {
    case 1:
        flake->texture = &tx_raindrop;
        break;
    case 2:
        flake->texture = &tx_flame;
        break;
    case 3:
        flake->texture = &tx_heart;
        break;
    case 4:
        flake->texture = &tx_raindrop2;
        break;
    default:
        flake->texture = &tx_snowflake;
    }
    if (list_tail)
        list_tail->next = flake;
    flake->prev = list_tail;
    list_tail = flake;
    if (!list) {
        list = flake;
    }
}

void Background::KillParticle(Particle* flake) {
    if (list_tail == flake) {
        list_tail = flake->prev;
    }
    if (list == flake) {
        list = flake->next;
    }
    if (flake->prev)
        flake->prev->next = flake->next;
    if (flake->next)
        flake->next->prev = flake->prev;
    delete flake;
}

void Background::Particle::Update(float dt) {
    if (show_in)
        show_in--;
    if (particle_wind) {
        vx += (float)particle_wind * dt * 10.0f;
    }
    if (!(rand() % (int)(particle_jittering_chance))) {
        x += (rand() % 2) ? (int)particle_jittering : -(int)particle_jittering;
    }
    vy += (float)particle_gravity * dt;
    x += vx * dt;
    y += vy * dt;
    auto bounds = input::GetBounds();
    if (x > bounds.first + 16)
        x = -16;
    if (y > (int)particle_safe + 255)
        dead = true;
}

} // namespace ncc
