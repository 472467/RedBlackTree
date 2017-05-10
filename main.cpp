#include "treeNode.h"
#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

void seperateInput(char*, TreeNode*&);
void convertFileInput(char*, TreeNode*&);
void visualizeTreeUntilMaxDepth(TreeNode* head);
void searchAndDelete(TreeNode*, char*, bool&);
void searchTree(TreeNode*, char*, bool&);
void updateTreeColors(TreeNode*&, TreeNode*, bool&);
void separateInput(char*, TreeNode*&);
void performRotation(TreeNode*);
char* directionsToBalancedNode(int, int, char*&);
int convertCharPointerToInt(char*);
void addNumberToTree(TreeNode*, TreeNode*, TreeNode*);
int convertCharToInt(char);
void checkBottomMismatch(TreeNode*, TreeNode*);
bool isStraightPath(TreeNode*);
void translateInput(char*, TreeNode*&);

int main(){
	cout << "dots in visualization represent empty locations\n";
	
	TreeNode* head = NULL;
	
	while(true){
		char* input = new char[10];
		cout << "\n(i)nsert - inserts number/s into tree // (r)ead - reads inserts input from file into tree\n(s)earch - searches tree for number // (p)rint - prints tree // (d)elete - deletes treeNode\n(q)uit - exits program\n\n";
		cout << "Enter command:" ;
		cin.getline(input, 10);
		
		translateInput(input, head);
	}
}

void translateInput(char* input, TreeNode*& head){
	//char* input = new char[10];
	
	if(strcmp(input, "insert") == 0 || strcmp(input, "i") == 0){
		cout << "Input a number/s you would like to be in the tree(SEPERATE WITH SINGLE SPACE), will be added one after another:\n";
		input = new char[1000];
		cin.getline(input, 1000);
		
		separateInput(input, head);
		
	}else if(strcmp(input, "read") == 0 || strcmp(input, "r") == 0){
		cout << "Input file name(ex: 'john.txt'):\n";
		input = new char[100];
		cin.getline(input, 100);
		
		convertFileInput(input, head);
		
	}else if(strcmp(input, "print") == 0 || strcmp(input, "p") == 0){
		visualizeTreeUntilMaxDepth(head);
	}else if(strcmp(input, "delete") == 0 || strcmp(input, "d") == 0){
		cout << "Input number to delete:\n";
		input = new char[10];
		cin.getline(input, 10);
		
		bool numberFound  = false;
		TreeNode* current = head;
		
		searchAndDelete(current, input, numberFound);//clone of searchTree just deletes number instead of printing
	
	}else if(strcmp(input, "search") == 0 || strcmp(input, "s") == 0){
		cout << "input number you'd like to search for:\n";
		input = new char[10];
		cin.getline(input, 10);
		TreeNode* current = head;
		bool rofl  = false;
		
		searchTree(current, input, rofl);
	}else if(strcmp(input, "quit") == 0 || strcmp(input, "q") == 0){
		exit(999);
	}else{
		cout << "\nUnrecognized command.\n";
	}

	
	delete input;
}

