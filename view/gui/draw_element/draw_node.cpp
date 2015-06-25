#include "view/gui/draw_element/draw_node.h"

#include "view/gui/draw_element/draw_primitive/draw_triangle.h"

DrawNode::DrawNode(ElementID id, NodeType node_type, float x, float y, double scale)
  : DrawElement(id, ElementType::Node, scale), m_type(node_type), m_x(x), m_y(y)
{
  initializePrimitives();
}

void DrawNode::initializePrimitives() {
  DrawTriangle *triangle = new DrawTriangle(m_x, m_y, QColor(Qt::blue), QColor(Qt::black));
  triangle->setScale(m_scale);
  triangle->setRotation(180.0);

  m_primitives_vector.push_back(triangle);
}
