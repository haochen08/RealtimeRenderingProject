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

    // // Set width and height of the SDL window with the max screen resolution
    // SDL_DisplayMode display_mode;
    // SDL_GetCurrentDisplayMode(0, &display_mode);
    // win_width = display_mode.w;
    // win_height = display_mode.h;

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
    color_buffer_texture = SDL_CreateTexture(
        renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING,
        win_width, 
        win_height
    );

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

void draw_hor_line(int x1, int x2, int y, uint32_t color) {
    for (int x=x1; x<x2; x++) {
        color_buffer[win_width*y+x] = color  ;
    }
}

void draw_vert_line(int y1, int y2, int x, uint32_t color) {
    for (int y=y1; y<y2; y++) {
        color_buffer[win_width*y+x] = color;
    }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color) {
    draw_hor_line(x, x+width, y, color);
    draw_hor_line(x, x+width, y+height-1, color);
    draw_vert_line(y, y+height, x, color);
    draw_vert_line(y, y+height, x+width-1, color);
}

void draw_color(uint8_t margin, uint32_t color) {
    for (uint32_t row=0; row<win_height; row++) {
        for (uint32_t col=0; col<win_width; col++) {
            if (row % margin == 0 || col % margin == 0)
            {
                color_buffer[win_width*row+col] = color;
            }

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
    SDL_Quit();
}

void update(void) {
    // TODO:
}

void render(void) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    
    render_color_buffer();
    //draw_color(100, 0xFF123456);
    draw_rectangle(100, 100, 80, 40, 0xFFFF0000);
    draw_rectangle(300, 400, 180, 140, 0xFFFFFF00);
    draw_rectangle(400, 200, 80, 100, 0xFFFF00FF);
    //draw_vert_line(0, 300, 0, 0xFFFF0000);

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
