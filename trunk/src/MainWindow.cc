#include "MainWindow.h"

/* Main window constructor*/
MainWindow::MainWindow(Gtk::Main *kit)
: m_vbox(false, 5),
l_vbox(false, 3),
l_hbox(false, 2),
l_l_vbox(false, 3),
m_hbox(false, 2),
l_cor("To start"),
l_u("Press New -->"),
st("Correct/Not Correct"),
c_eng("Initialised ? "),
l_cor_label("Correct:"),
l_u_label("Your:"),
st_label("State:"),
input_box(),
p_bar(),
e_frame("English Word: "),
l_frame("Last Word: ")
{
	/*Set pointers to null value */
	hwindow = 0;
	nwindow = 0;
	popwindow = 0;
	ki = kit;
	ok_button = new Button(Gtk::Stock::NEW);
	node = NULL;
	en = new Engine("genki.dict");//Initialise engine with geni file.


	//Create actions for menus and toolbars:
	m_refActionGroup = Gtk::ActionGroup::create();
	
	//File menu:
	m_refActionGroup->add(Gtk::Action::create("FileMenu", "File"));

	//Sub-menu.
	m_refActionGroup->add(Gtk::Action::create("NewSession", Gtk::Stock::NEW),
        sigc::mem_fun(*this, &MainWindow::on_new_session));
	m_refActionGroup->add(Gtk::Action::create("FileQuit", Gtk::Stock::QUIT),
        sigc::mem_fun(*this, &MainWindow::on_menu_file_quit));
	
	//Help menu:
	m_refActionGroup->add( Gtk::Action::create("HelpMenu", "Help") );
	m_refActionGroup->add( Gtk::Action::create("HelpAbout", Gtk::Stock::ABOUT),
        sigc::mem_fun(*this, &MainWindow::on_menu_help) );

	m_refUIManager = Gtk::UIManager::create();
	m_refUIManager->insert_action_group(m_refActionGroup);

	add_accel_group(m_refUIManager->get_accel_group());

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info = 
		"<ui>"
		"  <menubar name='MenuBar'>"
		"    <menu action='FileMenu'>"
		"		<menuitem action='NewSession'/>"
		"		<separator/>"
		"      	<menuitem action='FileQuit'/>"
		"    </menu>"
		"    <menu action='HelpMenu'>"
		"      <menuitem action='HelpAbout'/>"
		"    </menu>"
		"  </menubar>"
		"</ui>";

	/* Throw exeptions from Glibmm */

	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	try
	{
		m_refUIManager->add_ui_from_string(ui_info);
	}
	catch(const Glib::Error& ex)
	{
		std::cerr << "building menus failed: " <<  ex.what();
	}
	#else
	std::auto_ptr<Glib::Error> ex;
	m_refUIManager->add_ui_from_string(ui_info, ex);
	if(ex.get())
	{
		std::cerr << "building menus failed: " <<  ex->what();
	}
	#endif //GLIBMM_EXCEPTIONS_ENABLED

	//Get the menubar and toolbar widgets, and add them to a container widget:
	Gtk::Widget* pMenubar = m_refUIManager->get_widget("/MenuBar");
	if(pMenubar) m_vbox.pack_start(*pMenubar, Gtk::PACK_SHRINK);
	
	p_bar.set_text("Initialised");//Set text on progress bar

	//Signal handlers
	input_box.signal_activate().connect(sigc::mem_fun(*this, &MainWindow::on_next_button) );
	ok_button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_new_session) );
	
	//Window properties
	c_eng.set_text("Welcome to Linjapp");
	set_title("Linjap 2.0");
	try {
		set_icon_from_file("jping.png");
	} catch (Glib::FileError e) {
		try {
			set_icon_from_file("/usr/local/share/linjap/jping.png");

		} catch (Glib::FileError e) {
			set_icon_from_file("/usr/share/linjap/jping.png");
		}
	}
	
	//Size requests
	e_frame.set_size_request(400,100);
	m_hbox.set_size_request(400, 100);
	l_frame.set_size_request(300, 100);
	
	//Pack last word label box
	l_l_vbox.pack_start(l_cor_label);
	l_l_vbox.pack_start(l_u_label);
	l_l_vbox.pack_start(st_label);
	
	//Pack last word box
	l_vbox.pack_start(l_cor);
	l_vbox.pack_start(l_u);
	l_vbox.pack_start(st);
	
	//pack last box
	l_hbox.pack_start(l_l_vbox);
	l_hbox.pack_start(l_vbox);
	
	//pack last box in frame
	l_frame.add(l_hbox);
	
	//Pack english box into lable.
	e_frame.add(c_eng);

	//pack main horizontal box (button and last ) 
	m_hbox.pack_start(l_frame);
	m_hbox.pack_start(*ok_button);

	//Pack main vertical box
	m_vbox.pack_start(e_frame);
	m_vbox.pack_start(input_box);
	m_vbox.pack_start(m_hbox);
	m_vbox.pack_start(p_bar);

	// Add main vertical box to window
	add(m_vbox);
	
	//Show everything
	show_all_children();
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::on_next_button() 
{
	cout << "Button Pressed: " << en->words_left() << endl;
	if (en->words_left() > 0) { //If there are no words left in engine
		cout << "Engine has next" << endl;
		if (node == NULL) {
			cout << "Node is null, getting next" << endl;
			node = en->next();
			
			c_eng.set_text(node->get_eng());
			p_bar.set_text("Word: " + this->int_to_ustring(0) + " / " + this->int_to_ustring(en->words_total()) );
			p_bar.set_fraction(0.0);
			return;
		}
		ustring u_w(input_box.get_text());// Get user input
		l_u.set_text(u_w);//set l_u lable to your word.
		l_cor.set_text(node->get_jap());//set it to last correct lable
			
		/* if they are the same, set correct. If not, set Not correct */
		if (equals(u_w)) {
			st.set_markup("<span foreground=\"green\">CORRECT!</span>");
			delete node;
		} else {
			st.set_markup("<span foreground=\"red\">NOT CORRECT!</span>");
			en->wrong(node);
		}
		update_progress();
			
		input_box.set_text("");/* reset input */	
		node = en->next(); //Get next node
		c_eng.set_text(node->get_eng());//Set english box to next word.
	} else {
		if (node != 0) {
			ustring u_w(input_box.get_text());// Get user input
			l_u.set_text(u_w);//set l_u lable to your word.
			l_cor.set_text(node->get_jap());//set it to last correct lable
			
			/* if they are the same, set correct. If not, set Not correct */
			if (equals(u_w)) {
				st.set_markup("<span foreground=\"green\">CORRECT!</span>");
				delete node;
				delete ok_button;
				ok_button = new Button(Gtk::Stock::NEW);
				m_hbox.pack_start(*ok_button);
				ok_button->show();
				ok_button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_new_session));
				
				if (popwindow != 0) {
					delete popwindow;
				}
		
				float wrong_pros;
				if (en->wrong_total() == 0) {
					wrong_pros = 100;
				} else {
					wrong_pros = (float) en->wrong_total() / en->words_total();	
					wrong_pros = 1 - wrong_pros;
					wrong_pros *= 100;
				}
				popwindow = new PopWindow("End of Session", "Congratulations, you have just practised a whole chapter.\nYou got " + int_to_ustring((int) wrong_pros) + "% Correct.");
				popwindow->show();
				
			} else {
				st.set_markup("<span foreground=\"red\">NOT CORRECT!</span>");
				en->wrong(node);
			}
			update_progress();
			input_box.set_text("");//reset input
		}
	}
}

