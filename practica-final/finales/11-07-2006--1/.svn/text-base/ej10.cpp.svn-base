/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un línea discontinua horizontal en pantalla.
 *  _____
 * |_ _ _|
 * |_____|
 */


#include <gtkmm.h>
#include <vector>
#define ANCHO_LINEA 0.01
#define ESPACIADO_GUIONES 0.02

class Cruz : public Gtk::DrawingArea {
	public:
	private:
		bool on_expose_event(GdkEventExpose* ev) {
			Glib::RefPtr< Gdk::Window > window = get_window();
			if (window) {
				Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
				Gtk::Allocation alloc = get_allocation();
				const int height = alloc.get_height();
				const int width = alloc.get_width();

				ctx->scale(width, height); //escala para que ocupe siempre toda la pantalla. Notar que es ancho y después alto.
				ctx->set_line_width(ANCHO_LINEA);
				
				// fondo blanco
				ctx->save();
					ctx->set_source_rgb(1.0, 1.0, 1.0);
					ctx->rectangle(0.0, 0.0, 1.0, 1.0);
					ctx->fill();
				ctx->restore();
				
				// seteo el patrón de guiones
				std::vector< double > guiones(1);
				guiones[0] = ESPACIADO_GUIONES;
				ctx->set_dash(guiones, 0);
				
				// línea
				ctx->move_to(0.0, 0.5); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda, a la mitad de la altura
				ctx->line_to(1.0, 0.5); // línea hacia la derecha
				ctx->stroke(); // pinto el camino en negro			
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Cruz c;
	Gtk::Window v;
	v.add(c);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
