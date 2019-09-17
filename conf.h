#ifndef _CONF_H_ 
#define _CONF_H_

#define CONF_SCREEN_WIDTH 1280
#define CONF_SCREEN_HEIGHT 720
#define CONF_VIRTUAL_WIDTH 256
#define CONF_VIRTUAL_HEIGHT 144
#define CONF_TILE_SIZE 16
#define CONF_TILEMAP_WIDTH 32
#define CONF_TILEMAP_HEIGHT 18

/* Bit manipulation */
#define BIT(n)                  ( 1<<(n) )
#define BIT_SET(y, mask)        ( y |=  (mask) )
#define BIT_CLEAR(y, mask)      ( y &= ~(mask) )
#define BIT_FLIP(y, mask)       ( y ^=  (mask) )
#define BIT_MASK(len)           ( BIT(len)-1 )
#define BIT_FIELD_MASK(start, len)     ( BIT_MASK(len)<<(start) )
#define BIT_FIELD_PREP(x, start, len)  ( ((x)&BIT_MASK(len)) << (start) )
#define BIT_FIELD_GET(y, start, len)   ( ((y)>>(start)) & BIT_MASK(len) )
#define BIT_FIELD_SET(y, x, start, len)    \
    ( y= ((y) &~ BIT_FIELD_MASK(start, len)) | BIT_FIELD_PREP(x, start, len) )

/* global stuff */
unsigned char TB_INPUT = 0;
unsigned char* TB_TILEMAP;
unsigned char* TB_SPRITEMAP;

#endif