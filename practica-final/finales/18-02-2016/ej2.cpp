/*
 * 2) Escriba una rutina (para ambiente grafico Windows o Linux) que dibuje 3 lineas horizontales
 * dividiendo la ventana en 4 franjas iguales.
 * 
 * 
 * En definitiva seria una ventana asi:
 * ----------- => margen superior
 * |		 |
 * ----------- => esta se dibuja
 * |		 |
 * ----------- => esta se dibuja
 * |		 |
 * ----------- => esta se dibuja
 * |		 |
 * ----------- => margen inferior
 * 
 * */
 
 // Esto es el codigo, para verlo en funcionamiento reemplazar esta funcion en el main.cpp de
 // practica-final/gtk/main.cpp
 
 virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
	 Gtk::Allocation a = get_allocation();
	 int ancho = a.get_width();
	 int alto = a.get_height();
	 cr->scale(ancho, alto); // Primero ancho
	 cr->set_line_width(0.05); // Dibuja lineas muy gruesas sino
	 // Al escalar, trabajo con coordenadas de 0.0 a 1.0 tanto para x como y
	 cr->move_to(0.0, 0.25);
	 cr->line_to(1.0, 0.25);
	 cr->move_to(0.0, 0.50);
	 cr->line_to(1.0, 0.50);
	 cr->move_to(0.0, 0.75);
	 cr->line_to(1.0, 0.75);
	 cr->stroke();
	 return true;
 }
