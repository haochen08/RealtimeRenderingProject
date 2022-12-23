#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window* window = NULL; 
SDL_Renderer* renderer = NULL;
SDL_Texture *color_buffer_texture = NULL;
uint32_t *color_buffer = NULL;
uint32_t win_width = 800;
uint32_t win_height = 600;


bool initialize_window(void) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }
    // Create a SDL Window
    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        win_width,
        win_height,
        SDL_WINDOW_BORDERLESS
    );
    if (!window) {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }
    
    // Create a SDL renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

void setup(void) {
    color_buffer = malloc(sizeof(uint32_t) * win_width * win_height);
    color_buffer_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, win_width, win_height);

}

void render_color_buffer(void) {
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer,
        (int)(win_width * sizeof(uint32_t))
    );
    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void draw_grid(void) {
    // TODO
}

void draw_color(void) {
    for (uint8_t row=0; row<win_height; row++) {
        for (uint8_t col=0; col<win_width; col++) {
            color_buffer[win_width*row+col] = 0xFF00FFFF;
        }
    }
}

void process_input(void) {
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
    }
}

void tearDown(void) {
    free(color_buffer);
    SDL_DestroyTexture(color_buffer_texture);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

void update(void) {
    // TODO:
    //draw_grid();
    draw_color();
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    render_color_buffer();
    draw_color();
    //...

    SDL_RenderPresent(renderer);
}

int main(void) {
    is_running = initialize_window();

    setup();

    while (is_running) {
        process_input();
        update();
        render();
    }

    tearDown();

    return 0;
}
