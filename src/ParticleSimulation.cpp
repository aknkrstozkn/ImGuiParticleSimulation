// SDL_Test_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>
#include <time.h>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"
#include "Particle.h"
#include "Vec.h"

int main(int argc, char* args[])
{
	std::ostream::sync_with_stdio(false);
	srand(time(0));

	myengine::Screen screen;
	if(!screen.init())
	{
		std::cout << "Cant init SDL" << std::endl;
		return  1;
	}

	myengine::Swarm swarm;

	while (true)
	{
        if (screen.process_events())
        {
            break;
        }

		int elapsed = SDL_GetTicks();
		//screen.clear();

		auto red = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0005 * myengine::Particle::color_transition_speed * 2.f)) * 128);
		auto green = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0003 * myengine::Particle::color_transition_speed * 2.f)) * 128);
		auto blue = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0007 * myengine::Particle::color_transition_speed * 2.f)) * 128);

		const myengine::Particle * const p_particles = swarm.get_particles();
		for(int i = 0; i < myengine::Swarm::N_PARTICLES; i++)
		{
			myengine::Particle particle = p_particles[i];

			int x = (particle.position.x + 1.0) * (screen.SCREEN_WIDTH / 2);
			int y = (particle.position.y * (screen.SCREEN_WIDTH / 2)) + screen.SCREEN_HEIGHT / 2;
			
			screen.set_pixel(x, y, red, green, blue);
		}

		screen.box_blur();
		swarm.update(elapsed);
		screen.update();
	}

	screen.close();
	return 0;
}
