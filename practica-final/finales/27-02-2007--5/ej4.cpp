/*
 * 4) Escriba un trozo de código que: tome el contenido de un EDIT, le saque los espacios y ponga el resultado como contenido de ese mismo EDIT.
 */


#include <gtkmm.h>
#define ESPACIO ' '

void sacarEspacios(Gtk::Entry* entry) {
	Glib::ustring texto = entry->get_text();
	size_t pos = texto.find(ESPACIO);
	while (pos != Glib::ustring::npos) {
		texto.erase(pos, 1);
		pos = texto.find(ESPACIO);
	}	
	
	entry->set_text(texto);
}
// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonSacarEspacios : public Gtk::Button {
	public:
		BotonSacarEspacios(Gtk::Entry* entry) : Gtk::Button("Sacar espacios") {
			this->entry = entry;	
		}
	private:
		Gtk::Entry* entry;
		void on_clicked() { 
			sacarEspacios(entry);
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
	Gtk::Entry entry;
	BotonSacarEspacios boton(&entry);
	Gtk::VBox vbox;
	vbox.add(entry);
	vbox.add(boton);
	Gtk::Window v;
	v.add(vbox);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
