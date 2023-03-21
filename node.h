#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
using namespace std;

class Node{
 public:
  Node(char character);
  ~Node();
  void setNext(Node* newnext);
  char getCharacter();
  Node* getNext();
  void setRight(Node* nRight);
  Node* getRight();
  void setLeft(Node* nLeft);
  Node* getLeft();
  
 private:
  char value;
  Node* right;
  Node* left;
  Node* next;
};
#endif
