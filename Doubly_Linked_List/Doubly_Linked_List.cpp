

#include "pch.h"


struct Node
{
	int value;
	Node *next;
	Node *prev;
};

struct List
{
	Node *back	{ nullptr };
	Node *front { nullptr };
		
	void print(Node *front)
	{
		Node *current = front;
		while (current != nullptr)
		{
			std::cout << current->value << " | ";
			current = current->next;
		}
	}

	void printr(Node *back)
	{
		Node *current = back;
		while (current != nullptr)
		{
			std::cout << current->value << " | ";
			current = current->prev;
		}
	}

	Node *push_back (int value)
	{	
		Node *current  = new Node;
		current->value = value;
		current->prev  = back;
		if (back != nullptr)
			back->next = current;
		else
			front = current;

		back = current;
		back->next = nullptr;
		return current;
	}

	Node *pushToPosition(int value, int position)
	{
		Node *current = new Node;
		current->next = front;
		for (int i = 0; i < position - 1; i++)
		{
			current->next = current->next->next;
		}
		current->next->prev->next = current;
		current->prev = current->next->prev;
		current->next->prev = current;
		current->value = value;
		return current;
	}

	Node* swapNode(Node *node1, Node *node2)
	{
		Node *prev, *prev2, *next, *next2;
		prev  = node1->prev;
		prev2 = node2->prev;
		next  = node1->next;
		next2 = node2->next;
		if (node2 == next) //..|..|Node1|Node2|..|..|
		{
			node2->next = node1;
			node2->prev = prev;
			node1->next = next2;
			node1->prev = node2;
			if (next2 != nullptr)
			{
				next2->prev = node1;
			}
			if (node2 != front)
			{
				prev->next = node2;
			}
		}
		else //|Node1|..|Node2|..|
		{
			if (node1 != front)
				prev->next = node2;
			node2->next = next;
			if (node2 != front)
				prev2->next = node1;
			node1->next = next2;
			node2->prev = prev;
			if (next2 != nullptr)
				next2->prev = node1;
			node1->prev = prev2;
			if (next != nullptr)
				next->prev = node2;
		}	
		if (node1 == front)
		{
			if (node2 == back)
				back = node1;
			return node2;
		}
			
		if (node2 == front)
		{
			if (node1 == back)
				back = node2;
			return node1;
		}
		return front;
	}

	Node* deleteNode(Node* node)
	{
		Node *prev, *next;
		prev = node->prev;
		next = node->next;
		if (prev != nullptr)
			prev->next = next;
		if (next != nullptr)
			next->prev = prev;
		delete(node);
		return prev;
	}

	void deleteList()
	{
		Node *current = front;
		while (current != nullptr)
		{
			if (current->next != nullptr)
			{
				current = current->next;
				current->prev = nullptr;
			}
			else
				current = nullptr;
		}
		front = nullptr;
		back = nullptr;
	}
};


int main()
{
	List listTest;

	for (size_t i = 0; i < 4; i++)
	{
		listTest.push_back(i * 10);
	}
	listTest.print(listTest.front);
	std::cout << "\n";

	/////////////////////////////////////
	listTest.pushToPosition(1234, 3);
	listTest.print(listTest.front);
	std::cout << "\n";
	/////////////////////////////////////
	listTest.front = listTest.swapNode(listTest.front->next->next, listTest.back->prev);
	listTest.print(listTest.front);
	std::cout << "\n";
	listTest.printr(listTest.back);
	listTest.deleteNode(listTest.front->next->next);
	std::cout << "\n";
	listTest.print(listTest.front);
	listTest.deleteList();
	return 0;
}