void updateTreeColors(TreeNode*& head, TreeNode* current, bool& updated){
	bool rotated =false;
	if(current != NULL){
		if(current->getParent() == NULL){//at root of tree
			
			if(current->getColor() != true){//assures root is black
				updated = true;
				current->setColor(true);
			}
			
		}else if((current->getParent())->getColor() != true && current->getColor() != true){//parent is red and current is red
			updated = true;
			TreeNode* parent = current->getParent();//parent should NEVER be null here
			TreeNode* sibling = parent->getSibling();
			if(sibling != NULL){
				if(sibling->getColor()){//if true then black
					bool straightPath = isStraightPath(current);
					
					if(straightPath){
						if((current->getParent())->getID() == head->getID()){
							current = current->getParent();
							
							performRotation(current);
							//visualizeTreeUntilMaxDepth(head);
							head = current;

						}else{
							current = current->getParent();
							if(current->getParent() != NULL){
								bool tColor = current->getColor();
								current->setColor((current->getParent())->getColor());
								(current->getParent())->setColor(tColor);
								
							}
							performRotation(current);
							//visualizeTreeUntilMaxDepth(head);
						}
					}else{//only zigzag paths, must have GP
					
						performRotation(current);
						bool tColor = current->getColor();
						current->setColor((current->getParent())->getColor());
						(current->getParent())->setColor(tColor);
						//visualizeTreeUntilMaxDepth(head);
						cout << "Double ";
						performRotation(current);
						//visualizeTreeUntilMaxDepth(head);
						if(head->getParent() != NULL){
							head = head->getParent();
						}
						
					}
					rotated = true;
					
				}else{
					if(parent->getParent() != NULL){//swaps with parnet
						bool tColor = parent->getColor();
						parent->setColor((parent->getParent())->getColor());
						sibling->setColor((parent->getParent())->getColor());
						(parent->getParent())->setColor(tColor);
						
						
					}else{
						cout << "ERROR: GrandParent is NULL\nupdateTreeColors\n";
						exit(007);//heh
					}
				}
			}else{//this represents empty BLACK leaf, NULLs are black
				bool straightPath = isStraightPath(current);
				
				if(straightPath){
					if((current->getParent())->getID() == head->getID()){
						current = current->getParent();
						
						performRotation(current);
						head = current;
						
						
					}else{
						current = current->getParent();
						if(current->getParent() != NULL){
							bool tColor = current->getColor();
							current->setColor((current->getParent())->getColor());
							(current->getParent())->setColor(tColor);
							
						}
						performRotation(current);
					}
				}else{
					if((current->getParent())->getID() == head->getID()){
						performRotation(current);
						
						bool tColor = current->getColor();
						current->setColor((current->getParent())->getColor());
						(current->getParent())->setColor(tColor);
						
						//visualizeTreeUntilMaxDepth(head);
						cout << "Double ";
						performRotation(current);
						head = current;
						//visualizeTreeUntilMaxDepth(head);
						if(head->getParent() != NULL){
							head = head->getParent();
						}
						
					}else{
						
						performRotation(current);
						//visualizeTreeUntilMaxDepth(head);
						cout << "Double ";
						
						bool tColor = current->getColor();
						current->setColor((current->getParent())->getColor());
						(current->getParent())->setColor(tColor);
						
						performRotation(current);
						if(head->getParent() != NULL){
							head = head->getParent();
						}
						//visualizeTreeUntilMaxDepth(head);
					}
				}
				rotated = true;
			}
			
			
		}
		if(head->getParent() != NULL){
			head = head->getParent();
		}
		if(current->getParent() != NULL){//runs its children
			current = current->getParent();
			updateTreeColors(head, current, updated);
			
		}
		
		
		
	}else{
		cout << "ERROR: Tree is NULL\nupdateTreeColors\n";
		exit(212);//boiling hot!
	}
	
}

bool isStraightPath(TreeNode* current){
	TreeNode* p = current->getParent();
	TreeNode* gp = p->getParent();
	bool gpToP = p->isLeft();
	bool pToCurrent = current->isLeft();
	
	if(gp == NULL){
		return true;
	}
	
	if(gpToP == pToCurrent){// both false or both true
		return true;
	}else{
		return false;
	}
	
}

void performRotation(TreeNode* current){
	if(current->getParent() != NULL){
		bool tColor = current->getColor();
		//current->setColor((current->getParent())->getColor());
		//(current->getParent())->setColor(tColor);
		
		if(current->isLeft()){//rotates right, never rotates the root(i think)
			cout << "right rotation on " << current->getChar() << "\n";
		
			TreeNode* p = current->getParent();
			TreeNode* gp = p->getParent();
			TreeNode* r = current->getRight();
		
			if(gp != NULL){
				if(p->isLeft()){//gp 1/2
					gp->setLeft(current);//gets wrong one!
				}else{
					gp->setRight(current);
				}
			}
			
			current->setParent(gp);//gp 2/2
			current->setRight(p);//p 1/2
			p->setLeft(r);
			p->setParent(current);
			if(r != NULL){
				r->setParent(p);
			}
			
		}else{//rotates left
		
			cout << "left rotation on " << current->getChar() << "\n";
			TreeNode* p = current->getParent();
			TreeNode* gp = p->getParent();
			TreeNode* l = current->getLeft();
			
			if(gp != NULL){
				if(p->isLeft()){
					gp->setLeft(current);
				}else{
					gp->setRight(current);
				}
			}
			
			current->setParent(gp);//if null sets to null
			current->setLeft(p);
			p->setRight(l);
			p->setParent(current);
			if(l != NULL){
				l->setParent(p);
			}
			
		}
		
		
	}
}


