#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree<int> tree;
    tree.InsertLoop(100);
    tree.InsertLoop(50);
    tree.InsertLoop(250);
    tree.InsertLoop(70);
    tree.InsertLoop(30);
    tree.InsertLoop(150);
    tree.InsertLoop(300);

    tree.Print();
}
