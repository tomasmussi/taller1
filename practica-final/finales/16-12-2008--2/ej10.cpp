/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje la siguiente imagen en su área de dibujo:
 * Es algo así, los triángulos de los laterales de blanco, y los otros dos de azul, enmarcados en un tetrágono de bordes negros:
 *  
 * |\/|
 * |/\|
 */


#include <gtkmm.h>
#define ANCHO_LINEA 0.01

class Dibujo : public Gtk::DrawingArea {
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
				ctx->move_to(0.0, 1.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda abajo
				ctx->line_to(0.0, 0.0); // línea hacia el punto de arriba a la izquierda
				ctx->line_to(1.0, 0.0); // línea hacia el punto de arriba a la derecha
				ctx->line_to(1.0, 1.0); // línea hacia el punto de abajo a la derecha
				ctx->close_path(); // cierro el camino
				ctx->save(); // salvo porque voy a cambiar el color
					ctx->set_source_rgb(1.0, 1.0, 1.0); // seteo el color al blanco
					ctx->fill_preserve(); // relleno todo el cuadrado, preservando el camino para dibujar el contorno
				ctx->restore();
				ctx->stroke(); // pinto el camino en negro

				// triángulo azul de abajo
				ctx->move_to(0.0, 1.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda
				ctx->line_to(0.5, 0.5); // línea hacia el punto del medio
				ctx->line_to(1.0, 1.0); // línea hacia el punto de abajo a la derecha
				ctx->close_path(); // cierro el camino
				ctx->save(); // salvo porque voy a cambiar el color
					ctx->set_source_rgb(0.0, 0.0, 1.0); // seteo el color al azul
					ctx->fill_preserve(); // relleno todo triángulo, preservando el camino para dibujar el contorno
				ctx->restore();
				ctx->stroke(); // pinto el camino en negro

				// triángulo azul de arriba
				ctx->move_to(0.0, 0.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda
				ctx->line_to(0.5, 0.5); // línea hacia el punto del medio
				ctx->line_to(1.0, 0.0); // línea hacia el punto de arriba a la derecha
				ctx->close_path(); // cierro el camino
				ctx->save(); // salvo porque voy a cambiar el color
					ctx->set_source_rgb(0.0, 0.0, 1.0); // seteo el color al azul
					ctx->fill_preserve(); // relleno todo triángulo, preservando el camino para dibujar el contorno
				ctx->restore();
				ctx->stroke(); // pinto el camino en negro				
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Dibujo d;
	Gtk::Window v;
	v.add(d);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
