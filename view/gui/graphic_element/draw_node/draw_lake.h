#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_LAKE_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_LAKE_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawTriangle;

class DrawLake : public DrawNode {
public:
  DrawLake(double x, double y);

  NodeType type();

  int height();
  int width();

protected:
  void initialize();

  DrawTriangle *m_main_triangle;
};

#endif
