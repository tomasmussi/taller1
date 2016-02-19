/*
9) Describa el mecanismo que se utiliza crear una ventana con un area de dibujo.


 Para crear una ventana con un area de trabajo no se hace mas que crear una ventana y se le agregar el drawing area
Si queremos que se dibuje algo, hacemos una clase que herede de DrawingArea y redefinimos on_expose_event

*/

#include <gtkmm.h>

class MiArea : public Gtk::DrawingArea {
private:
	bool on_expose_event(GdkEventExpose* ev ){
		Glib::RefPtr< Gdk::Window > v = get_window();
		if (v) {
			Cairo::RefPtr< Cairo::Context > ctx = v->create_cairo_context();
			Gtk::Allocation alloc = get_allocation();
			const int altura = alloc.get_height();
			const int ancho = alloc.get_width();
			ctx->set_source_rgb(0.3, 0.1, 0.4);
			ctx->scale(ancho, altura);	
			ctx->rectangle(1.0 / 2.0, 1.0 / 4.0, 1.0 / 5.0, 1.0 / 5.0);
			ctx->fill();
		}
		return true;
	}

};

int main(int argc, char** argv) {
	Gtk::Main kit(argc, argv);
	MiArea ma;
	Gtk::Window v;
	v.add(ma);
	v.show_all();
	Gtk::Main::run(v);
	return 0;	
}
