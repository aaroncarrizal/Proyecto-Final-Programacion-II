#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
#include<time.h>
#include<windows.h>
using namespace std;
struct Nodo{//arbol
	int fe;
	char palabra[33], significado[500];
	struct Nodo *izq, *der, *padre;
}*raiz;
struct nodoLista{//lista
	int cont;
	struct Nodo *arbolito;
	struct nodoLista *siguiente;
}*primero, *ultimo;
typedef Nodo *ArbolAVL;
typedef Nodo *pNodo;
#include"funcionesAVL.h"
#include"validaciones.h"