void checkBottomMismatch(TreeNode* head, TreeNode* current){
	bool outdatedInput = false;
	if(current != NULL){
		if(current->getLeft() != NULL){
			TreeNode* tCurrent = current;
			current = current->getLeft();
			checkBottomMismatch(head, current);
			current = tCurrent;
		}
		
		if(current->getRight() != NULL){
			TreeNode* tCurrent = current;
			current = current->getRight();
			checkBottomMismatch(head, current);
			current = tCurrent;
		}
		
		if(current->getRight() == NULL && current->getLeft() == NULL){
			updateTreeColors(head, current, outdatedInput);
		}
	}
}

void createRedBlackTree(char** seperatedInput, TreeNode*& head){
	int count = 0;
	if(head == NULL){
		head = new TreeNode(NULL, seperatedInput[0], true);
		count = 1;//skips 0 since that is the root of tree
	}
	
	//visualizeTreeUntilMaxDepth(head);
	while(strcmp(seperatedInput[count], "null") != 0){
		cout << "RUN ==== " << count << endl;
		TreeNode* newNode = new TreeNode(NULL, seperatedInput[count]);
		
		TreeNode* current = head;
		addNumberToTree(head, newNode, current);//default color is red
		bool updated = false;
		if(newNode->getParent() == NULL){
			newNode->setColor(true);
		}
		updateTreeColors(head, newNode, updated);
		updateTreeColors(head, newNode, updated);
		//visualizeTreeUntilMaxDepth(head);
		//checkBottomMismatch(head, current);
		count++;
	}
	
}

void separateInput(char* input, TreeNode*& head){
	int count = 0;
	int currentLength = 0;
	int numberAmount = 0;
	
	char** seperatedInput = new char*[1000];
	
	for(int x = 0; x < 1000; x++){
		seperatedInput[x] = new char[40];
		strcpy(seperatedInput[x], "null");
	}
	char* currentNum = new char[5];
	
	
	while(input[count] != '\0'){
		char c = input[count];
		
		if(c == ' ' || c == '\n'){
			
			if(currentLength > 0){
				seperatedInput[numberAmount][currentLength] = '\0';
				
				currentLength = 0;
				numberAmount++;
			}
			
		}else{
			seperatedInput[numberAmount][currentLength] = c;
			currentLength++;
			
			if(input[count] != '\0'){
				seperatedInput[numberAmount][currentLength] = '\0';
			}
		}
		
		
		count++;
	}
	
	createRedBlackTree(seperatedInput, head);
}

void convertFileInput(char* f, TreeNode*& head){
	char* input = new char[10000];
	
	int count = 0;
	ifstream fin(f);
	
	if(fin.is_open()){//THIS CONVERTS INPUT TO A LONG ASS INT ARRAY

		cout << "File Opened successfully!!! Reading data from file into array." << endl;
		
		while(!fin.eof()){
			char c;
			fin.get(c);
			input[count] = c;
			
			count++;
		}
		
		input[count - 1] = '\0';//magic
		cout << input << endl; 
		separateInput(input, head);//calls seperate input here
		
	}
	else //file could not be opened
	{
		cout << "File could not be opened." << endl;
	}
}

void visualizeTreeUntilMaxDepth(TreeNode* head){
	int currentDepth = 0;
	int depthProgression = 1;
	TreeNode* tCurrent = head;
	bool allNull = false;
	int nullCounter = 0;
	if(head == NULL){
		allNull  = true;
		cout << "ERROR: trying to print null tree\n\n";
	}
	while(!allNull){
		
		char* directions;
		directionsToBalancedNode(currentDepth, depthProgression, directions);//sets direction
		int count = 0;
		while(directions[count] != '\0'){//adds newNode to the most balanced spot by following the directions provided
			if(directions[count] == 'L'){
				if(tCurrent->getLeft() != NULL){
					tCurrent = tCurrent->getLeft();
					
				}else{
					nullCounter++;
					tCurrent = NULL;
					break;
				}
				
			}else{
				if(tCurrent->getRight() != NULL){
					tCurrent = tCurrent->getRight();
				}else{
					nullCounter++;
					tCurrent = NULL;
					break;
				}
			}

			count++;
		}
		
		if(depthProgression == 1){
			cout << currentDepth << ": ";
			
		}
		if(tCurrent != NULL){
			if(tCurrent->getColor()){
				cout << tCurrent->getChar()<< "B" << "";
			}else{
				cout << tCurrent->getChar()<< "R" << "";
			}
			//cout << " " <<tCurrent->getID() <<  "|";
		}else{
			cout << ".";
		}
		
		if(nullCounter == pow(2, currentDepth)){
			allNull = true;
			break;
		}
		
		depthProgression++;
		if(depthProgression > pow(2, currentDepth)){//designates where the most balanced spot on the tree to add next
			nullCounter = 0;
			depthProgression = 1;
			currentDepth++;
			cout << "\n";
		}
		tCurrent = head;
	}
	
	cout << "\n\n";
}

