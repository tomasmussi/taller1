lat_inf = -0.001100
long_inf = -0.002600

lat_sup = 0.001100
long_der = 0.002600

alto = 50
ancho = 100


def get_y(latitud):
	return (latitud - lat_inf) * 111319
	
def get_x(longitud):
	return (longitud - long_inf) * 111131
	
inc_y = get_y(lat_sup)  / alto
inc_x = get_x(long_der) / ancho
tope = get_x(long_der)


def prueba_area():
	# Anda perfecto
	p1 = (get_x(-0.000100), get_y(0.000100))
	p2 = (get_x(0.000100), get_y(0.000100))
	p3 = (get_x(0.000100), get_y(-0.000100))
	p4 = (get_x(-0.000100), get_y(-0.000100))
	l = [p1, p2, p3, p4, p1]
	area = 0
	for i in xrange(len(l) - 1):
		area += (l[i][0] * l[i+1][1]) - (l[i+1][0] * l[i][1])
	area = area / 2
	area = abs(area)
	print area
	


RIGHT = "RIGHT"
LEFT = "LEFT"


def inside_convex_polygon(point, vertices):
	#print vertices
	previous_side = None
	n_vertices = len(vertices)
	for n in xrange(n_vertices):
		a, b = vertices[n], vertices[(n+1)%n_vertices]
		#print "A: " + str(a)
		#print "B: " + str(b)
		affine_segment = v_sub(b, a)
		affine_point = v_sub(point, a)
		current_side = get_side(affine_segment, affine_point)
		if current_side is None:
			#print "Falso"
			return False #outside or over an edge
		elif previous_side is None: #first segment
			previous_side = current_side
		elif previous_side != current_side:
			#print "Falso"
			return False
	#print "Verdadero"
	return True

def get_side(a, b):
	x = x_product(a, b)
	if x < 0:
		return LEFT
	elif x > 0: 
		return RIGHT
	else:
		return None

def v_sub(a, b):
	return (a[0]-b[0], a[1]-b[1])

def x_product(a, b):
	return a[0]*b[1]-a[1]*b[0]


def prueba_centro():
	print "Entrar entra"
	p1 = (get_x(-0.000100), get_y(0.000100))
	p2 = (get_x(0.000100), get_y(0.000100))
	p3 = (get_x(0.000100), get_y(-0.000100))
	p4 = (get_x(-0.000100), get_y(-0.000100))
	l = [p1, p2, p3, p4]
	
	adentro = inside_convex_polygon((0,0), l)
	if not adentro:
		print "FUNCIONA"
	adentro = inside_convex_polygon((280,125), l)
	if adentro:
		print "FUNCIONA"
	adentro = inside_convex_polygon((302,125), l)
	if not adentro:
		print "FUNCIONA"

prueba_centro()
