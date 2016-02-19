/*
Ej1:
Implemente una rutina (en Windows o Linux) que dibuje un óvalo que ocupe toda la ventana.

*/

#include <gtkmm/drawingarea.h>
#include <gtkmm/application.h>
#include <gtkmm/window.h>

#include <cmath>
#define ANCHO_LINEA 0.05

class Ovalo : public Gtk::DrawingArea {

	protected:
		// OVALO
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation alloc = get_allocation();
			int ancho = alloc.get_width();
			int alto = alloc.get_height();
			int x = ancho / 2;
			int y = alto / 2;
			
			int w = 3 * ancho / 4.0;
			int h = alto / 2.0;
			cr->save();
			
			cr->translate(x, y);
			cr->scale(w, h);
			cr->arc(0, 0, 1.0, 0, 2 * M_PI);
			cr->set_source_rgba(0, 0, 1.0, 0);
			// cr->fill_preserve();
			cr->restore();  // back to opaque black
			cr->stroke();
			return true;
		}*/
		// CUADRADO
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation alloc = get_allocation();
			int ancho = alloc.get_width();
			int alto = alloc.get_height();
			cr->save();
			cr->scale(ancho / 3.0, alto / 3.0);
			cr->move_to(0, 0);
			cr->line_to(1.0, 0.0);
			cr->line_to(1, 1);
			cr->line_to(0, 1);
			cr->close_path();
			cr->set_source_rgb(1, 0,0);
			cr->stroke();
			cr->restore();
			return true;
		};*/
		
		// CRUZ ROJA SOBRE FONDO BLANCO
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation alloc = get_allocation();
			int ancho = alloc.get_width();
			int alto = alloc.get_height();
			cr->scale(ancho, alto);
			cr->set_source_rgb(1, 1, 1);
			cr->rectangle(0, 0, 1, 1);
			cr->fill();
			
			cr->set_line_width(0.05);
			cr->set_source_rgb(1, 0, 0);
			cr->move_to(0, 0.5);
			cr->line_to(1, 0.5);
			cr->move_to(0.5, 0);
			cr->line_to(0.5, 1);			
			cr->stroke();
			return true;
		}*/
		// Triangulo rojo
		/*
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation all = get_allocation();
			int ancho = all.get_width();
			int alto = all.get_height();
			cr->set_source_rgb(1, 1, 1);
			cr->rectangle(0, 0, 1, 1);
			cr->fill();
			cr->scale(ancho, alto);
			cr->set_source_rgb(1, 0, 0);
			cr->set_line_width(0.05);
			cr->move_to(0, 1);
			cr->line_to(1, 0);
			cr->line_to(1, 1);
			cr->close_path();
			cr->fill();
			cr->stroke();
			return true;
		}*/
		// Rectangulo de 1 / 3
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation alloc = get_allocation();
			int ancho = alloc.get_width();
			int alto = alloc.get_height();
			cr->scale(ancho, alto);
			cr->set_source_rgb(1, 1, 1);
			cr->rectangle(0, 0, 1, 1);
			cr->fill();			
			cr->set_source_rgb(1, 0, 0);
			cr->rectangle(1 / 3.0, 1 / 3.0, 1 /3.0, 1 /3.0);
			cr->fill();
			return true;
		}*/
		// Franjas horizontales
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation all = get_allocation();
			int ancho = all.get_width();
			int alto = all.get_height();
			cr->scale(ancho, alto);
			cr->set_line_width(0.05);
			cr->set_source_rgb(0, 0, 0);
			cr->move_to(0, 1 / 3.0);
			cr->line_to(1, 1 / 3.0);
			cr->move_to(0, 2 / 3.0);
			cr->line_to(1, 2 / 3.0);
			cr->stroke();
			return true;
		}*/
		// Triangulos azules
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation a = get_allocation();
			int ancho = a.get_width();
			int alto = a.get_height();
			cr->scale(ancho, alto);
			cr->set_line_width(0.05);
			cr->move_to(0, 0);
			cr->line_to(1, 0);
			cr->line_to(1, 1);
			cr->line_to(0, 1);
			cr->close_path();
			cr->save();
				cr->set_source_rgb(1, 1, 1);
				cr->fill_preserve();
			cr->restore();
			cr->stroke();
			
			cr->move_to(0, 0);
			cr->line_to(0.5, 0.5);
			cr->line_to(1, 0);
			cr->close_path();
			cr->save();
				cr->set_source_rgb(0, 0, 1);
				cr->fill_preserve();
			cr->restore();
			cr->stroke();
			
			cr->move_to(0, 1);
			cr->line_to(0.5, 0.5);
			cr->line_to(1, 1);
			cr->close_path();
			cr->save();
				cr->set_source_rgb(0, 0, 1);
				cr->fill_preserve();
			cr->restore();
			cr->stroke();
			return true;
		}*/
		// Triangulo azul
		/*virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation a = get_allocation();
			int ancho = a.get_width();
			int alto = a.get_height();
			cr->scale(ancho, alto);
			cr->set_source_rgb(1, 1, 1);
			cr->rectangle(0, 0, 1, 1);
			cr->fill();
			cr->move_to(1, 0);
			cr->line_to(1, 1);
			cr->line_to(0, 1);
			cr->close_path();
			cr->save();
				cr->set_source_rgb(0, 0, 0);
				cr->fill_preserve();
			cr->restore();
			return true;
		}*/
		// Triangulo azul inferior
		virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
			Gtk::Allocation a = get_allocation();
			int ancho = a.get_width();
			int alto = a.get_height();
			cr->scale(ancho, alto);
			cr->set_source_rgb(1, 1, 1);
			cr->rectangle(0, 0, 1, 1);
			cr->fill();
			cr->move_to(0, 1);
			cr->line_to(0.5, 0.5);
			cr->line_to(1, 1);
			cr->close_path();
			cr->save();
				cr->set_source_rgb(0, 0, 1);
				cr->fill_preserve();
			cr->restore();
			return true;
		}
};

int main(int argc, char* argv[]) {
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Gtk::Window win;
	win.set_title("DrawingArea");
	Ovalo area;
	win.add(area);
	area.show();
    return app->run(win);
}
