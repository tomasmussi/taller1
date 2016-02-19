/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje 2 lineas horizontales dividiendo la ventana en 3 franjas iguales.
 */


#include <gtkmm.h>
#define ANCHO_LINEA 0.01

class FranjasHorizontales : public Gtk::DrawingArea {
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
				
				// contorno
				ctx->move_to(0.0, 1.0/3.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda
				ctx->line_to(1.0, 1.0/3.0); // línea hacia la derecha
				ctx->move_to(0.0, 2.0/3.0);
				ctx->line_to(1.0, 2.0/3.0); // línea hacia la derecha
				ctx->stroke(); // pinto el camino en negro			
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	FranjasHorizontales f;
	Gtk::Window v;
	v.add(f);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
