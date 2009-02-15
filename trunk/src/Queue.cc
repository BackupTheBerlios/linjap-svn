#include "Queue.h"
using namespace std;

Queue::Queue()
{
	next = NULL;
	last = NULL;
	var_size = 0;
}

Queue::~Queue()
{
//TODO Make Deconstructor

}

void Queue::stack(LinkNode::LinkNode* node)
{
	Glib::ustring test_jap = node->get_jap();
	Glib::ustring test_eng = node->get_eng();
	if (false) cout << "--Stack()--" << endl;
	if (node == NULL) {
		cout << "Node == NULL" << endl;
	} else if (test_jap.size() <= 0 || test_eng.size() <= 0) {
		cout << "In node == NULL" << endl;
	}
	if (node != NULL) {
		if (last != NULL) {
			//cout << "last != null" << endl;
			last->set_next(node);
			last = node;
		} else {
			//cout << "last == null" << endl;
			next = node;
			last = node;
		}
	} else {
		cout << "We get a nullnode in stack?!?!" << endl;
	}
	//cout << "size ++" << endl;
	var_size++;
}

LinkNode::LinkNode* Queue::pop()
{
	if (next != NULL) {
		LinkNode::LinkNode *tmp = next;
		if (next->has_next()) {
			next = next->get_next();
		} else {
			next = NULL;
			last = NULL;
		}
		var_size--;
		return tmp;
	} else {
		return NULL;
	}
}

int Queue::size()
{
	return var_size;
}

bool Queue::is_empty()
{
	if (var_size <= 0) {
		return true;
	}
	return false;
}

