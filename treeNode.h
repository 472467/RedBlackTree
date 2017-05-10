#pragma warning
#ifndef TREENODE_H
#define TREENODE_H

#include <string.h>
#include <iostream>

class TreeNode
{
	private:
		TreeNode* parent;
		TreeNode* left;
		TreeNode* right;
		char* c;
		float id;
		bool isBlack;
	
	public:
		TreeNode(TreeNode*, char*);
		TreeNode(TreeNode*, TreeNode*, char*);
		TreeNode(TreeNode*, TreeNode*, TreeNode*, char*);
		~TreeNode();
		TreeNode(TreeNode*, char*, bool);
		TreeNode(TreeNode*, TreeNode*, char*, bool);
		TreeNode(TreeNode*, TreeNode*, TreeNode*, char*, bool);
		char* getChar();
		void setChar(char*);
		void safeDelete();
		void safeDelete2();
		bool hasChildren();
		TreeNode* hasOneChild();
		
		TreeNode* getParent();
		void setParent(TreeNode*);
		
		TreeNode* getLeft();
		void setLeft(TreeNode*);
		
		TreeNode* getRight();
		void setRight(TreeNode*);
		int getDepth();
		int convertCharToInt2(char);
		int convertCharPointerToInt2(char*);
		float getID();
		bool getColor();//true is black
		void setColor(bool);
		bool isLeft();
		TreeNode* getSibling();
		void setID(float);
		TreeNode* getHead(TreeNode*);
};

#endif