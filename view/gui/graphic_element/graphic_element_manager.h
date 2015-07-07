#ifndef VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_ELEMENT_MANAGER_H
#define VIEW_GUI_GRAPHIC_ELEMENT_GRAPHIC_ELEMENT_MANAGER_H

#include <map>

#include "core/element/element_manager.h"
#include "view/gui/graphic_element/graphic_node.h"
#include "view/gui/graphic_element/graphic_link.h"

/*!
 * \brief This class is intended to keep the graphic elements synchonized with the actual
 * abstract elements and to provide some facilities like undo/redo operations.
 */

class GraphicLink;

class GraphicElementManager {
public:
  GraphicElementManager(ElementManager &element_manager);
  virtual ~GraphicElementManager();

  GraphicNode& addNode(NodeType type, double world_x, double world_y);
  bool removeElement(ElementID id);

  bool getGraphicNode(ElementID id, GraphicNode* &result);
  //bool getGraphicLink(ElementID id, GraphicLink* &result);
  bool getGraphicElement(ElementID id, GraphicElement* &result);

  bool setNodeType(GraphicNode &node, NodeType new_type);
  bool setNodeType(ElementID node_id, NodeType new_type);

  //bool setLinkType(GraphicLink &link, LinkType new_type);
  //bool setLinkType(ElementID link_id, LinkType new_type);

  //bool setLinkNodes(ElementID link_id, ElementID node_origin_id, ElementID node_destiny_id);

private:
  ElementManager *m_element_manager;

  std::map< ElementID, GraphicNode* > m_graphic_nodes_map;
  std::map< ElementID, GraphicElement* > m_graphic_elements_map;
  //std::map< ElementID, GraphicLink* > m_graphic_links_map;
};

#endif
