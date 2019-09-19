#ifndef _EVENT_H_
#define _EVENT_H_

#include <raylib.h>
#include <libguile.h>

typedef struct {
    char* name;
    void (*callback)(SCM value); // array of callbacks
} t_event;

static int event_count = 0;
static t_event *events;

void add_event(char* name) {
    
}

#endif