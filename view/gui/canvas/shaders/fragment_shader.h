#ifndef VIEW_GUI_CANVAS_SHADERS_FRAGMENT_SHADER_H
#define VIEW_GUI_CANVAS_SHADERS_FRAGMENT_SHADER_H
#include <QString>

const QString kCanvasFragmentShader =
    "#version 130\n\
    uniform vec4 color; \n\
    out vec4 frag_color; \n\
    \n \
    void main(void) { \n\
      frag_color = color; \n\
    }";

#endif
