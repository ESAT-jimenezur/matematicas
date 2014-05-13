#include <SDL.h>


/**
	Estructuras de datos
	-*	Punto
	-*	Vector
	-	Recta (Varios Tipos)

	Funciones
	-	Sumar vectores
	-	Restar vectores
	-	Dibujar cuadrado con punto y vector --> * Importante *
	-	Dibujar cubo 3D
	-	Funcion translacion --> @get(x,y); @return(mat3) --> * Importante *
	-	Vector +- punto
	-	Modulo vector
	-	Escalar vector
	-	Vector dado 2 puntos
	-	Combinacion de puntos		(baricentrico)
	-	Producto Escalar			(dot)
	-	Vector perpendicular a otro
	-	Normalizar vector

	-	Construccion de recta con 2 puntos
	-	Construccion de recta con punto y vector
	-	Construccion de recta con punto y vector perpendicular
**/

// variables GLOBALES
struct {
	float frame;
	int mouse_x;
	int mouse_y;
	bool mouse_left;
	bool mouse_right;
	bool must_continue;
	SDL_Renderer *r; 
} State;

struct Punto{
	float x;
	float y;
};

struct Vector{
	float incrementoX;
	float incrementoY;
};

struct Recta2Ptos{
	float ptoX;
	float ptoY;

	Vector v;
};

struct vec2 {
	float x;
	float y;
	vec2(float a = 0.0f, float b = 0.0f)  {
		x = a;
		y = b;
	}
};

struct vec3{
	float x;
	float y;
	float z;
	vec3(float a = 0.0f, float b = 0.0f, float c = 0.0f){
		x = a;
		y = b;
		z = c;
	}
};


struct mat2 {
	float m00;
	float m01;
	float m10;
	float m11;

	mat2(vec2 a = vec2(1,0), vec2 b = vec2(0,1)) {
		m00 = a.x;
		m01 = a.y;
		m10 = b.x;
		m11 = b.y;
	}
};

struct mat3{
	float m00;
	float m01;
	float m02;

	float m10;
	float m11;
	float m12;

	float m20;
	float m21;
	float m22;

	mat3(vec3 a = vec3(1, 0, 0), vec3 b = vec3(0, 1, 0), vec3 c = vec3(0, 0, 0){
		m000 = a.x;
		m01 = a.y;
		m02 = a.z;

		m10 = b.x;
		m11 = b.y;
		m12 = b.z;

		m20 = c.x;
		m21 = c.y;
		m22 = c.z;
	}
};






void drawRecta(SDL_Renderer *renderer, Recta2Ptos r){
	SDL_RenderDrawLine(renderer, r.v.incrementoX, r.v.incrementoY, r.ptoX, r.ptoY);
}

void drawSquare(SDL_Renderer *renderer, int x, int y, int side) {
	int half_side = side/2;
	SDL_RenderDrawLine(renderer, x - half_side, y - half_side, x-half_side, y+half_side);
	SDL_RenderDrawLine(renderer, x - half_side, y + half_side, x+half_side, y+half_side);
	SDL_RenderDrawLine(renderer, x + half_side, y + half_side, x+half_side, y-half_side);
	SDL_RenderDrawLine(renderer, x + half_side, y - half_side, x-half_side, y-half_side);
}

void drawVector(SDL_Renderer *renderer, Punto p, Vector v){
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderDrawLine(renderer, p.x, p.y, (v.incrementoX*0.95), (v.incrementoY*0.95));

	//Azul
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	//TODO
}

Vector sumaVectores(Vector v1, Vector v2){
	Vector v3;
	v3.incrementoX = v2.incrementoX + v1.incrementoX;
	v3.incrementoY = v2.incrementoY + v1.incrementoY;

	return v3;
}

Vector productoEscalar(Vector v1, Vector v2){
	Vector v3;

	

	return v3;
}

Vector restaVectores(Vector v1, Vector v2){
	Vector v3;

	v3.incrementoX = v2.incrementoX - v1.incrementoX;
	v3.incrementoY = v2.incrementoY - v1.incrementoY;

	return v3;
}

vec3 multMat3xVec3(mat3 m, vec3 v){
	vec3 vAux;
	vAux.x = m.m00 * v.x + m.01 * v.y + m.02 * v.z;
	vAux.y = m.m10 * v.x + m.11 * v.y + m.12 * v.z;
	vAux.z = m.m20 * v.x + m.21 * v.y + m.22 * v.z;
	return vAux;
}

mat3 multMat3xMat3(mat3 m1, mat3 m2){
	mat3 mAux;
	
	// Linea 1
	mAux.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.02 * m2.20;
	mAux.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.02 * m2.21;
	mAux.m02 = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.02 * m2.22;

	// Linea 2
	mAux.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.12 * m2.20;
	mAux.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.12 * m2.21;
	mAux.m12 = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.12 * m2.22;

	// Linea 3
	mAux.m20 = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.22 * m2.20;
	mAux.m21 = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.22 * m2.21;
	mAux.m22 = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.22 * m2.22;

	return mAux;
}

//-- implementacion --------------------------------------
vec2 add(vec2 a, vec2 b) {
	return vec2(a.x+b.x, a.y+b.y);
}

void drawVector(vec2 pos, vec2 v) {
	// SDL_RenderDrawLine(State.r, x0, y0, x1, y1); ....
}

void drawSquare(mat3 m){
	
}

void draw_shape(vec2 pos, mat2 m) {
	float v[] = {
		0, 100,
		-15,100,
		+15,100,
		-50,0,
		+50,0,
		-10,-40,
		10,-40
	};
	static const unsigned int num_vectors = sizeof(v)/(sizeof(float)*2);
	SDL_SetRenderDrawColor(State.r, 255, 200, 200, 255);
	for(unsigned int i = 0; i < num_vectors; ++i) {
		drawVector(pos, vec2(v[i*2],v[i*2+1]));
	}
}

void drawCube(mat3 m){

	vec2 p00;
	vec2 p01;
	vec2 p10;
	vec2 p11;

}

void render() {
	SDL_SetRenderDrawColor(State.r, 128, 0, 0, 255);
	SDL_RenderClear(State.r);
	SDL_SetRenderDrawColor(State.r, 255,255,255,255);

	//Trabajar aqui


	vec3 v3;
	v3.x = 10;
	v3.y = 10;
	v3.z = 1;

	mat3 m3;


	drawCube(m3);




	SDL_RenderPresent(State.r);
}



int main(int argc, char **argv) {
	State.frame = 0;
	State.mouse_x = 0;
	State.mouse_y = 0;
	State.mouse_left  = false;
	State.mouse_right = false;

	SDL_Window *w = NULL;
	SDL_Renderer *r = NULL;
	SDL_Init(SDL_INIT_VIDEO);
	w = SDL_CreateWindow("ESAT",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		640, 480,
		0);
	r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

	State.r = r;
	State.must_continue = true;

	while(State.must_continue) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					State.must_continue = false;
					break;
				case SDL_MOUSEMOTION:
					State.mouse_x = e.motion.x;
					State.mouse_y = e.motion.y;
					break;
				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button) {
						case SDL_BUTTON_LEFT:  State.mouse_left = true; break;
						case SDL_BUTTON_RIGHT: State.mouse_right = true; break;
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch(e.button.button) {
						case SDL_BUTTON_LEFT:  State.mouse_left = false; break;
						case SDL_BUTTON_RIGHT: State.mouse_right = false; break;
					}
					break;
			}
		}
		render();
		State.frame += 1;
	}
	
	SDL_DestroyRenderer(r);
	SDL_DestroyWindow(w);
	SDL_Quit();
	return 0;
}