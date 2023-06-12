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
void dequeue(Node* current, Node*& head);
void push(Node* current, Node* data);
Node* peek(Node* current);
void pop(Node* current);
void buildTree(Node* current);
void infix(Node* current);
void prefix(Node* current);
void postfix(Node* current);
bool isOperator(char op);

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

        //look at stack, move top value until you see a (                             //delete both parenthesis                                                            //keep going until all ( and ) are removed                            //look at stack, move top value until you see a (                                    
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
	  Node* temp = new Node(input[i]);
	  push(stackHead, temp);
      }
      
      /*
      //move ( to stack
      else if (!isdigit(input[i]) && input[i] != '(') {
	//cout << "hi" << endl;
	Node* temp = new Node(input[i]);
	push(temp);
	}	*/
    }
    //cout << "helen" << endl;
  }  
    
  //cars have been moved
  //binary expression tree

    while(stackHead != NULL) {
      if(peek(stackHead)->getData() != '(') {
	enqueue(queueHead, peek(stackHead)->getData());
      }
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
    
 if (current == nullptr) {
        queueHead = new Node(data);
    } else {
        // Find end
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }

        Node* temp = new Node(data);
        current->setNext(temp);
    }
}

  void dequeue(Node* current, Node*& head) {
  //Remove front node
  // Remove front node
    if (current->getNext() == nullptr) {
        head = nullptr;
        delete current;
    } else {
        Node* temp = current->getNext();
	head = NULL;
	delete current;
	head = temp;
    }
}

void push(Node* current, Node* data) {
  //Push value of new character into list
  
  //If list is empty
  if (current == NULL) {
    stackHead = data;
  }
  //If id is smaller than head
  else {
    
    while(current->getNext() != NULL) {
      current = current->getNext();
    }
    //Node* temp = new Node(data);
    current->setNext(data);
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

void pop(Node* current) {
  //Remove element on top of the stack

if (current->getNext() == nullptr) {
        stackHead = nullptr;
        delete current;
    } else {
        while (current->getNext()->getNext() != nullptr) {
            current = current->getNext();
        }

        delete current->getNext();
        current->setNext(nullptr);
    }
}

void buildTree(Node* current) {
  // Add all numbers to stack

  if (isdigit(current->getData())) {
        push(stackHead, current);
    } else if (isOperator(current->getData())) {
        Node* operatorNode = new Node(current->getData());
        operatorNode->setRight(peek(stackHead));
        pop(stackHead);
        operatorNode->setLeft(peek(stackHead));
        pop(stackHead);
        push(stackHead, operatorNode);
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
  //print operations after numbers 

  if(current!= NULL) {
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
