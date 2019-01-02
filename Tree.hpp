#pragma once
#ifndef _Tree_HPP_
#define _Tree_HPP_

#include <vector>
#include <stack>
#include <string>
#include<queue>
#include<stdlib.h>
#include<cmath>
#include<iostream>
#include<cstring>
#include<array>
//////////////////////////////////////////////////////////////////////
// NOTE: 
//	for the template class, we need to put all the implementation
//	in one file
//
//	Yangang Wang, 2014/08/27, @MSRA
//
//  Modified on 2018/10/10, @SEU
//
const int MaxSize = 100;
int visited[MaxSize] = {0};//判断是否被访问
const int nodeDataDim =3;//结点数据个数
#define SAFE_DELETE(p) \
		{\
			if(p) {\
				delete p; \
				p = nullptr;\
			}\
		}

// search method
enum searchMethod
{
	DFS = 0,
	BFS,
	UCS
};

//////////////////////////////////////////////////////////////////////
// tree node
//
template <class T = float>
struct treeNode
{
	treeNode() : m_ptrParent(nullptr) { m_data = new T(); };

	// data 
	// class T should have constructor and operator =
	T*					m_data;

	// name of the node
	std::string			m_nodeName;

	// ref index for the node
	int					m_nodeIndex;
	int                 m_ptrParentnodeIndex;

	// pointer
	treeNode*				m_ptrParent;

	std::vector<treeNode*>	m_ptrChildren;//指针数组
	//distance to ptrRoot
	float				m_distancetptrRoot;
};

//////////////////////////////////////////////////////////////////////
// tree structure :: base class
//
template <class T = float>
class  Tree
{
protected:
	typedef treeNode<T> node;

public:
	Tree() : m_ptrRoot(nullptr), m_seMeth(DFS) { ; };//default constructor
	Tree(Tree& tree);//shollow copy

	// overload operator =
	virtual Tree& operator=(const Tree& tree);//deep copy 重载

	virtual ~Tree()
	{
		destroy(m_ptrRoot);
	};

public:
	// insert Node
	void insert(node* const ptrNode, node* const ptrParent = nullptr);
	//copy tree
	//void copy();

	// change the search method
	void changeSeachMethod(searchMethod seMeth = DFS) { m_seMeth = seMeth; };

	// get the number of node
	const int	getNodeNum() const;

	// get the number of endsite node
	const int	getEndSiteNodeNum() const;

	// get the node pointer according to the nodeIndex
	node* const getNodePointer(const int nodeIndex);

	// get the node pointer according to the nodeName
	node* const getNodePointer(const char* nodeName);

	// get the node pointer closet to the given data point
	node* const getClosetNodePointer(T* ptrData, const int dataDimension);

	// get the root node pointer
	node* const getRootPointer() const { return m_ptrRoot; };

private:
	void destroy(node* ptr) {
		if (ptr == nullptr) return;
		for (int i = 0; i < (int)ptr->m_ptrChildren.size(); i++)
		{
			destroy(ptr->m_ptrChildren[i]);
			SAFE_DELETE(ptr);
		}

	}

private:
	node* m_ptrRoot;//根结点
	searchMethod m_seMeth;//搜索方法
};

