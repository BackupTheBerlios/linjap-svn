#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>
#include <cstdlib>
#include <iostream>
#include "Engine.h"
#include "HelpWindow.h"
#include "NeWindow.h"
#include "PopWindow.h"

using namespace std;
using namespace Gtk;

class MainWindow : public Gtk::Window
{
	public:
		MainWindow(Gtk::Main *kit);
		~MainWindow();

	private:
		//Signal handlers:
		void on_menu_file_quit();
		void on_menu_help();		
		void on_next_button();
		void on_new_session();
		
		//Functions
		ustring int_to_ustring(int x);
		bool equals(ustring last_word);
		void update_progress();
		
		//Child Widgets
		HelpWindow *hwindow;
		NeWindow *nwindow;
		PopWindow *popwindow;
		
		VBox m_vbox, l_l_vbox, l_vbox;
		HBox m_hbox, l_hbox;
		Frame e_frame, l_frame;
		
		Engine::Engine *en;
		LinkNode::LinkNode *node;
		Button *ok_button;
		Label c_eng, l_cor, l_u, st, l_cor_label, l_u_label, st_label;
		Entry input_box;
		ProgressBar p_bar;
		Gtk::Main *ki;
		Glib::RefPtr<Gtk::UIManager> m_refUIManager;
		Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
		
};

#endif
