#ifndef CORE_ELEMENT_ELEMENT_MANAGER_H
#define CORE_ELEMENT_ELEMENT_MANAGER_H

#include "core/element/link.h"
#include "core/element/node.h"

class ElementManager {
public:
  ElementManager();
  virtual ~ElementManager();

  Node& addNode(NodeType type = NodeType::Basin, double latitude = 0.0, double longitude = 0.0); //!< Creates a new node

  bool addLink(
      ElementID node_origin_id,
      ElementID node_destiny_id,
      Link* &result,
      LinkType type = LinkType::Default,
      bool bidirectional = false,
      bool lateral_inflow = false,
      bool artificial = false
      );

  //!< remove the element by the id specified if it exists - returns true if the removal was successful, false otherwise
  bool removeElement(ElementID id);

  bool getNode(ElementID id, Node* &result); //!< returns true and fills the pointer result with the node's pointer if it exists
  bool getLink(ElementID id, Link* &result); //!< returns true and fills the pointer result with the link's pointer if it exists
  bool getElement(ElementID id, Element* &result); //!< returns true and fills the pointer result with the element's pointer if it exists
  bool getElementName(ElementID id, std::string &name); //!< returns the label from the Element

  bool setNodeType(Node &node, NodeType new_type);
  bool setNodeType(ElementID node_id, NodeType new_type);

  bool setLinkType(Link &link, LinkType new_type);
  bool setLinkType(ElementID link_id, LinkType new_type);

  bool setLinkNodes(ElementID link_id, ElementID node_origin_id, ElementID node_destiny_id);

  bool setElementID(ElementID old_id, ElementID new_id);

  // The methods below should only be used by the Network Command Classes and by ElementManager internal methods
  bool attachNode(Node &node); //!< this method adds the node passed if it's id does not match with the id of any element added
  Node* detachNode(ElementID id); //!< this method removes the node from the list, but it does NOT delete the node itself

  bool attachLink(Link &link); //!< this method adds the link passed if it id does not match with the id of any element added
  Link* detachLink(ElementID id); //!< this method detaches the link from the map but does not delete it

  std::map< ElementID, Node* >& nodesMap(); //!< return the map of all nodes
  std::map< ElementID, Link* >& linksMap(); //!< return the map of all links
  std::map< ElementID, Element* >& elementsMap(); //!< return the map of all elements

  //!< Delete an element that is not present in the list - This method SHALL only be called by the Command Classes
  bool deleteExternalElement(Element *element);
  void clear();

  uint32_t countElements();
  uint32_t countLinks();
  uint32_t countNodes();

private:
  bool removeNode(ElementID id); //!< removes an existing node
  bool removeLink(ElementID id); //!< returns true if the link exists and was removed, or false if not

  void setLinkID(Link &link, ElementID new_id); //!< Modifies the link id - This method SHALL only be invoked by the setElementID()
  void setNodeID(Node &node, ElementID new_id); //!< Modifies the node id - This method SHALL only be invoked by the setElementID()

  std::map< ElementID, Link* > m_link_map;
  std::map< ElementID, Node* > m_node_map;
  std::map< ElementID, Element* > m_element_map; //!< Map that hold pointers to entries of m_link_map and m_node_map

  ElementID m_id_counter;
};

#endif
