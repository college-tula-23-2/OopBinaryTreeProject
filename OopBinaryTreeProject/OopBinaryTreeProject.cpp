#include <iostream>
#include "BinaryTree.h"

int main()
{
    BinaryTree<int> tree;
    tree.InsertReq(100);
    tree.InsertReq(50);
    tree.InsertReq(250);
    tree.InsertReq(70);
    tree.InsertReq(30);
    tree.InsertReq(150);
    tree.InsertReq(300);
    tree.InsertReq(130);
    tree.InsertReq(280);
    tree.InsertReq(350);
    tree.InsertReq(270);
    tree.InsertReq(290);

    tree.Print();
    std::cout << "\n";

    /*auto node = tree.Find(50);
    tree.RemoveBranch(node);*/

    //auto node = tree.Find(70);
    //auto node = tree.Find(150);
    auto node = tree.Find(250);
    tree.Remove(node);

    tree.Print();
    std::cout << "\n";
}
