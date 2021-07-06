#pragma once
#include"Room.h"
#include"GameCharacter.h"


using namespace std;

template<class T>


class RoomTree
{

public:
	T* foundRoom;
	T* root;

public:
	RoomTree();
	T* SelectRoom(int key);
	void DisplayInOrder(T* localRoot);
	void TreeInsert(int roomLevel, int roomNum, int roomOxygen, int spaces);
	void DisplaySelecetedRoom();
	void AssignEnemy(GameCharacter* enemy);
	


};

template<class T>
RoomTree<T>::RoomTree() {
	root = 0;
	foundRoom = 0;
}

template<class T>
T* RoomTree<T>::SelectRoom(int key) {

	foundRoom = root;
	while (foundRoom->key != key) {
		//cout << "While entered";
		if (key < foundRoom->key)

			foundRoom = foundRoom->leftChild;
		else
			foundRoom = foundRoom->rightChild;
		if (foundRoom == 0)
			cout << "Room not found" << endl;
		return 0;
	}
	cout << " Found room key " << foundRoom->key << endl;
	return foundRoom;
}

template<class T>
void RoomTree<T>::DisplaySelecetedRoom() {


	foundRoom->Display();

}

template<class T>
void RoomTree<T>::AssignEnemy(GameCharacter* enemy) {

	foundRoom->spaMan->Insert(enemy);
}


template<class T>
void RoomTree<T>::DisplayInOrder(T* localRoot) {
	if (localRoot != 0) {
		DisplayInOrder(localRoot->leftChild);
		localRoot->Display();
		DisplayInOrder(localRoot->rightChild);
	}
}

template<class T>
void RoomTree<T>::TreeInsert(int roomLevel, int roomNum, int roomOxygen, int spaces) {

	T* newNode = new T(roomLevel, roomNum, roomOxygen, spaces);

	if (root == 0) {
		root = newNode;
	}
	else {

		T* current;
		current = root;
		T* parent;
		while (true)
		{
			parent = current;
			if (newNode->LessThan(newNode, current)) {
				//if (data < current->data) {
				current = current->leftChild;
				if (current == 0) {
					parent->leftChild = newNode;
					return;
				}
			}
			else {
				current = current->rightChild;
				if (current == 0) {
					parent->rightChild = newNode;
					return;
				}
			}
		}
	}

}