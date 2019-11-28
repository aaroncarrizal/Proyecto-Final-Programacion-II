#define NUMNODO 20
void portada(){
	cout<<endl<<endl<<endl<<endl<<endl<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
	cout<<"\t\t\t";
	cout<<"Proyecto de Programacion II"<<endl<<endl;
	cout<<"\t\tUniversidad Politecnica de San Luis Potosi"<<endl<<endl;
	cout<<"\t\t\tGuadalupe Ledesma Ramos"<<endl<<endl;
	cout<<"\tBravo Rotuno Jorge Enrique\tCarrizal Mendez Aaron Mishael"<<endl<<endl;
	Sleep(800);
	cout<<"\t\tPresiona cualquier tecla para continuar . . ."<<endl<<"\t\t\t\t     ";
	getch();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
	system("cls");
}
void rotacionSimpleDer(ArbolAVL &arbol, pNodo nodo){
	pNodo Padre=nodo->padre;
	pNodo P=nodo;
	pNodo Q=P->izq;
	pNodo B=Q->der;
	if(Padre)
		if(Padre->der==P)Padre->der=Q;
		else Padre->izq=Q;
	else arbol=Q;
	P->izq=B;
	Q->der=P;
	P->padre=Q;
	if(B)B->padre=P;
	Q->padre=Padre;
	P->fe=0;
	Q->fe=0; 
}
void rotacionSimpleIzq(ArbolAVL &arbol, pNodo nodo){
	pNodo Padre=nodo->padre;
	pNodo P=nodo;
	pNodo Q=P->der;
	pNodo B=Q->izq;
	if(Padre)
		if(Padre->der == P)Padre->der=Q;
		else Padre->izq=Q;
	else arbol=Q;
	P->der=B;
	Q->izq=P;
	P->padre=Q;
	if(B)B->padre=P;
	Q->padre=Padre;
	P->fe=0;
	Q->fe=0; 
}
void rotacionDobleDer(ArbolAVL &arbol, pNodo nodo){
	pNodo Padre=nodo->padre;
	pNodo P=nodo;
	pNodo Q=P->izq;
	pNodo R=Q->der;
	pNodo B=R->izq;
	pNodo C=R->der;
	if(Padre)
		if(Padre->der==nodo)Padre->der=R;
		else Padre->izq=R;
	else arbol=R;
	Q->der=B;
	P->izq=C;
	R->izq=Q;
	R->der=P;
	R->padre=Padre;
	P->padre=Q->padre=R;
	if(B)B->padre=Q;
	if(C)C->padre=P;
	switch(R->fe){
		case -1:
			Q->fe=0;
			P->fe=-1;
			break;
		case 0:
			Q->fe=0;
			P->fe=0;
			break;
		case 1:
			Q->fe=-1;
			P->fe=0;
			break;
	}
	R->fe=0;
}
void rotacionDobleIzq(ArbolAVL &arbol, pNodo nodo){
	pNodo Padre=nodo->padre;
	pNodo P=nodo;
	pNodo Q=P->der;
	pNodo R=Q->izq;
	pNodo B=R->izq;
	pNodo C=R->der;
	if(Padre)
		if(Padre->der==nodo)Padre->der=R;
		else Padre->izq=R;
	else arbol=R;
	P->der=B;
	Q->izq=C;
	R->izq=P;
	R->der=Q;
	R->padre=Padre;
	P->padre=Q->padre=R;
	if(B)B->padre=P;
	if(C)C->padre=Q;
	switch(R->fe){
		case -1:
			P->fe=0;
			Q->fe=-1;
			break;
		case 0:
			P->fe=0;
			Q->fe=0;
			break;
		case 1:
			P->fe=-1;
			Q->fe=0;
			break;
	}
	R->fe=0;
}
void balanceo(ArbolAVL &arbol, pNodo nodo, int rama, int nuevo){
	bool salir=false;
	while(nodo && !salir){
		if(nuevo)
			if(rama==0) nodo->fe--;
			else nodo->fe++;
		else if(rama==0)nodo->fe++;
			else nodo->fe--;
		if(nodo->fe==0)salir=true;
		else if(nodo->fe==-2){
			if(nodo->izq->fe==1)rotacionDobleDer(arbol,nodo);
			else rotacionSimpleDer(arbol,nodo);
			salir=true;
		}
		else if(nodo->fe==2){
			if(nodo->der->fe == -1)rotacionDobleIzq(arbol,nodo);
			else rotacionSimpleIzq(arbol,nodo);
			salir=true;
		}
		if(nodo->padre)
			if(nodo->padre->der==nodo)rama=1;
			else rama=0;
		nodo=nodo->padre;
	}
}
void insertarAVL(ArbolAVL &arbol,char word[],char def[]){
	pNodo padre=NULL;
	pNodo actual=arbol;
	while(actual!=NULL && strcmp(word,actual->palabra)!=0){
		padre=actual;
		if(strcmp(word,actual->palabra)==-1)actual=actual->izq;
		else if(strcmp(word,actual->palabra)==1)actual=actual->der;
	}
	if(actual!=NULL) return;
	if(padre==NULL){
		arbol=(Nodo *)malloc(sizeof(Nodo));
		strcpy(arbol->palabra,word);
		strcpy(arbol->significado,def);
		arbol->izq=NULL;
		arbol->der=NULL;
		arbol->padre=NULL;
		arbol->fe=0;
	}
	else if(strcmp(word,padre->palabra)==-1){
		actual=(Nodo *)malloc(sizeof(Nodo));
		padre->izq=actual;
		strcpy(actual->palabra,word);
		strcpy(actual->significado,def);
		actual->izq=actual->der=NULL;
		actual->padre=padre;
		actual->fe=0;
		balanceo(arbol,padre,0,1);
	}
	else if(strcmp(word,padre->palabra)==1){
		actual=(Nodo *)malloc(sizeof(Nodo));
		padre->der=actual;
		strcpy(actual->palabra,word);
		strcpy(actual->significado,def);
		actual->izq=actual->der=NULL;
		actual->padre=padre;
		actual->fe=0; 
		balanceo(arbol,padre,1,1);
	}
}
void eliminarNodo(ArbolAVL &arbol, char word[]){
	pNodo padre=NULL;
	pNodo actual=arbol;
	pNodo nodo;
	char auxw[33],auxdef[500];
	while(actual != NULL){
		if(strcmp(actual->palabra,word)==0){
			if(actual->der == NULL && actual->izq == NULL){
				if(padre)
					if(padre->der == actual)padre->der=NULL;
				else if(padre->izq == actual)padre->izq=NULL;
				free(actual);
				actual=NULL;
				if(padre->der==actual && padre->fe==1 || padre->izq==actual && padre->fe==-1){
					padre->fe=0;
					actual=padre;
					padre=actual->padre;
				}
				if(padre){
					if(padre->der==actual)balanceo(arbol,padre,1,0);
					else balanceo(arbol,padre,0,0);
				}
				return;
			}
			else{
				padre=actual;
				if(actual->der){
					nodo=actual->der;
					while(nodo->izq){
						padre=nodo;
						nodo=nodo->izq;
					}
				}
				else{
					nodo =actual->izq;
					while(nodo->der){
						padre=nodo;
						nodo=nodo->der;
					}
				}
			}
			strcpy(auxw,actual->palabra);
			strcpy(actual->palabra,nodo->palabra);
			strcpy(nodo->palabra,auxw);
			strcpy(auxdef,actual->significado);
			strcpy(actual->significado,nodo->significado);
			strcpy(nodo->significado,auxdef);
			actual=nodo;
		}
		else{
			padre=actual;
			if(strcmp(word,actual->palabra)==1)actual=actual->der;
			else if(strcmp(word,actual->palabra)==-1)actual=actual->izq;
		}
	}
}
void espera(){
	Sleep(800);
	cout<<" . ";
	Sleep(600);
	cout<<". ";
	Sleep(600);
	cout<<". "<<endl;
}
void buscar(Nodo *aux,char wordb[]){
	if(aux){
		buscar(aux->izq,wordb);
		if(strcmp(wordb,aux->palabra)==0){
			cout << aux->palabra <<":\n"<< aux->significado << endl;
			return;
		}
		buscar(aux->der,wordb);
	}
}
void inOrden(Nodo *aux){
	if(aux){
		inOrden(aux->izq);
		Sleep(300);
		cout << aux->palabra <<":\n" << aux->significado << endl << endl;
		Sleep(300);
		inOrden(aux->der);
	}
}
void exportar_datos(Nodo *aux,FILE *arch){
		if(aux){
			exportar_datos(aux->izq,arch);
			fprintf(arch,"%s\t",aux->palabra);
			fprintf(arch,"%s\n\n",aux->significado);
			exportar_datos(aux->der,arch);
		}
}
void exportar(Nodo *aux,FILE *arch){
	arch = fopen("diccionario.xls", "w+");
	exportar_datos(raiz,arch);
	fclose(arch);
}
void exportarProv(Nodo *aux,FILE *arch){
	arch = fopen("provisional.xls", "w+");
	exportar_datos(raiz,arch);
	fclose(arch);
}
void importar(FILE *arch, ArbolAVL &arbol){
	char auxw[33],auxdef[500];
	if(!(arch=fopen("diccionario.xls", "r+"))){	
		cout<<"Error al intentar crear el archivo";
		exit(1);	
	}
	rewind(arch);
	cout<<"Importando";
	espera();
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t",auxw);
		fscanf(arch,"%[^\n]\n",auxdef);
		insertarAVL(arbol,auxw,auxdef);
	}
	cout<<"Se han importado con éxito los datos."<<endl;
	fclose(arch);
}
void historial(FILE *busqueda, char word[]){
	if(!(busqueda=fopen("historial.xls", "w+"))){	
		cout<<"Error al intentar crear el archivo";
		exit(1);	
	}
	fprintf(busqueda,"%s\n",word);
	fclose(busqueda);
}
void mostrar_historial(FILE *busqueda){
	char auxw[33];
	if(!(busqueda=fopen("historial.xls", "r+"))){	
		cout<<"Error al intentar crear el archivo";
		exit(1);	
	}
	cout<<"Historial de busqueda:"<<endl;
	while(!feof(busqueda)){
		fscanf(busqueda,"%[^\n]\n",auxw);
		cout<<"+ "<<auxw<<endl;
	}
	fclose(busqueda);
}
void formato(char word[]){
	word[0]=toupper(word[0]);
	for(int i=1;i<strlen(word);i++)
		word[i]=tolower(word[i]);	
}
void impresionArbol(Nodo *arbol, int cont){
	if(arbol==NULL){
		return;
	}else{
		impresionArbol(arbol->der,cont+1);
		for(int i=0;i<cont;i++){
			cout<<"        ";
		}
		cout<<arbol->palabra<<endl;
		impresionArbol(arbol->izq,cont+1);
	}
}

