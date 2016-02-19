/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que pinte un triángulo rojo con las carcterísticas que muestra la siguiente figura:
 * Es algo así, pintado de rojo la parte derecha:
 *  
 * | /|
 * |/_|
 */


#include <gtkmm.h>

class Triangulo : public Gtk::DrawingArea {
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
				
				ctx->move_to(0.0, 1.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de la izquierda
				ctx->line_to(1.0, 0.0); // línea hacia el punto de arriba
				ctx->line_to(1.0, 1.0); // línea hacia el punto de abajo a la derecha
				ctx->close_path(); // cierro el camino
				ctx->set_source_rgb(1.0, 0.0, 0.0); // seteo el color hacia el pedido
				ctx->fill(); // relleno en rojo, el color seteado
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Triangulo triangulo;
	Gtk::Window v;
	v.add(triangulo);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
