#pragma once

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>

namespace myengine
{
	class Screen
	{

	public:
		constexpr static int SCREEN_WIDTH = 800;
		const static int SCREEN_HEIGHT = 600;
	
	private:
		SDL_Window * window_;
		SDL_Renderer * renderer_;
		SDL_Texture * texture_;

		Uint32 * buffer_;
		Uint32 * new_buffer_;

	public:
		Screen() : window_(nullptr), renderer_(nullptr), texture_(nullptr),
		buffer_(nullptr), new_buffer_(nullptr){};
		bool init() noexcept;
		bool process_events();
		void close();
		void set_pixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
		void update();
		void clear();
		void box_blur();

		void destroy_renderer() const;
		void destroy_texture();
	};
}

#endif // !SCREEN_H_



