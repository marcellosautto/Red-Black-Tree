//Marcello Sautto
//Date Completed: 4/9/2021

#include "rbt.h"

rbt::rbt()
{
	color = GetStdHandle(STD_OUTPUT_HANDLE);
	number = -1;
	root = nullptr;
}

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

void rbt::displayTree(Node* r, int x, int y, int width)
{
	if (r == nullptr)
		return;
	if (r == root)
	{
		gotoxy(x - 1, y - 1);
		cout << "root";
	}
	gotoxy(x, y);
	//if node has 2 children
	if (r->left != nullptr && r->right != nullptr)
	{
		if (r->black == true)
		{
			SetConsoleTextAttribute(color, 3);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		else
		{
			SetConsoleTextAttribute(color, 4);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		gotoxy(x - width, y + 1);
		for (int i = 1; i <= width; i++)
			cout << "_";
		cout << "||";
		for (int j = 1; j <= width; j++)
			cout << "_";
		gotoxy(x - width, y + 2);
		cout << "|";
		for (int k = 1; k <= (width) * 2; k++)
			cout << " ";
		cout << "|";
	}
	//if theres only a left child
	else if (r->left != nullptr && r->right == nullptr)
	{
		if (r->black == true)
		{
			SetConsoleTextAttribute(color, 3);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		else
		{
			SetConsoleTextAttribute(color, 4);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		gotoxy(x - width, y + 1);
		for (int i = 1; i <= width; i++)
			cout << "_";
		cout << "|";
		gotoxy(x - width, y + 2);
		cout << "|";
		for (int j = 1; j <= width; j++)
			cout << " ";
	}
	//if there's only a right child
	else if (r->left == nullptr && r->right != nullptr)
	{
		if (r->black == true)
		{
			SetConsoleTextAttribute(color, 3);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		else
		{
			SetConsoleTextAttribute(color, 4);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		gotoxy(x, y + 1);
		cout << "|";
		for (int i = 1; i <= width; i++)
			cout << "_";
		gotoxy(x, y + 2);
		for (int j = 1; j <= width; j++)
			cout << " ";
		cout << "|";
	}
	else
	{
		if (r->black == true)
		{
			SetConsoleTextAttribute(color, 3);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
		else
		{
			SetConsoleTextAttribute(color, 4);
			cout << r->num;
			SetConsoleTextAttribute(color, 15);
		}
	}
	displayTree(r->right, x + width, y + 3, width / 2);
	displayTree(r->left, x - width, y + 3, width / 2);
}

void rbt::menu()
{
	cout << "         Red-Black Tree Implemenation \n\n";
	cout << "===================\n";
	cout << "Color Key: \n\n";
	cout << "Black Nodes -> ";
	SetConsoleTextAttribute(color, 3);
	cout << "BLUE\n";
	SetConsoleTextAttribute(color, 15);
	cout << "Red Nodes -> ";
	SetConsoleTextAttribute(color, 4);
	cout << "RED\n";
	SetConsoleTextAttribute(color, 15);
	cout << "===================" << endl << endl;
	cout << "Insert a set of integers into tree and show the red-black tree being built as each node is inseted.\n"
		"Once the tree is completed, you may either enter additional nodes into the tree or you may enter '0' to exit."
		"\n-------------------------------------------------------------------------------------------------------------\n";
}

void rbt::run()
{
	cin >> number;

	if (number > 0)
	{
		//add the user input into the tree
		root = buildTree(root, nullptr, false, number);
		root->black = true;
	}
	else
		return;

	system("cls");
	menu();
	displayTree(root, 110, 20, 20);
	cout << endl << endl << endl << endl << endl;
	Sleep(500);
}

struct rbt::Node* rbt::buildTree(Node* r, Node* p, bool isLC, int n) //insert a node into the tree then balance it
{
	//builds the root
	if (r == nullptr)
	{
		Node* temp = new Node(p, n, isLC);
		if (root == nullptr)
			root = temp;
		return temp;
	}
	//build the rest of the tree based on whether the nodes are greater or less than their parents
	if (n < r->num) { //if the value is less than the current value, go to the left
		r->left = buildTree(r->left, r, true, n);
		r->pnc = r->left; //update children
	}

	else if (n > r->num) { //if the value is greater than the current value, go to the right
		r->right = buildTree(r->right, r, false, n);
		r->pnc = r->right; //update children
	}
	else
		return r;

	//balance the tree once the new node is inserted
	balanceTree(r);
}

struct rbt::Node* rbt::balanceTree(Node* r)
{
	if (r->pnc->pnc != nullptr && !r->pnc->black && !r->pnc->pnc->black)
	{
		//error is in left sub tree
		if (r->pnc->isLC)
		{
			//check if we need to rotate
			if ((r->right == nullptr || r->right->black)) // && r == r->pnc->pnc->parent->parent
			{
				if (Difference(r->left) > 0) //determines if we need to do a single right rotation or a left-right rotation
					return rightRightRotate(r);
				else
					return leftRightRotate(r);
			}
			//left color change
			if (!r->pnc->black && r->left != nullptr && !r->left->black)
			{
				r->pnc->black = true;
				r->right->black = true;
				r->black = false;
			}
		}
		//error is in right subtree
		else if (!r->pnc->isLC)
		{
			//check if we need to rotate
			if (r->left == nullptr || r->left->black)
			{
				if (Difference(r->right) < 0) //determines if we need to do a single left rotation or a right-left rotation
					return leftLeftRotate(r);
				else
					return rightLeftRotate(r);
			}
			//right color change
			if (!r->pnc->black && r->right != nullptr && !r->right->black)
			{
				r->pnc->black = true;
				r->left->black = true;
				r->black = false;
			}
		}
	}
	else
		return r;

}

struct rbt::Node* rbt::leftLeftRotate(Node* r)
{
	//Returns the tree node resulting from
	// a left rotation.
	Node* S = r->right;
	Node* B = S->left;
	S->left = r;
	r->right = B;

	if (S->right != nullptr) //update parents, leftChild, and colors
	{
		//update parents
		S->parent = r->parent;
		S->left->parent = S;
		S->right->parent = S;
		//update lc
		S->left->isLC = true;
		S->right->isLC = false;
		//update colors
		S->black = true;
		S->left->black = false;
	}
	return S;
}

struct rbt::Node* rbt::rightRightRotate(Node* r)
{
	// Returns the tree node resulting from
	// a right rotation.
	Node* S = r->left;
	Node* B = S->right;
	S->right = r;
	r->left = B;

	if (S->left != nullptr) //update parents, leftChild, and colors
	{
		//update parents
		S->parent = r->parent;
		S->left->parent = S;
		S->right->parent = S;
		//update isLC
		S->left->isLC = true;
		S->right->isLC = false;
		//update colors
		S->black = true;
		S->right->black = false;
	}

	return S;
}

struct rbt::Node* rbt::leftRightRotate(Node* r)
{
	// Returns the tree node resulting from a
	// right-left rotation.
	Node* S = r->left;
	r->left = leftLeftRotate(S);
	return rightRightRotate(r);
}

struct rbt::Node* rbt::rightLeftRotate(Node* r)
{
	// Returns the tree node resulting from a
	// right-left rotation.
	Node* S = r->right;
	r->right = rightRightRotate(S);
	return leftLeftRotate(r);
}

int rbt::Difference(Node* r) //takes the difference between the left and right height of a node
{
	return (height(r->left) - height(r->right));
}

int rbt::height(Node* r) const //checks the height of each node
{
	if (r == nullptr)
		return 0;
	else
	{
		int heightLeft = height(r->left);
		int heightRight = height(r->right);
		if (heightLeft > heightRight)
			return heightLeft + 1;
		else
			return heightRight + 1;
	}
}