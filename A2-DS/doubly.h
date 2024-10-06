#pragma once
#include <iostream>
#include <Windows.h>


void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
class CharacterNode {
private:
	char letter;
	int col;
	int line;
	static int currCol;
	static int currLine;
	CharacterNode* left;
	CharacterNode* right;
	CharacterNode* up;
	CharacterNode* down;
public:
	CharacterNode(const char newLetter =  ' ', int c = currCol, int ln = currLine, CharacterNode* l = nullptr, CharacterNode* r = nullptr,
		CharacterNode* u = nullptr, CharacterNode* d = nullptr) 
		: letter(newLetter), left(l), right(r), up(u), down(d),col(c), line(ln){}
	char getLetter() const
	{
		return letter;
	}
	int getCol() const
	{
		return col;
	}
	int getLine() const
	{
		return line;
	}
	static int getCurrCol() 
	{
		return currCol;
	}
	static int getCurrLine()
	{
		return currLine;
	}
	CharacterNode* getLeft() const
	{
		return left;
	}
	CharacterNode* getRight() const
	{
		return right;
	}
	CharacterNode* getUp() const
	{
		return up;
	}
	CharacterNode* getDown() const
	{
		return down;
	}
	void setLetter(char l)
	{
		letter = l;
	}
	void setLeft(CharacterNode* l)
	{
		left = l;
	}
	void setRight(CharacterNode* r)
	{
		right = r;
	}
	void setUp(CharacterNode* u)
	{
		up = u;
	}
	void setDown(CharacterNode* d)
	{
		down = d;
	}
	void setCol(const int c)
	{
		col = c;
	}
	void setLine(const int l)
	{
		line = l;
	}
	static void setCurrCol(int c) 
	{
		currCol = c;
	}
	static void setCurrLine(int ln) 
	{
		currLine = ln;
	}

};
int CharacterNode::currCol = 1;
int CharacterNode::currLine = 3;

class LinkList2D {
private:
	CharacterNode* head;
	CharacterNode* currentCol;
	CharacterNode* currentLine;
	int inputAreaWidth;
	int inputAreaHeight;
public:
	LinkList2D(int width = 125 * 0.8, int height = 30 * 0.8, CharacterNode* h = nullptr, CharacterNode* currCol = nullptr,
		CharacterNode* currLine = nullptr);// : inputAreaWidth(width), inputAreaHeight(height), head(h),
		//currentCol(currCol), currentLine(currLine) {}
	bool isEmpty()
	{
		/*if (head == nullptr)
		{
			return 1;
		}*/
		return head == nullptr;
	}
	CharacterNode* getHead()
	{
		return head;
	}
	CharacterNode* getCurrCol()
	{
		return currentCol;
	}
	CharacterNode* getCurrLine()
	{
		return currentLine;
	}
	void setHead(CharacterNode* n)
	{
		head = n;
	}
	void setCurrCol(CharacterNode* n)
	{
		currentCol = n;
	}
	void setCurrLine(CharacterNode* n)
	{
		currentLine = n;
	}
	void cursorUpdate(int c, int l)
	{
		CharacterNode::setCurrCol(c);
		CharacterNode::setCurrLine(l);
	}
	//real funcs
	void addLetter(char newLetter);
	void newLine();
	void handleBackspace();
	void deleteNode();
	void printList();
	void moveCursorLeft();
	void moveCursorRight();
	void moveCursorUp();
	void moveCursorDown();
};

