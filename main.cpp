#include <iostream>
#include <cstring>
#include "node.h"

/*
  Name: Helen Wang
  Date: March 17, 2023
  Program: Create an expression tree to read in a mathematical expression.
  Entered as infix notation, can be outputted as a prefix, postfix or infix.
 */

using namespace std;

Node* stackHead = NULL;
Node* queueHead = NULL;

void enqueue(Node* current, char data);
void dequeue(Node* current, Node* &head);
void push(Node* current, Node* data);
Node* peek(Node* current);
void pop(Node* current);
void buildTree(Node* current);
void infix(Node* current);
void prefix(Node* current);
void postfix(Node* current);
bool isOperator(char op);

int main() {
  char input[20];
  
  cout << "symbols: '+' '-' '*' '/' '^' '()'" << endl;
  cout << "only single-digit integers" << endl;
  cout << "Please enter an expression (with a space between each #): ";

  cin.get(input, 20, '\n');
  cin.ignore();

  for (int i = 0; i < strlen(input); i++) {

    if(!isspace(input[i])) {
      if (isdigit(input[i])) {
	//numbers go straight to queue
	enqueue(queueHead, input[i]);
	//cout << queueHead->getCharacter() << endl;
      }

      else if (input[i] == ')') {

        //look at stack, move top value until you see a (                                    
        //delete both parenthesis                                                            
        //keep going until all ( and ) are removed                                           

        //look at stack, move top value until you see a (                                    
        while (peek(stackHead)->getCharacter() != '(' ) {
          enqueue(queueHead, peek(stackHead)->getCharacter());
          pop(stackHead);
        }
	if(peek(stackHead)->getCharacter() == '(') {
	  pop(stackHead);
	}
      }

      //move ( to stack
      else if (!isdigit(input[i]) && input[i] != ')') {
	//cout << "hi" << endl;
	Node* temp = new Node(input[i]);
	push(stackHead, temp);
      }	
    }
    //cout << "helen" << endl;
  }  
  
  //cars have been moved
  //binary expression tree

  while(stackHead != NULL) {
    if(peek(stackHead)->getCharacter() != '(' ) {
      enqueue(queueHead, peek(stackHead)->getCharacter());
    }
    pop(stackHead);
  }

  //print postfix
  cout << "postfix: " << endl;
  Node* current = queueHead;
  
  while(current!= NULL) {  
    cout << current->getCharacter() << " ";
    current = current->getNext();
  }

  cout << endl;

  //build expression tree
  while(queueHead != NULL) {
    //cout << "work" << endl;
    buildTree(queueHead);
    dequeue(queueHead, queueHead);
  }

  
  bool playing = true;
  while(playing == true) {
    
    char output[10];
    cout << "Print 'infix', 'prefix', 'postfix' or 'quit'"<< endl;
    cin.get(output, 10, '\n');
    cin.ignore();

    if(strcmp("infix", output) == false) {
      infix(stackHead);
      cout << endl;
    }
    else if(strcmp("prefix", output) == false) {
      prefix(stackHead);
      cout << endl;
    }
    else if(strcmp("postfix", output) == false) {
      postfix(stackHead);
      cout << endl;
    }
    else if (strcmp("quit", output) == false) {
      playing = false;
    }
    else {
      cout << "please enter a valid command" << endl;
    }
  }
  
 return 0;
}

void enqueue(Node* current, char data) {
  //Adds element to the end of the queue
    
  if(current == NULL) {
    queueHead = new Node(data);
  }

  else if (current != NULL) {

    //find end
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    
    Node* temp = new Node(data);
    current->setNext(temp);
  }
}

void dequeue(Node* current, Node* &head) {
  //Remove front node
  if (current->getNext() == NULL) {
    queueHead = NULL;
    delete current;
  }

  else if (current->getNext() != NULL) {
    Node* temp = current->getNext();
    queueHead = NULL;
    delete current;
    queueHead = temp;
  }
}

void push(Node* current, Node* data) {
  //Push value of new character into list
  
  //If list is empty
  if (current == NULL) {
    stackHead = data;
  }

  //If id is smaller than head
  else if (current != NULL) {
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    //Node* temp = new Node(data);
    current->setNext(data);
  }
}

Node* peek(Node* current) {
  //Return value of last (top) element in list
  while(current->getNext() != NULL) {
    current = current->getNext();
  }
  return current;
}

void pop(Node* current) {
  //Remove element on top of the stack

  //If there's only 1 value in the stack
  if (current->getNext() == NULL) {
    stackHead = NULL;
    delete current;
  }

  else {
    while (current->getNext()->getNext() != NULL) {
      current = current->getNext();
    }
      
    delete current->getNext();
    current->setNext(NULL);
  }
}

void buildTree(Node* current) {
  //add all numbers to stack
  if(isdigit(current->getCharacter())) {
    Node* now = new Node(current->getCharacter());
    push(stackHead, now);
  }

  else if(!isdigit(current->getCharacter())) {
    //in stack, set left and right nodes as top nodes
    Node* now = new Node(current->getCharacter());
    //create new node for left and right
    Node* nRight = new Node(peek(stackHead)->getCharacter());
    nRight->setRight(peek(stackHead)->getRight());
    nRight->setLeft(peek(stackHead)->getLeft());
    now->setRight(nRight);
    pop(stackHead);
    
    Node* nLeft = new Node(peek(stackHead)->getCharacter());
    nLeft->setRight(peek(stackHead)->getRight());
    nLeft->setLeft(peek(stackHead)->getLeft());
    now->setLeft(nLeft);
    pop(stackHead);

    push(stackHead, now);
  }
}

void infix(Node* current) {
  //print original expression
  if(current != NULL) {
    if (isOperator(current->getCharacter()) == true) {
      cout << '(' << " ";
    }
    infix(current->getLeft());
    cout << current->getCharacter() << " ";
    infix(current->getRight());
    if(isOperator(current->getCharacter()) == true) {
      cout << ')';
    }
  }
}

void postfix(Node* current) {
  //print operations after numbers 
  if (current != NULL) {
    if(current->getLeft() != NULL) {
      postfix(current->getLeft());
    }
    if (current->getRight() != NULL) {
      postfix(current->getRight());
    }
    cout << current->getCharacter() << " ";
  }
}

void prefix(Node* current) {
  //print numbers after operations
  if (current != NULL) {
    cout << current->getCharacter() << " ";
    prefix(current->getLeft());
    prefix(current->getRight());
  }
}

//check to see if character is an operation
bool isOperator(char op){
  if(op == '^' || op == '*' || op == '/' || op == '+' ||
     op == '-') {
    return true;
  } else {
    return false;
  }
}
