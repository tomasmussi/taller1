/*
 * 3) Implemente una rutina (en Windows o Linux) que dibuje un trapecio regular en la ventana.
 */


#include <gtkmm.h>
#define ANCHO_LINEA 0.05

class TrapecioRegular : public Gtk::DrawingArea {
	public:
		TrapecioRegular(float baseMayor, float baseMenor, float altura) {
			v1[0] = 0.0; v1[1] = 1.0;
			v2[0] = (baseMayor - baseMenor) / 2; v2[1] = 1.0 - altura;
			v3[0] = v2[0] + baseMenor; v3[1] = v2[1];
			v4[0] = v1[0] + baseMayor; v4[1] = v1[1];
		}	
	private:
		// vértices
		float v1[2], v2[2], v3[2], v4[2];
		bool on_expose_event(GdkEventExpose* ev) {
			Glib::RefPtr< Gdk::Window > window = get_window();
			if (window) {
				Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
				Gtk::Allocation alloc = get_allocation();
				const int height = alloc.get_height();
				const int width = alloc.get_width();
				const int min = height < width ? height : width;

				ctx->scale(min, min); // escalado para que siempre sea cuadrada la zona de dibujo, y que las coordenadas vayan de 0 a 1
				ctx->set_line_width(ANCHO_LINEA);
				ctx->move_to(v1[0], v1[1]);
				ctx->line_to(v2[0], v2[1]);
				ctx->line_to(v3[0], v3[1]);
				ctx->line_to(v4[0], v4[1]);
				ctx->close_path(); // cerrar el camino, en general, sería equivalente a line_to(v1);
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
	TrapecioRegular trapecio(0.8, 0.6, 0.9);
	Gtk::Window v;
	v.add(trapecio);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	
