#pragma once
#include <SDL.h>
#include <vector>
#include <array>
#include <assert.h>
#include <iostream>

#include "utils.h"


class Renderer
{
public:
	Renderer() = default;
	~Renderer();

	void init();
	void processInput();
	void clearBuffer();
	void drawBuffer();
	void debugGrid();
	void render();
	void run();


	void drawRect(int x, int y, int width, int height, uint32_t rectColor);
	void orthoProjection();

private:
	SDL_Window* m_window = NULL;
	SDL_Renderer* m_renderer = NULL;
	SDL_Texture* m_colorbufferTexture = NULL;
	SDL_DisplayMode* m_displayMode = NULL;

	bool rendererActive = false;
	bool debugGridActive = true;
	bool fullscreenMode = true;
	uint32_t* colorBuffer = new uint32_t[480000];

	std::vector<Vec3>projectPoints;
	//std::vector<uint32_t>* colorBuffer;
	//uint32_t colorBuffer[];
	//int colorBuffer[];
	/*std::array <uint32_t, 480000> colorBuffer;*/
};