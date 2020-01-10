#include <iostream>
#include <queue>
using namespace std;


struct nodeptr {
	int data;
	int height;
	int size;
	bool visit;
	nodeptr *left;
	nodeptr *right;
	nodeptr *parent;

	nodeptr();
	nodeptr(int obj);
};

class bstree {
	int currentSize;
public:
	bstree();
	void del(const int &key, nodeptr &root);
	//�������� ��� ���
	void Search(const int &key, nodeptr &currentNode);

	//���������� ������, ���ڽ�, �����ڽ� ���
	void Showresult(nodeptr &root);
	void insert(const int &key, nodeptr &currentNode);
	//�뷱�� üũ, �θ��� ���󰡸� üũ
	void CheckBalance(nodeptr *&node);
	int getHeight(nodeptr *&node);
	void Rebalance(nodeptr *&node);
	void LLRotation(nodeptr *&node);
	void LRRotation(nodeptr *&node);
	void RRRotation(nodeptr *&node);
	void RLRotation(nodeptr *&node);
	friend bool operator!=(nodeptr a, int b);
};