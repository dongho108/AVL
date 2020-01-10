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
	//지나가는 경로 출력
	void Search(const int &key, nodeptr &currentNode);

	//위에서부터 데이터, 왼자식, 오른자식 출력
	void Showresult(nodeptr &root);
	void insert(const int &key, nodeptr &currentNode);
	//밸런스 체크, 부모노드 따라가며 체크
	void CheckBalance(nodeptr *&node);
	int getHeight(nodeptr *&node);
	void Rebalance(nodeptr *&node);
	void LLRotation(nodeptr *&node);
	void LRRotation(nodeptr *&node);
	void RRRotation(nodeptr *&node);
	void RLRotation(nodeptr *&node);
	friend bool operator!=(nodeptr a, int b);
};