//////////////////////////////////////////////////////////////////////
// implementation
//
template<class T>
Tree<T>::Tree( Tree<T>& tree)//shallow copy
{
	destroy(this->m_ptrRoot);
	node* ptrNode = nullptr;
	
	// copy the data
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		node* ptr = nullptr;
		stack<node*>s;
		s.push();
		while (!s.empty())
		{	
			ptrNode = s.top();
			s.pop();
			for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
			{
				s.push(ptrNode->m_ptrChildren[i]);
			}
			treeNode<>* ptrNode = new treeNode<>();
			ptrNode->m_nodeIndex = ptr->m_nodeIndex;

			for (int i = 0; i < nodeDataDim; i++)
			{
				ptrNode->m_data[i] = ptr->m_data[i];
			}
			ptrNode->m_nodeName = ptr->m_nodeName;
			ptrNode->m_ptrParentnodeIndex = ptr->m_ptrParentnodeIndex;
			ptrNode->m_distancetptrRoot = ptr->m_distancetptrRoot;
			ptrNode->m_ptrParent = this->getNodePointer(ptrNode->m_ptrParentnodeIndex);
			this->insert(ptrNode, ptrNode->m_ptrParent);
		}
	}
	break;
	case BFS:
	default:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//Ai Xing ,2018,10/21,
		node* ptr = nullptr;
		queue<node*>q;//队列实现BFS
		q.push(&tree);
		while (!q.empty())
		{
			ptrNode = q.front();

			for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
			{
				q.push(ptrNode->m_ptrChildren[i]);
			}
			q.pop();
			treeNode<>* ptrNode = new treeNode<>();
			ptrNode->m_nodeIndex = ptr->m_nodeIndex;

			for (int i = 0; i < nodeDataDim; i++)
			{
				ptrNode->m_data[i] = ptr->m_data[i];
			}
			ptrNode->m_nodeName = ptr->m_nodeName;
			ptrNode->m_ptrParentnodeIndex = ptr->m_ptrParentnodeIndex;
			ptrNode->m_distancetptrRoot = ptr->m_distancetptrRoot;
			ptrNode->m_ptrParent = this->getNodePointer(ptrNode->m_ptrParentnodeIndex);
			this->insert(ptrNode, ptrNode->m_ptrParent);
		}
	}
	break;
	//this->m_ptrroot = &tree->m_ptrRoot;
	}
}

template<class T>
Tree<T>& Tree<T>::operator=(const Tree<T>& tree)//depth copy
{
	destroy(this->m_ptrRoot);
		// copy the data
	//Tree<>* ptrTree = new Tree<>();
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		
		stack<node*>s;
		node* ptr = nullptr;
		node* ptr2 =(tree.m_ptrRoot);
		s.push(ptr2);
		while (!s.empty())
		{	
			ptr = s.top();
			s.pop();
			if (ptr->m_ptrChildren.size() > 0)
			{	
				for (int i = 0; i < ptr->m_ptrChildren.size(); i++)
				{
					s.push(ptr->m_ptrChildren[i]);
				}
			}
			treeNode<>* ptrNode = new treeNode<>();
			ptrNode->m_nodeIndex = ptr->m_nodeIndex;

			for (int i = 0; i < nodeDataDim; i++)
			{
				ptrNode->m_data[i] = ptr->m_data[i];
			}
			ptrNode->m_nodeName = ptr->m_nodeName;
			ptrNode->m_ptrParentnodeIndex = ptr->m_ptrParentnodeIndex;
			ptrNode->m_distancetptrRoot = ptr->m_distancetptrRoot;
			ptrNode->m_ptrParent= this->getNodePointer(ptrNode->m_ptrParentnodeIndex);
			this->insert(ptrNode,ptrNode->m_ptrParent);
		}
	}
	break;
	case BFS:
	default:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//
		//Ai Xing, 2018/10/21
		
		queue<node*>q;
		visited[MaxSize] = { 0 };
		node* ptr=nullptr;
		node* ptr2 = (tree.m_ptrRoot);
		q.push(ptr2);
		while (!q.empty())
		{
			ptr= q.front();
			//visited[ptr->m_nodeIndex] = 1;
			if ((int)ptr->m_ptrChildren.size() > 0)
				for (int i = 0; i < (int)ptr->m_ptrChildren.size(); i++)
				{
					q.push(ptr->m_ptrChildren[i]);
				}
			q.pop();
			treeNode<>* ptrNode = new treeNode<>();
			ptrNode->m_nodeIndex = ptr->m_nodeIndex;

			for (int i = 0; i < nodeDataDim; i++)
			{
				ptrNode->m_data[i] = ptr->m_data[i];
			}
			ptrNode->m_nodeName = ptr->m_nodeName;
			ptrNode->m_ptrParentnodeIndex = ptr->m_ptrParentnodeIndex;
			ptrNode->m_distancetptrRoot = ptr->m_distancetptrRoot;
			ptrNode->m_ptrParent= this->getNodePointer(ptrNode->m_ptrParentnodeIndex);
			this->insert(ptrNode, ptrNode->m_ptrParent);
		}
	}
	break;
	}
	//this = &ptrTree;
	return *this;//this指Tree
}

