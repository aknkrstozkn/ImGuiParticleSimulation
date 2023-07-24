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
	}

	
	void Particle::update(int interval)
	{
        speed_ = speed_multiplier * rand() / RAND_MAX;
        speed_ *= speed_;

		direction_ += interval * 0.0003;
		
		Vec speed_vector{ speed_ * cos(direction_) * interval,
			speed_ * sin(direction_) * interval};

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
