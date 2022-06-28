#include "Renderer.h"

//uint32_t* colorBuffer = new uint32_t[480000];

Renderer::~Renderer()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}


void Renderer::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	/*if(fullscreenMode)
	{
		SDL_GetCurrentDisplayMode(0, m_displayMode);
	}*/

	m_window = SDL_CreateWindow("3DRenderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
	assert(m_window != NULL);

	m_renderer = SDL_CreateRenderer(m_window, -1, 0);
	assert(m_renderer != NULL);

	m_colorbufferTexture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 800, 600);
	assert(m_colorbufferTexture != NULL);

	if (fullscreenMode) { SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN); }


	for (float i = -1; i <= 1; i+=0.25)
	{
		for (float j = -1; j <= 1; j+=0.25)
		{
			for (float k = -1; k<=1; k+=0.25)
			{
				projectPoints.push_back(Vec3(i, j, k));
			}
		}
	}

	std::cout << projectPoints.size() << std::endl;

	//int* colorBuffer = new int[480000];

	//std::vector<uint32_t>* colorBuffer = new std::vector<uint32_t>(480000);
	//colorBuffer.reserve(800 * 600);

	/*for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			std::cout << colorBuffer[j * 800 + i] << std::endl;
		}*/

	//}

	rendererActive = true;

	run();

}

void Renderer::run()
{
	while(rendererActive)
	{		
		// Process input
		processInput();


		// Update in-game elements
		// Render to screen	

		render();
	
	}
}

void Renderer::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			rendererActive = false;
		}
	case SDL_QUIT:
		rendererActive = false;
		break;
	}

}

void Renderer::render()
{
	/*SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	SDL_RenderClear(m_renderer);*/
	//std::cout << "Happening" << std::endl;
	//drawBuffer();
	debugGrid();
	//drawRect(20, 20, 300, 300, 0xFFFF0000);
	for (size_t i = 0; i < projectPoints.size(); i++)
	{
		//projectPoints[i].z -= 0.5f;
		//std::cout << ((projectPoints[i].x * 128) / (projectPoints[i].z)) + 400 << " " << ((projectPoints[i].y * 128) / (projectPoints[i].z)) + 300 << std::endl;
		//if (((projectPoints[i].x * 128) / (projectPoints[i].z)) + 400 > 800 || ((projectPoints[i].y * 128) / (projectPoints[i].z)) + 300 > 600) { continue; }
		//std::cout << ((projectPoints[i].x * 128) / (projectPoints[i].z)) + 400 << " " << ((projectPoints[i].y * 128) / (projectPoints[i].z)) + 300 << std::endl;
		
		float projectedpointX = (projectPoints[i].x * 128) / (projectPoints[i].z - 2.5f);
		float projectedpointY = (projectPoints[i].y * 128) / (projectPoints[i].z - 2.5f);

		drawRect(projectedpointX + 400, projectedpointY + 300, 4, 4, 0xFF0000FF);
	}
	drawBuffer();
	//debugGrid(); 
	clearBuffer();
	//clearBuffer();


	SDL_RenderPresent(m_renderer); // presenting backbuffer
}

void Renderer::clearBuffer()
{
	for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			//if ((j * 800 + i + 1) % 10 == 0) { colorBuffer[j * 800 + i] = 0x00000000; continue; }
			colorBuffer[j * 800 + i] = 0xFFFFFF00;
		}
	}
	//std::cout << colorBuffer[479999] << std::endl;

}

void Renderer::drawBuffer()
{
	//std::cout << " happening2 " << (int)sizeof(int) * 800 << std::endl;
	SDL_UpdateTexture(m_colorbufferTexture, NULL, colorBuffer, 800 * sizeof(uint32_t));
	SDL_RenderCopy(m_renderer, m_colorbufferTexture, NULL, NULL);
}	

void Renderer::debugGrid()
{


	for (size_t j = 0; j < 600; j++)
	{
		for (size_t i = 0; i < 800; i++)
		{
			if ((j * 800 + i + 1) % 10 == 0) { colorBuffer[j * 800 + i] = 0x00000000; }
		}
	}
	
	for (size_t i = 0; i < 600; i+=10)
	{
		for (size_t j = 0; j < 800; j++)
		{
			colorBuffer[i * 800 + j] = 0x00000000;
		}
	
	}


}

void Renderer::drawRect(int x, int y, int width, int height, uint32_t rectColor)
{
	if (!(x < 800 && x > 0 && y < 600 && y > 0)) { std::cout << "Reposition rectangle coordinates, out of bounds" << std::endl; return; }
	//std::cout << "lol" << std::endl;
	std::cout << x << " " << y << std::endl;
	for (size_t i = x; i < x + width; i++)
	{
		for (size_t j = y; j < y + height; j++)
		{
			//std::cout << i << " " << j << std::endl;
			colorBuffer[i + j * 800] = rectColor;			
		}
	}


}
