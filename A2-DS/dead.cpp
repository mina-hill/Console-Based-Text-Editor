#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

void setCursor(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ddrawBoundary(int startX, int startY, int width, int height) {
    for (int i = 0; i < height; ++i) {
        setCursor(startX, startY + i);
        if (i == 0 || i == height - 1) {
            for (int j = 0; j < width; ++j) std::cout << "-";
        }
        else {
            std::cout << "|";
            setCursor(startX + width - 1, startY + i);
            std::cout << "|";
        }
    }
}

int dead() {
    // Clear screen
    system("cls");

    int consoleWidth = 169;  // fullscreen=169, default = 125
    int consoleHeight = 44; // fullscreen=44, default = 30

    // Defining the input area to be 60% of the console height
    int inputAreaHeight = consoleHeight * 0.6;
    int suggestionAreaStartY = inputAreaHeight + 1;

    // Draw the input area
    ddrawBoundary(0, 0, consoleWidth, inputAreaHeight);

    // Label for the input area
    setCursor(1, 1);
    std::cout << "Welcome to the Notepad.";
    setCursor(1, 2);
    std::cout << "This is the area where you are supposed to write the content.";

    // Draw the suggestions area
    setCursor(0, suggestionAreaStartY);
    ddrawBoundary(0, suggestionAreaStartY, consoleWidth, consoleHeight - inputAreaHeight - 1);

    // Label for the word suggestions
    setCursor(1, suggestionAreaStartY + 1);
    std::cout << "Word Suggestions";

    // Input Handling (restricted to the input area)
    setCursor(1, 3);
    std::string userInput;
    while (true) {
        setCursor(1, inputAreaHeight - 2); // Input at the bottom of the input box
        std::cout << "Enter text: ";
        std::getline(std::cin, userInput);

        if (userInput == "exit") break; // Exit condition for the loop

        // Clear last input area
        setCursor(0, inputAreaHeight - 1);
        std::cout << std::string(consoleWidth, ' ');

        // Output the entered content inside the writing area
        setCursor(1, inputAreaHeight - 3);
        std::cout << "You entered: " << userInput;
    }

    return 0;
}


//void addLetter(char newLetter)
//{
//	if (isEmpty())
//	{
//		// If the list is empty, initialize the head
//		head = new CharacterNode(newLetter, CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
//		currentCol = head;
//		currentLine = head;
//	}
//	else
//	{
//		// If we are at the start of a new line, the node might already exist with '\0'
//		if (currentCol->getLetter() == '\0')
//		{
//			currentCol->setLetter(newLetter);  // Update the letter in the existing node
//		}
//		else
//		{
//			// Check if we're at the end of the row
//			if (CharacterNode::getCurrCol() == inputAreaWidth - 1)
//			{
//				newLine();  // Move to the next line
//				currentCol->setLetter(newLetter);  // Set the letter for the new node
//			}
//			else
//			{
//				// Make a new node and initialize it
//				CharacterNode* newNode = new CharacterNode(newLetter, CharacterNode::getCurrCol(), CharacterNode::getCurrLine());
//
//				// Link horizontally to the previous column
//				currentCol->setRight(newNode);
//				newNode->setLeft(currentCol);
//
//				// Link vertically if there's a node in the line above
//				CharacterNode* lineAbove = currentLine->getUp();
//				int targetColumn = CharacterNode::getCurrCol();
//
//				// Traverse to find the node above at the same column
//				while (lineAbove != nullptr && lineAbove->getCol() < targetColumn)
//				{
//					lineAbove = lineAbove->getRight();
//				}
//
//				// Link vertically to the node above (if it exists)
//				if (lineAbove != nullptr && lineAbove->getCol() == targetColumn)
//				{
//					newNode->setUp(lineAbove);
//					lineAbove->setDown(newNode);
//				}
//
//				// Move current to new Node in list
//				currentCol = newNode;
//			}
//		}
//	}
//
//	// Increment the column after adding a new letter
//	CharacterNode::setCurrCol(CharacterNode::getCurrCol() + 1);
//}
