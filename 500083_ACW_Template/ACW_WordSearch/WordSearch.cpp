#include "WordSearch.h"
#include "BinaryTree.h"
#include "Node.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

WordSearch::WordSearch() : m_filePath()
{ }

WordSearch::WordSearch(const char* const filename) : m_filePath(filename)
{ }

WordSearch::~WordSearch()
= default;

// This method collates the size of 'm_grid_size' which has been set from the grid read file.
int WordSearch::GetGridSize() const
{
	return m_grid_size;
}



// ---------------------------------------- Simple Implementation ----------------------------------------
//
// This method reads the puzzle and stores the letters in this simple grid data structure by using a input-file-stream
// which reads in the allocated grid text file and populates a 2D char array given each character provided within this file
// into each relevant index from the 'm_word_puzzle' array.
// If the file is deemed to NOT be open, then a "failed to read message" become the exit condition.
void WordSearch::readSimplePuzzle()
{
	ifstream fin(puzzleName); //reads in streamed wordsearch_grid.txt file
	if (!fin.is_open()) 
	{
		cout << "failed to read file." << endl;
	}
	else
	{
		fin >> m_grid_size; // grid size initialized from the first line of .txt file

		for (int i = 0; i < m_grid_size; i++)
		{
			for (int j = 0; j < m_grid_size; j++)
			{
				fin >> m_word_puzzle[i][j]; // writes/inputs into m_word_puzzle char array all characters from .txt file
				//cout << m_word_puzzle[i][j] << " "; // to console
			}
			//cout << "\n";
		}

		//cout << endl;

		fin.close();
	}
}

// This method reads the dictionary and stores the words in the simple dictionary data structure by using an input-file-stream
// which reads in the allocated dictionary of words, each word discovered is then added to 'm_word_dictionary' and the size of this
// variable (denoted by 'm_dictionary_size') is incremented for output performance requirements. This continues until there are no more
// words to be found within the text file.
// If the file is deemed to NOT be open, then a "failed to read message" become the exit condition.
void WordSearch::readSimpleDictionary()
{
	string line;
	ifstream fin(dictionaryName); // read in streamed dictionary.txt file
	if (!fin.is_open())
	{
		cout << "failed to read file." << endl;
	}
	else
	{
		while (!fin.eof()) // not end of stream -->
		{
			fin >> line; // reads per line of words
			m_word_dictionary.push_back(line); // adds word found to vector from .txt file

			m_dictionary_size += 1; // increment how many words found inside the dictionary 
		}
	}

	fin.close();
}