//------------------------------------------Funciones de la lista-----------------------------------------------------------------//

void agrega_elemento(){//crea la lista 
	nodoLista *nuevo;
	nuevo=(struct nodoLista*)malloc(sizeof(struct nodoLista));//reserva memoria
	if(nuevo==NULL)
		cout<<"No hay memoria disponible"<<endl;
	else{
		nuevo->arbolito=NULL;
		nuevo->siguiente=NULL;
		if(primero==NULL){
			primero=nuevo;
			ultimo=nuevo;
		}else{
			ultimo->siguiente=nuevo;
			ultimo=nuevo;
		}
	}
}
void mostrar_lista(){//recorre toda la lista e imprime sus arboles
	nodoLista *aux;
	aux=primero;
	while(aux!=NULL){
		cout<<"Este arbol tiene "<<aux->cont<<" datos"<<endl<<endl<<endl;
		inOrden(aux->arbolito);
		aux=aux->siguiente; //recorrido de la lista
		cout<<endl<<endl;
	}
}
void mostrar_lista_grafico(){//recorre toda la lista e imprime sus arboles
	nodoLista *aux;
	aux=primero;
	while(aux!=NULL){
		cout<<endl<<"Este arbol tiene "<<aux->cont<<" datos"<<endl<<endl<<endl;
		impresionArbol(aux->arbolito,0);
		aux=aux->siguiente; //recorrido de la lista
		cout<<endl<<endl;
	}
}
void importarArbolitosArchivo(FILE *arch){
	char auxw[33],auxdef[500];
	nodoLista *aux;
	agrega_elemento();
	aux=primero;
	if(!(arch=fopen("provisional.xls", "r+"))){	
		cout<<"Error al intentar crear el archivo";
		exit(1);	
	}
	rewind(arch);
	aux->cont=0;
	while(!feof(arch) && aux->cont<=NUMNODO){
		fscanf(arch,"%[^\t]\t",auxw);
		fscanf(arch,"%[^\n]\n",auxdef);
		insertarAVL(aux->arbolito,auxw,auxdef);
		aux->cont++;
		if(aux->cont==NUMNODO){
			agrega_elemento();
			aux=aux->siguiente;
			aux->cont=0;
		}
	}
	fclose(arch);
}
