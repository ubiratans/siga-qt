#ifndef VIEW_GUI_CANVAS_SHADERS_VERTEX_SHADER_H
#define VIEW_GUI_CANVAS_SHADERS_VERTEX_SHADER_H

#include <QString>

const QString kCanvasVertexShader =
  "#version 130\n\
  uniform mat4 projection_matrix; \n\
  in vec4 vertex; \n\
  \n\
  void main(void) { \n\
    gl_Position = projection_matrix * vertex;\n\
  }";

#endif
