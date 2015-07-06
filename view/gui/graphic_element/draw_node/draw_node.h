#ifndef VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_NODE_H
#define VIEW_GUI_GRAPHIC_ELEMENT_DRAW_NODE_DRAW_NODE_H

#include <QString>
#include <vector>
#include <map>

#include "core/element/element_structs.h"

class DrawPrimitive;

struct DrawNodePrimitiveSt {
  DrawNodePrimitiveSt() {
    m_rotation = 0.0;
    m_scale = 1.0;

    m_draw_primitive = nullptr;
  }

  DrawPrimitive *m_draw_primitive;
  double m_rotation;
  double m_scale;
};

class DrawNode {
public:
  DrawNode(double x, double y);
  virtual ~DrawNode();

  double x();
  void setX(double x);

  double y();
  void setY(double y);

  void setPosition(double x, double y);

  void setRotation(double angle);
  void setScale(double scale);

  virtual NodeType type() = 0;

  virtual bool hitTest(double x, double y);

  bool verticesUpdated();

  std::vector< DrawPrimitive* >& primitives();

  //!< The main intent of this method is to compute all the primitives vertices, but it also calls the initialize() if is needed.
  void calculateVertices(double screen_world_width_proportion, double screen_world_height_proportion);

protected:
  //!< This method will instantiate the primitives and fill the primitives vector, it SHALL not calculate the primitive vertices.
  virtual void initialize() = 0;
  QString m_label;

  double m_x;
  double m_y;

  bool m_has_to_compute_vertices;
  bool m_initialized;

  std::vector< DrawPrimitive* > m_primitives_vector;
  std::vector< DrawNodePrimitiveSt > m_primitives_info;
};

#endif
