#include "treeNode.h"
#include <stdlib.h>

TreeNode::TreeNode(TreeNode* p, char* n){
	c = n;
	parent = p;
	isBlack = false;
	left = NULL;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));//for differentiating which nodes are which, checking by memory locations doesnt work
	//checkng by value doesn't work since there can be duplicates
	//having two inputs be the same id should be astronomically unlikely
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n){
	c = n;
	parent = p;
	isBlack = false;
	left = l;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n){
	
	c = n;
	parent = p;
	isBlack = false;
	left = l;
	right = r;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));
}

TreeNode::TreeNode(TreeNode* p, char* n, bool col){//SETS COLOR
	c = n;
	parent = p;
	isBlack = col;
	left = NULL;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));//for differentiating which nodes are which, checking by memory locations doesnt work
	//checkng by value doesn't work since there can be duplicates
	//having two inputs be the same id should be astronomically unlikely
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, char* n, bool col){//SETS COLOR
	c = n;
	parent = p;
	isBlack = col;
	left = l;
	right = NULL;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));
}

TreeNode::TreeNode(TreeNode* p, TreeNode* l, TreeNode* r, char* n, bool col){//SETS COLOR
	c = n;
	parent = p;
	isBlack = col;
	left = l;
	right = r;
	id = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100000));
}

TreeNode::~TreeNode(){
	delete c;
}

TreeNode* TreeNode::getSibling(){
	TreeNode* current = this;
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

bool TreeNode::isLeft(){//returns true if left false if right
	TreeNode* current = this;
	if(current->getParent() != NULL){
		TreeNode* p = current->getParent();
		if((p->getLeft()) == NULL){//parent's left is NULL(meaning its right
			return false;
		}else if(this->getID() == (p->getLeft())->getID()){//is the left
			//std::cout << this->getID() << " " <<(p->getLeft())->getID() << "\n";
			return true;
		}else{//right is null or not the same ID
			return false;
		}
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
TreeNode* TreeNode::getHead(TreeNode* current){
	if(current->getParent() != NULL){
		current = current->getParent();
		return getHead(current);
	}else{
		return getHead(current);
	}
	
}

void TreeNode::setColor(bool black){//true is black, false is red
	isBlack = black;
}

bool TreeNode::getColor(){//true is black, false is red
	return isBlack;
}

void TreeNode::safeDelete2(){//BINARY DELETE FIRST THEN FIX THE NODES IT SCREWS UP
	TreeNode* left = getLeft();
	TreeNode* right = getRight();
	TreeNode* selectedReplacement = NULL;
	
	if(left == NULL && right == NULL){//no children, NEED DOUBLE BLACK FIX
		if(parent != NULL){
			if((getParent()->getLeft())->getID() == getID()){
				getParent()->setLeft(NULL);
			}else{
				getParent()->setRight(NULL);
			}
		}
		
		if(!getColor()){
			delete this;
		}else{//double black
			//this will be replaced by a double black NULL
			
			if(getParent() != NULL){
				if(getSibling()->getColor() && oneRedChild(getSibling())){//sibling is black and has one red child
					if(
					
				}
			}else{
				std::cout << "ERROR: Trying to delete the last node, deletion aborted.\n";
			}
			
			delete this;
		}
	}else if(left == NULL && right != NULL){//one right child, DONE
		right->setParent(getParent());
		if(parent != NULL){
			if((getParent()->getLeft())->getID() == getID()){
				getParent()->setLeft(right);
			}else{
				getParent()->setRight(right);
			}
		}
		
		if(!getColor()){//impossible to have only one child and for it and parent to be black
			delete this;
		}else{
			right->setColor(true);
		}
		
	}else if(left != NULL && right == NULL){//one left child, DONE
		right->setParent(getParent());
		if(parent != NULL){
			if((getParent()->getLeft())->getID() == getID()){
				getParent()->setLeft(left);
			}else{
				getParent()->setRight(left);
			}
		}
		
		if(!getColor()){//impossible to have only one child and for it and parent to be black
			delete this;
		}else{
			left->setColor(true);
		}
		
	}else{//two children!, NEED DOUBLE BLACK FIX
		TreeNode* successor = right;// find successor( go right once then left until NULL
		while(successor->getLeft() != NULL){
			successor = successor->getLeft();
		}
		char* charStorage = successor->getChar();
		successor->setChar(getChar());
		setChar(charStorage);
		
		if(successor->getRight() != NULL){
			if((successor->getParent())->getID() != getID()){//means that successor isnt the right child of this
				successor->getParent()->setLeft(successor->getRight());
			}else{
				setRight(successor->getRight());
			}
			
			successor->getRight()->setParent(successor->getParent());
		}else{
			if((successor->getParent())->getID() != getID()){//means that successor isnt the right child of this
				successor->getParent()->setLeft(successor->getRight());
			}else{
				setRight(successor->getRight());
			}
		}
		
		if(!successor->getColor()){
			delete this;
		}else{//double black
			
		}
		
	}
}

bool TreeNode:oneRedChild(TreeNode* current){
	if(current->getLeft() != NULL){
		if(!(current->getLeft())->getColor()){
			return true;
		}
	}
	
	if(current->getRight() != NULL){
		if(!(current->getRight())->getColor()){
			return true;
		}
	}
	
	return false;
}

void TreeNode::performRotation(){
	TreeNode* current = this;
	
	if(current->getParent() != NULL){
		bool tColor = current->getColor();
		//current->setColor((current->getParent())->getColor());
		//(current->getParent())->setColor(tColor);
		
		if(current->isLeft()){//rotates right, never rotates the root(i think)
			std::cout << "right rotation on " << current->getChar() << "\n";
		
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
		
			std::cout << "left rotation on " << current->getChar() << "\n";
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

TreeNode* TreeNode::hasOneChild(){
	if(getRight() != NULL && getLeft() != NULL){
		return NULL;
	}else if(getRight() == NULL && getLeft() == NULL){
		return NULL;
	}
	if(getRight() != NULL){
		return getRight();
	}
	
	if(getLeft() != NULL){
		return getLeft();
	}
	
	return NULL;
}

bool TreeNode::hasChildren(){
	if(getRight() != NULL){
		return true;
	}
	
	if(getLeft() != NULL){
		return true;
	}
	
	return false;
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
					std::cout << "CRITICAL ERROR: ASTRONOMICAL ID MISMATCH(restart)";
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

void TreeNode::setID(float id2){
	id = id2;
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