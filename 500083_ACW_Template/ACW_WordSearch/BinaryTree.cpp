#include "BinaryTree.h"

#include <iostream>
#include <vector>

using namespace std;

BinaryTree::BinaryTree() : m_root(nullptr)
{ }

BinaryTree::~BinaryTree()
{
	if (m_root != nullptr)
	{
		try
		{
			DeleteTree(m_root);
		}
		catch (const std::exception& e)
		{
			cerr << e.what() << endl;
		}
	}
}

// Deletes newly created nodes upon unwinding from end node back to the root node in order of how it was inserted.
void BinaryTree::DeleteTree(const Node* const node)
{
	if (node->GetLeft() != nullptr)
	{
		DeleteTree(node->GetLeft());
	}

	if (node->GetRight() != nullptr)
	{
		DeleteTree(node->GetRight());
	}

	if(node == m_root)
	{
		delete m_root;
	}
	else
	{
		delete node;
	}
}

// This method is designed to get the root node which has been set and return this node to the solveAdvancedPuzzle
// once attempting to traverse through the graph.
const Node* BinaryTree::GetRoot() const
{
	return m_root;
}

// This method defines a hierarchical tree structure for which the words are inserted alphabetically into each node throughout the Binary Tree. Each word is checked to see
// if its characters current indexed values are lower or higher of that given by the root node previously set, this occurs once the root has been
// set and the next location of insertion is to be defined.
// From here recursive calls define the inclusion of further nodes to be allocated within the node structure of the Binary Tree and on insertion.
// If the value of each index is found to be the same a size comparison is adjudicated on each word being checked - if the words are the same length
// then the loop continues, else the word being checked against' size is compared - if the size is smaller it is inserted left, else it is set right.
// This continues until all words from the dictionary have been inserted.
void BinaryTree::AddNode(const Node* const nodeWord)
{
	if (m_root == nullptr) // binary tree is empty at this point -->
	{
		m_root = nodeWord; // set root to word passed through parameters

		return;
	}
	else // root is not empty, find next location -->
	{
		for (unsigned int i = 0; i < nodeWord->GetWord().size(); i++) // left
		{
			if (nodeWord->GetWord()[i] < m_root->GetWord()[i]) // lesser in the alphabet than whats already stored in root nodeWord
			{
				if (m_root->GetLeft() == nullptr) // if to the left of the root is a null pointer -->
				{
					m_root->SetLeft(nodeWord); // insert passed node word 
				}
				else
				{
					AddNode(nodeWord, m_root->GetLeft()); // adds a node beyond word to the left of root
					// passes in nodeWord and a parent as root into a recursive method 
				}

				return;
			}
			else if (nodeWord->GetWord()[i] == m_root->GetWord()[i]) // if words the same
			{
				if (nodeWord->GetWord().size() == m_root->GetWord().size()) // checks to whether both words have become the same size
				{
					continue;
				}

				// --- Special Case ---
				// example - PROJECTOR/PROJECT
				else if (nodeWord->GetWord().size() < m_root->GetWord().size()) // lesser / left
				{
					if (i == nodeWord->GetWord().size() - 1) // last index will be 1 less than the size of the word
					{
						m_root->SetLeft(nodeWord);
					}
				}
				else if (nodeWord->GetWord().size() > m_root->GetWord().size())  // greater / right
				{
					if (i == m_root->GetWord().size() - 1) 
					{
						m_root->SetRight(nodeWord);
					}
				}
			}
			else // right
			{
				if (m_root->GetRight() == nullptr) // if to the right of the root is a null pointer -->
				{
					m_root->SetRight(nodeWord); // insert passed node word 
				}
				else
				{
					AddNode(nodeWord, m_root->GetRight()); // adds a node beyond word to the right of root
				}

				return;
			}
		}
	}
}

// This method works similarly to 'AddNode' method above but uses the parent of each node as a reference point to the next node to traverse to
// from within the Binary Tree.
// Root node in public method is checked against the parent node.
// Parent has been changed from a static root node to the node which is passed down by the parameters for the purpose of recursion through the nodes
// of the binary tree.
void BinaryTree::AddNode(const Node* const node, const Node* const parent)
{
	for (unsigned int i = 0; i < node->GetWord().size(); i++)
	{
		if (node->GetWord()[i] < parent->GetWord()[i]) // left
		{
			if (parent->GetLeft() == nullptr)
			{
				parent->SetLeft(node);
			}
			else
			{
				AddNode(node, parent->GetLeft());
			}

			return;
		}
		else if (node->GetWord()[i] == parent->GetWord()[i]) 
		{
			if (node->GetWord().size() == parent->GetWord().size()) 
			{
				continue;
			}
			else if (node->GetWord().size() < parent->GetWord().size()) 
			{
				if (i == node->GetWord().size() - 1) 
				{
					parent->SetLeft(node);
				}
			}
			else if (node->GetWord().size() > parent->GetWord().size()) 
			{
				if (i == parent->GetWord().size() - 1) 
				{
					parent->SetRight(node);
				}
			}
		}
		else // right
		{
			if (parent->GetRight() == nullptr)
			{
				parent->SetRight(node);
			}
			else
			{
				AddNode(node, parent->GetRight());
			}

			return;
		}
	}
}

// Here implements recursive calls designed to discover nodes of words throughout the Binary Tree. each of the parameters passed are included to reflect the same implementation
// of the 'solveSimplePuzzle' method, therefore having access to each variable from the call. These are required to
// check through each word in the binary tree looking for the fist index of each word and attempting to match that with each character from within the grids current incrementation within the 2D arrays index.
// This repeats until all words from within the tree structure have been traversed through on each of these x and y grid co-ordinates.
// Once a character from a word has been matched during nested iteration (in 'solvePuzzleAdvanced), this in turn calls 'CheckGridCell' to traverse through the grid in search of further matching letters.