void MainWindow::on_menu_file_quit()
{
	if (popwindow != 0) {
		popwindow->hide();
		delete popwindow;
	}
	if (hwindow != 0) {
		hwindow->hide();
		delete hwindow;
	}
	ki->quit();
}

void MainWindow::on_menu_help()
{
	hwindow = new HelpWindow();
  	hwindow->show(); 	//Shows the window.
}

void MainWindow::on_new_session() 
{	
	if (!en->has_list()) {
		on_menu_file_quit();
	}
	if (nwindow == 0) {
		nwindow = new NeWindow(en);
		ki->run(*nwindow);
		
		delete nwindow;
		nwindow = 0;
		delete node;
		node = NULL;
		
		delete ok_button;
		ok_button = new Button(Gtk::Stock::OK);
		m_hbox.pack_start(*ok_button);
		ok_button->show();
		ok_button->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_next_button) );
		st.set_use_markup(true);
		
		on_next_button();
	} else {
		cout << "Window Exist" << endl;
	}
}

/* Convert an int between 0 and 999 to a Unicode string */
ustring MainWindow::int_to_ustring(int num_typed)
{
	
	ustring return_string;
	if (num_typed > 9) {
		if (num_typed > 99) {
			int tmp3 = 0;
			int tmp = (int) (num_typed / 100);
			char tmp2 = (char) (tmp + 48);
			return_string = tmp2;
			tmp3 = tmp * 10;
			tmp = ((num_typed - (tmp * 100)) / 10 );
			tmp2 = (char) (tmp + 48);
			tmp3 += tmp;
			return_string += tmp2;
			tmp = (num_typed - (tmp3 * 10));
			tmp2 = (char) (tmp + 48);
			return_string += tmp2;
			
		} else {
			int tmp = (int) (num_typed / 10);
			char tmp2 = (char) (tmp + 48);
			return_string = tmp2;
			tmp = (num_typed - (tmp * 10));
			tmp2 = (char) (tmp + 48);
			return_string += tmp2;
		}
	} else {
		char tmp2 = (char) (num_typed + 48);
		return_string = tmp2;
	}
	return return_string;
}

/* Check if input and last word is the same. */
bool MainWindow::equals(ustring last_word)
{
	ustring last_wd = node->get_jap();//Get last corret word hir/kat
	ustring last_wd_kji = node->get_kanji(); //Get last corret Kanji
	bool returner = false;	//return value
	
	if (last_word.compare(last_wd_kji) == 0) {
		returner = true;
		cout << "Checking Kanji" << endl;
		const char* u_c_str = last_word.c_str();
		const char* l_cor_kji = last_wd_kji.c_str();
	
		int place =0;
		while(u_c_str[place] != '\0' || l_cor_kji[place] != '\0') {
			if (u_c_str[place] != l_cor_kji[place]) returner = false;
			place++;
		} 
	}
		
	if (last_word.compare(last_wd) == 0) {
		returner = true;
		const char* u_c_str = last_word.c_str();
		const char* l_cor_c_str = last_wd.c_str();
		
		int place = 0;
		while ((u_c_str[place] != '\0' || l_cor_c_str[place] != '\0') && returner ) {
			if (u_c_str[place] != l_cor_c_str[place]) returner = false;
			place++;
		}
	}
	
	return returner;
}

/* Update the status of the progressbar */
void MainWindow::update_progress()
{
	int total = en->words_total();
	int num_typed = (total - en->words_left());	
	float presentage = (float) num_typed / total;
	
	p_bar.set_text("Word: " + this->int_to_ustring(num_typed) + " / " + this->int_to_ustring(total) );
	p_bar.set_fraction(presentage);
}
