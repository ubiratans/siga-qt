#ifndef VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_ELEMENT_STRUCTS_H
#define VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_ELEMENT_STRUCTS_H

#include "core/element/element_structs.h"

struct GraphicNodeStruct {
  GraphicNodeStruct(GraphicNodeStruct &st) {
    m_type = st.m_type;
    m_x = st.m_x;
    m_y = st.m_y;

    m_rotation = st.m_rotation;
    m_scale = st.m_scale;

    m_screen_world_height_ratio = st.m_screen_world_height_ratio;
    m_screen_world_width_ratio = st.m_screen_world_width_ratio;
  }

  GraphicNodeStruct(
      NodeType type,
      double node_world_x,
      double node_world_y,
      float screen_world_x_ratio,
      float screen_world_y_ratio,
      float rotation = 0.0,
      float scale = 1.0)
  {
    m_type = type;
    m_x = node_world_x;
    m_y = node_world_y;

    m_rotation = rotation;
    m_scale = scale;

    m_screen_world_height_ratio = screen_world_y_ratio;
    m_screen_world_width_ratio = screen_world_x_ratio;
  }

  NodeType m_type;

  float m_rotation;
  float m_scale;

  double m_x;
  double m_y;
  double m_screen_world_width_ratio;
  double m_screen_world_height_ratio;
};

#endif
