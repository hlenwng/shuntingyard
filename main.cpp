#include <iostream>
#include <cstring>
#include "node.h"

using namespace std;

Node* stackHead = NULL;
Node* queueHead = NULL;

void enqueue(Node* current, char data);
void dequeue(Node* current, Node* &head);
void push(Node* current, char data);
Node* peek(Node* current);
void pop(Node* current);
void buildTree(Node* current);
void infix(Node* current);
void prefix(Node* current);
void postfix(Node* current);

int main() {
  char input[20];
  char tchar;
  char mchar;
  
  for(int i = 0; i < 20; i++) {
    input[i] = 'e';
  }
  
  cout << "symbols: '+' '-' '*' '/' '^' '()'" << endl;
  cout << "only single-digit integers" << endl;
  cout << "Please enter an expression (with a space between each #): ";

  cin.get(input, 20, '\n');
  cin.ignore();

  for (int i = 0; i < strlen(input); i++) {

    if(!isspace(input[i])) {
      if (isdigit(input[i])) {
	//cout << tchar << ": it is a number" << endl;
	//numbers go straight to queue
	enqueue(queueHead, tchar);
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
      
      else if (isdigit(input[i]) == false && input[i] != ')') {
	Node* temp = new Node(input[i]);
	push(temp, stackHead->getCharacter());
      }	
    }
  }


  /*
  
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
  while(current != NULL) {
    cout << current->getCharacter() << " ";
    current = current->getNext();
  }

  while(queueHead != NULL) {
    buildTree(queueHead);
    dequeue(queueHead, queueHead);
  }

  /*
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
  */
// return 0;
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
  if (current == NULL) {
    cout << "Nothing in queue" << endl;
    return;
  }

  else if (current->getNext() != NULL) {
    Node* temp = current->getNext();
    queueHead = NULL;
    delete current;
    queueHead = temp;
  }
}

void push(Node* current, char data) {
  //Push value of new character into list
  
  //If list is empty
  if (current == NULL) {
    stackHead = new Node(data);
  }

  //If id is smaller than head
  else if (current != NULL) {
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    Node* temp = new Node(data);
    current->setNext(temp);
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

/*
void buildTree(Node* current) {
  //add all numbers to stack
  if(isdigit(current->getCharacter())) {
    Node* no = new Node(current->getCharacter());
    push(stackHead, no->getCharacter());
  }

  else if(!isdigit(current->getCharacter())) {
    //in stack, set left and right nodes as top nodes
    Node* no = new Node(current->getCharacter());
    //create new node for left and right
    Node* nRight = new Node(peek(stackHead)->getCharacter());
    nRight->setRight(peek(stackHead)->getRight());
    nRight->setLeft(peek(stackHead)->getLeft());
    no->setRight(nRight);
    pop(stackHead);
    
    Node* nLeft = new Node(peek(stackHead)->getCharacter());
    nLeft->setRight(peek(stackHead)->getRight());
    nLeft->setLeft(peek(stackHead)->getLeft());
    no->setLeft(nLeft);
    pop(stackHead);

    push(stackHead, no->getCharacter());
  }
}

void infix(Node* current) {
  if(current->getLeft() != NULL) {
    cout << "(";
    infix(current->getLeft());
  }

  cout << current->getCharacter() << " ";
  if(current->getRight() != NULL) {
    infix(current->getRight());
    cout << ")";
  }
}

void postfix(Node* current) {
  if (current->getLeft() != NULL) {
    postfix(current->getLeft());
  }
  if(current->getRight() != NULL) {
    postfix(current->getRight());
  }

  //print leaf nodes
  cout << current->getCharacter() << " ";
}

void prefix(Node* current) {
  cout << current->getCharacter() << " ";
  if(current->getLeft() != NULL) {
    prefix(current->getLeft());
  }
  if (current->getRight() != NULL) {
    prefix(current->getRight());
  }
}
*/
