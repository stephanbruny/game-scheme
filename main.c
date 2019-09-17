#include <stdio.h>
#include <stdlib.h>
#include <libguile.h>
#include <raylib.h>

#include "conf.h"
#include "picture.h"

#include "src/texture.h"
#include "src/rect.h"
#include "src/color.h"

// static SDL_Window* window = NULL;
// static SDL_Renderer* renderer = NULL;
// static SDL_Surface* screenSurface = NULL;
static int quit = 0;

void createTileMap() {
    TB_TILEMAP = (unsigned char*) calloc( CONF_TILEMAP_WIDTH * CONF_TILEMAP_HEIGHT, sizeof(unsigned char) );
}

unsigned int* decomposePicture(unsigned char* data, unsigned char width, unsigned char height) {
    int size = width * height;
    unsigned int* result = calloc( size * 4, sizeof(unsigned int) );
    int outIndex = 0;
    for(int i = 0; i < size; i++) {
        int index0 = BIT_FIELD_GET(data[i], 0, 2);
        int index1 = BIT_FIELD_GET(data[i], 2, 2);
        int index2 = BIT_FIELD_GET(data[i], 4, 2);
        int index3 = BIT_FIELD_GET(data[i], 6, 2);
        result[outIndex] = index0;
        result[outIndex + 1] = index1;
        result[outIndex + 2] = index2;
        result[outIndex + 3] = index3;
        outIndex += 4;
    }
    return result;
}

unsigned int* getPaletteColors(unsigned int* palette, unsigned int* data, unsigned char dataLength) {
    unsigned int* result = calloc(dataLength, sizeof(unsigned int));
    for (int i = 0; i < dataLength; i++) {
        int pidx = data[i];
        int color = palette[pidx];
        result[i] = color;
    }
    return result;
}

void insertTile(unsigned int x, unsigned int y, unsigned char value) {
    if (x > CONF_TILEMAP_WIDTH || y > CONF_TILEMAP_HEIGHT) {
        return;
    }
    int pos = CONF_TILEMAP_WIDTH * y + x;
    *(TB_TILEMAP + pos) = value;
}

unsigned char getTile(unsigned int x, unsigned int y) {
    if (x > CONF_TILEMAP_WIDTH || y > CONF_TILEMAP_HEIGHT) {
        return 0;
    }
    int pos = CONF_TILEMAP_WIDTH * y + x;
    return TB_TILEMAP[pos];
}


// void drawScene(void) {
//     if (NULL == renderer) {
//         printf("ERROR");
//         return;
//     }
//     SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
//     SDL_RenderClear( renderer );
//     SDL_Rect rect;
//     rect.x = 250;
//     rect.y = 150;
//     rect.w = 200;
//     rect.h = 200;

//     SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
//     SDL_RenderFillRect(renderer, &rect);
// }

int* get_scm_array(SCM s_list, int* len) {
    unsigned long list_length;
    int* result;
    SCM s_value;
    if (SCM_NFALSEP(scm_list_p(s_list))) {
	
        /* Find its length */
        list_length = scm_to_ulong(scm_length(s_list));
        
        /* Allocate a C array to hold the values */ 
        result = (int *)malloc(sizeof(int) * list_length);
        
        /* Copy the Guile list into the C array */ 
        for (int i=0; i < list_length; i++) {

            /* Get the i-th element of the list */ 
            s_value = scm_list_ref(s_list, scm_from_int(i));

            /* Convert it into a C double */
            result[i] = scm_to_int(s_value);
        }
        *len = list_length;
        return result;
    }
    return NULL;
}

// static SCM load_texture(SCM path) {
//     SDL_Texture* texture = NULL;


// }

// static SCM draw_rect(SCM s_rect) {
//     if (renderer == NULL) return scm_from_int(-1);
//     int l;
//     int* rect_data = get_scm_array(s_rect, &l);
//     if (l < 4) return scm_from_int(-1);
//     SDL_Rect rect;
//     rect.x = rect_data[0];
//     rect.y = rect_data[1];
//     rect.w = rect_data[2];
//     rect.h = rect_data[3];
//     SDL_RenderFillRect(renderer, &rect);
//     free(rect_data);
//     return scm_from_int(0);
// }
// static SCM set_color(SCM r, SCM g, SCM b) {
//     if (renderer == NULL) return scm_from_int(-1);
//     SDL_SetRenderDrawColor(
//         renderer, 
//         scm_to_int(r),
//         scm_to_int(g),
//         scm_to_int(b),
//         255
//     );
//     return scm_from_int(0);
// }

// static SCM clear_screen(SCM r, SCM g, SCM b) {
//     set_color(r, g, b);
//     SDL_RenderClear( renderer );
//     return SCM_UNSPECIFIED;
// }

static SCM draw_text(SCM text, SCM x, SCM y, SCM size, SCM color) {
    color_assert_type(color);
    Color *col = scm_foreign_object_ref(color, 0);
    DrawText(scm_to_locale_string(text), scm_to_int(x), scm_to_int(y), scm_to_int(size), *col);
    return SCM_UNSPECIFIED;
}

static SCM ray_window(SCM width, SCM height, SCM title, SCM load_callback, SCM update_callback, SCM draw_callback) {
    int win_w = scm_to_int(width);
    int win_h = scm_to_int(height);
    char* win_title = scm_to_locale_string(title);
    InitWindow(win_w, win_h, win_title);
    SetTargetFPS(60);

    scm_call_0(load_callback);

    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        scm_call_1(update_callback, scm_from_double(deltaTime));
        BeginDrawing();

            ClearBackground(RAYWHITE);
            scm_call_0(draw_callback);

        EndDrawing();
    }
    CloseWindow();
    return scm_from_int(0);
}

static void* register_functions (void* data)
{
  return NULL;
}

int main(int argc, char* argv[]) {
    scm_with_guile (&register_functions, NULL);
    scm_c_define_gsubr ("game", 6, 0, 0, &ray_window);
    scm_c_define_gsubr ("draw-text", 5, 0, 0, &draw_text);
    texture_module_init();
    color_module_init();
    rect_module_init();
    // scm_c_define_gsubr ("draw-rect", 1, 0, 0, &draw_rect);
    // scm_c_define_gsubr ("set-color", 3, 0, 0, &set_color);
    // scm_c_define_gsubr ("clear-screen", 3, 0, 0, &clear_screen);
    scm_c_primitive_load("main.scm");
    // scm_shell (argc, argv);
    return 0;
}