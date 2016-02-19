# Makefile

CXXFLAGS = -O0 -g -pthread -lpthread


GTKFLAGS = `pkg-config gtkmm-3.0 --cflags --libs`

CC = g++

#EN ESTA VARIABLE VAN TODAS LAS DEPENDENCIAS QUE TENGAN UN MAIN Y SE QUIERAN COMPILAR
TARGETS = $(wildcard ej*.cpp)

archivos = $(filter-out $(targets), $(wildcard *.cpp))

# EN ESTA VARIABLE SE DEFINEN TODAS LAS CARPETAS QUE TENGAN .H
# EXTERNOS QUE ESTEN USANDO
INCLUDES = .

I-INCLUDES = $(addprefix -I, $(INCLUDES))

bin = $(archivos:.cpp=.o)

robjs = $(wildcard *.o main test)

#######################################
#verbose = si

occ := $(CC)
ocxx := $(CXX)
orm := $(RM)
old := $(LD)
ifdef verbose
RM := $(RM) -v
else
#CC =  @echo "  Compilando  $@"; $(occ)
#CXX = @echo "  CXX $@"; $(ocxx)
#RM =  @echo "  CLEAN"; $(orm)
#LD =  @echo "  LD  $@"; $(old)
endif

COMP_DEPEND = @echo "Compilar dependencias externas..."
LIMPIAR = @echo "Limpiando..."

#########################################


all: targets

binaries: $(bin)

%.o: %.cpp
	$(CC) $(CXXFLAGS) $(I-INCLUDES) -c $< $(GTKFLAGS)

targets: $(TARGETS)

$(TARGETS):
	$(CC) $(CXXFLAGS) $(I-INCLUDES) $@ -o $(@:.cpp= ) $(GTKFLAGS)

clean:
	$(LIMPIAR); rm -f $(robjs)

.PHONY: clean all binaries targets $(TARGETS)
