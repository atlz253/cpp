#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main(int argc, char *argv[])
{
	int minX = -10, maxX = 10;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
	const float Width = 1280;
	const float Height = 720;
	SDL_Window *w = SDL_CreateWindow("Graphs", 63, 126, Width, Height, 0);
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_PRESENTVSYNC);

	bool
		isRunning = true,
		aDirection = true;
	SDL_Event e;
	while (isRunning)
	{
		SDL_PollEvent(&e);
		switch (e.type)
		{
		case SDL_QUIT:
			SDL_DestroyWindow(w);
			SDL_Quit();
			return 0;
			break;
		}
		if (aDirection && maxX > 100)
			aDirection = false;
		else if (!aDirection && maxX < 10)
			aDirection = true;
		else if (aDirection)
			maxX++;
		else
			maxX--;

		float scaleX = Width / (maxX - minX);
		float scaleY = Height / (maxX - minX);

		SDL_SetRenderDrawColor(r, 176, 224, 230, 255);
		SDL_RenderClear(r);

		SDL_SetRenderDrawColor(r, 255, 250, 250, 0xff);
		/* y = 0 */
		SDL_RenderDrawLineF(
			r,
			Width / 2 - 5 * scaleX, Height / 2,
			Width / 2 + 5 * scaleX, Height / 2);

		/* x = 0 */
		SDL_RenderDrawLineF(
			r,
			Width / 2, Height / 2 - 5 * scaleY,
			Width / 2, Height / 2 + 5 * scaleY);

		/* косой крест */
		SDL_RenderDrawLineF(
			r,
			Width / 2 - 5 * scaleX, Height / 2 + 5 * scaleY,
			Width / 2 + 5 * scaleX, Height / 2 - 5 * scaleY);
		SDL_RenderDrawLineF(
			r,
			Width / 2 + 5 * scaleX, Height / 2 + 5 * scaleY,
			Width / 2 - 5 * scaleX, Height / 2 - 5 * scaleY);

		for (size_t i = 0; i < 3; i++)
		{
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2 + (5 - i) * scaleY,
				Width / 2 - (5 - i) * scaleX, Height / 2 + (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2 + (5 - i) * scaleY,
				Width / 2 - (4.375 - i) * scaleX, Height / 2 + (5 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2 + (5 - i) * scaleY,
				Width / 2 + (5 - i) * scaleX, Height / 2 + (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2 + (5 - i) * scaleY,
				Width / 2 + (4.375 - i) * scaleX, Height / 2 + (5 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2 - (5 - i) * scaleY,
				Width / 2 - (5 - i) * scaleX, Height / 2 - (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2 - (5 - i) * scaleY,
				Width / 2 - (4.375 - i) * scaleX, Height / 2 - (5 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2 - (5 - i) * scaleY,
				Width / 2 + (5 - i) * scaleX, Height / 2 - (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2 - (5 - i) * scaleY,
				Width / 2 + (4.375 - i) * scaleX, Height / 2 - (5 - i) * scaleY);
		}

		for (size_t i = 0; i < 3; i++)
		{
			SDL_RenderDrawLineF(
				r,
				Width / 2, Height / 2 + (5 - i) * scaleY,
				Width / 2 + 0.75 * scaleX, Height / 2 + (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2, Height / 2 + (5 - i) * scaleY,
				Width / 2 - 0.75 * scaleX, Height / 2 + (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2, Height / 2 - (5 - i) * scaleY,
				Width / 2 + 0.75 * scaleX, Height / 2 - (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2, Height / 2 - (5 - i) * scaleY,
				Width / 2 - 0.75 * scaleX, Height / 2 - (4 - i) * scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2,
				Width / 2 - (4 - i) * scaleX, Height / 2 + scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 - (5 - i) * scaleX, Height / 2,
				Width / 2 - (4 - i) * scaleX, Height / 2 - scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2,
				Width / 2 + (4 - i) * scaleX, Height / 2 + scaleY);
			SDL_RenderDrawLineF(
				r,
				Width / 2 + (5 - i) * scaleX, Height / 2,
				Width / 2 + (4 - i) * scaleX, Height / 2 - scaleY);
		}

		SDL_RenderPresent(r);
	}
}
