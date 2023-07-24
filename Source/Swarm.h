#pragma once

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace myengine
{

class Swarm
{
public:
	const static int N_PARTICLES = 5000;
	
private: 
	Particle * p_particles_;
	int lastTime_;

public:
	Swarm();
	virtual ~Swarm();

	void update(int elapsed);
	const Particle * const get_particles() { return p_particles_; };
};
}
#endif
