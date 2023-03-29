#pragma once
#include "BinaryTree.h"

#include <string>
#include <vector>

using namespace std;

class WordSearch
{
public:
	//std::vector<std::string> m_discovered_words;

	WordSearch();
	WordSearch(const WordSearch& w) = delete;
	WordSearch& operator=(WordSearch& w) = delete;
	~WordSearch();
	explicit WordSearch(const char * const filename);

	void readSimplePuzzle();
	void readSimpleDictionary();
	void readAdvancedPuzzle();
	void readAdvancedDictionary();
	void solvePuzzleSimple();
	void solvePuzzleAdvanced();
	void writeResults(const	double loadTime, const double solveTime);

	int GetGridSize() const;
	void UnmatchedWordsDiscoveredSimple();
	void UnmatchedWordsDiscoveredBinaryTree();

private:
	BinaryTree m_binary_tree;

	std::vector<std::string> m_word_dictionary;
	std::vector<std::string> m_discovered_words;
	std::vector<std::string> m_discovered_coordiantes;
	std::vector<std::string> m_unmatched_word_list;

	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	const char* m_filePath;

	int m_grid_size{}; 
	int m_dictionary_size{}; 
	int m_grid_cells_visited{};
	int m_dict_entries_visited{};

	char m_word_puzzle[9][9]{}; // <----- may need modding manually to change puzzle size.
};