void searchTree(TreeNode* current, char* input, bool& numberFound){
	if(current != NULL){
		int newNum = convertCharPointerToInt(input);
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum == currentNum){
			if(!numberFound){
				numberFound = true;
				if(current->getParent() != NULL){
					cout << currentNum << " was found in the tree. Parent: " << (current->getParent())->getChar() << endl; 
					if(current->getLeft() != NULL){
						cout << "LeftChild: " << (current->getLeft())->getChar() << endl;
					}else{
						cout << "LeftChild: NULL\n" ;// << (current->getLeft())->getChar();
					}
					
					if(current->getRight() != NULL){
						cout << "RightChild: " << (current->getRight())->getChar() << endl;
					}else{
						cout << "RightChild: NULL\n" ;// << (current->getLeft())->getChar();
					}
				}else{
					cout << currentNum << " was found in the tree. Parent: NULL" << endl; 
				}
				
			}
			
		}else{
			if(newNum >= currentNum){
				if(current->getRight() != NULL){
					current = current->getRight();
					searchTree(current, input, numberFound);
				}
			}else{
				if(current->getLeft() != NULL){
					current = current->getLeft();
					searchTree(current, input, numberFound);
					
				}
			}
			
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
	
}



void searchAndDelete(TreeNode* current, char* input, bool& numberFound){
	if(current != NULL){
		int newNum = convertCharPointerToInt(input);
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum == currentNum){
			if(!numberFound){
				numberFound = true;
				current->safeDelete2();
				if(current->getColor() == false){//if red just delete the mofo
					
				}else{
					
				}
				
			}
			
		}else{
			if(newNum >= currentNum){
				if(current->getRight() != NULL){
					current = current->getRight();
					
					searchAndDelete(current, input, numberFound);
				}
			}else{
				if(current->getLeft() != NULL){
					current = current->getLeft();
					searchAndDelete(current, input, numberFound);
					
				}
			}
			
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
	
}

int convertCharPointerToInt(char* c){
	int count = 1;

	int newNum = convertCharToInt(c[0]);

	while(c[count] != '\0'){
		
		newNum = (newNum * 10) + convertCharToInt(c[count]);
		count++;
		
	}
	
	return newNum;
}
	
	
void addNumberToTree(TreeNode* head, TreeNode* newNode, TreeNode* current){
	if(current != NULL){
		
		
		int newNum = convertCharPointerToInt(newNode->getChar());
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum >= currentNum){
			if(current->getRight() != NULL){
				
				current = current->getRight();
				addNumberToTree(head, newNode, current);
				
			}else{
				
				current->setRight(newNode);
				newNode->setParent(current);
			}
			
		}else{
			if(current->getLeft() != NULL){
				
				current = current->getLeft();
				addNumberToTree(head, newNode, current);
				
			}else{
				
				current->setLeft(newNode);
				newNode->setParent(current);
				
			}
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
		
	
}
	
char* directionsToBalancedNode(int currentDepth, int depthProgression, char*& directions){//this gives directions to next balanced node in the heap
	directions = new char[currentDepth + 1];
	
	for(int x  = currentDepth; x > 0; x--){//builds upwards from the designated location
		if(depthProgression % 2 ==  0){
			directions[x - 1] = 'R';
		}else{
			directions[x - 1] = 'L';
		}
		int newProgression = 1;
		int tProgression =  depthProgression;// 2
		bool running = true;
		
		while(running){
			tProgression =  tProgression -2;
			if(tProgression > 0){
				//cout << tProgression << "TProg"<< endl;
				newProgression++;
			}else{
				//cout << newProgression << endl;
				running = false;
			}
		}
		depthProgression = newProgression;
	}
	directions[currentDepth] = '\0';
	
	return directions;
}
	
int convertCharToInt(char c){
	//cout << c;
	if(c == '0'){
		return 0;
	}else if(c == '1'){
		return 1;
	}else if(c == '2'){
		return 2;
	}else if(c == '3'){
		return 3;
	}else if(c == '4'){
		return 4;
	}else if(c == '5'){
		return 5;
	}else if(c == '6'){
		return 6;
	}else if(c == '7'){
		return 7;
	}else if(c == '8'){
		return 8;
	}else if(c == '9'){
		return 9;
	}
	
	//cout << "error";
	return NULL;
}