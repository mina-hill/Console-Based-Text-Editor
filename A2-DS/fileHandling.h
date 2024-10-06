#pragma once
#include "doubly.h"
#include <iostream>
#include <fstream>
using namespace std;

class FileHandling {
private:
	char pathOfFile[6];
public:
	FileHandling()
	{
		const char* fileName = "f.txt";
		for (int i = 0; fileName[i] != '\0'; ++i) {
			pathOfFile[i] = fileName[i];
		}
		pathOfFile[5] = '\0';


		ofstream MyFile(fileName); // This will create the file if it doesn't exist
		if (MyFile.is_open()) {
			cout << "File 'f.txt' created successfully." << endl;
		}
		else {
			cout << "Error: Could not create the file 'f.txt'." << endl;
		}
		MyFile.close();
	}
	FileHandling(const char* fileName)//char* path) //open or create file
	{
		for (int i = 0; fileName[i] != '\0'; ++i) {
			pathOfFile[i] = fileName[i];
		}
		pathOfFile[5] = '\0';

		fstream file(pathOfFile, ios::in | ios::out | ios::app);

		if (!file.is_open()) {
			// File doesn't exist, so we create it by opening with ofstream (output stream)
			ofstream createFile(pathOfFile);
			if (createFile.is_open()) {
				cout << "File '" << pathOfFile << "' created successfully." << endl;
			}
			else {
				cout << "Error: Could not create the file '" << pathOfFile << "'." << endl;
			}
			createFile.close();
		}
		else {
			cout << "File '" << pathOfFile << "' opened successfully." << endl;
		}
		file.close(); 
	}
	//void saveFile(LinkList2D& list)
	//{
	//	ofstream outFile(pathOfFile);
	//
	//	CharacterNode* currentRow = list.getHead();
	//	while (currentRow != nullptr)
	//	{
	//		CharacterNode* currentCol = currentRow;
	//		while (currentCol != nullptr)
	//		{
	//			outFile << currentCol->getLetter();  
	//			currentCol = currentCol->getRight();
	//		}
	//		outFile << '\n';//endl; //idk it doesnt work right
	//		currentRow = currentRow->getDown();
	//	}
	//
	//	outFile.close(); 
	//	cout << "File saved successfully." << endl;
	//}

	void saveFile(LinkList2D& list)
	{
		ofstream outFile(pathOfFile);

		CharacterNode* currentRow = list.getHead();

		while (currentRow != nullptr) // Traverse rows (downwards)
		{
			CharacterNode* currentCol = currentRow;

			while (currentCol != nullptr) // Traverse columns (rightwards)
			{
				outFile << currentCol->getLetter();  // Output each character
				currentCol = currentCol->getRight(); // Move to the next column
			}

			outFile << '\n';  // After finishing a row, add a newline
			currentRow = currentRow->getDown(); // Move to the next row
		}

		outFile.close();  // Close the file once all data is written
		cout << "File saved successfully." << endl;
	}
	void readFile(LinkList2D& list)
	{
		ifstream inFile(pathOfFile);

		if (!inFile.is_open()) {
			cout << "Error: Could not open the file '" << pathOfFile << "' for reading." << endl;
			return;
		}
		char ch;
		while (inFile.get(ch)) { // Read character by character
			if (ch == '\n') {
				// When a newline is encountered, start a new line in the linked list
				list.newLine();
			}
			else {
				// Add the character to the linked list
				list.addLetter(ch);
			}
		}

		inFile.close();

	}
};