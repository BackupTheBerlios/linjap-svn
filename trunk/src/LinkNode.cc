#include "LinkNode.h"
#include <iostream>
using namespace std;

LinkNode::LinkNode(ustring en_wd, 
					   ustring ja_wd, 
					   ustring ki, 
					   int ch, int pt)
{
		eng_wd = en_wd;
		jap_wd = ja_wd;
		knji = ki;
		chap = ch;
		part = pt;
		next = NULL;
}
		
LinkNode::~LinkNode()
{
	
}

ustring LinkNode::get_eng()
{
	return eng_wd;
}

ustring LinkNode::get_jap()
{
	return jap_wd;		
}
	
ustring LinkNode::get_kanji()
{
	return knji;
}

int LinkNode::get_chap()
{
	return chap;	
}
		
int LinkNode::get_part()
{
	return part;
}
		
LinkNode* LinkNode::get_next()
{
	return next;
}

void LinkNode::set_next(LinkNode* t_next)
{
	next = t_next;
}

bool LinkNode::has_next()
{
	return next != NULL;
}
