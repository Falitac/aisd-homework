#pragma once
#include "Node.hpp"

Node* insertBST(Node*& root, int val, Node* father = nullptr);
void printBST(Node* root);
void print2BST(Node* root);
void removeBST(Node*& root, Node* node);
void clearBST(Node* root);

Node* findValueBST(Node* root, int val);

Node* minBST(Node* root);
Node* maxBST(Node* root);

Node* findNextBST(Node* node);
Node* findPrevBST(Node* node);

int getHeightBST(Node* root);