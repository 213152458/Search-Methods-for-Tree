#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Tree.hpp"
using namespace std;

void printInform(treeNode<>* ptrNode, const int nodeDataDim)
{
	printf("node Index: %d ", ptrNode->m_nodeIndex);
	printf("node Data:");
	for (int i = 0; i < nodeDataDim; i++) {
		printf("%.3f ", ptrNode->m_data[i]);//保留3位小数
	}
	printf("\n");
}


void main(int argc, char** argv)
{
	// This is the code for testing the search Tree in
	//
	//  'The first project homework for Artifical Intelligence'
	// 
	// Yangang Wang, 2018/10/10, @SEU
	//

	// initialize the search tree
	Tree<>* ptrTree = new Tree<>();

	// read the search tree data
	ifstream infile("D:\\joint.txt");
	string line;

	if (infile.is_open())
	{//建立搜索树
		while (getline(infile, line))
		{
			treeNode<>* ptrNode = new treeNode<>();

			// read the data
			stringstream ss(line);
			string item;
			getline(ss, item, ' '); ptrNode->m_nodeName = item;
			getline(ss, item, ' '); ptrNode->m_nodeIndex = atoi(item.c_str());//ascii to integer
			ptrNode->m_data = new float[nodeDataDim];
			for (int i = 0; i < nodeDataDim; i++) {
				getline(ss, item, ' '); ptrNode->m_data[i] = atof(item.c_str());
			}
			getline(ss, item, ' ');
			ptrNode->m_ptrParentnodeIndex = atoi(item.c_str());
			if (ptrNode->m_ptrParentnodeIndex < 0) ptrTree->insert(ptrNode,nullptr);
			else {
				ptrNode->m_ptrParent = ptrTree->getNodePointer(ptrNode->m_ptrParentnodeIndex);
				ptrTree->insert(ptrNode, ptrNode->m_ptrParent);
			}
		}
		infile.close();
	}

	// Test the method
	//float dataPoint[3] = { 2.3,-1.5,-3.9 };
	float dataPoint[3] = {0,0,0.5};
	treeNode<>* ptrNode = nullptr;


	Tree<>* ptrTree2 = new Tree<float>();
	ptrTree2 = ptrTree;
	//Tree<>* ptrTree2 = new Tree<>(*ptrTree);
//	ptrTree2->~Tree();
	// change the search method
	cout << "重载后" << endl;
	cout << "searchMethed:BFS" << endl;
	cout << endl;
	ptrTree2->changeSeachMethod(searchMethod::DFS);
	ptrNode = ptrTree2->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree2->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree2->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	cout << "nodeNum:	 " << ptrTree2->getNodeNum() << endl;
	cout << "endsizenodeNum:	 " << ptrTree2->getEndSiteNodeNum() << endl;
	cout << endl;
	//ptrTree2->~Tree();

	// change the search method
	cout << "重载前" << endl;
	cout << "searchMethed:BFS" << endl;
	cout << endl;
	ptrTree->changeSeachMethod(searchMethod::BFS);
	ptrNode = ptrTree->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	cout <<"nodeNum:	 "<< ptrTree->getNodeNum()<<endl;
	cout << "endsizenodeNum:	 " << ptrTree->getEndSiteNodeNum()<<endl;
	cout<< endl;

	// change the search method
	cout << "searchMethed:DFS" << endl;
	cout << endl;
	ptrTree->changeSeachMethod(searchMethod::DFS);
	ptrNode = ptrTree->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	cout << "nodeNum:	 " << ptrTree->getNodeNum() << endl;
	cout << "endsizenodeNum:	 " << ptrTree->getEndSiteNodeNum() << endl;
	cout << endl;
	
	// change the search method
	cout << "searchMethed:UCS" << endl;
	cout << endl;
	ptrTree->changeSeachMethod(searchMethod::UCS);
	ptrNode = ptrTree->getNodePointer("joint15");
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getNodePointer(10);
	printInform(ptrNode, nodeDataDim);
	ptrNode = ptrTree->getClosetNodePointer(dataPoint, nodeDataDim);
	printInform(ptrNode, nodeDataDim);
	ptrTree->~Tree();
	//delete ptrTree;
}