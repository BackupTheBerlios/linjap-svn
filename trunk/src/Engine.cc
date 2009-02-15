#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include "Engine.h"
using namespace std;

static int MAX_RAND_WORDS = 3;

Engine::Engine() 
{
	list = new LinkedList();
	practise_queue = NULL;
	wrong_queue = NULL;
	srand((unsigned)time(0));
	total = 0;
}

Engine::Engine(std::string filename)
{
	list = new LinkedList();
	haslist = list->read_file(filename);
	practise_queue = NULL;
	wrong_queue = NULL;	
	srand((unsigned)time(0));
	total = 0;
	number_wrong = 0;
}

Engine::~Engine()
{
	
}

int Engine::words_total()
{
	return total;
}

int Engine::wrong_total()
{
	return number_wrong;
}

bool Engine::has_next() {
	return false;
}

int Engine::words_left() {
	if (practise_queue != NULL) {
		if(wrong_queue != NULL) {
			return (practise_queue->size() + wrong_queue->size());
		} else {
			return practise_queue->size();
		}
	} else {
		return 0;	
	}
}

bool Engine::prepare_session(int chap/*, int part*/)
{
	delete practise_queue;
	delete wrong_queue;
	
	practise_queue = NULL;
	wrong_queue = NULL;
	if (list->size() != 0) {
		Queue::Queue *temp = new Queue(); 
		LinkNode::LinkNode *line = list->get(chap/*, part*/);
		bool has_all = false;
		
		while(!has_all && line->has_next()) {
			
			if(line->get_chap() == chap) {
       			int random_integer = (rand()%MAX_RAND_WORDS)+1;
 				for(int index=0; index<random_integer; index++){ 
					LinkNode::LinkNode *node = new LinkNode(line->get_eng(), line->get_jap(), line->get_kanji(), line->get_chap(), line->get_part());
					temp->stack(node);
    			} 
				
			} else {
				has_all = true;
			}
			line = line->get_next();
		}
		
		int length = temp->size();
		LinkNode::LinkNode* mk_random[length];
		
		int x = 0;
		while (!temp->is_empty()) {
			mk_random[x++] = temp->pop();
		}
		
		practise_queue = new Queue();
		
		for (; length > 0; length--) {
			int random_integer = (rand()%length);
			practise_queue->stack(mk_random[random_integer]);
			mk_random[random_integer] = mk_random[length - 1];
		}
		
	}
	
	number_wrong = 0;
	total = practise_queue->size();
	return true;
}

bool Engine::prepare_session()
{	
	//cout << "--- Prepare Session () ---" << endl;
	int length = wrong_queue->size();
	LinkNode::LinkNode *mk_random[length];
		
	int x;
	for (x = 0; x < length; x++) {
		mk_random[x] = wrong_queue->pop();
	}
	
	delete practise_queue;
	practise_queue = new Queue();
	
	for (; length > 0; length--) {
		int random_integer = (rand()%length);
		practise_queue->stack(mk_random[random_integer]);
		mk_random[random_integer] = mk_random[length - 1];
	}
	
	return true;
}

LinkNode::LinkNode* Engine::next()
{
	//cout << "-- Next() --" << endl;
	if (practise_queue != NULL ) {
		if (!practise_queue->is_empty()) {
			//cout << "Poping from practise_queue" << endl;
			//cout << practise_queue->size() << endl;
			return practise_queue->pop();
		} else if (!wrong_queue->is_empty()) {
			//cout << "Creating new practise_queue from wrong_queue" << endl;
			this->prepare_session();
			return practise_queue->pop();
		} else {
			//cout << "Everything is empty" << endl;
			return NULL;
		}
	} else {
		//cout << "No queue created" << endl;
		return NULL;
	}
}

void Engine::wrong(LinkNode::LinkNode *node)
{
	if (wrong_queue == NULL) {
		wrong_queue = new Queue();
	}
	
	int random_integer = (rand()%4)+2;
	total += random_integer;
	for(int index=0; index < random_integer; index++){ 
		wrong_queue->stack(new LinkNode(node->get_eng(), node->get_jap(), node->get_kanji(), node->get_chap(), node->get_part()));
    }
	number_wrong++;
}

bool Engine::has_list() {
	return haslist;
}