template<class T>
void Tree<T>::insert(node* const ptrNode, node* const ptrParent /* = nullptr */)
{
	if (m_ptrRoot != nullptr&&ptrParent == nullptr) {//根结点
		std::string errMsg = "Tree<T>::insert_ptrNode: Can not insert node, only one root for the tree structure!";
		throw std::exception(errMsg.c_str());
	}
	else if (m_ptrRoot == nullptr&&ptrParent == nullptr)//结点为空
		m_ptrRoot = ptrNode;
	else
		ptrParent->m_ptrChildren.push_back(ptrNode);//添加新结点ptrNode

	ptrNode->m_ptrParent = ptrParent;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getNodePointer(const int nodeIndex)
{
	node* ptrNode = nullptr;//出结点
	node* ptrNodein = nullptr;//入结点
	//node* searchptrNode =nullptr;
	if (nodeIndex == -1)
		return nullptr;
	// search the node
	switch (m_seMeth)
	{
	case DFS:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//Ai Xing,2018/10/18
		stack<node*>s;//堆栈实现DFS
		s.push(this->m_ptrRoot);
		while (!s.empty())
		{
			ptrNode = s.top();
			s.pop();
			//visited[ptrNode->m_nodeIndex] = 1;
			if (ptrNode->m_nodeIndex == nodeIndex)
			{
				return ptrNode;
			}
			else 
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{
					s.push(ptrNode->m_ptrChildren[i]);
				}	
			}
		}
		break;
	}
	case BFS:
	{//finished
		//Ai Xing,2018/10/18
		queue<node*>q;//队列实现BFS
		q.push(this->m_ptrRoot);
		while (!q.empty())
		{
			ptrNode = q.front();
			if (ptrNode->m_nodeIndex == nodeIndex)
			{
				return ptrNode;
			}
			else 
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{
					q.push(ptrNode->m_ptrChildren[i]);
				}
					
			}
			q.pop();
		}		
		//cout << visited[0];
		break;
	}
	case UCS:
	{
		//node*  ptr_parent[] = {nullptr};
		int front = -1;
		int rear = -1;
		int index = 0;
		node* ptrnodeChange1 = nullptr;//交换结点指针
		node* ptrnodeChange2 = nullptr;
		node* temp = nullptr;

		node* ptr = nullptr;//目标结点
		//int* ptrnode_Queue[100] = { nullptr };//模拟优先级队列
		array<node*, 30> ptrnode_Queue = { nullptr };
		int node_Parent_Index[21] = { -1 };//父节点索引
		array<float, 21>distance;//存放距离
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i] = 9999;
		}
		ptrnode_Queue[++rear] = this->m_ptrRoot;
		while (front < rear)
		{
			ptrNode = ptrnode_Queue[++front];
			if (ptrNode->m_ptrParent = nullptr)
			{//是根结点？
				ptrNode->m_distancetptrRoot = 0.0;
			}
			if (ptrNode->m_nodeIndex==nodeIndex)
			{
				ptr = ptrNode;
			}
			if ((int)ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{//有孩子就进队列
					ptrNodein = ptrNode->m_ptrChildren[i];
					rear++;
					ptrnode_Queue[rear] = ptrNodein;

					//欧式距离
					float currentdistance = 0;
					for (int i = 0; i < nodeDataDim; i++)
					{
						currentdistance += pow((ptrNode->m_data[i] - ptrNodein->m_data[i]), 2);
					}
					currentdistance = sqrt(currentdistance);
					ptrNodein->m_distancetptrRoot = ptrNode->m_distancetptrRoot + currentdistance;
					if (ptrNodein->m_distancetptrRoot < distance[ptrNodein->m_nodeIndex])
					{//多条路径时取最短路径
						distance[ptrNodein->m_nodeIndex] = ptrNodein->m_distancetptrRoot;
						if(ptrNodein->m_ptrParent!=nullptr)
						node_Parent_Index[ptrNodein->m_nodeIndex] = ptrNodein->m_ptrParent->m_nodeIndex;
					}
					else
						ptrNodein->m_distancetptrRoot = distance[ptrNodein->m_nodeIndex];

					for (int j = rear; j > front; j--)
					{
						ptrnodeChange1 = ptrnode_Queue[j];
						ptrnodeChange2 = ptrnode_Queue[j - 1];
						///添加优先级队列。
						if (ptrnodeChange1->m_distancetptrRoot < ptrnodeChange2->m_distancetptrRoot)
						{
							temp = ptrnode_Queue[j];
							ptrnode_Queue[j] = ptrnode_Queue[j - 1];
							ptrnode_Queue[j - 1] = temp;
							break;
						}
					}
				}
			}
		}
		return ptr;
	}
	break;
	default:
	{
		// Yangang Wang, 2018/10/10, @SEU
		// Ai Xing,2018/10/18,
		std::string errMsg = "Tree<T>::getNodePointer: Can not find nodeIndex,do you have a approprite search mothed like DFS,BFS or UCS";
		throw std::exception(errMsg.c_str());
	}

	}
	return ptrNode;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getNodePointer(const char* nodeName)
{
	if (strlen(nodeName) == 0)
		return nullptr;

	node* ptrNode = nullptr;//出结点
	node* ptrNodein = nullptr;//入结点
	// search the node
	switch (m_seMeth)
	{
	case DFS:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//Ai Xing,2018/10/29
		stack<node*>s;//堆栈实现DFS
		s.push(this->m_ptrRoot);
		while (!s.empty())
		{
			ptrNode = s.top();
			s.pop();
			//visited[ptrNode->m_nodeIndex] = 1;
			if (ptrNode->m_nodeName ==nodeName)
			{
				return ptrNode;
			}
			else
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{
					s.push(ptrNode->m_ptrChildren[i]);
				}
			}
		}
		break;
	}
	case BFS:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//
		//Ai Xing ,2018/10/21
		queue<node*>q;//队列实现BFS
		q.push(this->m_ptrRoot);
		while (!q.empty())
		{
			ptrNode = q.front();
			if (ptrNode->m_nodeName == nodeName)
			{
				return ptrNode;
			}
			else//(searchptrNode->m_ptrChildren.size()>0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{
					ptrNodein = ptrNode->m_ptrChildren[i];
					q.push(ptrNodein);
				}
			}
			q.pop();
		}
		break;
	}
	case UCS:
	default:
	{
		//node*  ptr_parent[] = {nullptr};
		int front=-1;
		int rear = -1;
		int index = 0;
		node* ptrnodeChange1 = nullptr;//交换结点指针
		node* ptrnodeChange2 = nullptr;
		node* temp = nullptr;

		node* ptr = nullptr;//目标结点
		//int* ptrnode_Queue[100] = { nullptr };//模拟优先级队列
		array<node*,30> ptrnode_Queue = {nullptr};
		int node_Parent_Index[21] = { -1 };//父节点索引
		array<float, 21>distance;//存放距离
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i] = 9999;
		}
		ptrnode_Queue[++rear] = this->m_ptrRoot;
		while (front < rear)
		{	
			ptrNode = ptrnode_Queue[++front];
			if (ptrNode->m_ptrParent = nullptr)
			{//是根结点？
				ptrNode->m_distancetptrRoot = 0.0;
			}
			if (ptrNode->m_nodeName == nodeName)
			{
				ptr=ptrNode;
			}
			if ((int)ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{//有孩子就进队列
					ptrNodein = ptrNode->m_ptrChildren[i];
					rear++;
					ptrnode_Queue[rear] = ptrNodein;

					//欧式距离
					float currentdistance = 0;
					for (int i = 0; i < nodeDataDim; i++)
					{
						currentdistance += pow((ptrNode->m_data[i] - ptrNodein->m_data[i]), 2);
					}
					currentdistance = sqrt(currentdistance);
					ptrNodein->m_distancetptrRoot = ptrNodein->m_ptrParent->m_distancetptrRoot + currentdistance;
					if (ptrNodein->m_distancetptrRoot < distance[ptrNodein->m_nodeIndex])
					{//多条路径时取最短路径
						distance[ptrNodein->m_nodeIndex] = ptrNodein->m_distancetptrRoot;
						node_Parent_Index[ptrNodein->m_nodeIndex] = ptrNodein->m_ptrParent->m_nodeIndex;
					}
					else
						ptrNodein->m_distancetptrRoot = distance[ptrNodein->m_nodeIndex];

					for (int j = rear; j > front; j--)
					{
						ptrnodeChange1 = ptrnode_Queue[j];
						ptrnodeChange2 = ptrnode_Queue[j - 1];
						///添加优先级队列。
						if (ptrnodeChange1->m_distancetptrRoot < ptrnodeChange2->m_distancetptrRoot)
						{
							temp = ptrnode_Queue[j];
							ptrnode_Queue[j] = ptrnode_Queue[j - 1];
							ptrnode_Queue[j - 1] = temp;
							break;
						}
					}
				}
			}
		}
		return ptr;
	}
	}
	//for(int i=0;i<dist)
	return ptrNode;
}

