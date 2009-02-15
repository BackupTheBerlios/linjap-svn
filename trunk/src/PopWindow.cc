#include "PopWindow.h"
#include <string>

PopWindow::PopWindow(Glib::ustring lab, Glib::ustring msg)
: frame(lab)
{
	set_title("L2::" + lab);
	try {
		set_icon_from_file("jping.png");
	} catch (Glib::FileError e) {
		try {
			set_icon_from_file("/usr/local/share/linjap/jping.png");

		} catch (Glib::FileError e) {
			set_icon_from_file("/usr/share/linjap/jping.png");
		}
	}
	label.set_text(msg);
	frame.add(label);
	add(frame);
	label.show();
	frame.show();
}

PopWindow::~PopWindow()
{
	hide();
}
