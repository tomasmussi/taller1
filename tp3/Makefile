# Makefile de ejemplo para C/C++
# Creado: 15/04/2004 - Leandro Lucarella
# Modificado: 23/04/2014 - Pablo Roca
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]

# CONFIGURACION
################

# Nombre del ejecutable y los directorios a usar.
target = tp
SRCDIR = ./src
INCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Archivos a usar
SRC = $(wildcard $(SRCDIR)/*.$(extension))
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.$(extension)=.o)))

# Archivos con el código fuente que componen el ejecutable. Si no se especifica,
# toma todos los archivos con la extensión mencionada. Para especificar hay que
# descomentar la línea (quitarle el '#' del principio).
# NOTA: No poner cabeceras (.h).
#fuentes = entrada.cpp

# Si usa funciones de math.h, descomentar (quitar el '#' a) la siguiente línea.
math = si

# Si usa pthreads, descomentar (quitar el '#' a) la siguiente línea.
#pthreads = si

# Si es un programa GTK+, descomentar (quitar el '#' a) la siguiente línea.
#gtk = si

# Si es un programa gtkmm, descomentar (quitar el '#' a) la siguiente línea.
#gtkmm = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si


# CONFIGURACION "AVANZADA"
###########################

CC = gcc

# Opciones para el compilador C/C++ para tratamiento de errores y warnings.
CFLAGS = -Wall -Werror -pedantic -pedantic-errors

# Para optimizar el binario resultante lo mejor posible
CFLAGS += -O3 -DNDEBUG

# Para valgrind o debug
CFLAGS += -ggdb -DDEBUG -fno-inline

# Opciones del enlazador.
#LDFLAGS =

# Estandar de C a usar
CSTD = c99

# Estandar de C++ a usar
CXXSTD = c++98

# Si se quiere compilar estaticamente, descomentar la siguiente linea
#static = si


# VARIABLES CALCULADAS A PARTIR DE LA CONFIGURACION
####################################################

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtk
CFLAGS += $(shell pkg-config --cflags gtk+-3.0) \
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED
LDFLAGS += $(shell pkg-config --libs gtk+-3.0)
endif

# Agrego flags y libs de GTK+ de ser necesario.
ifdef gtkmm
CFLAGS += $(shell pkg-config --cflags gtkmm-3.0) \
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED	\
	-DGDKMM_DISABLE_DEPRECATED 	\
	-DGTKMM_DISABLE_DEPRECATED
LDFLAGS += $(shell pkg-config --libs gtkmm-3.0)
endif

# Linkeo con libm de ser necesario.
ifdef math
LDFLAGS += -lm
endif

# Linkeo con pthreads de ser necesario.
ifdef pthreads
LDFLAGS += -lpthread -pthread
endif

ifdef static
LDFLAGS += -static
endif

# Pongo flags de C para C++ también
CXXFLAGS += $(CFLAGS)

# Uso enlazador de c++ si es código no C.
ifeq ($(extension), c)
CFLAGS += -std=$(CSTD)
LD = $(CC)
else
CXXFLAGS += -std=$(CXXSTD)
LD = $(CXX)
endif

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
CC =  @echo "  CC  $@"; $(occ)
CXX = @echo "  CXX $@"; $(ocxx)
RM =  @echo "  CLEAN"; $(orm)
LD =  @echo "  LD  $@"; $(old)
endif

# REGLAS
#########

all: cpplint test-codes v-test1 v-test2 v-test3 v-test4

$(BINDIR)/$(target): $(OBJ) | $(BINDIR)
	@if [ -z "$(OBJ)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensión debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(OBJ) -o $(BINDIR)/$(target) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(extension) | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: all clean

$(OBJDIR):
	mkdir $@

$(BINDIR):
	mkdir $@

run-%: cpplint clean $(BINDIR)/$(target)
	$(BINDIR)/$(target) tests/test$*/mediciones.dat tests/test$*/tuberias.txt tests/test$*/recorrido.txt

test-codes: clean $(BINDIR)/$(target)
	$(BINDIR)/$(target) tests/test1/configuracion.txt tests/test1/mapa.txt > /dev/null 2> /dev/null; test $$? -eq 0
	$(BINDIR)/$(target) tests/test2/configuracion.txt tests/test2/mapa.txt > /dev/null 2> /dev/null; test $$? -eq 0
	$(BINDIR)/$(target) tests/test3/configuracion.txt tests/test3/mapa.txt > /dev/null 2> /dev/null; test $$? -eq 0
	$(BINDIR)/$(target) tests/test4/configuracion.txt tests/test4/mapa.txt > /dev/null 2> /dev/null; test $$? -eq 0

test%:
	diff -iad $(BINDIR)/$@__stdout__ tests/$@/__stdout__
	diff -iad $(BINDIR)/$@__stderr__ tests/$@/__stderr__

v-test%: valgrind-% test%
	
valgrind-%: $(BINDIR)/$(target)
	./execute_valgrind_and_verify_result_code.sh $(BINDIR)/$(target) tests/test$*/configuracion.txt tests/test$*/mapa.txt > $(BINDIR)/test$*__stdout__ 2> $(BINDIR)/test$*__stderr__

cpplint:
	echo "Hola"
	python ./cpplint.py --extensions=h,hpp,c,cpp --filter=`cat filter_options` `find -regextype posix-egrep -regex '.*\.(h|hpp|c|cpp)'`

clean:
	$(RM) $(o_files) $(BINDIR)/$(target)
	$(RM) -R $(BINDIR)
	$(RM) -R $(OBJDIR)

