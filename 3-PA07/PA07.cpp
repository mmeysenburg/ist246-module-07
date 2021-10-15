#include <cstdlib>
#include <iostream>
#include "SimpleBST.h"

int main() {
    SimpleBST<int> bst1;
    SimpleBST<int> bst2;

    int data1[] = {13, 7, 20, 1, 3, 15, 25, 22, 27};
    int data2[] = {13, 1, 20, 3, 15, 25, 7, 27};

    for(int i = 0; i < 9; i++) {
        bst1.insert(data1[i]);
    }
    for(int i = 0; i < 8; i++) {
        bst2.insert(data2[i]);
    }

    std::cout << "*** TREE 1 SHOULD BE PROPER ***" << std::endl;
    std::cout << bst1 << std::endl;
    std::cout << "Tree 1 is " << (bst1.isProper() ? "proper" : "not proper") << std::endl;

    std::cout << "\n\n*** TREE 2 SHOULD NOT BE PROPER ***" << std::endl;
    std::cout << bst2 << std::endl;
    std::cout << "Tree 2 is " << (bst2.isProper() ? "proper" : "not proper") << std::endl;

    return EXIT_SUCCESS;
}