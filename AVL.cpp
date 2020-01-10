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
	//삭제되면 currentSize--;해주기
	nodeptr *current = &root;
	//삭제할 노드의 자식개수로 구분
	if (current->height == 0) {
		delete[] current;
		return;
	}
	while (current) {
		//지나갈때마다 높이 1씩증가
		//insert 되면 currentSize(treesize) 1씩 증가
		if (key > current->data) {
			current = current->right;
		}
		else if (key < current->data) {
			current = current->left;
		}
		else {
			//삭제할 노드가 리프노드 일때 자식 0
			if (current->left == NULL && current->right == NULL) {
				delete[] current;
				current = 0;
				CheckBalance(current);
				return;
			}
			//삭제할 노드의 자식이 왼쪽 하나
			else if (current->left != NULL && current->right == NULL) {
				//current의 자식을 current로 만들고 원래꺼 삭제
				nodeptr *temp;
				temp = current;
				current = current->left;
				delete[] temp;
				CheckBalance(current);
				return;
			}
			//삭제할 노드의 자식이 오른쪽 하나
			else if (current->left == NULL && current->right != NULL) {
				nodeptr *temp;
				temp = current;
				current = current->right;
				delete[] temp;
				CheckBalance(current);
				return;
			}
			//삭제할 노드의 자식이 두개 다
			else {
				//오른쪽 자식의 왼쪽자식을 따라가서 그 값을 current에주고
				//끝까지 따라간 노드 삭제
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
				//temp가 교체노드
				current->data = rightchild->data;
				delete[] rightchild;
				CheckBalance(current);
				return;
			}
		}
	}
}

//지나가는 경로 출력
void bstree::Search(const int &key, nodeptr &currentNode) {
	//key값이랑 데이터값이랑 비교하면서 큐에 넣고출력
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

//위에서부터 데이터, 왼자식, 오른자식 출력
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
		//지나갈때마다 높이 1씩증가
		//insert 되면 currentSize(treesize) 1씩 증가
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
//밸런스 체크, 부모노드 따라가며 체크
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