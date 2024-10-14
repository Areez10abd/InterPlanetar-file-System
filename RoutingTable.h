#include <Windows.h>
#include <codecvt>
#include <cstdio>

/*
#pragma once
#include <direct.h>
#include "sha1.hpp"
#include "Btree.h"
#include<cstring>

class CircularNode;

class Node
{
public:
	BigInt data;
	CircularNode* address;
	Node* next;
	Node* prev;
	Node(BigInt d, CircularNode* a)
	{
		data = d;
		address = a;
		next = NULL;
		prev = NULL;
	}
};

class DoublyLinkedList
{
public:
	Node* head;
	Node* tail;
	DoublyLinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	Node* search(BigInt d)
	{
		Node* p = head;
		while (p != NULL)
		{
			if (p->data == d)
			{
				break;
			}
			p = p->next;
		}
		return p;
	}
	void insertAtEnd(BigInt d, CircularNode* C)
	{
		Node* p = head, * q = head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}
		p = new Node(d, C);
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			q->next = p;
			p->prev = q;
		}
		tail = p;
	}
	void insertAfter(BigInt after, BigInt newData, CircularNode* C)
	{
		Node* p = search(after);
		if (p != NULL)
		{
			Node* q = p->next;
			if (q != NULL)
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				q->prev = r;
				r->next = q;
			}
			else
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				tail = r;
			}
		}
		else
		{
			cout << "Node to insert after not found" << endl;
		}
	}
	void removeNode(BigInt d)
	{
		Node* p = search(d);
		if (p != NULL)
		{
			if (p == head)
			{
				delete p;
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node* q = p->prev;
				q->next = p->next;
				p->next->prev = q;
				if (p == tail)
				{
					tail = q;
				}
				delete p;
			}
		}
		else
		{
			cout << "Node to delete not found" << endl;
		}
	}
	void display()
	{
		Node* p = head;
		cout << "Front: ";
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

class CircularNode
{
public:
	BigInt ID;
	int size;
	BigInt tSize;
	DoublyLinkedList* T;
	CircularNode* next;
	BTreeNode *btreeroot;
	CircularNode(BigInt i, int totalSize)
	{
		T = new DoublyLinkedList();
		size = totalSize;
		tSize = 2;
		for (int i = 1; i < size; i++)
		{
			tSize *= 2;
		}
		ID = i;
		next = NULL;
	}
	void update()
	{
		for (int i = 1; i <= size; i++)
		{
			bool once = true;
			BigInt distance = 1;
			for (int power = 0; power < i - 1; power++)
			{
				distance *= 2;
			}
			distance += ID;
			while (distance > tSize)
			{
				distance -= tSize;
			}
			CircularNode* p = this, * q = p;
			while (p != NULL)
			{
				if (ID == distance)
				{
					T->insertAtEnd(ID, p);
					break;
				}
				q = p;
				p = p->next;
				if (p->ID <= ID && ID > distance)
				{
					once = false;
				}
				if (p->ID >= distance && ID > distance)
				{
					if (!once)
					{
						T->insertAtEnd(p->ID, p);
						break;
					}
				}
				else if (p->ID >= distance && ID < distance)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
				if (distance > q->ID && q->ID > p->ID)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
			}
		}
	}
	void display()
	{
		CircularNode* p = this;
		while (p != NULL)
		{
			DoublyLinkedList* TP = p->T;
			cout << p->ID << ": ";
			TP->display();
			p = p->next;
			if (p->ID == ID)
			{
				break;
			}
		}
	}
	CircularNode* traverseRoutingTable(BigInt machineID)
	{
		Node* p = T->head;
		for (int i = 1; i <= size; i++)
		{
			if (machineID == p->address->ID)
			{
				return p->address;
			}
			if (i == 1 && p->address->ID > machineID)
			{
				return p->address;
			}
			else if (i != 1 && p->address->ID >= machineID && machineID >= p->prev->address->ID)
			{
				return p->prev->address;
			}
			if (i == size)
			{
				return p->address;
			}
			p = p->next;
		}
	}
};

class CircularLinkedList
{
public:
	BigInt totalSize;
	int logSize;
	CircularNode* root;
	CircularLinkedList(int identifier)
	{
		totalSize = 2;
		for (int i = 1; i < identifier; i++)
		{
			totalSize *= 2;
		}
		logSize = identifier;
		root = NULL;
	}

	void displaymybtree(BigInt i) {
		if (nodealreadyexists(i) == 0) {
			cout << "Machine is not active!\n";
			return;
		}
		else {
			CircularNode* temp = root;
			while (BigInt(i) != temp->next->ID) {
				temp = temp->next;
			}
			cout << "B-tree: ";
			
			displayb(temp->btreeroot);
			cout << "\n";
			print_tree(temp->btreeroot, 0);
		}
	}


	void addfile(const string& path) {

	

		string hh= SHA1::from_file(path);


		CircularNode* temp = root;
		while (BigInt(hh)<=temp->next->ID) {
			temp = temp->next;
		}
		temp->btreeroot = insert(temp->btreeroot,stoi(hh));


		std::ifstream my_file_src(path, std::ios::binary);

		if (!my_file_src.is_open()) {
			std::cerr << "Error opening source file." << std::endl;
			return ;
		}
		size_t lBl = path.find_last_of("\\");

		std::string dpath = path.substr(lBl + 1);
	
		std::ofstream my_file_dst(dpath, std::ios::binary);

		if (!my_file_dst.is_open()) {
			std::cerr << "Error opening destination file." << std::endl;
			my_file_src.close();
			return;
		}

		my_file_dst << my_file_src.rdbuf();

		my_file_src.close();
		my_file_dst.close();

		std::cout << "File copied successfully." << std::endl;
	}

	bool nodealreadyexists(BigInt id) {
		CircularNode* p = root;
		if (root == NULL) return 0;
		if (root->ID == id) return 1;
		while (p->next != root) {
			if (p->next->ID == id) return 1;
			p = p->next;
		}
		return 0;
	}


	void insertion(BigInt id)
	{
		string strFromCharArray(id.Big);
		if (_mkdir(strFromCharArray.c_str()) == 0) {
			std::cout << "Folder created successfully." << std::endl;
		}
		else {
			std::cerr << "Failed to create folder." << std::endl;
		}

		CircularNode* p = root, * q = p;
		if (root == NULL)
		{
			root = new CircularNode(id, logSize);

			root->next = root;
			return;
		}
		p = p->next;
		while (p != NULL)
		{
			if (p->ID == root->ID || p->ID >= id)
			{
				CircularNode* r = new CircularNode(id, logSize);
				q->next = r;
				r->next = p;
				return;
			}
			q = p;
			p = p->next;
		}
		
	}

	void deletion(BigInt id) {

		string strFromCharArray(id.Big);

		if (_rmdir(strFromCharArray.c_str()) == 0) {
			std::cout << "Folder deleted successfully.\n";
			//return;
		}
		else {
			std::cerr << "Failed to delete folder.\n";
			//return;
		}
		CircularNode* p = root;

		if (root == NULL) {
			cout << "No active machine!\n";
			return;
		}
		if (root->next == root) {
			if (root->ID == id) {
				delete root;
				root = NULL;
				cout << "Deletion done!\n";
			}
			else {
				cout << "Machine already inactive!\n";
			}
			return;
		}
		
		while (p->next != root) {
			if (p->next->ID == id) {
				CircularNode* temp = p->next;
				p->next = p->next->next;
				//------------------------------
				while (temp->btreeroot) {
					int ph = temp->btreeroot->value[0];
					p->next->next->btreeroot = insert(p->next->next->btreeroot,ph);
						temp->btreeroot = Delete(temp->btreeroot, ph);
				}

				//------------------------------
				delete temp;
				cout << "Successful deletion!\n";
				return;
			}
			p = p->next;
		}
		cout << "Machine already inactive!\n";
		return;

	}
	void display()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			cout << p->ID << " ";
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void updateRoutingTable()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			p->update();
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void displayRoutingTable()
	{
		root->display();
	}
	void traverseRoutingTable(BigInt startID, BigInt machineID)
	{
		CircularNode* p = root;
		while (p->ID != startID)
		{
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
		do
		{
			cout << p->ID << endl;
			p = p->traverseRoutingTable(machineID);

		} while (p->ID < machineID);
		cout << p->ID << endl;
	}
};
*/