// In Order-Traversal (left - root - right) based on the nodes which have been inserted alphabetically, then looking through each node within the binary tree searching for a word which matches
// characters from the grid.
void BinaryTree::FindNodeTraversal(const Node* const node, const int i, const int j, char grid[][9], int& grid_size, vector<string>& discovered_words, vector<string>& discovered_co_ordinates, int& grid_cells_visited, int& dict_entries_visited)
{
	dict_entries_visited++; // incrementing dictionary entries

	if (node->GetLeft() != nullptr)
	{
		FindNodeTraversal(node->GetLeft(), i, j, grid, grid_size, discovered_words, discovered_co_ordinates, grid_cells_visited, dict_entries_visited);
	}

	if (grid[i][j] == node->GetWord()[0])
	{
		CheckGridCell(i, j, grid, grid_size, (node->GetWord()), discovered_words, discovered_co_ordinates, grid_cells_visited);
	}

	if (node->GetRight() != nullptr)
	{
		FindNodeTraversal(node->GetRight(), i, j, grid, grid_size, discovered_words, discovered_co_ordinates, grid_cells_visited, dict_entries_visited);
	}
}

// This method implements the traversal and discovery of words within the Binary Tree using the similar implementation of the 'solveSimplePuzzle' method.
// Includes the required parameters to to reflect the same implementation but negates the need to loop through the x and y co-ordinates as this is done in the 'SolvePuzzleAdvanced' method.
void BinaryTree::CheckGridCell(const int i, const int j, const char grid[][9], const int& grid_size, const string& word, vector<string>& discovered_words, vector<string>& discovered_co_ordinates, int& grid_cells_visited) const
{
	bool word_found = false;

	// ------------ LEFT ------------
	if (word_found == false)
	{
		string word_to_match = word; // defines the _word in which we are trying to find
		string matched_word;
		const int x_co = i; // to plot x co-ordinate given position of i from loop
		int y_co = j; // to plot y co-ordinate given position of j from loop		avoid index errors.

		for (unsigned int k = 0; k < word_to_match.length(); k++)
		{
			if (grid_cells_visited > 0)
			{
				grid_cells_visited++;
			}

			// including bounds check -->
			if ((y_co >= 0) && grid[x_co][y_co] == word_to_match[k]) // checks if the character found is the first index of the _word to match 
			{
				matched_word += grid[x_co][y_co]; // string will hold the matched _word if fully matched
				y_co--; // move m_left
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;

			discovered_words.push_back(matched_word); // adds fully matched _word to discovered
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}

	//------------ DOWN ------------
	if (word_found == false)
	{
		string word_to_match = word;
		string matched_word;
		int x_co = i;
		const int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (grid_cells_visited >= 1)
			{
				grid_cells_visited++;
			}

			if ((x_co < grid_size) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co++;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}

	// ------------ RIGHT ------------
	if (word_found == false)
	{

		string word_to_match = word;
		string matched_word;
		const int x_co = i;
		int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (grid_cells_visited >= 1)
			{
				grid_cells_visited++;
			}

			if ((y_co < grid_size) && grid[x_co][y_co] == word_to_match[l]) // range check 
			{
				matched_word += grid[x_co][y_co];
				y_co++;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}

	// ------------ UP ------------
	if (word_found == false)
	{
		string word_to_match = word;
		string matched_word;
		int x_co = i;
		const int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (grid_cells_visited >= 1)
			{
				grid_cells_visited++;
			}

			if ((x_co >= 0) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co--;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}


	// ------------ UP-RIGHT ------------
	if (word_found == false)
	{
		if (grid_cells_visited >= 1)
		{
			grid_cells_visited++;
		}

		string word_to_match = word;
		string matched_word;
		int x_co = i;
		int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (((x_co >= 0) && (y_co < grid_size)) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co--;
				y_co++;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}


	// ------------ RIGHT-DOWN ------------
	if (word_found == false)
	{
		if (grid_cells_visited >= 1)
		{
			grid_cells_visited++;
		}

		string word_to_match = word;
		string matched_word;
		int x_co = i;
		int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (((x_co < grid_size) && (y_co < grid_size)) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co++;
				y_co++;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}

	// ------------ DOWN-LEFT ------------
	if (word_found == false)
	{
		if (grid_cells_visited >= 1)
		{
			grid_cells_visited++;
		}

		string word_to_match = word;
		string matched_word;
		int x_co = i;
		int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (((x_co < grid_size) && (y_co >= 0)) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co++;
				y_co--;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}


	// ------------ LEFT-UP ------------
	if (word_found == false)
	{
		string word_to_match = word;
		string matched_word;
		int x_co = i;
		int y_co = j;

		for (unsigned int l = 0; l < word_to_match.length(); l++)
		{
			if (grid_cells_visited >= 1)
			{
				grid_cells_visited++;
			}

			/*if (y_co >= 0 && y_co < 9)
			{
				
			}*/
			if (((x_co >= 0) && (y_co >= 0)) && grid[x_co][y_co] == word_to_match[l])
			{
				matched_word += grid[x_co][y_co];
				x_co--;
				y_co--;
			}
			else
			{
				break;
			}
		}

		if (word_to_match == matched_word)
		{
			// _word has been found.
			word_found = true;
			discovered_words.push_back(matched_word);
			discovered_co_ordinates.push_back(to_string(i) + " " + to_string(j));
		}
	}
}