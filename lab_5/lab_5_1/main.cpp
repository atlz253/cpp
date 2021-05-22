#include <cmath>
#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

int main()
{
	int minX, maxX;
	cout << "Введите xmin" << endl;
	cin >> minX;
	cout << "Введите xmax" << endl;
	cin >> maxX;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
	const float Width = 1280;
	const float Height = 720;
	float scaleX = Width/(maxX-minX);
	float scaleY = Height/(maxX-minX);
	SDL_Window *w = SDL_CreateWindow("Graphs", 63, 126, Width, Height, 0);
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);

	SDL_Event e;
	while (SDL_WaitEvent(&e))
	{
		switch (e.type)
		{
		case SDL_QUIT:
			SDL_DestroyWindow(w);
			SDL_Quit();
			return 0;
			break;
		}
		SDL_SetRenderDrawColor(r, 0xff, 0xff, 0xff, 0xff);
		SDL_RenderClear(r);

		SDL_SetRenderDrawColor(r, 0xee, 0xee, 0xee, 0xff);
		/* вертикальные линии */
		for (int i = 0; i < 64; i++)
			SDL_RenderDrawLine(
				r,
				(Width / 64 * i), 0,
				(Width / 64 * i), Height);

		/* горизонтальные линии */
		for (int i = 0; i < 36; i++)
			SDL_RenderDrawLineF(
				r,
				0, (Height / 36 * i),
				Width, (Height / 36 * i));

		SDL_SetRenderDrawColor(r, 0xee, 0x00, 0x00, 0xff);
		/* ось X */
		SDL_RenderDrawLineF(
			r,
			0, Height / 2,
			Width, Height / 2);

		/* ось Y */
		SDL_RenderDrawLineF(
			r,
			Width / 2, 0,
			Width / 2, Height);

		SDL_SetRenderDrawColor(r, 0x00, 0x00, 0x00, 0xff);
		int oldX = 0,
			oldY = 0;
		for (float x = minX; x < maxX; x += 0.01)
		{
			float y = (5) / (x * x);
			float newX = Width/2 + x * scaleX,
				  newY = Height/2 - y * scaleY;

			SDL_RenderDrawLineF(r, oldX, oldY, newX, newY);
			oldX = newX;
			oldY = newY;
		}

		SDL_RenderPresent(r);
	}
}
