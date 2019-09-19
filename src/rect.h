#ifndef _RECT_H_
#define _RECT_H_
#include <raylib.h>
#include <libguile.h>

static SCM rectangle_type_scm;

void init_rect_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("rect");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  rectangle_type_scm =
    scm_make_foreign_object_type (name, slots, finalizer);
}

void rect_assert_type(SCM obj) {
    scm_assert_foreign_object_type (rectangle_type_scm, obj);
}

SCM rectangle_create(SCM x, SCM y, SCM w, SCM h) {
    Rectangle* result = (Rectangle *)scm_gc_malloc(sizeof(Rectangle), "rect"); 
    result->x = scm_to_double(x);
    result->y = scm_to_double(y);
    result->width = scm_to_double(w);
    result->height = scm_to_double(h);
    return scm_make_foreign_object_1(rectangle_type_scm, result);
}

SCM rect_width(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->width);
}

SCM rect_height(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->height);
}

SCM rect_x(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->x);
}


SCM rect_y(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->y);
}

SCM rect_w(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->width);
}

SCM rect_h(SCM rect) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    return scm_from_double(r->height);
}

SCM rect_set_x(SCM rect, SCM x) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    r->x = scm_to_double(x);
    return SCM_UNSPECIFIED;
}

SCM rect_set_y(SCM rect, SCM value) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    r->y = scm_to_double(value);
    return SCM_UNSPECIFIED;
}

SCM rect_set_w(SCM rect, SCM value) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    r->width = scm_to_double(value);
    return SCM_UNSPECIFIED;
}

SCM rect_set_h(SCM rect, SCM value) {
    rect_assert_type(rect);
    Rectangle* r = scm_foreign_object_ref(rect, 0);
    r->height = scm_to_double(value);
    return SCM_UNSPECIFIED;
}

void rect_module_init() {
    init_rect_type();
    scm_c_define_gsubr ("rectangle", 4, 0, 0, &rectangle_create);
    scm_c_define_gsubr ("rectangle:x", 1, 0, 0, &rect_x);
    scm_c_define_gsubr ("rectangle:y", 1, 0, 0, &rect_y);
    scm_c_define_gsubr ("rectangle:width", 1, 0, 0, &rect_w);
    scm_c_define_gsubr ("rectangle:height", 1, 0, 0, &rect_h);
    scm_c_define_gsubr ("rectangle:x!", 2, 0, 0, &rect_set_x);
    scm_c_define_gsubr ("rectangle:y!", 2, 0, 0, &rect_set_y);
    scm_c_define_gsubr ("rectangle:width!", 2, 0, 0, &rect_set_w);
    scm_c_define_gsubr ("rectangle:height!", 2, 0, 0, &rect_set_h);
}

#endif