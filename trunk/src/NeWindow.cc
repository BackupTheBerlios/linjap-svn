#include "NeWindow.h"

NeWindow::NeWindow(Engine *engine) 
: m_vbox(2, false),
m_adjustment_day(1.0, 1.0, 24.0, 1.0, 5.0, 0.0),
chap_hbox(2, false),
start_button(Gtk::Stock::OK),
chap_spin(m_adjustment_day),
chap_label("Choose Chapter:")
{
	eng = engine;
	set_title("L2::New Session");
	try {
		set_icon_from_file("jping.png");
	} catch (Glib::FileError e) {
		try {
			set_icon_from_file("/usr/local/share/linjap/jping.png");

		} catch (Glib::FileError e) {
			set_icon_from_file("/usr/share/linjap/jping.png");
		}
	}
	
	start_button.signal_clicked().connect(sigc::mem_fun(*this, &NeWindow::start_button_clicked));
	chap_hbox.pack_start(chap_label);
	chap_hbox.pack_start(chap_spin);
	
	m_vbox.pack_start(chap_hbox);
	m_vbox.pack_start(start_button);
	add(m_vbox);
	
	show_all_children();
}

NeWindow::~NeWindow()
{
	hide();
}

void NeWindow::start_button_clicked()
{
	cout << "Button pressed: " << chap_spin.get_value_as_int() << endl;
	eng->prepare_session(chap_spin.get_value_as_int());
 	cout << ", Engine loaded with words: " << eng->words_total() << endl;
	hide();
}
