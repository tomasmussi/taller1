/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje una cruz del tamaño de la ventana:
 *  ___
 * |_|_|
 * |_|_|
 *
 * cruz roja sobre fondo blanco
 */


#include <gtkmm.h>
#define ANCHO_LINEA 0.01

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
				
				// fondo
				ctx->set_source_rgb(1.0, 1.0, 1.0);
				ctx->rectangle(0.0, 0.0, 1.0, 1.0);
				ctx->fill();
				
				// cruz
				ctx->set_source_rgb(1.0, 0.0, 0.0);
				ctx->move_to(0.0, 0.5); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda
				ctx->line_to(1.0, 0.5); // línea hacia la derecha
				ctx->move_to(0.5, 0.0);
				ctx->line_to(0.5, 1.0); // línea hacia la derecha
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
