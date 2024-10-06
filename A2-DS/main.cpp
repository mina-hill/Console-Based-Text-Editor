#include "doubly.h"
#include "fileHandling.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
using namespace std;


void drawBoundary(int startX, int startY, int width, int height, bool drawupper) 
{
	for (int i = 0; i <= height; ++i) 
	{
		gotoxy(startX, startY + i);
		if ((i == 0 &&drawupper) || (i == height))
		{
			for (int j = 0; j < width; ++j) 
				std::cout << "-";
		}
		else 
		{
			std::cout << "|";
			gotoxy(startX + width - 1, startY + i);
			std::cout << "|";
		}
	}
}
int main(int argc, char* argv[]) 
{
	system("cls");
	cout << "Enter the name of the file."<<endl;
	char f;
	cin >> f;
	const char a[6] = { f, '.','t','x','t','\0'};

	FileHandling file(a);

	system("cls");
	HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

	DWORD Events = 0;     // Event count
	DWORD EventsRead = 0; // Events read from console

	//setting the bounds 
	int consoleWidth = 125;  // fullscreen=169, default = 125
	int consoleHeight = 30; // fullscreen=44, default = 30

	// Defining the input area to be 60% of the console height
	int inputAreaWidth = consoleWidth * 0.8;
	int inputAreaHeight = consoleHeight * 0.8;
	int suggestionAreaStartY = inputAreaHeight + 1;
	int wordSearchStartX = inputAreaWidth + 1;
	//drawing boundary of notepad area
	drawBoundary(0, 0, inputAreaWidth, inputAreaHeight,0);
	bool Running = true;
	
	int x = wordSearchStartX, y = 0;
	gotoxy(x, y);
	cout << "Search" << endl;
	x = 1, y = suggestionAreaStartY;
	gotoxy(x, y);
	cout << "Word Suggestion" << endl;
	//start notepad
	x = 1, y = 1;
	gotoxy(x, y);
	cout << " Welcome to the Notepad.";
	x = 1, y = 2;
	gotoxy(x, y);
	cout<<  " This is the area where you are supposed to write the content."; 
	//go to writing area
	x = 1, y = 3;
	gotoxy(x, y);

	LinkList2D list;
	bool printUpdate = false;
	//file.readFile(list);
	list.printList();
	//programs main loop
	while (Running) {

		// gets the systems current "event" count
		GetNumberOfConsoleInputEvents(rhnd, &Events);

		if (Events != 0) { // if something happened we will handle the events we want

			// create event buffer the size of how many Events
			INPUT_RECORD eventBuffer[200];

			// fills the event buffer with the events and saves count in EventsRead
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			// loop through the event buffer using the saved count
			for (DWORD i = 0; i < EventsRead; ++i) {

				// check if event[i] is a key event && if so is a press not a release
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) 
				{
					// check if the key press was an arrow key
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

					case VK_UP: //up
						/*y--;
						gotoxy(x, y);
						list.cursorUpdate(x, y);*/
						list.moveCursorUp();
						break;
					case VK_DOWN: //down
						/*y++;
						gotoxy(x, y);
						list.cursorUpdate(x, y);*/
						list.moveCursorDown();
						break;
					case VK_RIGHT: //right
						/*x++;
						gotoxy(x, y);
						list.cursorUpdate(x, y);*/
						list.moveCursorRight();
						break;
					case VK_LEFT: //left
						/*x--;
						gotoxy(x, y);
						list.cursorUpdate(x, y);*/
						list.moveCursorLeft();
						break;
					case VK_ESCAPE: //esc
						file.saveFile(list);
						Running = false; 
						break;
					case VK_RETURN: //enter
						cout << "\n"; 
						list.newLine();
						y++;
						x = 0;
						gotoxy(x, y);
						break;
					case VK_BACK:
						list.handleBackspace();
						printUpdate = true;
						break;
					default:
						char letter = eventBuffer->Event.KeyEvent.uChar.AsciiChar;
						if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') || letter == ' ')
						{							
							list.addLetter(letter);
							x++;
							gotoxy(x, y);
							printUpdate = true;
						}
						//cout << letter;
						break;
					}
				}

			} // end EventsRead loop

		}
		if (printUpdate)
		{
			list.printList();
			printUpdate = false;
		}
	} // end program loop

	return 0;
}