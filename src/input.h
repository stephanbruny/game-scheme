#ifndef _INPUT_H_
#define _INPUT_H_

#include <raylib.h>
#include <libguile.h>

SCM is_key_down(SCM code) {
    int keycode = scm_to_int(code);
    return scm_from_bool(IsKeyDown(keycode));
}

SCM is_key_pressed(SCM code) {
    int keycode = scm_to_int(code);
    return scm_from_bool(IsKeyPressed(keycode));
}

SCM get_pressed(void) {
    return scm_from_int(GetKeyPressed());
}

void init_input() {
    scm_c_define_gsubr ("input:key-down?", 1, 0, 0, &is_key_down);
    scm_c_define_gsubr ("input:key-pressed?", 1, 0, 0, &is_key_pressed);
    scm_c_define_gsubr ("input:pressed", 0, 0, 0, &get_pressed);
}

#endif