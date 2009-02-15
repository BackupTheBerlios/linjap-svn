#include "HelpWindow.h"

HelpWindow::HelpWindow()
: frame("About:")
{
	set_size_request(400, 400);
	set_title("L2::Help");
	try {
		set_icon_from_file("jping.png");
	} catch (Glib::FileError e) {
		try {
			set_icon_from_file("/usr/local/share/linjap/jping.png");

		} catch (Glib::FileError e) {
			set_icon_from_file("/usr/share/linjap/jping.png");
		}
	}
	label.set_markup("<span size=\"27153\">Linjap 2.0.0.4</span>\n"
					"\nWritten by: Sindre Wetjen\nBugreports and requests goes to:"
					"\n	sindre.w@gmail.com\nDistributed under GPLv3 License");
	label.set_use_markup(true);
	frame.add(label);
	add(frame);
	label.show();
	frame.show();
}

HelpWindow::~HelpWindow()
{
	hide();
}
