void inOrden(Nodo *aux){
	if(aux){
		inOrden(aux->izq);
		cout << aux->palabra <<"\t" << aux->significado << endl;
		inOrden(aux->der);
	}
}

void exportar(Nodo *aux,FILE *arch){
		if(aux){
			if(!(arch=fopen("diccionario.xls", "a+")))
			{	
				cout<<"Error al intentar crear el archivo";
				exit(1);	
			}
			//cout<<"Exportando"<<endl;
			exportar(aux->izq,arch);
			fprintf(arch,"%s\t",aux->palabra );
			cout<<aux->palabra<<"\t";
			fprintf(arch,"%s\n",aux->significado);
			cout<<aux->significado<<endl;;
			exportar(aux->der,arch);
		}
		fclose(arch);
}

void importar(FILE *arch, ArbolAVL &arbol){
	char auxw[33],auxdef[80];
	if(!(arch=fopen("diccionario.xls", "r"))){	
		cout<<"Error al intentar crear el archivo";
		exit(1);	
	}
	rewind(arch);
	while(!feof(arch)){
		fscanf(arch,"%[^\t]\t",auxw);
		fscanf(arch,"%[^\n]\n",auxdef);
		insertarAVL(arbol,auxw,auxdef);
	}
	fclose(arch);
}
