#include "BinaryNode.h"
#include <iostream>
#include <glibmm/ustring.h>
using namespace std;

BinaryNode::BinaryNode(ustring en_wd, 
					   ustring ja_wd, 
					   ustring ki, 
					   int ch, int pt)
{
		eng_wd = en_wd;
		jap_wd = ja_wd;
		knji = ki;
		chap = &ch;
		part = &pt;
}
		
BinaryNode::~BinaryNode()
{
	
}

ustring* BinaryNode::get_eng()
{
	return &eng_wd;
}

ustring* BinaryNode::get_jap()
{
	return &jap_wd;		
}
		
ustring* BinaryNode::get_kanji()
{
	return &knji;
}

int* BinaryNode::get_chap()
{
	return chap;	
}
		
int* BinaryNode::get_part()
{
	return part;
}
		
BinaryNode* BinaryNode::get_right()
{
	return right;
}

BinaryNode* BinaryNode::get_left()
{
	return left;
}

void BinaryNode::set_right(BinaryNode* right)
{
	right = right;
}

void BinaryNode::set_left(BinaryNode* left)
{
	left = left;
}	

bool BinaryNode::has_left()
{
	return left != 0;
}

bool BinaryNode::has_right() 
{
	return right != 0;	
}

int main(int argv, char ** argc) {
	ustring eng("Japanese");
	Glib::ustring nor("NÅRSK!");
	Glib::ustring example_string("NÅRSK!");
	ustring jap("Det er ikke en aA"/*"にほんご"*/);
	ustring kan("Japp japp" /*"日本語"*/);
	BinaryNode node(eng, jap, kan, 1, 1);
	ustring tst("Japansk på Engelsk og japansk");
	ustring* pt = &tst;
	ustring* en_wd = node.get_eng();
	ustring* ja_wd = node.get_jap();
	ustring* ka_wd = node.get_kanji();
	cout /*<< *pt */<< ": " << *en_wd << " : " << *ja_wd << " : " << *ka_wd 
		<< " : " << example_string << " : " << nor << endl;
	return 0;
}
