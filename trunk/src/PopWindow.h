#ifndef POPWINDOW_H
#define POPWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <glibmm/ustring.h>
#include <cstdlib>

class PopWindow : public Gtk::Window
{
	public:
		PopWindow(Glib::ustring lab, Glib::ustring msg);
		~PopWindow();
	
	private:
		Gtk::Frame frame;
		Gtk::Label label;
};

#endif
