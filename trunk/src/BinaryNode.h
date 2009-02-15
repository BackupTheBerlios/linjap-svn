#include <glibmm/ustring.h>
using namespace Glib;

class BinaryNode
{
	public:
		BinaryNode(ustring eng_word, 
					ustring jap_word, 
					ustring kanji,
					int chap,
					int part);
		~BinaryNode();
		ustring* get_eng();
		ustring* get_jap();
		ustring* get_kanji();
		int* get_chap();
		int* get_part();
		
		BinaryNode* get_right();
		BinaryNode* get_left();
		void set_left(BinaryNode* left);
		void set_right(BinaryNode* right);
		bool has_left();
		bool has_right();
		
	private:
		ustring eng_wd, jap_wd, knji;
		int *chap, *part;
		BinaryNode *left, *right;
};
