#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_JUNCTION_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_JUNCTION_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawCircle;

class DrawJunction : public DrawNode {
public:
  DrawJunction(double x, double y);

  int width();
  int height();

  NodeType type();

protected:
  void initialize();

  DrawCircle *m_circle;
};

#endif
