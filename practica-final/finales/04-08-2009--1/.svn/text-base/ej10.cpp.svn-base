/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un rombo como el que se muestra en la siguiente figura:
 * Es un rombito así:
 *  
 * |/\|
 * |\/|
 */


#include <gtkmm.h>

class Rombo : public Gtk::DrawingArea {
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
				
				ctx->move_to(0.5, 1.0); // muevo hacia el punto inicial, que arbitrariamente elegí que fuera el de abajo
				ctx->line_to(0.0, 0.5); // línea hacia el punto de la izquierda
				ctx->line_to(0.5, 0.0); // línea hacia el punto de arriba
				ctx->line_to(1.0, 0.5); // línea hacia el punto de la derecha
				ctx->close_path(); // cierro el camino
				ctx->fill(); // relleno todo de negro, el color por defecto
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Rombo rombo;
	Gtk::Window v;
	v.add(rombo);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
