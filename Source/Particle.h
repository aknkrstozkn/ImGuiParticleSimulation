#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vec.h"

namespace myengine
{

struct Particle
{
public:
	Vec position;

private:	
	double speed_;
	double direction_;

public:
	Particle();
	void update(int interval);

private:
	void init();
};

#endif
}

