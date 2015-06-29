#include "view/gui/graphic_element/graphic_node.h"

#include "core/element/node.h"
#include "view/gui/graphic_element/draw_node/draw_node.h"
#include "view/gui/graphic_element/draw_node/draw_reservoir.h"
#include "view/gui/graphic_element/draw_node/draw_basin.h"
#include "view/gui/graphic_element/draw_node/draw_demand.h"
#include "view/gui/graphic_element/draw_node/draw_junction.h"
#include "view/gui/graphic_element/draw_node/draw_lake.h"

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

void GraphicNode::setPosition(float x, float y) {
  m_x = x;
  m_y = y;

  m_draw_node->setPosition(x, y);
  m_draw_node->computeVertices(m_last_screen_world_width_ratio, m_last_screen_world_height_ratio);
}

NodeType GraphicNode::type() {
  return m_draw_node->type();
}

bool GraphicNode::setType(NodeType type) {
  bool ret = type != m_draw_node->type();

  if (ret) {
    if (m_draw_node == nullptr) {
      delete m_draw_node;
    }

    initialize(type);
  }

  return ret;
}

const std::vector<DrawPrimitive *> &GraphicNode::primitives() {
  return m_draw_node->primitives();
}

void GraphicNode::initialize(NodeType type) {
  switch (type) {
    case NodeType::Reservoir:
      m_draw_node = new DrawReservoir(m_x, m_y);
    break;

    case NodeType::Basin:
      m_draw_node = new DrawBasin(m_x, m_y);
    break;

    case NodeType::Demand: {
      m_draw_node = new DrawDemand(m_x, m_y);
    }
    break;

    case NodeType::Junction: {
      m_draw_node = new DrawJunction(m_x, m_y);
    }
    break;

    case NodeType::Lake: {
      m_draw_node = new DrawLake(m_x, m_y);
    }
    break;
  }

  m_draw_node->computeVertices(m_last_screen_world_width_ratio, m_last_screen_world_height_ratio);
}
