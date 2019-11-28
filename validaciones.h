float validaFlotante(){
	char cadena [20]="";
	int cont = 0;
	bool bandera = true;
	float flotante = 0;
	
	while (bandera){
		scanf("%[^\n]", cadena);
		fflush(stdin);
		if(strlen(cadena)>20){
			continue;
		}else{
			for(int i = 0; i<strlen(cadena); i++){
				if( !(isdigit(cadena[i]))){
					if(cadena[i]=='.' && cont == 0){
						cont++;
					}else{
						cont=0;
						break;
					}
				}
				if (i == (strlen(cadena)-1)){
					flotante = atof(cadena);
					bandera = false;
				}
			}
		}
	}
	return flotante;
}
//---------------------------------------------------------
int validaEntero(){
	char cadena [20]="";
	int entero=0;
	bool bandera = true;
	
	while (bandera){
		scanf("%[^\n]", cadena);
		fflush(stdin);
		if(strlen(cadena)>20){
			continue;
		}else{
			for(int i = 0; i<strlen(cadena); i++){
				if(isdigit(cadena[i])){
					if(i==(strlen(cadena)-1)){
						entero = atoi(cadena);
						bandera=false;
					}
				}else{
					cout<<"Por favor inserta un numero"<<endl;
					break;
				}	
			}	
		}
	}
	return entero;
}
//---------------------------------------------------------
void validaCadena(char nombre[20]){
	bool bandera = true;
	
	while (bandera){
		scanf("%[^\n]", nombre);
		fflush(stdin);
		if(strlen(nombre)>20){
			continue;
		}else{
			for(int i = 0; i<strlen(nombre); i++){
				if(isalpha(nombre[i])){
					if(i==(strlen(nombre)-1)){
						for(int i = 0; i<strlen(nombre);i++){
							nombre[i] = tolower(nombre[i]);
					}
					bandera=false;
					}
			}else{
				break;
				}
			}
		}
	}
}

