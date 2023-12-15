#include <iostream>
#include <array>
#include <random>
#include "include/screen.h"

const int WIN_WIDTH = 192;
const int WIN_HEIGHT = 108;

bool isAlive(std::array<std::array<int, (size_t)WIN_HEIGHT>, (size_t)WIN_WIDTH>& game, const int x, const int y)
{
    int alive = 0;
    if (x > 0 && game[x - 1][y] == 1) alive++;
    if (x < WIN_WIDTH && game[x + 1][y] == 1) alive++;
    if (y > 0 && game[x][y - 1] == 1) alive++;
    if (y < WIN_HEIGHT && game[x][y + 1] == 1) alive++;

    if (x > 0 && y > 0 && game[x - 1][y - 1] == 1) alive++;
    if (x < WIN_WIDTH && y > 0 && game[x + 1][y - 1] == 1) alive++;
    if (x < WIN_WIDTH && y < WIN_HEIGHT && game[x + 1][y + 1] == 1) alive++;
    if (x > 0 && y < WIN_HEIGHT && game[x - 1][y + 1] == 1) alive++;

    bool is_alive = false;
    if (game[x][y] == 1 && alive < 2) is_alive = false;
    if (game[x][y] == 1 && (alive == 2 || alive == 3)) is_alive = true;
    if (alive > 3) is_alive = false;
    if (game[x][y] == 0 && (alive == 3)) is_alive = true;

    return is_alive;
}

int main(int argc, char* argv[])
{
    Screen renderer(WIN_WIDTH, WIN_HEIGHT);
    SDL_Event event;

    std::array<std::array<int, (size_t)WIN_HEIGHT>, (size_t)WIN_WIDTH> blocks = { };
    std::array<std::array<int, (size_t)WIN_HEIGHT>, (size_t)WIN_WIDTH> swap = { };

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 1);

    for (int i = 0; i < WIN_WIDTH; i++)
    {
        for (int j = 0; j < WIN_HEIGHT; j++)
        {
            blocks[i][j] = dist6(rng);
        }
    }

    bool isRunning = true;
    int frames = 0;
    int delay = 100;
    float startTime = SDL_GetTicks();
    while (isRunning)
    {
        while (SDL_PollEvent(&event))
        {
            if ((event.type == SDL_QUIT) || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            {
                isRunning = false;
            }
        }

        for (int i = 0; i < WIN_WIDTH; i++)
        {
            for (int j = 0; j < WIN_HEIGHT; j++)
            {
                swap[i][j] = (int)isAlive(blocks, i, j);
            }
        }

        for (int i = 0; i < WIN_WIDTH; i++)
        {
            for (int j = 0; j < WIN_HEIGHT; j++)
            {
                if (swap[i][j])
                {
                    renderer.drawPixel(i * 10, j * 10);
                }
            }
        }

        std::copy(swap.begin(), swap.end(), blocks.begin());
        renderer.update();

        renderer.clearPixels();

        frames++;

        SDL_Delay(delay);
    }
    float endTime = SDL_GetTicks();
    float time = (endTime - startTime) / 1000.0f;

    std::cout << "Time: " << time << std::endl;
    std::cout << "Frames : " << frames << std::endl;
    std::cout << "Average FPS: " << frames / time << std::endl;

    renderer.cleanUp();
    SDL_Quit();

    return 0;
}
