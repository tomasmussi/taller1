/*
 * 10) Escriba la función Desordenar que tome el contenido de un Combo de una ventana y altere la posición de sus opciones ordenándolas por el tercer caracter.
 */


#include <gtkmm.h>
#include <map>

void Desordenar(Gtk::ComboBoxText* combo) {
	combo->set_active(0);
	Glib::ustring texto;
	Glib::ustring tercera_letra;
	std::map< Glib::ustring, Glib::ustring > mapa;
	while (combo->get_active_row_number() != -1) {
		texto = combo->get_active_text();
		tercera_letra = texto.substr(2, 3);
		mapa[tercera_letra] = texto;
		combo->remove_text(texto);
		combo->set_active(0);
	}
	
	std::map< Glib::ustring, Glib::ustring >::const_iterator it = mapa.begin();
	for ( ; it != mapa.end(); ++it)
		combo->append_text(it->second);
}
// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonDesordenar : public Gtk::Button {
	public:
		BotonDesordenar(Gtk::ComboBoxText* combo) : Gtk::Button("Desordenar") {
			this->combo = combo;	
		}
	private:
		Gtk::ComboBoxText* combo;
		void on_clicked() { 
			Desordenar(combo);
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
	BotonDesordenar boton(&combo);
	Gtk::VBox vbox;
	vbox.add(combo);
	vbox.add(boton);
	Gtk::Window v;
	v.add(vbox);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
