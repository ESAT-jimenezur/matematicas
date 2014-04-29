#include <SDL.h>


/**
	Estructuras de datos
	-*	Punto
	-*	Vector
	-	Recta (Varios Tipos)

	Funciones
	-	Sumar vectores
	-	Restar vectores
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
*/

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

struct mat2 {
	float m00;
	float m01;
	float m10;
	float m11;

	mat2(vec2 a = vec2(1,0) , vec2 b = vec2(0,1)) {
		m00 = a.x;
		m01 = a.y;
		m10 = b.x;
		m11 = b.y;
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


//-- implementacion --------------------------------------
vec2 add(vec2 a, vec2 b) {
	return vec2(a.x+b.x, a.y+b.y);
}

void drawVector(vec2 pos, vec2 v) {
	// SDL_RenderDrawLine(State.r, x0, y0, x1, y1); ....
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

void render() {
	SDL_SetRenderDrawColor(State.r, 128, 0, 0, 255);
	SDL_RenderClear(State.r);
	SDL_SetRenderDrawColor(State.r, 255,255,255,255);

	//Trabajar aqui


	vec2 v2;
	v2.x = 10;
	v2.y = 10;

	mat2 m;

	draw_shape(v2, m);




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