#ifndef LINKNODE_H
#define LINKNODE_H
#include <glibmm/ustring.h>
using namespace Glib;

class LinkNode
{
	public:
		LinkNode(ustring eng_word, 
					ustring jap_word, 
					ustring kanji,
					int chap,
					int part);
		~LinkNode();
		ustring get_eng();
		ustring get_jap();
		ustring get_kanji();
		int get_chap();
		int get_part();
		
		LinkNode* get_next();
		void set_next(LinkNode* left);
		bool has_next();
		
	private:
		ustring eng_wd, jap_wd, knji;
		int chap, part;
		LinkNode *next;
};
#endif
