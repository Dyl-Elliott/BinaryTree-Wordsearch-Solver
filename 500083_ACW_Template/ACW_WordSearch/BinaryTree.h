#pragma once
#include <vector>

#include "Node.h"

using namespace std;
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(const BinaryTree& bt) = delete;
	BinaryTree& operator=(const BinaryTree& bt) = delete;
	~BinaryTree();

	void AddNode(const Node* const nodeWord); // Entry point
	const Node* GetRoot() const;

	void FindNodeTraversal(const Node* const node, int i, int j, char grid[][9], int& grid_size, vector<string>& discovered_words, vector<string>& discovered_co_ordinates, int& grid_cells_visited, int& dict_entries_visited);
	void CheckGridCell(const int i, const int j, const char grid[][9], const int& grid_size, const string& word, vector<string>& discovered_words, vector<string>& discovered_co_ordinates, int& grid_cells_visited) const;

	void DeleteTree(const Node* const node);

private:
	// as part of recursion, does not need to be public
	void AddNode(const Node* const node, const Node* const parent); // can only call it if part of this class

	const Node* m_root;
};

