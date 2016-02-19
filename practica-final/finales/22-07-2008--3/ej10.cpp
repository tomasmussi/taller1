/*
 * 10) Escriba una rutina (para ambiente gráfico Windows o Linux) que pinte un rectángulo rojo de la 1/3 parte del alto y ancho de la ventana:
 *  
 * | _ |
 * || ||
 * | - |
 *
 * ponele que así es la imagen, con fondo blanco
 */


#include <gtkmm.h>

class Rectangulo : public Gtk::DrawingArea {
	public:
	private:
		bool on_expose_event(GdkEventExpose* ev) {
			Glib::RefPtr< Gdk::Window > window = get_window();
			if (window) {
				Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
				Gtk::Allocation alloc = get_allocation();
				const int height = alloc.get_height();
				const int width = alloc.get_width();

				ctx->scale(width, height); //escala para que se mantenga la relación pedida respecto de la pantalla. Notar que es ancho y después alto.
				// fondo
				ctx->set_source_rgb(1.0, 1.0, 1.0);				
				ctx->rectangle(0.0, 0.0, // esquina superior izquierda
							   1.0, // ancho 
							   1.0  // alto
							  ); 
				ctx->fill();

				// rectángulo pedido
				ctx->set_source_rgb(1.0, 0.0, 0.0);				
				ctx->rectangle(1.0/3.0, 1.0/3.0, 1.0/3.0, 1.0/3.0);
				ctx->fill();	
			}
			return true;			
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Rectangulo r;
	Gtk::Window v;
	v.add(r);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
