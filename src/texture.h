#ifndef _TEXTURE_H_
#define _TEXTURE_H_
#include <raylib.h>
#include <libguile.h>

static SCM texture_type_scm;

void init_texture_type (void)
{
  SCM name, slots;
  scm_t_struct_finalize finalizer;

  name = scm_from_utf8_symbol ("texture");
  slots = scm_list_1 (scm_from_utf8_symbol ("data"));
  finalizer = NULL;

  texture_type_scm =
    scm_make_foreign_object_type (name, slots, finalizer);
}

void texture_assert_type(SCM obj) {
    scm_assert_foreign_object_type (texture_type_scm, obj);
}

SCM texture_load(SCM path) {
    Texture2D* result = (Texture2D *)scm_gc_malloc(sizeof(Texture2D), "texture");
    *result = LoadTexture(scm_to_locale_string(path));
    return scm_make_foreign_object_1(texture_type_scm, result);
}

SCM texture_width(SCM texture) {
    texture_assert_type(texture);
    Texture2D* tex = scm_foreign_object_ref(texture, 0);
    return scm_from_int(tex->width);
}

SCM texture_height(SCM texture) {
    texture_assert_type(texture);
    Texture2D* tex = scm_foreign_object_ref(texture, 0);
    return scm_from_int(tex->height);
}

SCM texture_unload(SCM texture) {
    texture_assert_type(texture);
    Texture2D* tex = scm_foreign_object_ref(texture, 0);
    UnloadTexture(*tex);
    return SCM_UNSPECIFIED;
}

SCM texture_draw(SCM texture, SCM x, SCM y) {
    texture_assert_type(texture);
    Texture2D* tex = scm_foreign_object_ref(texture, 0);
    DrawTexture(*tex, scm_to_double(x), scm_to_double(y), WHITE);
    return SCM_UNSPECIFIED;
}

void texture_module_init() {
    init_texture_type();
    scm_c_define_gsubr ("texture:load", 1, 0, 0, &texture_load);
    scm_c_define_gsubr ("texture:width", 1, 0, 0, &texture_width);
    scm_c_define_gsubr ("texture:height", 1, 0, 0, &texture_height);
    scm_c_define_gsubr ("texture:draw", 3, 0, 0, &texture_draw);
    scm_c_define_gsubr ("texture:unload", 1, 0, 0, &texture_unload);
}

#endif