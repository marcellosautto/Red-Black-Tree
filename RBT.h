#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

class rbt
{
public:
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		Node* pnc;
		int num;
		bool black, isLC;
		Node()
		{
			left = nullptr;
			right = nullptr;
			parent = nullptr;
			num = 0;
			isLC = false;
			black = false;
			pnc = nullptr;
		};
		Node(Node* p, int number, bool lc)
		{
			left = nullptr;
			right = nullptr;
			parent = p;
			num = number;
			isLC = lc;
			black = false;
			pnc = nullptr;
		};
	}*root;

	//member variables
	int number;
	HANDLE color;

	//constructor
	rbt();

	//member functions
	void run(),
		menu(),
		displayTree(Node* r, int x, int y, int width);
	struct Node* buildTree(Node* r, Node* p, bool isLC, int n),
		* rightRightRotate(Node* r),
		* leftLeftRotate(Node* r),
		* leftRightRotate(Node* r),
		* rightLeftRotate(Node* r),
		* balanceTree(Node* r);
	int Difference(Node* r);
	int height(Node* r) const;
};