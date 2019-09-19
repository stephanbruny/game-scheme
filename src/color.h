#ifndef _COLOR_H_
#define _COLOR_H_
#include <raylib.h>
#include <libguile.h>

static SCM color_type_scm;

void init_color_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("color");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  color_type_scm =
    scm_make_foreign_object_type (name, slots, finalizer);
}

SCM color_rgb(SCM r, SCM g, SCM b) {
    Color* result = (Color *)scm_gc_malloc(sizeof(Color), "color"); 
    result->r = scm_to_int(r);
    result->g = scm_to_int(g);
    result->b = scm_to_int(b);
    result->a = 255;
    return scm_make_foreign_object_1(color_type_scm, result);
}

void color_assert_type(SCM obj) {
    scm_assert_foreign_object_type (color_type_scm, obj);
}

void color_module_init() {
    init_color_type();
    scm_c_define_gsubr ("color:rgb", 3, 0, 0, &color_rgb);
}

#endif