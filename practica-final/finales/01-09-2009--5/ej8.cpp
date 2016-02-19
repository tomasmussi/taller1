/*
 * 8) Escriba una rutina que cargue un Listbox con una serie de 10 cadenas de la forma “Línea 1”, “Línea 2”,..., “Línea 10”.
 */


#include <gtkmm.h>
#include <sstream>

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Gtk::ComboBoxText combo;
	
	Glib::ustring str = "Combo ";
	std::stringstream sstream;
	for (int i = 1; i <= 10; ++i) {
		sstream << i;
		combo.append_text(str + sstream.str());
		sstream.str("");
	}
	
	Gtk::Window v;
	v.add(combo);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