LinkList2D::LinkList2D(int width, int height, CharacterNode* h, CharacterNode* currCol, CharacterNode* currLine) 
	: inputAreaWidth(width), inputAreaHeight(height), head(h), currentCol(currCol), currentLine(currLine)
{

}
void LinkList2D::addLetter(char newLetter)
{
	if (isEmpty())
	{
		head = new CharacterNode(newLetter, CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
		currentCol = head;
		currentLine = head;
	}
	else
	{
		if (currentCol->getLetter() == '\0') //handles special case of newLine
		{
			currentCol->setLetter(newLetter);  // Update the letter in the existing node
		}
		else
		{

			if (CharacterNode::getCurrCol() == inputAreaWidth - 1) //edge case of right boundary
			{
				//move to next line and reset column
				//CharacterNode::setCurrLine(CharacterNode::getCurrLine() + 1);
				//CharacterNode::setCurrCol(1);
				cursorUpdate(1, CharacterNode::getCurrLine() + 1);
				//make new Node
				CharacterNode* newNode = new CharacterNode(newLetter, CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
				//link node to vertical nodes
				currentLine->setDown(newNode);
				newNode->setUp(currentLine);
				// Update
				currentCol = newNode;
				currentLine = newNode;
			}
			else
			{
				//make new Node and initialize it
				CharacterNode* newNode = new CharacterNode(newLetter, CharacterNode::getCurrCol(), CharacterNode::getCurrLine());

				currentCol->setRight(newNode);
				newNode->setLeft(currentCol);

				CharacterNode* lineAbove = currentLine->getUp();
				int targetColumn = CharacterNode::getCurrCol();
				//traverse to column above of above line if it exists
				while (lineAbove != nullptr && lineAbove->getCol() < targetColumn)
				{
					lineAbove = lineAbove->getRight();
				}
				// Link the new node to the node above (if it exists)
				if (lineAbove != nullptr && lineAbove->getCol() == targetColumn)
				{
					newNode->setUp(lineAbove);
					lineAbove->setDown(newNode);
				}
				//move current to new Node in list
				currentCol = newNode;
			}
		}
	}
	//increment column
	//CharacterNode::setCurrCol(CharacterNode::getCurrCol() + 1);
	cursorUpdate(CharacterNode::getCurrCol() + 1, CharacterNode::getCurrLine());
}
void LinkList2D::newLine()
{
	//move to next line and reset column
	cursorUpdate(1, CharacterNode::getCurrLine() + 1);
	//make new Node
	CharacterNode* newNode = new CharacterNode('\0', CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
	//link up and down
	if (currentLine != nullptr)
	{
		currentLine->setDown(newNode);  // Link vertically to the new line
		newNode->setUp(currentLine);    // Link vertically upwards
	}
	//update current line and column
	currentLine = newNode;
	currentCol = newNode;

}
void LinkList2D::handleBackspace()
{
	if (currentCol != nullptr && currentCol->getLeft() != nullptr)
	{
		// Move cursor to the left of the character we want to delete
		gotoxy(currentCol->getCol(), currentCol->getLine());
		std::cout << ' ';  // Overwrite with a space (erase)

		// Update the linked list by removing the node
		deleteNode();  // Your deleteNode function that updates the list

		// Move the cursor back to the new currentCol position
		gotoxy(currentCol->getCol(), currentCol->getLine());
	}
}
void LinkList2D::deleteNode()
{
	if (currentCol == nullptr) return; // No node to delete
	//horizontal
	if (currentCol->getLeft() != nullptr)
	{
		currentCol->getLeft()->setRight(currentCol->getRight());
	}
	if (currentCol->getRight() != nullptr)
	{
		currentCol->getRight()->setLeft(currentCol->getLeft());
	}
	//vertical
	if (currentCol->getUp() != nullptr)
	{
		currentCol->getUp()->setDown(currentCol->getDown());
	}
	if (currentCol->getDown() != nullptr)
	{
		currentCol->getDown()->setUp(currentCol->getUp());
	}
	//if deleting head
	if (currentCol == head)
	{
		head = currentCol->getRight() != nullptr ? currentCol->getRight() : currentCol->getDown();
	}

	// Move cursor to the left node (or to the right if no left node exists)
	CharacterNode* temp = (currentCol->getLeft() != nullptr) ? currentCol->getLeft() : currentCol->getRight();

	/*currentCol->getLeft()->setRight(currentCol->getRight());
	CharacterNode* temp = currentCol->getLeft();*/
	delete currentCol;
	currentCol = temp;
}
void LinkList2D::printList()
{
	if (isEmpty())
	{
		return;
	}
	CharacterNode* currentR = head;
	while (currentR != nullptr)
	{
		CharacterNode* currentC = currentR;
		while (currentC != nullptr)
		{
			gotoxy(currentC->getCol(), currentR->getLine());
			std::cout << currentC->getLetter();
			currentC = currentC->getRight();
		}
		currentR = currentR->getDown();
	}
}
void LinkList2D::moveCursorLeft()
{
	if (currentCol->getLeft() != nullptr)  // Check if there's a node to the left
	{
		currentCol = currentCol->getLeft();
		gotoxy(currentCol->getCol(), currentCol->getLine());  // Move the cursor on screen
	}
}
void LinkList2D::moveCursorRight()
{
	if (currentCol->getRight() != nullptr)  // Check if there's a node to the right
	{
		currentCol = currentCol->getRight();
		gotoxy(currentCol->getCol(), currentCol->getLine());
	}
}
void LinkList2D::moveCursorUp()
{
	if (currentCol->getUp() != nullptr)  // Check if there's a node above
	{
		currentCol = currentCol->getUp();
		gotoxy(currentCol->getCol(), currentCol->getLine());
	}
}
void LinkList2D::moveCursorDown()
{
	if (currentCol->getDown() != nullptr)  // Check if there's a node below
	{
		currentCol = currentCol->getDown();
		gotoxy(currentCol->getCol(), currentCol->getLine());
	}
}

