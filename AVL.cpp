#include <iostream>
#include "AVL.h"
nodeptr :: nodeptr() {
	left = right = parent = NULL;
	height = 0;
	size = 0;
	data = 0;
	visit = false;
}
nodeptr::nodeptr(int obj) {
	left = right = parent = NULL;
	height = 0;
	size = 0;
	data = obj;
	visit = false;
}
bstree::bstree() {
	currentSize = 0;
}
void bstree :: del(const int &key, nodeptr &root) {
	//�����Ǹ� currentSize--;���ֱ�
	nodeptr *current = &root;
	//������ ����� �ڽİ����� ����
	if (current->height == 0) {
		delete[] current;
		return;
	}
	while (current) {
		//������������ ���� 1������
		//insert �Ǹ� currentSize(treesize) 1�� ����
		if (key > current->data) {
			current = current->right;
		}
		else if (key < current->data) {
			current = current->left;
		}
		else {
			//������ ��尡 ������� �϶� �ڽ� 0
			if (current->left == NULL && current->right == NULL) {
				delete[] current;
				current = 0;
				CheckBalance(current);
				return;
			}
			//������ ����� �ڽ��� ���� �ϳ�
			else if (current->left != NULL && current->right == NULL) {
				//current�� �ڽ��� current�� ����� ������ ����
				nodeptr *temp;
				temp = current;
				current = current->left;
				delete[] temp;
				CheckBalance(current);
				return;
			}
			//������ ����� �ڽ��� ������ �ϳ�
			else if (current->left == NULL && current->right != NULL) {
				nodeptr *temp;
				temp = current;
				current = current->right;
				delete[] temp;
				CheckBalance(current);
				return;
			}
			//������ ����� �ڽ��� �ΰ� ��
			else {
				//������ �ڽ��� �����ڽ��� ���󰡼� �� ���� current���ְ�
				//������ ���� ��� ����
				nodeptr *rightchild = current->right;
				if (rightchild->left == NULL) {
					current->data = rightchild->data;
					delete[] rightchild;
					CheckBalance(current);
					return;
				}
				while (rightchild->left != NULL) {
					rightchild = rightchild->left;
				}
				//temp�� ��ü���
				current->data = rightchild->data;
				delete[] rightchild;
				CheckBalance(current);
				return;
			}
		}
	}
}

//�������� ��� ���
void bstree::Search(const int &key, nodeptr &currentNode) {
	//key���̶� �����Ͱ��̶� ���ϸ鼭 ť�� �ְ����
	nodeptr *current = &currentNode;
	queue <int> q;
	while (current != NULL) {
		if (key == current->data) {
			q.push(current->data);
			while (q.empty() != NULL) {
				cout << q.front();
				q.pop();
				if (q.empty() != NULL)
					cout << " -> ";
			}
			cout << endl;
			return;
		}
		else if (key < current->data) {
			q.push(current->data);
			current = current->right;
		}
		else {
			q.push(current->data);
			current = current->left;
		}
	}
	cout << "There is no key in the Tree" << endl;
}

//���������� ������, ���ڽ�, �����ڽ� ���
void bstree::Showresult(nodeptr &root) {
	nodeptr *current = &root;
	queue <nodeptr *> q;
	q.push(current);
	while (!q.empty()) {
		nodeptr *temp = q.front();
		q.pop();
		cout << temp->data << " left : ";
		if (temp->left == NULL) {
			cout << " empty ";
		}
		else
		{
			cout << temp->left;
			q.push(temp->left);
		}

		cout << " right : ";
		if (temp->right == NULL) {
			cout << " empty ";
		}
		else {
			cout << temp->right;
			q.push(temp->right);
		}
		cout << endl;
	}
}
void bstree::insert(const int &key, nodeptr &currentNode) {
	nodeptr *current = &currentNode;
	nodeptr *par;
	while (current) {
		//������������ ���� 1������
		//insert �Ǹ� currentSize(treesize) 1�� ����
		if (key > current->data) {
			current->height++;
			par = current;
			current = current->right;
		}
		else if (key < current->data) {
			current->height++;
			par = current;
			current = current->left;
		}
		else {
			cout << "this key is in the tree" << endl;
			delete[] current;
			return;
		}
	}
	current->data = key;
	current->parent = par;
	currentSize++;
	CheckBalance(current);

}
//�뷱�� üũ, �θ��� ���󰡸� üũ
void bstree::CheckBalance(nodeptr *&node) {
	if (getHeight(node->left) - getHeight(node->right) > 1 ||
		getHeight(node->left) - getHeight(node->right) < -1) {
		Rebalance(node);
	}
	if (node->parent == NULL)
		return;
	CheckBalance(node->parent);
}
int bstree::getHeight(nodeptr *&node) {
	return node->height;
}
void bstree::Rebalance(nodeptr *&node) {
	if (getHeight(node->left) - getHeight(node->right) > 1) {
		if (getHeight(node->left->left) > getHeight(node->left->right)) {
			LLRotation(node);
		}
		else {
			LRRotation(node);
		}
	}
	else {
		if (getHeight(node->right->right) > getHeight(node->right->left)) {
			RRRotation(node);
		}
		else {
			RLRotation(node);
		}
	}
	/*if(node->parent == NULL){
	root = node;
	}*/
}
void bstree::LLRotation(nodeptr *&node) {
	nodeptr *temp = node->left;
	node->left = temp->right;
	temp->right = node;
}
void bstree::LRRotation(nodeptr *&node) {
	nodeptr *temp = node->left;
	nodeptr *temp2 = temp->right;
	node->left = temp2->right;
	temp2->right = node;
	temp->right = temp2->left;
	temp2->left = temp;

}
void bstree::RRRotation(nodeptr *&node) {
	nodeptr * temp = node->right;
	node->right = temp->left;
	temp->left = node;
}
void bstree::RLRotation(nodeptr *&node) {
	nodeptr *temp = node->right;
	nodeptr *temp2 = temp->left;
	node->right = temp2->left;
	temp2->left = node;
	temp->left = temp2->right;
	temp2->right = temp;

}
bool operator!=(nodeptr a, int b) {
	nodeptr *temp = &a;
	if (temp != NULL)
		return true;
	else
		return false;
}