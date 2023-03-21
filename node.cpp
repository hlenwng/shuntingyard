#include "node.h"

Node::Node(char character) {
  value = character;
  next = NULL;
  left = NULL;
  right = NULL;
}

Node::~Node() {
  //delete value;
  next = NULL;
  left = NULL;
  right = NULL;
}

void Node::setNext(Node* newnext) {
  next = newnext;
}

char Node::getCharacter() {
  return value;
}

Node* Node::getNext() {
  return next;
}

void Node::setRight(Node* nRight) {
  right = nRight;
}

Node* Node::getRight() {
  return right;
}

void Node::setLeft(Node* nLeft) {
  left = nLeft;
}

Node* Node::getLeft() {
  return left;
}
