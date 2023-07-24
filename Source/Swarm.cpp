#include "Swarm.h"

namespace myengine
{
	Swarm::Swarm(): lastTime_(0)
	{
		p_particles_ = new Particle[N_PARTICLES];
	}

	void Swarm::update(int elapsed)
	{
		int interval = elapsed - lastTime_;
		
		for (int i = 0; i < Swarm::N_PARTICLES; i++)
			p_particles_[i].update(interval);

		lastTime_ = elapsed;
	}

	Swarm::~Swarm()
	{
		delete[] p_particles_;
	}

}
