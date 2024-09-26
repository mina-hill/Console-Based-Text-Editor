#pragma once
#include <iostream>

class CharacterNode {
private:
	char letter;
	CharacterNode* left;
	CharacterNode* right;
	CharacterNode* up;
	CharacterNode* down;
public:
	CharacterNode(const char newLetter = ' ', CharacterNode* l = nullptr, CharacterNode* r = nullptr,
		CharacterNode* u = nullptr, CharacterNode* d = nullptr) : letter(newLetter), left(l), right(r), up(u), down(d) {}
	char getLetter() const
	{
		return letter;
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

};

class LinkList2D {
private:
	CharacterNode* head;
	CharacterNode* current;
public:
	LinkList2D(CharacterNode* h = nullptr) : head(h) {}
	bool isEmpty()
	{
		if (head == nullptr)
		{
			return 0;
		}
		return 1;
	}
	void addLetter(char newLetter)
	{
		if (isEmpty())
		{
			head = new CharacterNode(newLetter);
			current = head;
			return;
		}
		//make new Node and initialize it
		CharacterNode* newNode = new CharacterNode(newLetter);
		current->setRight(newNode);
		current->setLeft(nullptr);
		current->setUp(nullptr);
		current->setDown(nullptr);

		//move current to new Node in list
		current = current->getRight();

		/*CharacterNode* current = head;
		while (current)
		{

		}*/
	}
};