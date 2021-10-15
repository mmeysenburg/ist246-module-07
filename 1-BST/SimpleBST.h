#pragma once

#include <iostream>
#include <sstream>
#include <string>

//-----------------------------------------------------------
// class definitions
//-----------------------------------------------------------

/**
 * Simple, templated binary search tree class. The class does no
 * balancing as the contents of the tree changes.
 */
template <class T> class SimpleBST {
private:
  //-------------------------------------------------------
  // inner class definition
  //-------------------------------------------------------

  /**
   * Private nested class representing a node in the simple
   * binary search tree.
   */
  class Node {
  public:
    /**
     * Constructor. Make a new leaf node in the tree, with
     * the specified data value.
     *
     * \param val Type T payload to store in the node.
     */
    Node(const T &val) : data(val), pLeft(0), pRight(0) {}

    /**
     * Print tree from here as a horizontally-oriented ASCII
     * tree diagram.
     *
     * \param prefix String prefix of the line thus far.
     * \param isTail True if this node ends the line, false
     * otherwise.
     */
    void print(std::string prefix, bool isTail);

    /** Type T payload of the node. */
    T data;

    /** Pointer to the left child of this node. */
    Node *pLeft;

    /** Pointer to the right child of this node. */
    Node *pRight;
  };

public:
  /**
   * Default constructor. Create an empty binary search tree.
   */
  SimpleBST() : pRoot(0), n(0u) {}

  /**
   * Copy constructor. Make a new binary search tree just like an
   * existing one.
   *
   * \param tree Tree to copy.
   */
  SimpleBST(const SimpleBST<T> &tree) { pRoot = copy(tree.pRoot); }

  /**
   * Destructor. Free the memory used by this binary search tree.
   */
  ~SimpleBST() { clear(); }

  /**
   * Remove all the elements from the binary search tree.
   */
  void clear();

  /**
   * Determine if the binary search tree contains a given value.
   *
   * \param val Value to search for.
   * \return True if the binary search tree contains val, false
   * otherwise.
   */
  bool contains(const T &val) const { return contains(val, pRoot); }

  /**
   * Insert an element into the tree.
   *
   * \param val Element to insert into the tree.
   */
  void insert(const T &val) { pRoot = insert(val, pRoot); }

  /**
   * Determine if the binary search tree is empty.
   *
   * \return True if the tree is empty, false otherwise.
   */
  bool isEmpty() { return n == 0u; }

  /**
   * Override of the stream insertion operator for SimpleBST objects.
   * Prints via a preorder traversal.
   *
   * \param out ostream object to output to, e.g., cout
   *
   * \param tree SimpleBST to output
   *
   * \return the out ostream object
   */
  friend std::ostream &operator<<(std::ostream &out, const SimpleBST<T> &tree) {
    out << "[";
    tree.preOrderPrint(out, tree.pRoot);
    out << "]";
    return out;
  }

  /**
   * Override of the assignment operator.
   *
   * \param tree SimpleBST to copy from.
   * \return A reference to the newly created binary search tree,
   * for chaining.
   */
  SimpleBST &operator=(const SimpleBST<T> &tree);

  /**
   * Remove an item from the binary search tree. If the item isn't
   * in the tree, take no action.
   *
   * \param val Item to be removed from the tree.
   */
  void remove(const T &val) { pRoot = remove(val, pRoot); }

  /**
   * Get the number of nodes in the binary search tree.
   *
   * \return Number of nodes in the tree.
   */
  unsigned size() { return n; }

private:
  /** Pointer to the root node in the binary search tree. */
  Node *pRoot;

  /** Number of nodes in the binary search tree. */
  unsigned n;

  /**
   * Recursive helper for clear function.
   *
   * \param pCurr Pointer to current location in the deletion
   * process.
   */
  void clear(Node *pCurr);

  /**
   * Recursive helper for contains function.
   *
   * \param val Value to search for.
   * \param pCurr Pointer to the current node in the search.
   * \return True if the tree contains val, false otherwise.
   */
  bool contains(const T &val, Node *pCurr) const;

  /**
   * Recursive helper function for copying trees.
   *
   * \param pCurr Pointer to the current node in the tree being
   * copied.
   * \return Pointer to the newly created node, or 0 if no node
   * was created.
   */
  Node *copy(Node *pCurr);

  /**
   * Recursive helper for insert function.
   *
   * \param val Value to insert into the tree.
   * \param pCurr Pointer to current location to test during
   * insertion.
   * \return Pointer to the root of the subtree where the node
   * was inserted (or where it already exists)
   */
  Node *insert(const T &val, Node *pCurr);

  /**
   * Find the node containing the smallest value in a subtree.
   *
   * \param pCurr Pointer to the root of the subtree to search.
   * \return Pointer to the node containing the smallest value in
   * the subtree rooted as pCurr.
   */
  Node *minValueNode(Node *pCurr);

  /**
   * Recursive helper function for operator>>.
   *
   * \param out ostream object to output to, e.g., cout
   * \param pCurr Pointer to current node in the traversal.
   */
  void preOrderPrint(std::ostream &out, Node *pCurr) const;

  /**
   * Recursive helper for remove function.
   *
   * \param val Item to remove from the tree.
   * \param pCurr Pointer to the current node in the traversal of the
   * tree.
   * \param Pointer to the root of the subtree where the node
   * was removed (or where it would have been)
   */
  Node *remove(const T &val, Node *pCurr);
};