// This method solves the puzzle using the simple grid data structure with the simple dictionary data structure as combination.
// 'i' and 'j' iterate over each index in the 2D char array in turn, firstly traversing over each column index and then
// dropping to a new row each time the grids max capacity has been reached.
// An index iterator is implemented which loops for the size of words to be found from the dictionary, relating each
// words 0th index (first letter of the word) with the character found at current graph index, if the character
// is equal - then relevant checks are performed in multiple directions searching for duplicate values from each variable
// in attempt of finding a complete word within elements of the 2D graph, incremented by 'k'.
// 'x_co' and 'y_co' define the co-ordinates of each iterative search throughout the grid which reflect the values currently help by 'i' and 'j'.
// This is used to ensure no indexing errors occur while traversing through the grid.
// Additional bounds checking has been implemented which ensures when indexing through directions of the grid that no out of bounds
// occurs throughout all directions available.
// Extra entries 'm_grid_cells_visited' and 'm_dict_entries_ visited' are incremented for the purpose of output performance requirements.
// If a word has being matched 'word_found' is set to true, then the word along with its co-ordinates of discovery are added to relevant variables.
// The implementation of this method continues until reaching the end of the grid.
void WordSearch::solvePuzzleSimple()
{
	for (int i = 0; i < m_grid_size; i++) // pos x for row
	{
		for (int j = 0; j < m_grid_size; j++) // pos y for column
		{
			m_grid_cells_visited++; // <--

			for (int index = 0; index < m_dictionary_size; index++) // loops for the size of words to be found from the dictionary .txt file
			{
				m_dict_entries_visited++; // <---

				if (m_word_puzzle[i][j] == m_word_dictionary[index][0]) // checks the first index of the m_word to be found -->
				{
					bool word_found = false;

					// ------------ LEFT ------------
					if (word_found == false)
					{
						string word_to_match = m_word_dictionary[index]; // defines the m_word in which we are trying to find
						string matched_word;
						const int x_co = i; // to plot x co-ordinate given position of i from loop		//  MADE CONST
						int y_co = j; // to plot y co-ordinate given position of j from loop

						for (unsigned int k = 0; k < word_to_match.length(); k++)
						{
							if (m_grid_cells_visited > 0)
							{
								m_grid_cells_visited++;
							}

							// including bounds check -->
							if ((y_co >= 0) && m_word_puzzle[x_co][y_co] == word_to_match[k]) // checks if the character found is the first index of the m_word to match 
							{
								matched_word += m_word_puzzle[x_co][y_co]; // string will hold the matched m_word if fully matched
								y_co--; // move m_left
							}
							else
							{
								break;
							}
						}

						if (word_to_match == matched_word)
						{
							// m_word has been found.
							word_found = true;

							m_discovered_words.push_back(matched_word); // adds fully matched m_word to discovered
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					//------------ DOWN ------------
					if (word_found == false)
					{
						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						const int y_co = j; //  MADE CONST

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (m_grid_cells_visited >= 1)
							{
								m_grid_cells_visited++;
							}

							if ((x_co < m_grid_size) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
								x_co++;
							}
							else
							{
								break;
							}
						}

						if (word_to_match == matched_word)
						{
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					// ------------ RIGHT ------------
					if (word_found == false)
					{

						string word_to_match = m_word_dictionary[index];
						string matched_word;
						const int x_co = i; //  MADE CONST
						int y_co = j;

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (m_grid_cells_visited >= 1)
							{
								m_grid_cells_visited++;
							}

							if ((y_co < m_grid_size) && m_word_puzzle[x_co][y_co] == word_to_match[l]) // range check 
							{
								matched_word += m_word_puzzle[x_co][y_co];
								y_co++;
							}
							else
							{
								break;
							}
						}

						if (word_to_match == matched_word)
						{
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					// ------------ UP ------------
					if (word_found == false)
					{
						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						const int y_co = j; //  MADE CONST

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (m_grid_cells_visited >= 1)
							{
								m_grid_cells_visited++;
							}

							if ((x_co >= 0) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
								x_co--;
							}
							else
							{
								break;
							}
						}

						if (word_to_match == matched_word)
						{
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}


					// ------------ UP-RIGHT ------------
					if (word_found == false)
					{
						if (m_grid_cells_visited >= 1)
						{
							m_grid_cells_visited++;
						}

						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						int y_co = j;

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (((x_co >= 0) && (y_co < m_grid_size)) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
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
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					// ------------ RIGHT-DOWN ------------
					if (word_found == false)
					{
						if (m_grid_cells_visited >= 1)
						{
							m_grid_cells_visited++;
						}



						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						int y_co = j;

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (((x_co < m_grid_size) && (y_co < m_grid_size)) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
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
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					// ------------ DOWN-LEFT ------------
					if (word_found == false)
					{
						if (m_grid_cells_visited >= 1)
						{
							m_grid_cells_visited++;
						}

						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						int y_co = j;

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (((x_co < m_grid_size) && (y_co >= 0)) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
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
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}

					// ------------ LEFT-UP ------------
					if (word_found == false)
					{
						string word_to_match = m_word_dictionary[index];
						string matched_word;
						int x_co = i;
						int y_co = j;

						for (unsigned int l = 0; l < word_to_match.length(); l++)
						{
							if (m_grid_cells_visited >= 1)
							{
								m_grid_cells_visited++;
							}



							if (((x_co >= 0) && (y_co >= 0)) && m_word_puzzle[x_co][y_co] == word_to_match[l])
							{
								matched_word += m_word_puzzle[x_co][y_co];
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
							// m_word has been found.
							word_found = true;
							m_discovered_words.push_back(matched_word);
							m_discovered_coordiantes.push_back(to_string(i) + " " + to_string(j));
						}
					}
				}
			}
		}
	}

	//for (const string m_word : m_discovered_words) //  MADE CONST
	//{
	//	cout << m_word << endl;
	//}

	//for (const string coordinate : m_discovered_coordiantes) //  MADE CONST
	//{
	//	cout << coordinate << endl;
	//}

	UnmatchedWordsDiscoveredSimple();
}

// Each word which has not been discovered throughout traversing the grid is added to 'm_unmatched_words' using
// an vector<> iterator which checks through each word from the dictionary and assessing whether it has been added.
// If when checking discovered words a particular word has not been discovered, that word is added to unmatched variable.
void WordSearch::UnmatchedWordsDiscoveredSimple()
{
	for (unsigned int i = 0; i < m_word_dictionary.size(); i++)
	{
		const auto word_iterator = find(m_discovered_words.begin(), m_discovered_words.end(), m_word_dictionary[i]); //  MADE CONST

		if (word_iterator == m_discovered_words.end())
		{
			m_unmatched_word_list.push_back(m_word_dictionary[i]);
		}
	}
}




// ---------------------------------------- Advanced Implementation ----------------------------------------

// **This method defines the same logic from 'readSimplePuzzle'**
// As part of the simple/advanced data structure combination.
void WordSearch::readAdvancedPuzzle()
{
	ifstream fin(puzzleName); //reads in streamed wordsearch_grid.txt file 
	if (!fin.is_open()) //reads file if open
	{
		cout << "failed to read file." << endl;
	}
	else
	{
		fin >> m_grid_size; // grid size from first line of .txt file

		for (int i = 0; i < m_grid_size; i++)
		{
			for (int j = 0; j < m_grid_size; j++)
			{
				fin >> m_word_puzzle[i][j]; // writes/inputs into m_word_puzzle char array all characters from .txt file
				//cout << m_word_puzzle[i][j] << " "; // to console
			}
			//cout << "\n";
		}

		//cout << endl;
	}

	fin.close();
}

// This method reads the dictionary and stores the words in the advanced dictionary data structure using a Binary Tree for this implementation.
// The dictionary of words are again saved into 'm_word_dictionary' which allows comparison of unmatched-found words within the binary trees data storage which can
// then be replicated in the 'writeResults' method.
// The additional implementation of this method is assigning each word from each 'line' read into individual nodes within the Binary Tree
// represented using 'newWordNode' from within the 'BinaryTree' class through 'm_binary_tree' member variable.
void WordSearch::readAdvancedDictionary()
{
	ifstream fin(dictionaryName); // read in streamed dictionary.txt file
	if (!fin.is_open()) // reads file if open
	{
		cout << "failed to read file." << endl;
	}
	else
	{
		string line;
		while (!fin.eof()) // not end of stream -->
		{
			fin >> line; // reads per line of words
			const Node* const newWordNode = new Node(line); // create a new node for which resembles each word
			m_binary_tree.AddNode(newWordNode); // add each new node of words to the Binary Tree
			m_word_dictionary.push_back(line); // creating dictionary of words to find within binary search

			m_dictionary_size += 1; // increment how many words found inside the dictionary for output purposes
		}
	}

	fin.close();
}

// This method solves the puzzle using the simple grid data structure alongside the advanced dictionary Binary Tree by using reference to
// newly implemented classes 'Node' and 'BinaryTree'.
// 'm_binary_tree' allows implementation of BinaryTree class members, hence the call of 'FindNodeTraversal' from within the BinaryTree class.
// In the method call parameters necessary information is provided to replicate the discovery of cells throughout the grid given by the nested-loop incrementation
// of x and y co-ordiantes from within this method.
void WordSearch::solvePuzzleAdvanced()
{
	for (int i = 0; i < m_grid_size; i++)
	{
		for (int j = 0; j < m_grid_size; j++)
		{
			m_grid_cells_visited++;

			m_binary_tree.FindNodeTraversal(m_binary_tree.GetRoot(), i, j, m_word_puzzle, m_grid_size, m_discovered_words, m_discovered_coordiantes, m_grid_cells_visited, m_dict_entries_visited);
		}
	}

	UnmatchedWordsDiscoveredBinaryTree();
}

// ** This method replaces the same functionality as 'UnmatchedWordsDiscoveredSimple' **
//
// Each word which has not been discovered throughout traversing the grid is added to 'm_unmatched_words' using
// an vector<> iterator which checks through each word from the dictionary and assessing whether it has been added.
// If when checking discovered words a particular word has not been discovered, that word is added to unmatched variable.
void WordSearch::UnmatchedWordsDiscoveredBinaryTree()
{
	for (unsigned int i = 0; i < m_word_dictionary.size(); i++)
	{
		const auto word_iterator = find(m_discovered_words.begin(), m_discovered_words.end(), m_word_dictionary[i]); //  MADE CONST

		if (word_iterator == m_discovered_words.end())
		{
			m_unmatched_word_list.push_back(m_word_dictionary[i]);
		}
	}
}



// ---------------------------------------------- Results ----------------------------------------------
//
// This method will output the results from the previous simple or advanced solve method to the given output file,
// which will be either results_simple_puzzle_simple_dictionary.txt or results_simple_puzzle_advanced_dictionary.txt or results_advanced_puzzle_simple_dictionary.txt.
void WordSearch::writeResults(const double loadTime, const double solveTime)
{

	ofstream output(m_filePath);
	if (output.is_open())
	{
		output << "NUMBER_OF_WORDS_MATCHED" << " " << m_discovered_words.size();

		output << "\n\nWORDS_MATCHED_IN_GRID" << "\n";
		for (unsigned int i = 0; i < m_discovered_coordiantes.size(); i++)
		{
			string x;
			string y;
			string line = m_discovered_coordiantes[i];
			bool flag = false;

			for (unsigned int j = 0; j < line.size(); j++)
			{
				if (line[j] == ' ')
				{
					flag = true;
					continue;
				}
				if (flag == false)
				{
					x += line[j];
					continue;
				}

				y += line[j];
			}

			output << x << " " << y << " " << m_discovered_words[i] << "\n";
		}

		output << "\nWORDS_UNMATCHED_IN_GRID \n";
		for (unsigned int i = 0; i < m_unmatched_word_list.size(); i++)
		{
			output << m_unmatched_word_list[i] << "\n";
		}

		output << "\nNUMBER_OF_GRID_CELLS_VISITED " << m_grid_cells_visited;

		output << "\n\nNUMBER_OF_DICTIONARY_ENTRIES_VISITED " << m_dict_entries_visited;

		output << "\n\nTIME_TO_POPULATE_GRID_STRUCTURE " << loadTime;

		output << "\n\nTIME_TO_SOLVE_PUZZLE " << solveTime << endl;
	}
}