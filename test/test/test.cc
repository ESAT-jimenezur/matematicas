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

int main(int argc, char **argv) {
	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
		"ESAT",
		SDL_WINDOWPOS_CENTERED, // centrado en x
		SDL_WINDOWPOS_CENTERED, // centado en y
		800, 600,
		0);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int mx = 0; 
	int my = 0;
	bool must_exit = false;
	SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
		SDL_RenderClear(renderer);
	while(!must_exit) {
		SDL_Event event;
		while(SDL_PollEvent(&event)) {


			switch(event.type) {
				case SDL_QUIT: 
					must_exit = true;
					break;
				case SDL_MOUSEMOTION:
					mx = event.motion.x;
					my = event.motion.y;
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 128, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255,255,255,255);
		

		Punto p;
		p.x = mx;
		p.y = my;

		Vector v;
		v.incrementoX = 0;
		v.incrementoY = 0;


		Recta2Ptos r;
		r.ptoX = mx;
		r.ptoY = my;
		r.v = v;

		drawRecta(renderer, r);

		//drawVector(renderer, p, v);
		//drawSquare(renderer, mx, my, 20);
		
		
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();
	return 0;
}