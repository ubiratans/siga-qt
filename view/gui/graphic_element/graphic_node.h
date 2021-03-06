#ifndef VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_NODE_H
#define VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_NODE_H

#include "view/gui/graphic_element/graphic_element.h"
#include "view/gui/graphic_element/graphic_element_structs.h"

class Node;
class DrawNode;

class GraphicNode : public GraphicElement {
public:
  GraphicNode(ElementID id, GraphicNodeStruct graphic_node_st);

  void calculateVertices();
  void calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion);

  double x();
  double y();

  int height();
  int width();

  void setPosition(double x, double y); //!< position in world coordinates

  void setScale(double value);
  void setRotation(double value);

  bool hitTest(double x, double y);

  NodeType type();
  bool setType(NodeType type);

  Node* linkedNode();
  bool linkWithNode(Node &node);
  void unlinkNode();

  const std::vector< DrawPrimitive* >& primitives();

private:
  void initialize(NodeType type);
  void initializePrimitives();

  double m_last_screen_world_width_ratio;
  double m_last_screen_world_height_ratio;

  double m_x;
  double m_y;

  DrawNode *m_draw_node;
  Node *m_linked_node;
};

#endif
