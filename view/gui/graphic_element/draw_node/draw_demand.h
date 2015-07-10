#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_DEMAND_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_DEMAND_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawRectangle;

class DrawDemand : public DrawNode {
public:
  DrawDemand(double x, double y);

  NodeType type();

  int height();
  int width();

protected:
  void initialize();

  DrawRectangle *m_rectangle;
};

#endif
