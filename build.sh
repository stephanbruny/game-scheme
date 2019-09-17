
FRAMEWORK_FLAGS="-framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"
INCLUDE_FLAGS=-'I/usr/local/include/guile/2.2/ -I/usr/local/Cellar/raylib/2.5.0/include/'
LIB_FLAGS='-lguile-2.2 -lraylib -L/usr/local/Cellar/raylib/2.5.0/lib/'
echo "Compile Tinkerboy"
echo "clang main.c -o tinkerboy ${LIB_FLAGS} ${INCLUDE_FLAGS}"
clang main.c -o tinkerboy $LIB_FLAGS $INCLUDE_FLAGS