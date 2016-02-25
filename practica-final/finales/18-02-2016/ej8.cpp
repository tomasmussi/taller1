/**
 * 8) Declare una clase Nota para encapsular datos de una calificacion.
 * Incluya al menos:
 * constructor default
 * constructor con nro de punto flotante
 * constructor por copia
 * operadores: >, ==, =, int, >>(istream)
 * 
 * */
 
 class Nota {
	 public:
		Nota(); // Default
		Nota(float calif); // Con pto flotante
		Nota(const Nota &otro); // Por copia
		bool operator>(const Nota &otro) const;
		bool operator==(const Nota &otro) const;
		Nota operator=(const Nota &otro);
		operator int() const; // Seria como hacer: int i = (int) una_nota;
		friend std::istream& operator>>(std::istream& in, Nota &nota);
	private:
		calificacion_;
 };
