#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_RESERVOIR_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_RESERVOIR_H

#include "view/gui/graphic_element/draw_node/draw_node.h"

class DrawReservoir : public DrawNode {
public:
  DrawReservoir(float x, float y);

  NodeType type();

protected:
  void initialize();
};

#endif
