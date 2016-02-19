/*
 * 4) Escriba una rutina que lea los elementos de un listbox, los ordene y los escriba nuevamente en el control.
 */


#include <gtkmm.h>
#include <list>

void ordenar(Gtk::ComboBoxText* combo) {
	combo->set_active(0);
	Glib::ustring texto;
	std::list< Glib::ustring > contenido;
	while (combo->get_active_row_number() != -1) {
		texto = combo->get_active_text();
		combo->remove_text(texto);
		contenido.push_back(texto);
		combo->set_active(0);
	}
	contenido.sort();
	std::list< Glib::ustring >::const_iterator it = contenido.begin();
	for ( ; it != contenido.end(); ++it)
		combo->append_text(*it);
}
// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonOrdenar : public Gtk::Button {
	public:
		BotonOrdenar(Gtk::ComboBoxText* combo) : Gtk::Button("Ordenar") {
			this->combo = combo;	
		}
	private:
		Gtk::ComboBoxText* combo;
		void on_clicked() { 
			ordenar(combo);
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
	Gtk::ComboBoxText combo;
	combo.append_text("asdfhbb");
	combo.append_text("45ggdfdfs");
	combo.append_text("avbbhrr");
	combo.append_text("khjgh2");
	combo.append_text("cxzeee");
	combo.append_text("quieroaprobartaller");
	BotonOrdenar boton(&combo);
	Gtk::VBox vbox;
	vbox.add(combo);
	vbox.add(boton);
	Gtk::Window v;
	v.add(vbox);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
