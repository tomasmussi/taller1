# Makefile de ejemplo para C/C++
# Creado: 15/04/2004 - Leandro Lucarella
# Modificado: 23/04/2014 - Pablo Roca
# Copyleft 2004 - Leandro Lucarella, Bajo licencia GPL [http://www.gnu.org/]

# CONFIGURACION
################

# Nombre del ejecutable y los directorios a usar.
SRCDIR = ./src
INCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin
CLIENT = $(BINDIR)/client
SERVER = $(BINDIR)/server

# Extensión de los archivos a compilar (c para C, cpp o cc o cxx para C++).
extension = cpp

# Archivos a usar
SRC_COMMON = $(wildcard $(SRCDIR)/common*.$(extension))
SRC_CLIENT = $(wildcard $(SRCDIR)/client*.$(extension))
SRC_SERVER = $(wildcard $(SRCDIR)/server*.$(extension))
OBJ_COMMON = $(addprefix $(OBJDIR)/,$(notdir $(SRC_COMMON:.$(extension)=.o)))
OBJ_CLIENT = $(addprefix $(OBJDIR)/,$(notdir $(SRC_CLIENT:.$(extension)=.o))) $(OBJ_COMMON)
OBJ_SERVER = $(addprefix $(OBJDIR)/,$(notdir $(SRC_SERVER:.$(extension)=.o))) $(OBJ_COMMON)

# Archivos con el código fuente que componen el ejecutable. Si no se especifica,
# toma todos los archivos con la extensión mencionada. Para especificar hay que
# descomentar la línea (quitarle el '#' del principio).
# NOTA: No poner cabeceras (.h).
#fuentes = entrada.cpp

# Si usa funciones de math.h, descomentar (quitar el '#' a) la siguiente línea.
math = si

# Si usa pthreads, descomentar (quitar el '#' a) la siguiente línea.
pthreads = si

# Si es un programa GTK+, descomentar (quitar el '#' a) la siguiente línea.
#gtk = si

# Si es un programa gtkmm, descomentar (quitar el '#' a) la siguiente línea.
#gtkmm = si

# Descomentar si se quiere ver como se invoca al compilador
#verbose = si


# CONFIGURACION "AVANZADA"
###########################

# Opciones para el compilador C/C++ para tratamiento de errores y warnings.
CFLAGS = -Wall -Werror -Wextra -Wconversion -Wtype-limits -pedantic -pedantic-errors

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

catedra: cpplint $(CLIENT) $(SERVER)
	cp bin/client tests/client
	cp bin/server tests/server
	cd tests && ./runme.sh 01
	cd tests && ./runme.sh 02
	cd tests && ./runme.sh 03
	cd tests && ./runme.sh 04
	cd tests && ./runme.sh 05
	cd tests && ./runme.sh 06
	cd tests && ./runme.sh 07
	cd tests && ./runme.sh 08

cpplint: SRC_ALL = $(wildcard $(SRCDIR)/*)
cpplint: $(SRC_ALL)
	cpplint

$(CLIENT): $(OBJ_CLIENT) | $(BINDIR)
	@if [ -z "$(OBJ_CLIENT)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensión debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(OBJ_CLIENT) -o $@ $(LDFLAGS)

$(SERVER): $(OBJ_SERVER) | $(BINDIR)
	@if [ -z "$(OBJ_SERVER)" ]; \
	then \
		echo "No hay archivos de entrada, recuerde que la extensión debe ser '.$(extension)'."; \
		false; \
	fi >&2
	$(LD) $(OBJ_SERVER) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(extension) $(SRCDIR)/*.h | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/client_main.o: $(SRCDIR)/client_main.$(extension) | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR)/server_main.o: $(SRCDIR)/server_main.$(extension) | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) -r $(BINDIR) $(OBJDIR)

.PHONY: all clean

$(OBJDIR):
	mkdir $@

$(BINDIR):
	mkdir $@
