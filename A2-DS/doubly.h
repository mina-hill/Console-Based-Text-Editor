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
	int cursorX;  
	int cursorY;
public:
	LinkList2D(int width = 125 * 0.8, int height = 30 * 0.8, CharacterNode* h = nullptr, CharacterNode* currCol = nullptr,
		CharacterNode* currLine = nullptr); // : inputAreaWidth(width), inputAreaHeight(height), head(h),
		//currentCol(currCol), currentLine(currLine) {}
	bool isEmpty()
	{
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
	void cursorUpdate(int c, int l);
	//real funcs
	void addLetter(char newLetter);
	void newLine();
	void handleBackspace();
	void deleteNode();
	void printList(int x=1,int y=3);
	void moveCursorLeft();
	void moveCursorRight();
	void moveCursorUp();
	void moveCursorDown();
	void updateColsAndRows();
	void printAroundCursor(int radius);
};

LinkList2D::LinkList2D(int width, int height, CharacterNode* h, CharacterNode* currCol, CharacterNode* currLine) 
	: cursorX(1), cursorY(2), inputAreaWidth(width), inputAreaHeight(height), head(h), currentCol(currCol), currentLine(currLine)
{
	//head = new CharacterNode(); // Dummy head node
	//currentCol = head;
	//currentCol->setRight(new CharacterNode()); //dummy node in next
	//acurrentLine = head;
	cursorUpdate(cursorX, cursorY);
}
//void LinkList2D::addLetter(char newLetter)
//{
//	if (isEmpty())
//	{
//		head = new CharacterNode(newLetter, cursorX, cursorY);
//		currentCol = head;
//		currentLine = head;
//	}
//	else
//	{
//		if (currentCol->getLetter() == '\0') // Special case for new line
//		{
//			currentCol->setLetter(newLetter);
//		}
//		else
//		{
//			if (cursorX == inputAreaWidth - 1) // Edge case for right boundary
//			{
//				cursorUpdate(1, cursorY + 1); // Move to next line and reset column
//			}
//			else
//			{
//				// Insert the new node at the cursor position
//				CharacterNode* newNode = new CharacterNode(newLetter, cursorX, cursorY);
//				newNode->setRight(currentCol->getRight());
//				if (currentCol->getRight() != nullptr)
//				{
//					currentCol->getRight()->setLeft(newNode);
//				}
//				currentCol->setRight(newNode);
//				newNode->setLeft(currentCol);
//				currentCol = newNode;
//			}
//		}
//	}
//	cursorUpdate(cursorX + 1, cursorY); // Move cursor to next position
//}