/*
#pragma once
#include <direct.h>
#include "sha1.hpp"
#include "Btree.h"
#include<cstring>
class CircularNode;

class Node
{
public:
	BigInt data;
	CircularNode* address;
	Node* next;
	Node* prev;
	Node(BigInt d, CircularNode* a)
	{
		data = d;
		address = a;
		next = NULL;
		prev = NULL;
	}
};

class DoublyLinkedList
{
public:
	Node* head;
	Node* tail;
	DoublyLinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	Node* search(BigInt d)
	{
		Node* p = head;
		while (p != NULL)
		{
			if (p->data == d)
			{
				break;
			}
			p = p->next;
		}
		return p;
	}
	void insertAtEnd(BigInt d, CircularNode* C)
	{
		Node* p = head, * q = head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}
		p = new Node(d, C);
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			q->next = p;
			p->prev = q;
		}
		tail = p;
	}
	void insertAfter(BigInt after, BigInt newData, CircularNode* C)
	{
		Node* p = search(after);
		if (p != NULL)
		{
			Node* q = p->next;
			if (q != NULL)
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				q->prev = r;
				r->next = q;
			}
			else
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				tail = r;
			}
		}
		else
		{
			cout << "Node to insert after not found" << endl;
		}
	}
	void removeNode(BigInt d)
	{
		Node* p = search(d);
		if (p != NULL)
		{
			if (p == head)
			{
				delete p;
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node* q = p->prev;
				q->next = p->next;
				p->next->prev = q;
				if (p == tail)
				{
					tail = q;
				}
				delete p;
			}
		}
		else
		{
			cout << "Node to delete not found" << endl;
		}
	}
	void display()
	{
		Node* p = head;
		cout << "Front: ";
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

class CircularNode
{
public:
	BigInt ID;
	int size;
	BigInt tSize;
	DoublyLinkedList* T;
	CircularNode* next;
	BTreeNode* btreeroot;
	CircularNode(BigInt i, int totalSize)
	{
		T = new DoublyLinkedList();
		size = totalSize;
		tSize = 2;
		for (int i = 1; i < size; i++)
		{
			tSize *= 2;
		}
		ID = i;
		next = NULL;
	}
	void update()
	{
		for (int i = 1; i <= size; i++)
		{
			bool once = true;
			BigInt distance = 1;
			for (int power = 0; power < i - 1; power++)
			{
				distance *= 2;
			}
			distance += ID;
			while (distance >= tSize)
			{
				distance -= tSize;
			}
			CircularNode* p = this, * q = p;
			while (p != NULL)
			{
				if (ID == distance)
				{
					T->insertAtEnd(ID, p);
					break;
				}
				q = p;
				p = p->next;
				if (p->ID <= ID && ID > distance)
				{
					once = false;
				}
				if (p->ID >= distance && ID > distance)
				{
					if (!once)
					{
						T->insertAtEnd(p->ID, p);
						break;
					}
				}
				else if (p->ID >= distance && ID < distance)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
				if (distance > q->ID && q->ID > p->ID)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
			}
		}
	}
	void display()
	{
		CircularNode* p = this;
		while (p != NULL)
		{
			DoublyLinkedList* TP = p->T;
			cout << p->ID << ": ";
			TP->display();
			p = p->next;
			if (p->ID == ID)
			{
				break;
			}
		}
	}
	CircularNode* traverseRoutingTable(BigInt machineID, bool& stop)
	{
		Node* p = T->head;
		for (int i = 1; i <= size; i++)
		{
			if (machineID == p->address->ID)
			{
				return p->address;
			}
			if (i == 1 && p->address->ID > machineID)
			{
				return p->address;
			}
			else if (i != 1 && p->address->ID >= machineID && machineID >= p->prev->address->ID)
			{
				return p->prev->address;
			}
			else if (i != 1 && p->address->ID < p->prev->address->ID && machineID > p->prev->address->ID && machineID > p->address->ID)
			{
				stop = true;
				return p->prev->address;
			}
			if (i == size)
			{
				return p->address;
			}
			p = p->next;
		}
	}
};

class CircularLinkedList
{
public:
	BigInt totalSize;
	int logSize;
	CircularNode* root;
	CircularLinkedList(int identifier)
	{
		totalSize = 2;
		for (int i = 1; i < identifier; i++)
		{
			totalSize *= 2;
		}
		logSize = identifier;
		root = NULL;
	}

	void displaymybtree(BigInt i) {
		if (nodealreadyexists(i) == 0) {
			cout << "Machine is not active!\n";
			return;
		}
		else {
			CircularNode* temp = root;
			while (BigInt(i) != temp->next->ID) {
				temp = temp->next;
			}
			cout << "B-tree: ";

			displayb(temp->btreeroot);
			cout << "\n";
			print_tree(temp->btreeroot, 0);
		}
	}


	void addfile(const string& path) {

		string hh = SHA1::from_file(path);
		BigInt placement = stoi(hh);
		while (placement >= totalSize)
		{
			placement -= totalSize;
			cout << placement << ' ';
		}
		cout << "P: " << placement << endl;
		CircularNode* temp = traverseRoutingTable(root->ID, placement);
		//temp->btreeroot = insert(temp->btreeroot, int(placement));


		std::ifstream my_file_src(path, std::ios::binary);

		if (!my_file_src.is_open()) {
			std::cerr << "Error opening source file." << std::endl;
			return;
		}
		size_t lBl = path.find_last_of("\\");

		std::string dpath = path.substr(lBl + 1);

		std::ofstream my_file_dst(dpath, std::ios::binary);

		if (!my_file_dst.is_open()) {
			std::cerr << "Error opening destination file." << std::endl;
			my_file_src.close();
			return;
		}

		my_file_dst << my_file_src.rdbuf();

		my_file_src.close();
		my_file_dst.close();

		std::cout << "File copied successfully." << std::endl;
	}

	bool nodealreadyexists(BigInt id) {
		CircularNode* p = root;
		if (root == NULL) return 0;
		if (root->ID == id) return 1;
		while (p->next != root) {
			if (p->next->ID == id) return 1;
			p = p->next;
		}
		return 0;
	}


	void insertion(BigInt id)
	{
		string strFromCharArray(id.Big);
		if (_mkdir(strFromCharArray.c_str()) == 0) {
			std::cout << "Folder created successfully." << std::endl;
		}
		else {
			std::cerr << "Failed to create folder." << std::endl;
		}

		CircularNode* p = root, * q = p;
		if (root == NULL)
		{
			root = new CircularNode(id, logSize);

			root->next = root;
			return;
		}
		p = p->next;
		while (p != NULL)
		{
			if (p->ID == root->ID || p->ID >= id)
			{
				CircularNode* r = new CircularNode(id, logSize);
				q->next = r;
				r->next = p;
				return;
			}
			q = p;
			p = p->next;
		}

	}

	void deletion(BigInt id) {

		string strFromCharArray(id.Big);

		if (_rmdir(strFromCharArray.c_str()) == 0) {
			std::cout << "Folder deleted successfully.\n";
			//return;
		}
		else {
			std::cerr << "Failed to delete folder.\n";
			//return;
		}
		CircularNode* p = root;

		if (root == NULL) {
			cout << "No active machine!\n";
			return;
		}
		if (root->next == root) {
			if (root->ID == id) {
				delete root;
				root = NULL;
				cout << "Deletion done!\n";
			}
			else {
				cout << "Machine already inactive!\n";
			}
			return;
		}

		while (p->next != root) {
			if (p->next->ID == id) {
				CircularNode* temp = p->next;
				p->next = p->next->next;
				delete temp;
				cout << "Successful deletion!\n";
				return;
			}
			p = p->next;
		}
		cout << "Machine already inactive!\n";
		return;

	}
	void display()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			cout << p->ID << " ";
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void updateRoutingTable()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			p->update();
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void displayRoutingTable()
	{
		root->display();
	}
	CircularNode* traverseRoutingTable(BigInt startID, BigInt machineID)
	{
		CircularNode* p = root;
		bool stop = false;
		while (p->ID != startID)
		{
			p = p->next;
			if (p->ID == root->ID)
			{
				return p;
			}
		}
		do
		{
			cout << p->ID << endl;
			p = p->traverseRoutingTable(machineID, stop);

		} while (p->ID < machineID && !stop);
		cout << p->ID << endl;
		return p;
	}
};

*/


