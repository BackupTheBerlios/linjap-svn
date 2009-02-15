#ifndef QUEUE_H
#define QUEUE_H

#include "LinkNode.h"
#include <iostream>
#include <glibmm/ustring.h>

class Queue 
{
	public:
		Queue();
		~Queue();
		void stack(LinkNode::LinkNode* node);
		LinkNode::LinkNode* pop();
		bool is_empty();
		int size();
		
	private:
		LinkNode::LinkNode *next;
		LinkNode::LinkNode *last;
		int var_size;
};
#endif