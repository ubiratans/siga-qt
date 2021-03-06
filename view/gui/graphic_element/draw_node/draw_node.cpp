#include "view/gui/graphic_element/draw_node/draw_node.h"

#include "view/gui/graphic_element/draw_primitive/draw_primitive.h"

DrawNode::DrawNode(double x, double y) : m_x(x), m_y(y), m_has_to_compute_vertices(true) {

}

DrawNode::~DrawNode() {
  clearAndDeletePrimitives();
}

void DrawNode::clearAndDeletePrimitives() {
  for (auto primitive : m_primitives_vector) {
    delete primitive;
  }

  m_primitives_vector.clear();
  m_primitives_info.clear();
}

double DrawNode::x() {
  return m_x;
}

void DrawNode::setX(double x) {
  m_x = x;

  for (auto primitive : m_primitives_vector) {
    primitive->setX(x);
  }

  m_has_to_compute_vertices = true;
}

double DrawNode::y() {
  return m_y;
}

void DrawNode::setY(double y) {
  m_y = y;

  for (auto primitive : m_primitives_vector) {
    primitive->setY(y);
  }

  m_has_to_compute_vertices = true;
}

void DrawNode::setPosition(double x, double y) {
  setX(x);
  setY(y);
}

void DrawNode::setRotation(double angle) {
  for (DrawNodePrimitiveSt st : m_primitives_info) {
    st.m_draw_primitive->setRotation( st.m_rotation + angle );
  }

  m_has_to_compute_vertices = true;
}

void DrawNode::setScale(double scale) {
  for (DrawNodePrimitiveSt st : m_primitives_info) {
    st.m_draw_primitive->setScale( st.m_scale * scale );
  }

  m_has_to_compute_vertices = true;
}

bool DrawNode::hitTest(double x, double y) {
  for (auto primitive : m_primitives_vector) {
    if (primitive->hitTest(x, y)) {
      return true;
    }
  }

  return false;
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
