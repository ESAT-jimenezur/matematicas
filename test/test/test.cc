#include <SDL.h>
#include <stdio.h>
#include <math.h>

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

	mat3(vec3 a = vec3(1, 0, 0), vec3 b = vec3(0, 1, 0), vec3 c = vec3(0, 0, 1)){
		m00 = a.x;
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

/*
void drawSquare(SDL_Renderer *renderer, int x, int y, int side) {
	int half_side = side/2;
	SDL_RenderDrawLine(renderer, x - half_side, y - half_side, x-half_side, y+half_side);
	SDL_RenderDrawLine(renderer, x - half_side, y + half_side, x+half_side, y+half_side);
	SDL_RenderDrawLine(renderer, x + half_side, y + half_side, x+half_side, y-half_side);
	SDL_RenderDrawLine(renderer, x + half_side, y - half_side, x-half_side, y-half_side);
}
*/

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
	vAux.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
	vAux.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
	vAux.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
	return vAux;
}

mat3 mat3Translacion(vec2 v){
	mat3 mAux;

	mAux.m02 = v.x;
	mAux.m12 = v.y;

	return mAux;
}

mat3 mat3Rotacion(float radianes){
	mat3 mAux;

	mAux.m00 = cos(radianes);
	mAux.m01 = -sin(radianes);
	mAux.m10 = sin(radianes);
	mAux.m11 = cos(radianes);

	return mAux;
}

mat3 mat3Escalado(vec2 v){
	mat3 mAux;

	mAux.m00 = v.x;
	mAux.m11 = v.y;

	return mAux;
}

mat3 multMat3xMat3(mat3 m1, mat3 m2){
	mat3 mAux;
	
	// Linea 1
	mAux.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20;
	mAux.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21;
	mAux.m02 = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22;

	// Linea 2
	mAux.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20;
	mAux.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21;
	mAux.m12 = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22;

	// Linea 3
	mAux.m20 = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20;
	mAux.m21 = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21;
	mAux.m22 = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22;

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
	
	int t = 10;
	
	vec3 p1 = multMat3xVec3(m, vec3(-t, -t, 1));
	vec3 p2 = multMat3xVec3(m, vec3(-t, t, 1));
	vec3 p3 = multMat3xVec3(m, vec3(t, t, 1));
	vec3 p4 = multMat3xVec3(m, vec3(t, -t, 1));

	SDL_RenderDrawLine(State.r, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(State.r, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(State.r, p3.x, p3.y, p4.x, p4.y);
	SDL_RenderDrawLine(State.r, p4.x, p4.y, p1.x, p1.y);

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

	vec2 centro_pantalla;
	centro_pantalla.x = 320;
	centro_pantalla.y = 240;
	
	//Transladamos al centro
	mat3 m_centro = mat3Translacion(centro_pantalla);

	//Rotamos
	mat3 m_rotacion = mat3Rotacion(State.frame / 8000);
	mat3 m_escalado = mat3Escalado(vec2(1.5, 1.5));
	
	// Multiplicamos rotacion y centro
	mat3 mat1_final;

	mat1_final = multMat3xMat3(mat1_final, m_centro); // Primero la llevamos al centro
	mat1_final = multMat3xMat3(mat1_final, m_rotacion); // Hacemos que rote
	mat1_final = multMat3xMat3(mat1_final, m_escalado); // Lo hacemos mas grande
	mat1_final = multMat3xMat3(mat1_final, mat3Translacion(vec2(50, 50))); // Nos la llevamos ms lejos del centro
	mat1_final = multMat3xMat3(mat1_final, mat3Rotacion(State.frame / 3000)); // Hacemos que vuelva a rotar

	mat3 mat2_final;
	mat2_final = multMat3xMat3(mat2_final, mat1_final);

		
	
	// Pintamos cuadrados
	drawSquare(mat2_final);
	

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