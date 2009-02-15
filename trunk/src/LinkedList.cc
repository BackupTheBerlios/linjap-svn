#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <vector>
#include <glibmm.h>

using namespace std;

LinkedList::LinkedList()
{
	first = NULL;
}

LinkedList::~LinkedList()
{
	
}

void LinkedList::add(LinkNode *node)
{
	//ustring tmp = node->get_eng();
	//const char * c_str = tmp.c_str();
	//cout << c_str << endl;
	
	if (first != NULL) {
		//cout << "First != 0" << endl;
		bool add = false;
		LinkNode::LinkNode *last = NULL;
		LinkNode::LinkNode *current = first;
		
		while(!add && current->has_next()) {
			if (node->get_chap() < current->get_chap()) {
				if(last != NULL) {
					node->set_next(current);
					last->set_next(node);
					add = true;
				} else {
					node->set_next(current);
					first = node;
					add = true;
				}
			} else if (node->get_chap() == current->get_chap()) {
				bool part_add = false;
				while(!part_add && current->has_next()){
					if (node->get_part() < current->get_part()){
						if(last != NULL) {
							node->set_next(current);
							last->set_next(node);
							part_add = true;
							add = true;
						} else {
							node->set_next(current);
							first = node;
							part_add = true;
							add = true;
						}
					} else if (node->get_part() == current->get_part()) {
						node->set_next(current->get_next());
						current->set_next(node);
						part_add = true;
						add = true;
					} else {
						last = current;
						current = current->get_next();
					}
				}
			} else {
				last = current;
				current = current->get_next();
			}
		}
		if(!add) current->set_next(node);
	} else {
		//cout << "First = node " << endl;
		first = node;
	}
}

LinkNode::LinkNode* LinkedList::get(int chap)
{
	if (first != NULL) {
		LinkNode::LinkNode *current = first;
		
		while (current->has_next()) 
		{
			int cchap = current->get_chap();
			//int cpart = current->get_part();
			
			//cout << "chap: " << cchap << " pt:" << cpart << endl;
			if (chap == cchap /* && (part == cpart)*/){
				return current;
			}
			current = current->get_next();
		}
		
		cout << "Returning NULL" << endl;
		return NULL;
	} else {
		cout << "there is no first" << endl;
		return NULL;
	}
}

int LinkedList::size()
{
	if (first != 0) {
		int size = 1;
		LinkNode::LinkNode *current = first;
		while (current->has_next()) {
			current = current->get_next();
			size++;
		}
		return size;
	} else {
		return 0;
	}
}

void LinkedList::clear()
{
	first = NULL;
}

bool LinkedList::read_file(string name)
{
	cout << "Running read file with: " << name << endl;
	try {
		ifstream myfile(name.c_str());
		
		if(myfile.is_open()){
			LinkNode::LinkNode *node = NULL;
			
			while(!myfile.eof()) {
				string mystr;
				getline(myfile, mystr);
				const char *c_str = mystr.c_str();
				if (mystr.at(0) != '#') {
					vector<string> strs;
					boost::split(strs, mystr, boost::is_any_of("|"));
					if (strs.size() > 3) {
						//cout << "Hiragana/Katakana: " << strs.at(0) << endl;
						//cout << "Kanji: " << strs.at(1) << endl;
						//cout << "English: "<< strs.at(2) << endl;
					
						ustring jap(Glib::convert(strs.at(0), "UTF-8", "UTF-8"));
						ustring knji(Glib::convert(strs.at(1), "UTF-8", "UTF-8"));
						ustring eng(Glib::convert(strs.at(2), "UTF-8", "UTF-8"));
					
						string tmp = strs.at(3);
						
						int chap = 0;
						if (tmp.size() > 1) {
							chap = ((tmp.at(0) - 48) * 10);
							chap += (tmp.at(1) - 48);
						} else {
							chap = (tmp.at(0) - 48);
						}
						//cout << chap << endl;
					
						tmp = strs.at(4);
						int part = (tmp.at(0) - 48);
						//cout << part << endl;
						
						if(jap.size() <= 0){
							cout << "In node jap == NULL" << endl;
						}
						if (eng.size() <= 0) {
							cout << "In node eng == NULL" << endl;
						}
						if(knji.size() <= 0) {
							cout << "In node kanji == NULL" << endl;
						}
						if (knji.size() > 0 && jap.size() > 0 && eng.size() > 0){
							node = new LinkNode(eng, jap, knji, chap, part);
							this->add(node);
						}
					} else {
						cout << "Not enough arguments" << endl;
						
					}
				}
			}
			myfile.close();
			cout << "List made, Size : " << this->size() << endl;
			return true;
		} else {
			cout << "Unable to open file" << endl;
			if (name.compare("genki.dict") == 0){
				this->read_file("/usr/local/share/linjap/genki.dict");
			} else if (name.compare("/usr/local/share/linjap/genki.dict") == 0) {
				this->read_file("/usr/share/linjap/genki.dict");
			} else {
				cout << "Didnt find the dict file" << endl;
				return false;
			}
		}
	} catch (Glib::FileError e) {
		cout << "Didnt find file" << endl;
		return false;
	}
}


