/*
 * 10) Escriba la función PasarAMayusculas que tome el contenido de un Edit de una ventana y lo escriba en él después de haberlo convertido a Mayúsculas
 */


#include <gtkmm.h>

void PasarAMayusculas(Gtk::Entry* entry) {
	entry->set_text(entry->get_text().uppercase());
}
// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonPasarAMayusculas : public Gtk::Button {
	public:
		BotonPasarAMayusculas(Gtk::Entry* entry) : Gtk::Button("Pasar a mayúsculas") {
			this->entry = entry;	
		}
	private:
		Gtk::Entry* entry;
		void on_clicked() { 
			PasarAMayusculas(entry);
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
	Gtk::Entry entry;
	BotonPasarAMayusculas boton(&entry);
	Gtk::VBox vbox;
	vbox.add(entry);
	vbox.add(boton);
	Gtk::Window v;
	v.add(vbox);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
