#include "treeNode.h"
#include <iostream>
#include <fstream> 
#include <ctype.h>
#include <cstdlib>
#include <stdio.h>
#include <math.h>

using namespace std;

void seperateInput(char*);
void convertFileInput(char*);
void visualizeTreeUntilMaxDepth(TreeNode* head);
void searchAndDelete(TreeNode*, char*, bool&);
void updateTreeColors(TreeNode*, TreeNode*);

int main(){

	cout << "Would you like to input an a bunch of numbers or a textfile (1 = numbers, 2 = textfile):\n";
	char* input = new char[2];
	cin.getline(input, 2);
	
	if(input[0] == '2'){//textfile input
		
		cout << "Input file name:\n";
		input = new char[100];
		cin.getline(input, 100);
		
		convertFileInput(input);

	}else{//manual input
		
		cout << "Input a bunch of numbers you would like to be in the tree(seperate with single space), will be added one after another:\n";
		input = new char[1000];
		cin.getline(input, 1000);
		
		separateInput(input);
	}
	
}

void updateTreeColors(TreeNode* head, TreeNode* current){
	if(current != NULL){
		if(current == head){//at root of tree
			if(current->isBlack() != true){//assures root is black
				current->setColor(true);
			}
			if(current->getLeft() != NULL){//runs its children
				current = current->getLeft();
				updateTreeColors(head, current);
			}
			
			if(current->getRight() != NULL){
				current = current->getRight();
				updateTreeColors(head, current);
			}
			
		}else if(current->isBlack() != true){//parent is not red and current is red
			TreeNode* parent = current->getParent();//parent should NEVER be null here
			if(parent != NULL){
				TreeNode* sibling = current->getSibling();
				
				if(sibling != NULL){
					if(sibling->isBlack()){
						performRotation();
					}else{
						if(parent->getParent() != NULL){//swaps with parnet
							bool tColor = parent->isBlack();
							parent->setColor((parent->getParent())->isBlack());
							(parent->getParent())->setColor(tColor);
						}else{
							cout << "ERROR: GrandParent is NULL\nupdateTreeColors\n";
							exit(007);//heh
						}
					}
				}else{//this represents empty BLACK leaf, NULLs are black
					performRotation();
				}
			}else{
				cout << "ERROR: Parent is NULL\nupdateTreeColors\n";
				exit(1337);//L E E T
			}
		}
	}else{
		cout << "ERROR: Tree is NULL\nupdateTreeColors\n";
		exit(212);//boiling hot!
	}
}

void performRotation(){
	
}

void createRedBlackTree(char** seperatedInput){
	TreeNode* head = new TreeNode(NULL, seperatedInput[0]);
	int count = 1;//skips 0 since that is the root of tree
	
	while(strcmp(seperatedInput[count], "null") != 0){
		TreeNode* newNode = new TreeNode(NULL, seperatedInput[count]);
		TreeNode* current = head;
		addNumberToTree(head, newNode, current);//default color is red
		current = head;
		updateTreeColors(head, current);
		count++;
	}
	
	
	visualizeTreeUntilMaxDepth(head);
	
	cout << "would you like to delete numbers? (1 = yes, 2 = no) \n";
	char* input = new char[2];
	cin.getline(input, 2);
	
	if(input[0] == '1'){
		while(true){
			cout << "Enter number to delete: ";
			input = new char[6];
			cin.getline(input, 6);
			
			bool numFound = false;
			searchAndDelete(head, input, numFound);
			TreeNode* current = head;
			updateTreeColors(head, current);
			
			cout << endl;
			visualizeTreeUntilMaxDepth(head);
			
			cout << "Would you like to delete something else? (1 = yes, 2 = no)\n";
			input = new char[2];
			cin.getline(input, 2);
			if(input[0] != '1'){
				break;
			}
			
		}
		
	}else{
		exit(420);//lel
	}
	
}

void separateInput(char* input){
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
	
	createRedBlackTree(seperatedInput);
}

void convertFileInput(char* f){
	char* input = new char[10000];
	
	int count = 0;
	ifstream fin(f);
	
	if(fin.is_open()){//THIS CONVERTS INPUT TO A LONG ASS INT ARRAY

		cout << "File Opened successfully!!!. Reading data from file into array" << endl;
		
		while(!fin.eof()){
			char c;
			fin.get(c);
			input[count] = c;
			
			count++;
		}
		
		input[count + 1] = '\0';
		cout << input << endl; 
		separateInput(input);//calls seperate input here
		
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
			if(tCurrent->isBlack()){
				cout << tCurrent->getChar()<< "B" << " || ";
			}else{
				cout << tCurrent->getChar()<< "R" << " || ";
			}
		}else{
			cout << " || ";
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

void searchAndDelete(TreeNode* current, char* input, bool& numberFound){
	if(current != NULL){
		int newNum = convertCharPointerToInt(input);
		int currentNum = convertCharPointerToInt(current->getChar());
		
		if(newNum == currentNum){
			if(!numberFound){
				numberFound = true;
				current->safeDelete();
			}
			
		}else{
			if(current->getLeft() != NULL){
				
				current = current->getLeft();
				searchAndDelete(current, input, numberFound);
				
			}
			
			if(current->getRight() != NULL){
				
				current = current->getRight();
				searchAndDelete(current, input, numberFound);
				
			}
			
		}
		
	}else{
		cout << "Current is NULL" << endl;
	}
	
}
	