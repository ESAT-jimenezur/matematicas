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

struct vec4{
	float x;
	float y;
	float z;
	float w;
	vec4(float a = 0.0f, float b = 0.0f, float c = 0.0f, float d = 0.0f){
		x = a;
		y = b;
		z = c;
		w = d;
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

struct mat4{
	float m00;
	float m01;
	float m02;
	float m03;

	float m10;
	float m11;
	float m12;
	float m13;

	float m20;
	float m21;
	float m22;
	float m23;

	float m30;
	float m31;
	float m32;
	float m33;

	mat4(vec4 a = vec4(1, 0, 0, 0), vec4 b = vec4(0, 1, 0, 0), vec4 c = vec4(0, 0, 1, 0), vec4 d = vec4(0, 0, 0, 1)){
		m00 = a.x;
		m01 = a.y;
		m02 = a.z;
		m03 = a.w;

		m10 = b.x;
		m11 = b.y;
		m12 = b.z;
		m13 = b.w;

		m20 = c.x;
		m21 = c.y;
		m22 = c.z;
		m23 = c.w;

		m30 = d.x;
		m31 = d.y;
		m32 = d.z;
		m33 = d.w;
	}
};


void drawRecta(SDL_Renderer *renderer, Recta2Ptos r){
	SDL_RenderDrawLine(renderer, r.v.incrementoX, r.v.incrementoY, r.ptoX, r.ptoY);
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
	vAux.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z;
	vAux.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z;
	vAux.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z;
	return vAux;
}

vec4 multMat4xVec4(mat4 m, vec4 v){
	vec4 vAux;
	vAux.x = m.m00 * v.x + m.m01 * v.y + m.m02 * v.z + m.m03 * v.w;
	vAux.y = m.m10 * v.x + m.m11 * v.y + m.m12 * v.z + m.m13 * v.w;
	vAux.z = m.m20 * v.x + m.m21 * v.y + m.m22 * v.z + m.m23 * v.w;
	vAux.w = m.m30 * v.x + m.m31 * v.y + m.m32 * v.z + m.m33 * v.w;

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

mat4 multMat4xMat4(mat4 m1, mat4 m2){
	mat4 mAux;
	
	// Linea 1
	mAux.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20;
	mAux.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21;
	mAux.m02 = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22;
	mAux.m03 = m1.m00 * m2.m03 + m1.m01 * m2.m13 + m1.m02 * m2.m23;

	// Linea 2
	mAux.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20;
	mAux.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21;
	mAux.m12 = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22;
	mAux.m13 = m1.m10 * m2.m03 + m1.m11 * m2.m13 + m1.m12 * m2.m23;


	// Linea 3
	mAux.m20 = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20;
	mAux.m21 = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21;
	mAux.m22 = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22;
	mAux.m23 = m1.m20 * m2.m03 + m1.m21 * m2.m13 + m1.m22 * m2.m23;

	// Linea 4
	mAux.m30 = m1.m30 * m2.m00 + m1.m31 * m2.m10 + m1.m32 * m2.m20;
	mAux.m31 = m1.m30 * m2.m01 + m1.m31 * m2.m11 + m1.m32 * m2.m21;
	mAux.m32 = m1.m30 * m2.m02 + m1.m31 * m2.m12 + m1.m32 * m2.m22;
	mAux.m33 = m1.m30 * m2.m03 + m1.m31 * m2.m13 + m1.m32 * m2.m23;


	return mAux;
}


vec4 homogeneizar(vec4 v){
	vec4 vAux;
	vAux.x = v.x / v.w;
	vAux.y = v.y / v.w;
	vAux.z = v.z / v.w;
	vAux.w = 1;

	return vAux;
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

void drawCube(mat4 m){

	int t = 10;

	vec4 p1_1 = multMat4xVec4(m, vec4(-t, -t, 1, -1));
	homogeneizar(p1_1);
	vec4 p2_1 = multMat4xVec4(m, vec4(-t, t, 1, -1));
	homogeneizar(p2_1);
	vec4 p3_1 = multMat4xVec4(m, vec4(t, t, 1, -1));
	homogeneizar(p3_1);
	vec4 p4_1 = multMat4xVec4(m, vec4(t, -t, 1, -1));
	homogeneizar(p4_1);


	vec4 p1_2 = multMat4xVec4(m, vec4(-t, -t, 1, 1));
	homogeneizar(p1_2);
	vec4 p2_2 = multMat4xVec4(m, vec4(-t, t, 1, 1));
	homogeneizar(p2_2);
	vec4 p3_2 = multMat4xVec4(m, vec4(t, t, 1, 1));
	homogeneizar(p3_2);
	vec4 p4_2 = multMat4xVec4(m, vec4(t, -t, 1, 1));
	homogeneizar(p4_2);

	SDL_RenderDrawLine(State.r, p1_1.x, p1_1.y, p2_1.x, p2_1.y);
	SDL_RenderDrawLine(State.r, p2_1.x, p2_1.y, p3_1.x, p3_1.y);
	SDL_RenderDrawLine(State.r, p3_1.x, p3_1.y, p4_1.x, p4_1.y);
	SDL_RenderDrawLine(State.r, p4_1.x, p4_1.y, p1_1.x, p1_1.y);

	SDL_RenderDrawLine(State.r, p1_2.x, p1_2.y, p2_2.x, p2_2.y);
	SDL_RenderDrawLine(State.r, p2_2.x, p2_2.y, p3_2.x, p3_2.y);
	SDL_RenderDrawLine(State.r, p3_2.x, p3_2.y, p4_2.x, p4_2.y);
	SDL_RenderDrawLine(State.r, p4_2.x, p4_2.y, p1_2.x, p1_2.y);

}

void drawCircle(mat3 m, float nDivisiones){

	float pi = 3.141516;

	for(float i = 0.0; i < 2*pi; i+=0.01){

		SDL_Point point = {
			sin(i)*m.m00 + m.m02, 
			cos(i)*m.m11 + m.m12
		};

		SDL_RenderDrawPoints(State.r, &point, 1);
	}

}

void render() {
	SDL_SetRenderDrawColor(State.r, 128, 0, 0, 255);
	SDL_RenderClear(State.r);
	SDL_SetRenderDrawColor(State.r, 255,255,255,255);

	//Trabajar aqui
	
	vec2 centro_pantalla;
	centro_pantalla.x = 320;
	centro_pantalla.y = 240;

	mat4 mat1_final;
	drawCube(mat1_final);
	
	/*
	//Transladamos al centro
	mat3 m_centro = mat3Translacion(centro_pantalla);
	mat3 m_escalado = mat3Escalado(vec2(200, 200));

	mat3 mat1_final;

	mat1_final = multMat3xMat3(mat1_final, m_centro);
	mat1_final = multMat3xMat3(mat1_final, m_escalado); 

	drawCircle(mat1_final, 400.0);
	*/
	/*

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
	*/

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