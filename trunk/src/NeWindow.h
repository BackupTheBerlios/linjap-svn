#ifndef NEWINDOW_H
#define NEWINDOW_H

#include "Engine.h"
#include <iostream>
#include <gtkmm.h>
#include <cstdlib>

using namespace Gtk;
using namespace std;

class NeWindow : public Window
{
	public:
		NeWindow(Engine::Engine * en);
		~NeWindow();
	private:
		//signal handlers
		void start_button_clicked();
		
		Engine::Engine * eng;
		HBox chap_hbox;
		VBox m_vbox;
		//Adjustment spin_adj;
		Adjustment m_adjustment_day;

		SpinButton chap_spin;
		Label chap_label;
		Button start_button;
};

#endif
