#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vec.h"

namespace myengine
{

struct Particle
{
public:
    static inline float speed_multiplier = .5f;
    static inline float curve_multiplier = 3.f;
    static inline float color_transition_speed = 0.5f;

	Vec position;

private:
    double current_speed;
	double base_speed;

	double direction_;

public:
	Particle();
	void update(int interval);

private:
	void init();
};

#endif
}

