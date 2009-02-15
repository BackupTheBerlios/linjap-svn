#ifndef ENGINE_H
#define ENGINE_H

#include "LinkedList.h"
#include "Queue.h"

class Engine
{
	public:
		Engine();
		Engine(std::string filename);
		~Engine();
		int words_total();
		int words_left();
		int wrong_total();
		bool has_next(); //TODO
		bool has_list();
		bool prepare_session(int chap/*, int part*/); // What is this fucking part?
		LinkNode::LinkNode *next();
		void wrong(LinkNode::LinkNode *node);

	private:
		LinkedList::LinkedList *list;
		Queue::Queue *practise_queue;
		Queue::Queue *wrong_queue;
		bool prepare_session();
		int total;
		int number_wrong;
		bool haslist;
};

#endif
