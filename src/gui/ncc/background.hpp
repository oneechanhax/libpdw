/*
 * Background.hpp
 *
 *  Created on: Apr 28, 2017
 *      Author: nullifiedcat
 */

#pragma once

#include <chrono>
#include <glez/texture.hpp>

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

}
