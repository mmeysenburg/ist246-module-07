#include "SimpleBST.h"
#include <cstdlib>
#include <iostream>

int main() {
  using namespace std;

  SimpleBST<int> bst;

  // randomize the same way each time
  srand(68333);

  cout << "Initial bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;

  cout << "\nInserting 45." << endl;
  bst.insert(45);
  cout << "Now bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;

  cout << "\nInserting ";
  for (int i = 0; i < 10; i++) {
    int d = rand() % 200;
    cout << d << " ";
    bst.insert(d);
  }
  cout << "\nNow bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;

  cout << "\nInserting duplicate 175." << endl;
  bst.insert(175);
  cout << "\nNow bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;

  cout << "\nCopy constructor." << endl;
  SimpleBST<int> bst1(bst);
  cout << "\nNew bst has " << bst1.size() << " nodes" << endl;
  cout << "Tree: " << bst1 << endl;

  cout << "\nSearching." << endl;
  cout << "bst " << (bst.contains(159) ? "does" : "does not") << " contain 159"
       << endl;
  cout << "bst " << (bst.contains(160) ? "does" : "does not") << " contain 160"
       << endl;

  cout << "\nRemoving 160 and 45." << endl;
  bst.remove(160);
  bst.remove(45);
  cout << "bst " << (bst.contains(45) ? "does" : "does not") << " contain 45"
       << endl;
  cout << "bst " << (bst.contains(160) ? "does" : "does not") << " contain 160"
       << endl;
  cout << bst << endl;

  cout << "\nClearing tree." << endl;
  bst.clear();
  cout << "\nNow bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;
  cout << "bst " << (bst.contains(159) ? "does" : "does not") << " contain 159"
       << endl;
  cout << "bst " << (bst.contains(160) ? "does" : "does not") << " contain 160"
       << endl;
  cout << "\nNew bst has " << bst1.size() << " nodes" << endl;
  cout << "Tree: " << bst1 << endl;

  cout << "\nAssignment operator." << endl;
  bst = bst1;
  cout << "\nNow bst has " << bst.size() << " nodes" << endl;
  cout << "Tree: " << bst << endl;

  cout << "\nAllocating dynamic BST and filling:" << endl;
  SimpleBST<int> *pBst = new SimpleBST<int>();
  for (int i = 0; i < 20; i++) {
    pBst->insert(rand() % 200);
  }
  cout << "New bst has " << pBst->size() << " nodes" << endl;
  cout << "Tree: " << *pBst << endl;

  cout << "Clearing and making a chain" << endl;
  pBst->clear();
  for (int i = 0; i < 20; i++) {
    pBst->insert(i);
  }
  cout << *pBst << endl;

  cout << "Freeing dynamic tree." << endl;
  delete pBst;

  return EXIT_SUCCESS;
}