template<class T>
typename Tree<T>::node* const Tree<T>::getClosetNodePointer(T* ptrData, const int dataDimension)
{
	if (ptrData == nullptr)
		return nullptr;
	node* ptrNode = nullptr;//出结点
	node* ptrNodein = nullptr;//入结点
	node* closedptrNode = nullptr;
	float leastDisparity = 10086.0;//最短差距。
	float currentDisparity=10086.0 ;//当前点差距。

	// search the node closet to the ptrData
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		stack<node*>s;
		s.push(this->m_ptrRoot);
		while (!s.empty())
		{
			ptrNode=s.top();
			s.pop();
			if ((int)ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
					s.push(ptrNode->m_ptrChildren[i]);
			}
			currentDisparity = 0;//当前点差距。
			for (int i = 0; i < dataDimension; i++)//求距离
			{
				currentDisparity += pow((ptrData[i] - ptrNode->m_data[i]), 2);
			}
			if (currentDisparity <= leastDisparity)//取小值
			{
				closedptrNode = ptrNode;
				leastDisparity = currentDisparity;
			}
		}
	}
	break;
	case BFS:
	{
		// Yangang Wang, 2018/10/10, @SEU
		//
		//Ai Xing,2018/10/22
		queue<node*>q;
		q.push(this->m_ptrRoot);
		//visited[MaxSize] = {0};
		while (!q.empty()) 
		{
			ptrNode = q.front();
			q.pop();
			if ((int)ptrNode->m_ptrChildren.size() > 0)//子节点进队列
			{
				for (int j = 0; j < (int)ptrNode->m_ptrChildren.size(); j++)
					q.push(ptrNode->m_ptrChildren[j]);
			}
			currentDisparity = 0;//当前点差距。
			for (int i = 0; i < dataDimension; i++)//求距离
			{
				currentDisparity += pow((ptrData[i] - ptrNode->m_data[i]), 2);
			}
			if (currentDisparity <= leastDisparity)//取小值
			{
				closedptrNode = ptrNode;
				leastDisparity = currentDisparity;
			}
		
			//visited[(ptrNode->m_nodeIndex)] = 1;//标记
		}
		break;
	}
	case UCS:
	default:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		//优先级队列实现遍历，根据距离排序
		int front = -1;
		int rear = -1;
		int index = 0;

		node* ptrnodeChange1 = nullptr;//交换结点指针
		node* ptrnodeChange2 = nullptr;
		node* temp = nullptr;

		array<node*, 30> ptrnode_Queue = { nullptr };//模拟优先级队列
		int node_Parent_Index[21] = { -1 };//父节点索引
		array<float, 21>distance;//存放距离
		for (int i = 0; i < distance.size(); i++)
		{
			distance[i] = 9999;
		}

		ptrnode_Queue[++rear] = this->m_ptrRoot;
		while (front < rear)
		{
			ptrNode = ptrnode_Queue[++front];
			if (ptrNode->m_ptrParent = nullptr)
			{//是根结点？
				ptrNode->m_distancetptrRoot = 0.0;
			}

			if ((int)ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{//有孩子就进队列
					ptrNodein = ptrNode->m_ptrChildren[i];
					rear++;
					ptrnode_Queue[rear] = ptrNodein;

					//欧式距离
					float currentdistance = 0;
					for (int i = 0; i < nodeDataDim; i++)
					{
						currentdistance += pow((ptrNode->m_data[i] - ptrNodein->m_data[i]), 2);
					}
					currentdistance = sqrt(currentdistance);
					ptrNodein->m_distancetptrRoot = ptrNode->m_distancetptrRoot + currentdistance;
					if (ptrNodein->m_distancetptrRoot < distance[ptrNodein->m_nodeIndex])
					{//多条路径时取最短路径
						distance[ptrNodein->m_nodeIndex] = ptrNodein->m_distancetptrRoot;
						if(ptrNodein->m_ptrParent!=nullptr)
						node_Parent_Index[ptrNodein->m_nodeIndex] = ptrNodein->m_ptrParent->m_nodeIndex;
					}
					else
						ptrNodein->m_distancetptrRoot = distance[ptrNodein->m_nodeIndex];

					for (int j = rear; j > front; j--)
					{
						ptrnodeChange1 = ptrnode_Queue[j];
						ptrnodeChange2 = ptrnode_Queue[j - 1];
						///添加优先级队列。
						if (ptrnodeChange1->m_distancetptrRoot < ptrnodeChange2->m_distancetptrRoot)
						{
							temp = ptrnode_Queue[j];
							ptrnode_Queue[j] = ptrnode_Queue[j - 1];
							ptrnode_Queue[j - 1] = temp;
							break;
						}
					}
				}
			}
			currentDisparity = 0;//当前点差距。
			for (int i = 0; i < dataDimension; i++)//求距离
			{
				currentDisparity += pow((ptrData[i] - ptrNode->m_data[i]), 2);
			}
			if (currentDisparity <= leastDisparity)//取小值
			{
				closedptrNode = ptrNode;
				leastDisparity = currentDisparity;
			}
		}
		return closedptrNode;
	}
	break;
	}

	return closedptrNode;
}

