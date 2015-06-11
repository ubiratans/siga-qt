#ifndef CORE_ELEMENT_NODE_H
#define CORE_ELEMENT_NODE_H

#include "core/element/element.h"

#include <map>

// Forward declarations
class Link;

class Node : public Element {
  friend class NetworkNodeHandler;
  friend class NetworkLinkHandler;

public:
  std::map< ElementID, Link* >& ingoingLinks(); //!< get links up map - ElementID (id of the node linked with)
  std::map< ElementID, Link* >& outgoingLinks(); //!< get links down map - ElementID (id of the node linked with)

  virtual NodeType type() = 0;

  double longitude(); //!< get longitude - longitude is related to the x-axis
  void setLongitude(double value);

  double latitude(); //!< get latitude - latitude is related to the y-axis
  void setLatitude(double value);

  double area(); //!< get node area
  void setArea(double area);

  /*!
    * returns true if the node related to node_id is down-connected with this (instance) node
    * - in other words, Node(node_id).outgoingLinks() has this instance node and Node(this).ingoingLinks() has the Node(node_id)
  */
  bool hasIngoingNode(ElementID node_id);

  /*!
    * returns true if the node related to node_id is up-connected with this (instance) node
    * - in other words, Node(node_id).ingoingLinks() has this instance node and Node(this).outgoingLinks() has the Node(node_id)
  */
  bool hasOutgoingNode(ElementID node_id);

protected:
  Node(ElementID id, std::string name, double latitude = 0.0, double longitude = 0.0);
  virtual ~Node();

  bool insertIngoingLink(ElementID id, Link &link);
  bool insertOutgoingLink(ElementID id, Link &link);

  bool removeIngoingLink(ElementID id); //!< remove the link up associated with the node referred by the id
  bool removeOutgoingLink(ElementID id); //!< remove the link down associated with the node referred by the id

  void stealLinks(Node &node);

  double m_latitude;
  double m_longitude;
  double m_area;

  /**
  * Links acima do no
  * Aqueles que despejam água no nó
  */
  std::map< ElementID, Link* > m_ingoing_links_map;

  /**
  * Links abaixo do no
  * Aqueles que irão receber água do nó
  */
  std::map< ElementID, Link* > m_outgoing_links_map;
};

#endif
