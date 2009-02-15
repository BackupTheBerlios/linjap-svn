#include <gtkmm/main.h>
#include "MainWindow.h"

int main (int argc, char *argv[])
{
	Gtk::Main *kit = new Gtk::Main(argc, argv);
	MainWindow::MainWindow window(kit);
	
	kit->run(window);	
	return 0;
}
