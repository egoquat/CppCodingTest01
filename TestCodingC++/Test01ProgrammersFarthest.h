#pragma once
#include <iostream>
#include <string>
#include <vector>

#define NULL_NODE -1;
#define MAX_UINT 0xffffffff;

using namespace std;
typedef unsigned int uint;

class Node
{
	static Node* _root;
	static vector<int> _goals;
	static Node** _nodes;
	static int _count;

private:

	vector<int> _adjacents;

	int _nodeToGoal = NULL_NODE;
	uint _distanceToGoal = MAX_UINT;
	int _node = NULL_NODE;
	bool _isGoal = false;

private:

	template<typename T>
	static bool Remove(vector<T>& v, const T r)
	{
		if (v.size() <= 0) return false;

		bool isFound = false;

		typedef typename vector<T>::iterator iter_v;

		iter_v iter = v.begin();
		for (; iter != v.end(); ++iter)
		{
			if (r == *iter)
			{
				isFound = true;
				break;
			}
		}

		if (true == isFound)
		{
			v.erase(iter);
		}
		return isFound;
	}

	template<typename T>
	static bool AddNotOverlap(vector<T> &v, const T t)
	{
		typedef typename vector<T>::iterator iter_v;

		iter_v iter = std::find(v.begin(), v.end(), t);
		if (v.end() == iter)
		{
			v.push_back(t);
			return true;
		}

		return false;
	}

private:

	static Node* GetNode(int node)
	{
		return _nodes[node];
	}

public:

	static void Init(const int N)
	{
		_nodes = new Node*[N];

		for (int i = 0; i < N; ++i)
		{
			_nodes[i] = new Node(i);
		}
	}

	static void ClearAll()
	{
		if (0 == _count) return;

		for (int i = 0; i < _count; ++i)
		{
			Node* n = _nodes[i];
			delete n;
		}

		delete[] _nodes;
		_nodes = nullptr;

		_goals.clear();
	}

	static void AddLink(const int nodeA, const int nodeB)
	{
		Node* N = GetNode(nodeA);
		N->AddAdjacent(nodeB);

		N = GetNode(nodeB);
		N->AddAdjacent(nodeA);
	}

	static void RemoveLink(const int nodeA, const int nodeB)
	{
		Node* N = GetNode(nodeA);
		N->RemoveAdjacent(nodeB);

		N = GetNode(nodeB);
		N->RemoveAdjacent(nodeA);

		for (int i = 0; i < _count; ++i)
		{
			_nodes[i]->ClearToGoal();
		}

		for (uint i = 0; i < _goals.size(); ++i)
		{
			GetNode(_goals[i])->MappingPath();
		}
	}

	static void SetAsGoal(int g)
	{
		Node* goal = GetNode(g);
		goal->SetGoal();
		goal->MappingPath();
	}

	static void GetWayToGoal(int nodeStart, vector<int>& wayToGoal)
	{
		Node* N = GetNode(nodeStart);
		wayToGoal.push_back(N->GetNodeIdx());

		while (N->IsGoal() == false)
		{
			N = GetNode(N->GetNodeToGoal());
			wayToGoal.push_back(N->GetNodeIdx());
		}
	}

	static int GetNextWayToGoal(int nodeStart)
	{
		return GetNode(nodeStart)->GetNodeToGoal();
	}

public:
	bool IsGoal()
	{
		return _isGoal;
	}

	void SetGoal()
	{
		_isGoal = true;
		AddNotOverlap(_goals, _node);
	}

	int GetNodeIdx()
	{
		return _node;
	}

	int GetNodeToGoal()
	{
		return _nodeToGoal;
	}

	const vector<int> GetAdjacents()
	{
		return _adjacents;
	}

	void SetToGoal(const int nodeTo, const uint distance)
	{
		if (distance < _distanceToGoal)
		{
			_nodeToGoal = nodeTo;
			_distanceToGoal = distance;
		}
	}

	void ClearToGoal()
	{
		_nodeToGoal = NULL_NODE;
		_distanceToGoal = MAX_UINT;
	}

private:

	void MappingPath()
	{
		static uint counting = 0;
		MappingPathR(_node, 0, counting);
	}

	void MappingPathR(const int from, const uint distance, uint& counting)
	{
		if (distance > _distanceToGoal)
		{
			return;
		}

		uint D = distance;

		SetToGoal(from, D++);
		counting++;

		for (uint i = 0; i < _adjacents.size(); ++i)
		{
			GetNode(_adjacents[i])->MappingPathR(_node, D, counting);
		}
	}

	void AddAdjacent(const int a)
	{
		AddNotOverlap(_adjacents, a);
	}

	void RemoveAdjacent(const int a)
	{
		Remove(_adjacents, a);
	}

	Node(int node)
	{
		_node = node;
		_count++;
	}

	~Node()
	{
		_count--;
	}
};
Node* Node::_root;
vector<int> Node::_goals;
Node** Node::_nodes;
int Node::_count;