void LinkList2D::addLetter(char newLetter)
{
	//int prevX = cursorX;
	//int prevY = cursorY;
	if (isEmpty())
	{
		head = new CharacterNode(newLetter, cursorX,cursorY);
		currentCol = head;
		currentLine = head;
		gotoxy(cursorX, cursorY);  // Move to the current position
		std::cout << newLetter;  // Print the new letter
		//cursorX++;
	}
	else
	{
		if (currentCol->getLetter() == '\n') //handles special case of newLine
		{
			currentCol->setLetter(newLetter);  // Update the letter in the existing node
		}
		else
		{

			if (CharacterNode::getCurrCol() == inputAreaWidth - 1) //edge case of right boundary
			{
				cursorUpdate(1, cursorY + 1);
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
				CharacterNode* newNode = new CharacterNode(newLetter, cursorX, cursorY);//CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
				//updating cols of each node on the right
				CharacterNode* temp = currentCol->getRight();
				while (temp != nullptr) {
					temp->setCol(temp->getCol() + 1);  // Increment the column for each node to the right
					temp = temp->getRight();
				}
				//link node horizontally
				newNode->setRight(currentCol->getRight());
				if (currentCol->getRight() != nullptr) 
				{
					currentCol->getRight()->setLeft(newNode);
				}
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
	//gotoxy(cursorX, cursorY);  // Move to the current position
	//std::cout << newLetter;  // Print the new letter
	cursorX++;
	//printAroundCursor(1);
	cursorUpdate(cursorX, cursorY); 
}
void LinkList2D::newLine()
{
	//move to next line and reset column
	//cursorUpdate(1, CharacterNode::getCurrLine() + 1);
	cursorY++;
	cursorX = 1;
	cursorUpdate(cursorX, cursorY);
	//make new Node
	CharacterNode* newNode = new CharacterNode('\n', cursorX, cursorY);
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
	//updating cols of each node on the right
	CharacterNode* temp = currentCol->getRight();
	while (temp != nullptr) 
	{
		temp->setCol(temp->getCol() - 1);  // Increment the column for each node to the right
		temp = temp->getRight();
	}
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
	temp = (currentCol->getLeft() != nullptr) ? currentCol->getLeft() : currentCol->getRight();

	/*currentCol->getLeft()->setRight(currentCol->getRight());
	CharacterNode* temp = currentCol->getLeft();*/
	delete currentCol;
	currentCol = temp;
	cursorX--;
	cursorUpdate(cursorX, cursorY);
	//updateColsAndRows();
}
void LinkList2D::updateColsAndRows()
{
	CharacterNode* rowNode = head; // Start from the head of the list
	int currentLine = 0;

	// Iterate over the 2D list row by row
	while (rowNode != nullptr)
	{
		CharacterNode* colNode = rowNode;
		int currentCol = 0;

		// Traverse horizontally for each row
		while (colNode != nullptr)
		{
			colNode->setLine(currentLine); // Update row index
			colNode->setCol(currentCol);  // Update column index
			colNode = colNode->getRight(); // Move to the next column
			currentCol++;
		}

		// Move to the next row
		rowNode = rowNode->getDown();
		currentLine++;
	}
}
void LinkList2D::printList(int x,int y)
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
//void LinkList2D::printList(int startX, int startY) {
//	if (isEmpty()) {
//		return;
//	}
//
//	CharacterNode* currentR = head;
//	int currentY = 0; // To track the current row
//
//	while (currentR != nullptr) {
//		CharacterNode* currentC = currentR;
//
//		// Check if the current row is the startY or below it
//		if (currentY >= startY) {
//			// Print characters only if the current row is at or beyond the starting row
//			while (currentC != nullptr) {
//				int currentX = currentC->getCol(); // Get the column of the character
//
//				// Check if the character's column is at or beyond the startX
//				if (currentX >= startX) {
//					gotoxy(currentX, currentY); // Move cursor to (currentX, currentY)
//					std::cout << currentC->getLetter(); // Print the character
//				}
//				currentC = currentC->getRight(); // Move to the next character in the row
//			}
//		}
//
//		currentR = currentR->getDown(); // Move to the next row
//		currentY++; // Increment the row index
//	}
//}
void LinkList2D::cursorUpdate(int x, int y)
{
	if (x > 0 && x <= inputAreaWidth) 
	{
		cursorX = x;
	}
	if (y > 0 && y <= inputAreaHeight) 
	{
		cursorY = y;
	}
	// Move the cursor to the new position (this reflects on-screen cursor)
	gotoxy(cursorX, cursorY);
}
// Move cursor left
void LinkList2D::moveCursorLeft() 
{
	if (cursorX > 1 && currentCol->getLeft() != nullptr) 
	{
		// Move the node pointer to the left
		currentCol = currentCol->getLeft();
		// Update the cursor position
		cursorUpdate(cursorX - 1, cursorY);
	}
}
// Move cursor right
void LinkList2D::moveCursorRight() 
{
	if (cursorX < inputAreaWidth && currentCol->getRight() != nullptr) 
	{
		// Move the node pointer to the right
		currentCol = currentCol->getRight();
		// Update the cursor position
		cursorUpdate(cursorX + 1, cursorY);
	}
}
// Move cursor up
void LinkList2D::moveCursorUp() 
{
	if (cursorY > 1 && currentCol->getUp() != nullptr) 
	{
		// Move the node pointer up
		currentCol = currentCol->getUp();
		// Update the cursor position
		cursorUpdate(cursorX, cursorY - 1);
	}
}
// Move cursor down
void LinkList2D::moveCursorDown() 
{
	if (cursorY < inputAreaHeight && currentCol->getDown() != nullptr) 
	{
		// Move the node pointer down
		currentCol = currentCol->getDown();
		// Update the cursor position
		cursorUpdate(cursorX, cursorY + 1);
	}
}
void LinkList2D::printAroundCursor(int radius = 1)
{
	int startX = cursorX - radius;
	int endX = cursorX + radius;
	int startY = cursorY - radius;
	int endY = cursorY + radius;

	if (startX < 1) startX = 1;
	if (endX > inputAreaWidth) endX = inputAreaWidth;
	if (startY < 1) startY = 1;
	if (endY > inputAreaHeight) endY = inputAreaHeight;

	// Start from the head node and find the nodes around the cursor
	CharacterNode* currentLineNode = head;

	// Traverse to the relevant line
	while (currentLineNode != nullptr && currentLineNode->getLine() < startY)
	{
		currentLineNode = currentLineNode->getDown();
	}

	// Now traverse within the range from startY to endY
	while (currentLineNode != nullptr && currentLineNode->getLine() <= endY)
	{
		CharacterNode* currentColNode = currentLineNode;

		// Traverse to the relevant column
		while (currentColNode != nullptr && currentColNode->getCol() < startX)
		{
			currentColNode = currentColNode->getRight();
		}

		// Now traverse within the range from startX to endX
		while (currentColNode != nullptr && currentColNode->getCol() <= endX)
		{
			// Move cursor to the node's position and overwrite it with a space first
			gotoxy(currentColNode->getCol()+1, currentColNode->getLine());
			std::cout << ' ';  // Clear the previous character
			
			// Print only the nodes within the range
			gotoxy(currentColNode->getCol()+1, currentColNode->getLine());
			std::cout << currentColNode->getLetter()<<std::flush;

			currentColNode = currentColNode->getRight();  // Move to the next node to the right
		}

		currentLineNode = currentLineNode->getDown();  // Move to the next line
	}

	// Finally, reset the cursor to its current position after printing
	gotoxy(cursorX, cursorY);
}

