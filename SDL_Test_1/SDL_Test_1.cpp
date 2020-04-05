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

int test_screen();

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


		int elapsed = SDL_GetTicks();

		//screen.clear();
		

		auto red = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0005)) * 128);
		auto green = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0003)) * 128);
		auto blue = static_cast<unsigned char>((1 + std::sin(elapsed * 0.0007)) * 128);

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
		
		if (screen.process_events())
			break;
	}

	screen.close();
	
	
	
	return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
