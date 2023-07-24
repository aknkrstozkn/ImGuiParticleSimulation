#include "Particle.h"
#include <stdlib.h>
#include <SDL_stdinc.h>

namespace myengine
{
	Particle::Particle(): position(Vec{ 0, 0})
	{
		init();
	}

	void Particle::init()
	{
		position.x = 0;
		position.y = 0;
		
		direction_ = (M_PI * 2.0 * rand()) / RAND_MAX;

        base_speed = 0.04 * rand() / RAND_MAX;
        base_speed *= base_speed;
	}

	
	void Particle::update(int interval)
	{
        current_speed = base_speed * speed_multiplier;

		direction_ += interval * /*0.0003*/ curve_multiplier / 1000.f;
		
		Vec speed_vector{ current_speed * cos(direction_) * interval,
                          current_speed * sin(direction_) * interval};

		position += speed_vector;

		if(position.x < -1 || position.x > 1 || position.y < -1 || position.y >1)
		{
			init();
		}

		if(rand() < (RAND_MAX / 100))
		{
			init();
		}
	}
}
