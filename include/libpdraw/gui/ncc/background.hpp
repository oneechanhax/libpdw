
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

#pragma once

#include <chrono>
#include <glez/texture.hpp>
#include <gui/widgets/basewidget.hpp>

namespace ncc {

class Background : public CBaseWidget {
public:
    struct Particle {
        float x, y;
        float vx, vy;
        int show_in { 0 };
        bool dead { false };
        glez::texture* texture { nullptr };
        Particle* next { nullptr };
        Particle* prev { nullptr };
        void Update(float dt);
    };

public:
    Background();
    ~Background();
    virtual bool AlwaysVisible() override;
    virtual void Draw(int x, int y) override;
    virtual void Update() override;
    void MakeParticle();
    void KillParticle(Particle* flake);

public:
    glez::texture tx_snowflake;
    glez::texture tx_raindrop;
    glez::texture tx_raindrop2;
    glez::texture tx_flame;
    glez::texture tx_heart;
    std::chrono::time_point<std::chrono::system_clock> last_update;
    Particle* list { nullptr };
    Particle* list_tail { nullptr };
};

} // namespace ncc
