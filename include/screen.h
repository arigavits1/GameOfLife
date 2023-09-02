#include <SDL2/SDL.h>
#include <vector>

class Screen
{
public:
    Screen(int p_width, int p_height) : width(p_width), height(p_height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cerr << "Failed to initialize SDL. SDL Error: " << SDL_GetError() << std::endl;
            exit(1);
        }

        window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
        if (!window)
        {
            std::cerr << "Failed to create window\n" << std::endl;
            exit(1);
        }
        SDL_SetWindowSize(window, width * 10, height * 10);
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
        SDL_ShowCursor(false);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }

    int getRefreshRate()
    {
        int displayIndex = SDL_GetWindowDisplayIndex(window);
        SDL_DisplayMode mode;

        SDL_GetDisplayMode(displayIndex, 0, &mode);
        return mode.refresh_rate;
    }

    void drawPixel(int x, int y, Uint8 r = 255, Uint8 g = 255, Uint8 b = 255, Uint8 a = 255)
    {
        points.emplace_back(x, y);
        colors.emplace_back(r, g, b, a);
    }

    void clearPixels()
    {
        points.clear();
    }

    void update()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < points.size(); i++)
        {
            SDL_Rect rect;
            rect.x = points[i].x;
            rect.y = points[i].y;
            rect.w = 10;
            rect.h = 10;
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    void cleanUp()
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::vector<SDL_Point> points;
    std::vector<SDL_Color> colors;
};