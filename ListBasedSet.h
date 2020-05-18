#pragma once

template <typename T>
class ListBasedSet {//set based on linked list, returns false on insertion if element is already present
	class Node {
	public:
		T data; // data
		Node* next; // pointer to next
		Node() :next(NULL) {}
		Node(T data) :data(data), next(NULL) {}
		Node(const Node& obj)
		{
			*this = obj;
		}
		const Node& operator=(const Node& obj)
		{
			if (this != &obj)
			{
				data = obj.data;
				next = obj.next;
			}
			return *this;
		}
		~Node() {}
	};
	Node*head;
	Node* pointer;
public:
	ListBasedSet() :head(NULL) {}
	~ListBasedSet()
	{
		Node* currNode = head;
		Node* nextNode = NULL;
		while (currNode != NULL)
		{
			nextNode = currNode->next;
			delete currNode; // destroy the current node
			currNode = nextNode;
		}
	}
	ListBasedSet(const ListBasedSet& obj)
	{
		head = NULL;
		*this = obj;
	}
	const ListBasedSet& operator=(const ListBasedSet& obj)
	{
		if (this != &obj)
		{
			clear();
			Node* curr = obj.head;
			while (curr)
			{
				insert(curr->data);
				curr = curr->next;
			}
		}
		return *this;
	}
	bool isEmpty()const {
		return (head == NULL);
	}
	bool removeElement(T data) {
		Node* prevNode = NULL;
		Node* currNode = head;
		while (currNode && !(currNode->data == data)) {
			prevNode = currNode;
			currNode = currNode->next;
		}
		if (currNode == NULL) {
			//cout << "Does not exist" << endl;
			return false;
		}
		if (prevNode) {
			prevNode->next = currNode->next;
			delete currNode;
		}
		else {
			head = currNode->next;
			delete currNode;
		}
		return true;
	}
	void display()const {
		if (isEmpty() == false) {
			Node* currNode = head;
			while (currNode != NULL) {
				(currNode->data).display();
				currNode = currNode->next;
			}
		}
	}
	void clear() {
		Node* currNode = head;
		Node *cl = NULL;
		while (currNode != NULL) {
			cl = currNode;
			currNode = currNode->next;
			delete cl;
		}
		head = NULL;
	}
	void replaceAt(T x, int index) {
		Node* node = head; int ind = 0;
		while (node != NULL) {
			node = node->next;
			ind++;
		}
		if (index <= 0 || index > ind) {
			cout << "Invalid Index" << endl;
			return;
		}
		int cIndex = 2;
		Node* currNode = head;
		while (currNode  && index > cIndex) {
			currNode = currNode->next;
			cIndex++;
		}
		if (index > 1 && currNode == NULL) {
			cout << "Invalid Index" << endl;
			return;
		}
		Node* newNode = new Node;
		newNode->data = x;
		if (index == 1) {
			head->data = x;
		}
		else {
			currNode->next->data = x;
		}
	}
	bool insert(T x)
	{
		Node* previous = NULL;
		Node* currNode = head;
		while (currNode != NULL) {
			if (currNode->data == x)
			{ // redundancy check
				return false;
			}
			previous = currNode;
			currNode = currNode->next;
		}
		Node* newNode = new Node(x);
		if (currNode == head)
		{
			head = newNode;
		}
		else
		{
			previous->next = newNode;
		}
		return true;
	}
	T* getNodeAddress(T data)
	{//return NULL if node doesn't exist
		Node* current = head;
		while (current)
		{
			if (current->data == data)
				return &(current->data);
			current = current->next;
		}
		return NULL;
	}
	T* getAtIndex(int index)
	{
		if(index<0)
			return NULL;
		if (index == 0)
		{
			if (head)
				return &(head->data);
			return NULL;
		}
		Node* node = head; int ind = 0;
		while (node != NULL) {
			node = node->next;
			ind++;
		}
		if (index > ind) {
			return NULL;
		}
		int cIndex = 1;
		Node* currNode = head;
		while (currNode  && index > cIndex) {
			currNode = currNode->next;
			cIndex++;
		}
		if (index >= 1 && currNode == NULL) {
			return NULL;
		}
		return &(currNode->next->data);
	}
	int size()
	{
		Node* node = head; int ind = 0;
		while (node != NULL) {
			node = node->next;
			ind++;
		}
		return ind;
	}
};