#ifndef _TILEMAP_H_
#define _TILEMAP_H_
#include <raylib.h>
#include <libguile.h>

static unsigned char *background, *map, *ui;
static unsigned int tilemap_width, tilemap_height;

void init_tilemaps(const unsigned int width, const unsigned int height) {
    tilemap_width = width;
    tilemap_height = height;
    background = (unsigned char*) calloc( width * height, sizeof(unsigned char) );
    map = (unsigned char*) calloc( width * height, sizeof(unsigned char) );
    ui = (unsigned char*) calloc( width * height, sizeof(unsigned char) );
}

void insertTile(unsigned char* tilemap, unsigned int x, unsigned int y, unsigned char value) {
    if (x > tilemap_width || y > tilemap_height) {
        return;
    }
    int pos = tilemap_width * y + x;
    *(tilemap + pos) = value;
}

unsigned char getTile(unsigned char* tilemap, unsigned int x, unsigned int y) {
    if (x > tilemap_width || y > tilemap_height) {
        return 0;
    }
    int pos = tilemap_width * y + x;
    return tilemap[pos];
}

#endif