#pragma once
#include <direct.h>
#include "sha1.hpp"
#include "Btree.h"
#include<cstring>
#include "Btree.h"
class CircularNode;

class Node
{
public:
	BigInt data;
	CircularNode* address;
	Node* next;
	Node* prev;
	Node(BigInt d, CircularNode* a)
	{
		data = d;
		address = a;
		next = NULL;
		prev = NULL;
	}
};

class DoublyLinkedList
{
public:
	Node* head;
	Node* tail;
	DoublyLinkedList()
	{
		head = NULL;
		tail = NULL;
	}
	Node* search(BigInt d)
	{
		Node* p = head;
		while (p != NULL)
		{
			if (p->data == d)
			{
				break;
			}
			p = p->next;
		}
		return p;
	}
	void insertAtEnd(BigInt d, CircularNode* C)
	{
		Node* p = head, * q = head;
		while (p != NULL)
		{
			q = p;
			p = p->next;
		}
		p = new Node(d, C);
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			q->next = p;
			p->prev = q;
		}
		tail = p;
	}
	void insertAfter(BigInt after, BigInt newData, CircularNode* C)
	{
		Node* p = search(after);
		if (p != NULL)
		{
			Node* q = p->next;
			if (q != NULL)
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				q->prev = r;
				r->next = q;
			}
			else
			{
				Node* r = new Node(newData, C);
				p->next = r;
				r->prev = p;
				tail = r;
			}
		}
		else
		{
			cout << "Node to insert after not found" << endl;
		}
	}
	void removeNode(BigInt d)
	{
		Node* p = search(d);
		if (p != NULL)
		{
			if (p == head)
			{
				delete p;
				head = NULL;
				tail = NULL;
			}
			else
			{
				Node* q = p->prev;
				q->next = p->next;
				p->next->prev = q;
				if (p == tail)
				{
					tail = q;
				}
				delete p;
			}
		}
		else
		{
			cout << "Node to delete not found" << endl;
		}
	}
	void display()
	{
		Node* p = head;
		cout << "Front: ";
		while (p != NULL)
		{
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
};

class CircularNode
{
public:
	BigInt ID;
	int size;
	BigInt tSize;
	DoublyLinkedList* T;
	CircularNode* next;
	BTreeNode* btreeroot;
	CircularNode(BigInt i, int totalSize)
	{
		T = new DoublyLinkedList();
		size = totalSize;
		tSize = 2;
		for (int i = 1; i < size; i++)
		{
			tSize *= 2;
		}
		ID = i;
		next = NULL;
	}
	void update()
	{
		T->head = NULL;
		for (int i = 1; i <= size; i++)
		{
			bool once = true;
			BigInt distance = 1;
			for (int power = 0; power < i - 1; power++)
			{
				distance *= 2;
			}
			distance += ID;
			while (distance >= tSize)
			{
				distance -= tSize;
			}
			CircularNode* p = this, * q = p;
			while (p != NULL)
			{
				if (ID == distance)
				{
					T->insertAtEnd(ID, p);
					break;
				}
				q = p;
				p = p->next;
				if (p == q)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
				if (p->ID <= ID && ID > distance)
				{
					once = false;
				}
				if (p->ID >= distance && ID > distance)
				{
					if (!once)
					{
						T->insertAtEnd(p->ID, p);
						break;
					}
				}
				else if (p->ID >= distance && ID < distance)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
				if (distance > q->ID && q->ID > p->ID)
				{
					T->insertAtEnd(p->ID, p);
					break;
				}
			}
		}
	}
	void display()
	{
		CircularNode* p = this;
		while (p != NULL)
		{
			DoublyLinkedList* TP = p->T;
			cout << p->ID << ": ";
			TP->display();
			p = p->next;
			if (p->ID == ID)
			{
				break;
			}
		}
	}
	CircularNode* traverseRoutingTable(BigInt machineID)
	{
		Node* p = T->head;
		for (int i = 1; i <= size; i++)
		{
			if (machineID == p->address->ID)
			{
				return p->address;
			}
			if (i == 1 && p->address->ID > machineID)
			{
				return p->address;
			}
			else if (i != 1 && p->address->ID >= machineID && machineID >= p->prev->address->ID)
			{
				return p->prev->address;
			}
			else if (i != 1 && p->address->ID < p->prev->address->ID && machineID > p->prev->address->ID && machineID > p->address->ID)
			{
				return p->prev->address;
			}
			if (i == size)
			{
				return p->address;
			}
			p = p->next;
		}
	}
};

class CircularLinkedList
{
public:
	BigInt totalSize;
	int logSize;
	CircularNode* root;
	CircularLinkedList(int identifier)
	{
		totalSize = 2;
		for (int i = 1; i < identifier; i++)
		{
			totalSize *= 2;
		}
		logSize = identifier;
		root = NULL;
	}

	void displaymybtree(BigInt i) {
		if (nodealreadyexists(i) == 0) {
			cout << "Machine is not active!\n";
			return;
		}
		else {
			CircularNode* temp = traverseRoutingTable(root->ID, i);
			cout << "ID:  " << temp->ID << endl;
			cout << "B-tree: " << endl;
			displayb(temp->btreeroot);
			cout << "\n";
			print_tree(temp->btreeroot, 0);
		}
	}

	void removefile(int hval) {
		BigInt placement = hval;
		CircularNode* temp = traverseRoutingTable(root->ID, placement);


		int p = 0;
		BTreeNode* t = searchTree(hval, temp->btreeroot, &p);

		if (t == NULL) {
			cout << "File with this hash doesn't exist" << endl;
			return;
		}

		string path = t->path[p];



		temp->btreeroot = Delete(temp->btreeroot, t->value[p], t->hash[p], t->path[p]);

		
		size_t lBl = path.find_last_of("\\");

		std::string dpath = path.substr(lBl + 1);
		//cout <<"Temp ID: "<< temp->ID<< temp->ID.Big << '\\'<< endl;
		string myString(temp->ID.Big);


		dpath = myString + '\\' + dpath;

		if (std::remove(dpath.c_str()) == 0) {
			std::cout << "File removed successfully.\n";
		//	cout << "File has been removed!" << endl;
		}
		else {
			std::cerr << "Failed to remove file.\n";
		}

	}

	string search(int hval)
	{
		BigInt placement = hval;
		CircularNode* temp = traverseRoutingTable(root->ID, placement);
		//cout << "Path: " << temp->btreeroot->path[1] << endl;
		int p = 0;
		BTreeNode* t = searchTree(hval, temp->btreeroot, &p);
		if (t == NULL)
		{
			cout << "File with this hash doesn't exist" << endl;
			return "0";
		}
		else
		{
			return t->path[p];
		}
	}



	string search(string hh)
	{
		int base = 1;
		BigInt placement = 0;
		for (int i = hh.size() - 1; i >= hh.size() - 5; i--)
		{
			if (hh[i] >= '0' && hh[i] <= '9')
			{
				BigInt digit = (hh[i] - 48) * base;
				placement += digit;
			}
			else if (hh[i] >= 'a' && hh[i] <= 'f')
			{
				BigInt digit = (hh[i] - 55) * base;
				placement += digit;
			}
			base *= 16;
		}
		while (placement >= totalSize)
		{
			placement -= totalSize;
		}
		CircularNode* temp = traverseRoutingTable(root->ID, placement);
		int val = stoi(placement.Big);
		int p = 0;
		BTreeNode* t = searchTree(val, temp->btreeroot, &p);
		if (t == NULL)
		{
			cout << "File with this hash doesn't exist" << endl;
			return "0";
		}
		else
		{
			return t->path[p];
		}
	}


	void addfile(const string& path) {

		/*
		string hh = SHA1::from_file(path);
		int base = 1;
		BigInt placement = 0;
		for (int i = hh.size() - 1; i >= hh.size() - 5; i--)
		{
			if (hh[i] >= '0' && hh[i] <= '9')
			{
				BigInt digit = (hh[i] - 48) * base;
				placement += digit;
			}
			else if (hh[i] >= 'a' && hh[i] <= 'f')
			{
				BigInt digit = (hh[i] - 55) * base;
				placement += digit;
			}
			base *= 16;
		}
		//BigInt placement = hashInt;
		while (placement >= totalSize)
		{
			placement -= totalSize;
		}
		*/

		//--------------------

		string hh = SHA1::from_file(path);
		cout << "Hash: " << hh << endl;
		int base = 1;
		BigInt placement = 0;
		for (int i = hh.size() - 1; i >= hh.size() - 5; i--)
		{
			if (hh[i] >= '0' && hh[i] <= '9')
			{
				BigInt digit = (hh[i] - 48) * base;
				placement += digit;
			}
			else if (hh[i] >= 'a' && hh[i] <= 'f')
			{
				BigInt digit = (hh[i] - 55) * base;
				placement += digit;
			}
			base *= 16;
		}
		int val = stoi(placement.Big);
		cout << "Hash integer: " << val << endl;
		while (placement >= totalSize)
		{
			placement -= totalSize;
		}
		CircularNode* temp = traverseRoutingTable(root->ID, placement);
		temp->btreeroot = insert(temp->btreeroot, val, hh, path);


		//--------------------

	//	CircularNode* temp = traverseRoutingTable(root->ID, placement);
		//int val = stoi(placement.Big);
		//temp->btreeroot = insert(temp->btreeroot, val, hh, path);


		std::ifstream my_file_src(path, std::ios::binary);

		if (!my_file_src.is_open()) {
			std::cerr << "Error opening source file." << std::endl;
			return;
		}
		size_t lBl = path.find_last_of("\\");

		std::string dpath = path.substr(lBl + 1);
		//cout <<"Temp ID: "<< temp->ID<< temp->ID.Big << '\\'<< endl;
		string myString(temp->ID.Big);


		dpath = myString + '\\' + dpath;

		cout << dpath << endl;
		std::ofstream my_file_dst(dpath, std::ios::binary);

		if (!my_file_dst.is_open()) {
			std::cerr << "Error opening destination file." << std::endl;
			my_file_src.close();
			return;
		}

		my_file_dst << my_file_src.rdbuf();

		my_file_src.close();
		my_file_dst.close();

		std::cout << "File copied successfully." << std::endl;
	}

	bool nodealreadyexists(BigInt id) {
		CircularNode* p = root;
		if (root == NULL) return 0;
		if (root->ID == id) return 1;
		while (p->next != root) {
			if (p->next->ID == id) return 1;
			p = p->next;
		}
		return 0;
	}


	void insertion(BigInt id)
	{
		string strFromCharArray(id.Big);
		if (_mkdir(strFromCharArray.c_str()) == 0) {
			std::cout << "Folder created successfully." << std::endl;
		}
		else {
			std::cerr << "Failed to create folder." << std::endl;
		}

		CircularNode* p = root, * q = p;
		if (root == NULL)
		{
			root = new CircularNode(id, logSize);

			root->next = root;
			return;
		}
		p = p->next;
		while (p != NULL)
		{
			if (p->ID == root->ID || p->ID >= id)
			{
				CircularNode* r = new CircularNode(id, logSize);
				q->next = r;
				r->next = p;
				return;
			}
			q = p;
			p = p->next;
		}

	}

	bool DeleteDirectory(const std::wstring& path) {
		WIN32_FIND_DATA findFileData;
		HANDLE hFind = FindFirstFile((path + L"\\*").c_str(), &findFileData);

		if (hFind == INVALID_HANDLE_VALUE) {
			// No files found in the directory
			return RemoveDirectory(path.c_str());
		}

		do {
			if (wcscmp(findFileData.cFileName, L".") != 0 &&
				wcscmp(findFileData.cFileName, L"..") != 0) {
				std::wstring filePath = path + L"\\" + findFileData.cFileName;

				if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					// Recursively delete subdirectories
					if (!DeleteDirectory(filePath)) {
						FindClose(hFind);
						return false;
					}
				}
				else {
					// Delete files
					if (DeleteFile(filePath.c_str()) == FALSE) {
						FindClose(hFind);
						return false;
					}
				}
			}
		} while (FindNextFile(hFind, &findFileData) != 0);

		FindClose(hFind);

		// Remove the directory itself
		return RemoveDirectory(path.c_str()) != 0;
	}


	void deletion(BigInt id) {

		string strFromCharArray(id.Big);
		//------

		//std::wstring directoryPath;

		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring wideString = converter.from_bytes(strFromCharArray);


		if (DeleteDirectory(wideString)) {
			std::wcout << L"Directory deleted successfully.\n";
		}
		else {
			std::wcerr << L"Failed to delete directory.\n";
		}



		//------
		CircularNode* p = root;

		if (root == NULL) {
			cout << "No active machine!\n";
			return;
		}
		if (root->next == root) {
			if (root->ID == id) {
				delete root;
				root = NULL;
				cout << "Deletion done!\n";
			}
			else {
				cout << "Machine already inactive!\n";
			}
			return;
		}

		while (p->next != root) {
			if (p->next->ID == id) {
				CircularNode* temp = p->next;
				p->next = p->next->next;

				//------------------------------
				while (temp->btreeroot!=NULL) {

					int ph = temp->btreeroot->value[1];
					string hash= temp->btreeroot->hash[1];
						string path= temp->btreeroot->path[1];
				//		cout << "Path: "<<id<<' '<< path << ' ' << ph << " " << hash << endl;
					p->next->btreeroot = insert(p->next->btreeroot, ph,hash,path);
					temp->btreeroot = Delete(temp->btreeroot, ph,hash,path);

					//---------
					std::ifstream my_file_src(path, std::ios::binary);

					if (!my_file_src.is_open()) {
						std::cerr << "Error opening source file." << std::endl;
						return;
					}
					size_t lBl = path.find_last_of("\\");

					std::string dpath = path.substr(lBl + 1);
					//cout <<"Temp ID: "<< temp->ID<< temp->ID.Big << '\\'<< endl;
					string myString(p->next->ID.Big);


					dpath = myString + '\\' + dpath;

					cout << dpath << endl;
					std::ofstream my_file_dst(dpath, std::ios::binary);

					if (!my_file_dst.is_open()) {
						std::cerr << "Error opening destination file." << std::endl;
						my_file_src.close();
						return;
					}

					my_file_dst << my_file_src.rdbuf();

					my_file_src.close();
					my_file_dst.close();

					std::cout << "File copied successfully." << std::endl;

					//---------
				}
				//------------------------------

				delete temp;
				cout << "Successful deletion!\n";
				return;
			}
			p = p->next;
		}
		cout << "Machine already inactive!\n";
		return;

	}
	void display()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			cout << p->ID << " ";
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void updateRoutingTable()
	{
		CircularNode* p = root;
		while (p != NULL)
		{
			p->update();
			p = p->next;
			if (p->ID == root->ID)
			{
				return;
			}
		}
	}
	void displayRoutingTable()
	{
		root->display();
	}
	CircularNode* traverseRoutingTable(BigInt startID, BigInt machineID)
	{
		cout << "Path taken: ";
		CircularNode* p = root;
		while (p->ID != startID)
		{
			p = p->next;
			if (p->ID == root->ID)
			{
				return p;
			}
		}
		do
		{
			cout << p->ID << " ";
			p = p->traverseRoutingTable(machineID);
			//cout << p->next->ID << " " << p->ID << endl;
			if (p->next->ID < p->ID && p->ID < machineID)
			{
				break;
			}
		} while (p->ID < machineID);
		cout << p->ID << endl;
		return p;
	}
};