//-----------------------------------------------------------
// function implementations
//-----------------------------------------------------------

/*
 * Public clear function implementation.
 */
template <class T> void SimpleBST<T>::clear() {
  clear(pRoot);
  n = 0u;
  pRoot = 0;
}

/*
 * Implementation for recursive clear helper function.
 */
template <class T> void SimpleBST<T>::clear(Node *pCurr) {
  if (pCurr != 0) {
    clear(pCurr->pLeft);
    clear(pCurr->pRight);
    delete pCurr;
  }
}

/*
 * Implementation for recursive contains helper function.
 */
template <class T>
bool SimpleBST<T>::contains(const T &val, Node *pCurr) const {
  // empty? Doesn't contain val for sure
  if (pCurr == 0) {
    return false;
  }
  // found it?
  else if (pCurr->data == val) {
    return true;
  }
  // go left?
  else if (val < pCurr->data) {
    return contains(val, pCurr->pLeft);
  }
  // go right!
  else {
    return contains(val, pCurr->pRight);
  }
}

/*
 * Implementation for recursive copy helper function.
 */
template <class T>
typename SimpleBST<T>::Node *SimpleBST<T>::copy(Node *pCurr) {

  if (pCurr != 0) {
    Node *pN = 0;
    pN = new Node(pCurr->data);
    n++;
    pN->pLeft = copy(pCurr->pLeft);
    pN->pRight = copy(pCurr->pRight);

    return pN;
  } else {
    return 0;
  }
}

/*
 * Implementation for recursive insert helper function.
 */
template <class T>
typename SimpleBST<T>::Node *SimpleBST<T>::insert(const T &val,
                                                  SimpleBST<T>::Node *pCurr) {

  // Null pointer means we've located the insertion location
  if (pCurr == 0) {
    n++;
    return new Node(val);
  }
  // Otherwise, should we go left?
  else if (val < pCurr->data) {
    pCurr->pLeft = insert(val, pCurr->pLeft);
  }
  // Should we go right?
  else if (val > pCurr->data) {
    pCurr->pRight = insert(val, pCurr->pRight);
  }

  // if we get here, val was a duplicate, so return
  // pCurr unchanged
  return pCurr;
}

/*
 * Implementation of minValueNode function.
 */
template <class T>
typename SimpleBST<T>::Node *SimpleBST<T>::minValueNode(Node *pCurr) {
  while (pCurr->pLeft != 0) {
    pCurr = pCurr->pLeft;
  }

  return pCurr;
}

/*
 * Implementation for overridden assignment operator.
 */
template <class T>
SimpleBST<T> &SimpleBST<T>::operator=(const SimpleBST<T> &tree) {
  // clean existing tree
  clear();

  // copy tree
  pRoot = copy(tree.pRoot);

  return *this;
}

/*
 * Implementation for recursive printing helper function.
 */
template <class T>
void SimpleBST<T>::preOrderPrint(std::ostream &out, Node *pCurr) const {

  if (pCurr != 0) {
    out << pCurr->data << " ";

    preOrderPrint(out, pCurr->pLeft);
    preOrderPrint(out, pCurr->pRight);
  }
}

/*
 * Implementation for recursive remove helper function.
 */
template <class T>
typename SimpleBST<T>::Node *SimpleBST<T>::remove(const T &val, Node *pCurr) {
  // null pointer means not found, so just return
  if (pCurr == 0) {
    return pCurr;
  }

  // go left?
  if (val < pCurr->data) {
    pCurr->pLeft = remove(val, pCurr->pLeft);
  }
  // go right?
  else if (val > pCurr->data) {
    pCurr->pRight = remove(val, pCurr->pRight);
  }
  // found it!
  else {
    // one child or no child
    if ((pCurr->pLeft == 0) || (pCurr->pRight == 0)) {
      Node *pT = 0;
      if (pT == pCurr->pLeft) {
        pT = pCurr->pRight;
      } else {
        pT = pCurr->pLeft;
      }

      // No child case
      if (pT == 0) {
        pT = pCurr;
        pCurr = 0;
      }
      // One child case
      else {
        pCurr = pT;
      }
    }
    // node with two children: get inorder successor
    else {
      Node *pT = minValueNode(pCurr->pRight);
      // copy data to this node
      pCurr->data = pT->data;

      // delete successor
      pCurr->pRight = remove(pT->data, pCurr->pRight);
    }
  }

  // return (new?) root of subtree
  return pCurr;
}
