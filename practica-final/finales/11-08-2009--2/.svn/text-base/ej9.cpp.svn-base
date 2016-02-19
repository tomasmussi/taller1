/*
 * 9) Escriba una rutina gráfica (Linux o Windows) para dibujar un óvalo que abarque todo el área de trabajo de una ventana.
 */


#include <gtkmm.h>
#include <cmath>
#define ANCHO_LINEA 0.05

class Ovalo : public Gtk::DrawingArea {
	public:
	private:
		bool on_expose_event(GdkEventExpose* ev) {
			Glib::RefPtr< Gdk::Window > window = get_window();
			if (window) {
				Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
				Gtk::Allocation alloc = get_allocation();
				const int height = alloc.get_height();
				const int width = alloc.get_width();

				ctx->scale(width, height); //escalado para que ocupe siempre toda la pantalla. Notar que es ancho y después alto.
				ctx->set_line_width(ANCHO_LINEA);
				ctx->arc(0.5, 0.5,  	// el centro es siempre ( 0.5, 0.5 ) por el escalado anterior
						 0.5,			// radio 0.5 para que ocupe todo
						 0.0, 2*M_PI); 	// el arco irá de 0 a 2pi
				ctx->save(); // salvo el color, porque voy a pintar (no era necesario para el ejercicio igual)
					ctx->set_source_rgb(0.8, 0.1, 0.77); // seteo el color para pintar
					ctx->fill_preserve(); // fill() pinta, pero pierde el path. fill_preserve() pinta y mantiene el path
				ctx->restore(); // vuelvo al estado anterior, que tenía el color negro
				ctx->stroke(); // pinto el camino
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Ovalo ovalo;
	Gtk::Window v;
	v.add(ovalo);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
