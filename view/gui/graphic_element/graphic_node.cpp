#include "view/gui/graphic_element/graphic_node.h"

#include "core/element/node.h"
#include "view/gui/graphic_element/draw_node/draw_node.h"
#include "view/gui/graphic_element/draw_node/draw_reservoir.h"

GraphicNode::GraphicNode(ElementID id, GraphicNodeStruct st)
  : GraphicElement(id, ElementType::Node), m_x(st.m_x), m_y(st.m_y),
    m_last_screen_world_width_ratio(st.m_screen_world_width_ratio), m_last_screen_world_height_ratio(st.m_screen_world_height_ratio)
{
   m_scale = st.m_scale;
   m_rotation = st.m_rotation;

   initialize(st.m_type);
}

void GraphicNode::computeVertices() {
  computeVertices(m_last_screen_world_width_ratio, m_last_screen_world_height_ratio);
}

void GraphicNode::computeVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  if (m_last_screen_world_width_ratio != screen_world_width_proportion
      || screen_world_height_proportion != m_last_screen_world_height_ratio)
  {
    m_draw_node->computeVertices(screen_world_width_proportion, screen_world_height_proportion);

    m_last_screen_world_width_ratio = screen_world_width_proportion;
    m_last_screen_world_height_ratio = screen_world_height_proportion;
  }
}

NodeType GraphicNode::type() {
  return m_draw_node->type();
}

bool GraphicNode::setType(NodeType type) {
  return false;
}

const std::vector<DrawPrimitive *> &GraphicNode::primitives() {
  return m_draw_node->primitives();
}

void GraphicNode::initialize(NodeType type) {
  if (type == NodeType::Reservoir) {
    m_draw_node = new DrawReservoir(m_x, m_y);
  }

  m_draw_node->computeVertices(m_last_screen_world_width_ratio, m_last_screen_world_height_ratio);
}
