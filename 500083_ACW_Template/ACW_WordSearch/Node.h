#pragma once
#include <string>

using namespace std;

class Node
{
public:
	Node();
	explicit Node(const string& word);
	Node(const Node& n) = delete;
	Node& operator =(const Node& n) = delete;
	~Node();
	
	const string& GetWord() const;
	void SetWord(const string& word);

	const Node* GetLeft() const;
	const Node* GetRight() const;

	void SetLeft(const Node* node) const;
	void SetRight(const Node* node) const;

private:
	string m_word;
	mutable const Node* m_left;
	mutable const Node* m_right;
};