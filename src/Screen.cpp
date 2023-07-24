#include "Screen.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdlrenderer2.h"
#include "imgui/imgui_impl_sdl2.h"
#include "Particle.h"
#include <iostream>
#include <algorithm>
#include <time.h>

namespace myengine
{

	bool Screen::init() noexcept
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) < 0)
		{
			return false;
		}

		window_ = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window_ == nullptr)
		{
			return false;
		}

		renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_PRESENTVSYNC);
		if (renderer_ == nullptr)
		{
			SDL_DestroyWindow(window_);
			return false;
		}

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForSDLRenderer(window_, renderer_);
        ImGui_ImplSDLRenderer2_Init(renderer_);

		texture_ = SDL_CreateTexture(renderer_,
			SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, Screen::SCREEN_WIDTH, Screen::SCREEN_HEIGHT);
		if (texture_ == nullptr)
		{
			destroy_renderer();
			return false;
		}

		buffer_ = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
		new_buffer_ = new Uint32[Screen::SCREEN_WIDTH * Screen::SCREEN_HEIGHT];
		
		clear();
		
		return true;
	}

	bool Screen::process_events()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
            ImGui_ImplSDL2_ProcessEvent(&event);

			if (event.type == SDL_QUIT)
				return true;
		}

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        // ImGui::ShowDemoWindow();
        if (ImGui::Begin("Particle System Parameters")) {
            ImGui::SliderFloat("Particle speed multiplier", &Particle::speed_multiplier, 0.f, 1.f);
        }
        ImGui::End();

		return false;
	}

	void Screen::update()
	{
		SDL_UpdateTexture(texture_, nullptr, buffer_, Screen::SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(renderer_);
		SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);

        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());

		SDL_RenderPresent(renderer_);
	}

	void Screen::clear()
	{
		memset(buffer_, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(new_buffer_, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	}

	void Screen::box_blur()
	{
		//Swao the buffers,
		//so pixel is in new buffer and we are drawing to old buffer
		Uint32 * temp_buffer = buffer_;		
		buffer_ = new_buffer_;
		new_buffer_ = temp_buffer;

		for(int y = 0; y < SCREEN_HEIGHT; y++)
		{
			for(int x = 0; x < SCREEN_WIDTH; x++)
			{

				int red_total = 0;
				int green_total = 0;
				int blue_total = 0;

				for(int row = -1; row <=  1; row++)
				{
					for(int col = -1; col <= 1; col++)
					{
						int current_x = x + col;
						int current_y = y + row;

						if(current_x >= 0 && current_x < SCREEN_WIDTH &&
							current_y >= 0 && current_y < SCREEN_HEIGHT)
						{
							auto color = new_buffer_[current_y * SCREEN_WIDTH + current_x];

							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							red_total += red;
							green_total += green;
							blue_total += blue;
						}
					}
				}

				Uint8 red = red_total / 9;
				Uint8 green = green_total / 9;
				Uint8 blue = blue_total / 9;

				set_pixel(x, y, red, green, blue);
			}
		}
	}

	
	void Screen::set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
	{
		if(x <= 0 || y <= 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
			return;
		
		buffer_[(y * SCREEN_WIDTH) + x] = static_cast<Uint32>(red << 24 | green << 16 | blue << 8 | 0xff);
	}
	
	void Screen::destroy_renderer() const
	{
		SDL_DestroyRenderer(renderer_);
		SDL_DestroyWindow(window_);
	}

	void Screen::close()
	{
		delete [] buffer_;
		delete [] new_buffer_;

        ImGui_ImplSDLRenderer2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

		destroy_texture();
		SDL_Quit();
	}


	void Screen::destroy_texture()
	{

		SDL_DestroyTexture(texture_);
		destroy_renderer();
	}
}
