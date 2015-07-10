#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_RESERVOIR_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_RESERVOIR_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawTriangle;

class DrawReservoir : public DrawNode {
public:
  DrawReservoir(double x, double y);

  int height();
  int width();

  NodeType type();

protected:
  void initialize();

  DrawTriangle *m_triangle;
};

#endif
