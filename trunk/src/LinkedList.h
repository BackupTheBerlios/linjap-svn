#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinkNode.h"
#include <glibmm/ustring.h>
#include <string>
#include <cstdlib>
using namespace Glib;

class LinkedList 
{
	public:
		LinkedList();
		~LinkedList();
		void add(LinkNode::LinkNode *node);
		LinkNode::LinkNode* get(int chap/*, int part*/); //What is this fucking part?
		int size();
		void clear();
		bool read_file(std::string name);
		
	private:
		LinkNode::LinkNode *first;
};
#endif
