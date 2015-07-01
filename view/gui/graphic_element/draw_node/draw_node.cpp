#include "view/gui/graphic_element/draw_node/draw_node.h"

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

DrawNode::DrawNode(float x, float y) : m_x(x), m_y(y), m_has_to_compute_vertices(true) {

}

DrawNode::~DrawNode() {
  for (auto primitive : m_primitives_vector) {
    delete primitive;
  }
}

float DrawNode::x() {
  return m_x;
}

void DrawNode::setX(float x) {
  m_x = x;

  for (auto primitive : m_primitives_vector) {
    primitive->setX(x);
  }

  m_has_to_compute_vertices = true;
}

float DrawNode::y() {
  return m_y;
}

void DrawNode::setY(float y) {
  m_y = y;

  for (auto primitive : m_primitives_vector) {
    primitive->setY(y);
  }

  m_has_to_compute_vertices = true;
}

void DrawNode::setPosition(float x, float y) {
  setX(x);
  setY(y);
}

void DrawNode::setRotation(float angle) {
  for (DrawNodePrimitiveSt st : m_primitives_info) {
    st.m_draw_primitive->setRotation( st.m_rotation + angle );
  }

  m_has_to_compute_vertices = true;
}

void DrawNode::setScale(float scale) {
  for (DrawNodePrimitiveSt st : m_primitives_info) {
    st.m_draw_primitive->setRotation( st.m_scale * scale );
  }

  m_has_to_compute_vertices = true;
}

bool DrawNode::verticesUpdated() {
  return !m_has_to_compute_vertices;
}

std::vector<DrawPrimitive *> &DrawNode::primitives() {
  return m_primitives_vector;
}

void DrawNode::calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion) {
  if (!m_initialized) {
    initialize();

    m_initialized = true;
  }

  for (auto primitive : m_primitives_vector) {
    primitive->calculateVertices(screen_world_width_proportion, screen_world_height_proportion);
  }

  m_has_to_compute_vertices = false;
}
