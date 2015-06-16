#ifndef CORE_ELEMENT_LINK_H
#define CORE_ELEMENT_LINK_H

#include "core/element/element.h"

class Node;

class Link : public Element {
  friend class ElementManager;

public:
  bool isArtificial();
  void setArtificial(bool value);

  bool isBidirectional();
  void setBidirectional(bool value);

  bool hasLateralInflow();
  void setLateralInflow(bool value);

  double length();
  void setLength(double value);

  double depth();
  void setDepth(double value);

  double divPointLongitude();
  double divPointLatitude();

  bool hasDivPoint();
  void removeDivPoint();
  void setDivPoint(double longitude, double latitude);

  Node& nodeOrigin();
  Node& nodeDestiny();

  LinkType type();

protected:
  Link(ElementID id,
       std::string name,
       Node &node_origin,
       Node &node_destiny,
       LinkType type = LinkType::Default,
       bool bidirectional = false,
       bool lateral_inflow = false,
       bool artificial = false);

  virtual ~Link();

  bool setType(LinkType type);
  bool setNodes(Node &node_origin, Node &node_destiny);

  bool m_artificial; //!< indicate that the link is or not artificial
  bool m_bidirectional; //!< indicate that the link is bidirectional or not
  bool m_lateral_inflow; //!< link releases lateral inflow

  LinkType m_type; //!< type

  double m_depth; //!< depth of link
  double m_length; //!< size of link

  bool m_has_div_point;
  double m_div_point_latitude;
  double m_div_point_longitude;

  Node* m_node_origin; //!< origin node;
  Node* m_node_destiny; //!< destiny node
};

#endif
