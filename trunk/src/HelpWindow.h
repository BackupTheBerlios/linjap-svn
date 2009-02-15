#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <cstdlib>

class HelpWindow : public Gtk::Window
{
	public:
		HelpWindow();
		~HelpWindow();
	
	private:
		Gtk::Frame frame;
		Gtk::Label label;
};

#endif
