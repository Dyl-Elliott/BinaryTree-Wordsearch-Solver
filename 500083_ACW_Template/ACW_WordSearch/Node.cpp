#include "Node.h"

#include <string>

// Default Constructor
// Made null pointers in initialization list
Node::Node() : m_left(nullptr), m_right(nullptr)
{ }

// This method is used to create a new node object whereby a word which is inserted into the Binary Tree by
// passing a reference to the word that has been passed.
Node::Node(const string& word) : m_word(word), m_left(nullptr), m_right(nullptr)
{ }

// Destructor
Node::~Node()
= default;



// This method is passed a referenced string parameter which is then passed to set 'm_word'.
void Node::SetWord(const string& word)
{
	m_word = word;
}

// This method retrieves the 'm_word' currently set and returns this string as a reference to be returned.
const string& Node::GetWord() const
{
	return m_word;
}

// This methods returns a Node pointer which is designed to access the left side of nodes from within the populated
// Binary Tree.
const Node* Node::GetLeft() const
{
	return m_left;
}

// This methods returns a Node pointer which is designed to access the right side of nodes from within the populated
// Binary Tree.
const Node* Node::GetRight() const
{
	return m_right;
}

// This method sets 'm_left' node pointer give then node pointer passed through the parameter when the method is called.
void Node::SetLeft(const Node* const node) const
{
	m_left = node;
}

// This method sets 'm_right' node pointer give then node pointer passed through the parameter when the method is called.
void Node::SetRight(const Node* const node) const
{
	m_right = node;
}
