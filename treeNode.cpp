#include "treeNode.h"
#include <stdlib.h>

TreeNode::TreeNode(TreeNode* p, char* n){
	c = n;
	parent = p;
	isBlack = true;
	left = NULL;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));//for differentiating which nodes are which, checking by memory locations doesnt work
	//checkng by value doesn't work since there can be duplicates
	//having two inputs be the same id should be astronomically unlikely
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n){
	c = n;
	parent = p;
	isBlack = false;
	left = l;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n){
	c = n;
	parent = p;
	isBlack = false;
	left = l;
	right = r;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));
}

TreeNode::TreeNode(TreeNode* p, char* n, bool c){//SETS COLOR
	c = n;
	parent = p;
	isBlack = c;
	left = NULL;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));//for differentiating which nodes are which, checking by memory locations doesnt work
	//checkng by value doesn't work since there can be duplicates
	//having two inputs be the same id should be astronomically unlikely
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n, bool c){//SETS COLOR
	c = n;
	parent = p;
	isBlack = c;
	left = l;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n, bool c){//SETS COLOR
	c = n;
	parent = p;
	isBlack = c;
	left = l;
	right = r;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/10000000000));
}

TreeNode::~TreeNode(){
	delete c;
}

TreeNode::getSibling(TreeNode* current){
	if(current->getParent() != NULL){
		TreeNode* parent = current->getParent();
		if(parent->getLeft() != NULL && parent->getRight() != NULL){//which is which!!
			if((parent->getLeft())->getID() == current->getID()){//if the left child of parent is the current
				return (parent->getRight());
			}else{//if the right child of parent is the current
				return (parent->getLeft());
			}
		}else{
			return NULL;
		}
	}
}

int TreeNode::isLeftOrRight(TreeNode* current){
	if(current->getParent() != NULL){
		
	}
}

char* TreeNode::getChar(){
	return c;
}
void TreeNode::setChar(char*  n){
	strcpy(c, n);
}

TreeNode* TreeNode::getParent(){
	return parent;
}
void TreeNode::setParent(TreeNode* p){
	parent = p;
}

TreeNode* TreeNode::getLeft(){
	return left;
}
void TreeNode::setLeft(TreeNode* l){
	left = l;
}

TreeNode* TreeNode::getRight(){
	return right;
}
void TreeNode::setRight(TreeNode* r){
	right = r;
}

void TreeNode::setColor(bool black){//true is black, false is red
	isBlack = black;
}

bool TreeNode::isBlack(){//true is black, false is red
	return isBlack;
}

void TreeNode::safeDelete(){//removes references to this and relocates current children to replace itself within tree
	int leftNum = 0;
	int rightNum = 0;
	
	if(getLeft() != NULL){
		leftNum  = convertCharPointerToInt2(getLeft()->getChar());
	}
	
	if(getRight() != NULL){
		rightNum  = convertCharPointerToInt2(getRight()->getChar());
	}


	if(getLeft() == NULL && getRight() == NULL){//no children, easy part
		if(getParent() != NULL){
			if(getParent()->getRight() == NULL){
				getParent()->setLeft(NULL);
				delete this;
			}else if(getParent()->getLeft() == NULL){
				getParent()->setRight(NULL);
				delete this;
			}else{
				
				
				if(getParent()->getLeft()->getID() == getID()){//need to compare memory locations of these two shiite objects
					getParent()->setLeft(NULL);
					delete this;
				}else if(getParent()->getRight()->getID() == getID()){
					getParent()->setRight(NULL);
					delete this;
				}else{//in the extremely rare case that the IDs manage to be equal(insanely unlikely)
					std::cout << "CRITICAL ERROR: PARENT CHILDREN NOT EQUIVELENT TO THIS";
					exit(20);
				}
			}
		}else{
			delete this;
			std::cout << "No more chilren to delete.";
			exit(0);
		}
	}else if(getLeft() != NULL || getRight() != NULL){//left child only , right child only, both
		if(getParent() != NULL){
			
			if(getLeft() != NULL){
				getLeft()->setParent(getParent());
				getParent()->setLeft(getLeft());
			}
			
			if(getRight() != NULL){
				getRight()->setParent(getParent());
				getParent()->setRight(getRight());
			}
			
			delete this;
			
		}else{//needs to find child to swap with and delete so we dont have to delete the head(too much work to deal with)
			TreeNode* tRight = NULL;
			TreeNode* tLeft = NULL;
			
			if(getLeft() != NULL && getRight() != NULL){
				TreeNode* current = this;//this is the head of the entire tree
				current = current->getLeft();
				while(current->getRight() != NULL){
					current = current->getRight();
				}
				this->setChar(current->getChar());
				
				current->safeDelete();
				
			}else if(getLeft() != NULL){//just call safeDelete for left or right children
				setChar(getLeft()->getChar());
				getLeft()->safeDelete();
			}else{
				setChar(getRight()->getChar());
				getRight()->safeDelete();
			}
			
			
			
		}
	}else{
		std::cout <<"Error: safeDelete rare exception";
		exit(20);
	}
}

float TreeNode::getID(){
	return id;
}

int TreeNode::convertCharPointerToInt2(char* c){
	int count = 1;

	int newNum = convertCharToInt2(c[0]);

	while(c[count] != '\0'){
		
		newNum = (newNum * 10) + convertCharToInt2(c[count]);
		count++;
		
	}
	
	return newNum;
}

int TreeNode::getDepth(){
	TreeNode* current = this;
	int depth = 0;
	while(current != NULL){
		if(current->getParent() != NULL){
			depth++;
			current = current->getParent();
		}else{
			return depth;
		}
	}
	return depth;
}

int TreeNode::convertCharToInt2(char c){
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