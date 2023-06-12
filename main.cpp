#include <iostream>
#include <cstring>

/*
  Name: Helen Wang
  Date: March 17, 2023
  Program: Create an expression tree to read in a mathematical expression.
  Entered as infix notation, can be outputted as a prefix, postfix or infix.
 */

using namespace std;

class Node {
private:
  char data;
  Node* next;
  Node* left;
  Node* right;
  
public:
  Node(char value) {
    data = value;
    next = nullptr;
    left = nullptr;
    right = nullptr;
  }
  
  char getData() {
    return data;
  }
  
  Node* getNext() {
    return next;
  }
  
  void setNext(Node* node) {
    next = node;
  }
  
  Node* getLeft() {
    return left;
  }
  
  void setLeft(Node* node) {
    left = node;
  }
  
  Node* getRight() {
    return right;
  }
  
  void setRight(Node* node) {
    right = node;
  }
};
  
Node* stackHead = NULL;
Node* queueHead = NULL;

void enqueue(Node* current, char data);
void dequeue(Node*& current, Node*& head);
void push(Node*& current, Node* data);
Node* peek(Node* current);
void pop(Node*& current);
void buildTree(Node* current);
void infix(Node* current);
void prefix(Node* current);
void postfix(Node* current);
bool isOperator(char op);
int precedence(char op);

int main() {
  char input[30];
  
  cout << "symbols: '+' '-' '*' '/' '^' '()'" << endl;
  cout << "only single-digit integers" << endl;
  cout << "Please enter an expression (with a space between each #): ";

  cin.get(input, 30, '\n');
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
	
        while (peek(stackHead)->getData() != '(' ) {
          enqueue(queueHead, peek(stackHead)->getData());
          pop(stackHead);
        }
	if(peek(stackHead)->getData() == '(') {
	  pop(stackHead);
	}
      }

      else if (!isdigit(input[i]) && input[i] != '(') {
	//Move operators from stack to queue if precedence is higher
	//FIX (6/11): ADD PRECEDENCE FUNCTION
	while (peek(stackHead) != nullptr && isOperator(peek(stackHead)->getData()) &&
	       precedence(input[i]) <= precedence(peek(stackHead)->getData())) {

	  enqueue(queueHead, peek(stackHead)->getData());
	  pop(stackHead);
	}
	Node* temp = new Node(input[i]);
	push(stackHead, temp);
      }
    }
    //cout << "helen" << endl;
  }  
    
  //cars have been moved
  //binary expression tree

  while(stackHead != NULL) {
    enqueue(queueHead, peek(stackHead)->getData());
    pop(stackHead);
  }

  //print postfix
  cout << "postfix: " << endl;
  Node* current = queueHead;
  
  while(current!= NULL) {  
    cout << current->getData() << " ";
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
      //postfix(root);
      cout << endl;
    }
    else if (strcmp("quit", output) == false) {
      playing = false;
    }
    else {
      cout << "please enter a valid command" << endl;
    }
  }

  //clean up memory
  while(stackHead != NULL) {
    pop(stackHead);
  }

  while(queueHead != NULL) {
    dequeue(queueHead, queueHead);
  }
  
 return 0;
}

void enqueue(Node* current, char data) {
  //Adds element to the end of the queue
  
  Node* newNode = new Node(data);
  
  if (current == nullptr) {
    queueHead = newNode;
  } else {
    // Find end
    while (current->getNext() != nullptr) {
      current = current->getNext();
    }
    current->setNext(newNode);
  }
}

void dequeue(Node*& current, Node*& head) {
  //Remove front node
  // Remove front node
  if (head->getNext() == nullptr) {
    delete head;
    head = nullptr;
  } else {
    Node* temp = head->getNext();
    delete head;
    head = temp;
  }
}

void push(Node*& current, Node* data) {
  //Push value of new character into list
  
  // If list is empty
  if (current == nullptr) {
    current = data;
  }
  // If the list is not empty
  else {
    Node* temp = current;
    while (temp->getNext() != nullptr) {
      temp = temp->getNext();
    }
    temp->setNext(data);
  }
}

Node* peek(Node* current) {
  //Return value of last (top) element in list
  
  if(current == NULL) {
    return NULL;
  }
  while (current->getNext() != NULL) {
    current = current->getNext();
  }
  return current;
}

void pop(Node*& current) {
  //Remove element on top of the stack

  if (current->getNext() == nullptr) {
    delete current;
    current = nullptr;
  } else {
    Node* temp = current;
    while (temp->getNext()->getNext() != nullptr) {
      temp = temp->getNext();
    }
    delete temp->getNext();
    temp->setNext(nullptr);
  }
}

void buildTree(Node* current) {
  // Add all numbers to stack

  if (current == nullptr) {
    return;
  }

  if (isdigit(current->getData())) {
    Node* now = new Node(current->getData());
    push(stackHead, now);
  } else if (!isdigit(current->getData())) {
    if (stackHead == nullptr) {
      //handle the case when the stack is empty
      cout << "Invalid expression" << endl;
      return;
    }
    
    Node* now = new Node(current->getData());
    Node* nRight = new Node(peek(stackHead)->getData());
    nRight->setRight(peek(stackHead)->getRight());
    nRight->setLeft(peek(stackHead)->getLeft());
    now->setRight(nRight);
    pop(stackHead);
    
    if (stackHead == nullptr) {
      //handle the case when the stack becomes empty after popping
      cout << "Invalid expression" << endl;
      return;
    }
    
    Node* nLeft = new Node(peek(stackHead)->getData());
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
    if (isOperator(current->getData())) {
      cout << "(" << " ";
    }
    
    infix(current->getLeft());
    cout << current->getData() << " ";
    infix(current->getRight());
    if (isOperator(current->getData())) {
      cout << ')';
    }
  }
}

void postfix(Node* current) {
  // Print operations after numbers
  if (current != nullptr) {
    postfix(current->getLeft());
    postfix(current->getRight());
    cout << current->getData() << " ";
  }
}

void prefix(Node* current) {
  //print numbers after operations
  if (current != NULL) {
    cout << current->getData() << " ";
    prefix(current->getLeft());
    prefix(current->getRight());
  }
}

//check to see if character is an operation
bool isOperator(char op){
  if(op == '^' || op == '*' || op == '/' || op == '+' || op == '-') {
    return true;
  } else {
    return false;
  }
}

//assign higher priorites to operations
int precedence(char op) {
    if (op == '^') {
        return 3;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '+' || op == '-') {
        return 1;
    } else {
        return 0;
    }
}