template<class T>
const int Tree<T>::getNodeNum() const
{
	if (m_ptrRoot == nullptr)
		return 0;

	int nodeNum = 0;
	node* ptrNode = nullptr;


	// search the tree
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		stack<node*>s;
		s.push(this->m_ptrRoot);
		while (!s.empty())
		{
			ptrNode = s.top();
			s.pop();
			nodeNum++;
			if (ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
				{
					s.push(ptrNode->m_ptrChildren[i]);
				}
			}
		}
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		queue<node*>q;
		q.push(this->m_ptrRoot);
		while (!q.empty())
		{
			ptrNode=q.front();
			//vistted
			nodeNum++;
			if ((int)ptrNode->m_ptrChildren.size()>0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size(); i++)
					q.push(ptrNode->m_ptrChildren[i]);
			}
			q.pop();

		}
	}
	break;
	}

	return nodeNum;
}

template<class T>
const int Tree<T>::getEndSiteNodeNum() const
{
	if (m_ptrRoot == nullptr)
		return 0;

	int endSiteNodeNum = 0;
	node* ptrNode = nullptr;

	// search the tree
	switch (m_seMeth)
	{
	case DFS:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		stack<node*>s;
		s.push(this->m_ptrRoot);
		while (!s.empty())
		{	
			ptrNode = s.top();
			s.pop();
			if (ptrNode->m_ptrChildren.size() > 0)
			{
				for (int i = 0; i < (int)ptrNode->m_ptrChildren.size();i++)
				{
					s.push(ptrNode->m_ptrChildren[i]);
				}
			}
			else
			{
				endSiteNodeNum++;
			}
		}
	}
	break;
	case BFS:
	default:
	{
		// ==============================
		// fill the code here
		// ==============================
		//
		// Yangang Wang, 2018/10/10, @SEU
		//
		queue<node*>q;
		q.push(this->m_ptrRoot);
		while (!q.empty())
		{
			ptrNode = q.front();
			q.pop();
			if ((int)ptrNode->m_ptrChildren.size()<=0)
				endSiteNodeNum+=1;
			else
				for (int i = 0; i <(int) ptrNode->m_ptrChildren.size(); i++)
					q.push(ptrNode->m_ptrChildren[i]);
		}
		break;
	}
	}
	return endSiteNodeNum;
}

#endif
