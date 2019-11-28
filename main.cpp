#include "libreria.h"
int main(){
	int op,opgraf,opgrafarb;
	primero=NULL;
	ultimo=NULL;
	raiz =NULL;
	FILE *arch, *busqueda,*prov;
	char word[33],sign[500],guardar,buscarp;
	portada();
	importar(arch,raiz);
	system("cls");
	do
	{
		fflush(stdin);
		cout<<"Selecciona una opcion:"<<endl<<"1.Agregar Palabra"<<endl<<"2.Eliminar Palabra"<<endl<<"3.Buscar Palabra"<<endl<<"4.Exportar Diccionario"<<endl<<"5.Mostrar Diccionario"<<endl<<"6.Historial de Busqueda"<<endl<<"7.Salir"<<endl;
		fflush(stdin);
		op=validaEntero();
		system("cls");
		switch(op){
			case 1://Agregar
				system("cls");
				cout<<"Palabra a agregar: ";
				fflush(stdin);
				cin>>word;
				cout<<"Significado: ";
				fflush(stdin);
				cin.getline(sign,500);
				formato(word);
				formato(sign);
				insertarAVL(raiz,word,sign);
				cout<<"Presiona cualquier tecla para continuar."<<endl;
				getch();
				system("cls");
				break;
			case 2://Borrar
				system("cls");
				cout<<"Palabra a borrar: ";
				fflush(stdin);
				cin>>word;
				formato(word);
				eliminarNodo(raiz,word);
				cout<<"Presiona cualquier tecla para continuar."<<endl;
				getch();
				system("cls");
				break;
			case 3://Buscar
				do
				{
					system("cls");
					cout<<"Palabra a buscar: ";
					fflush(stdin);
					cin>>word;
					formato(word);
					buscar(raiz,word);
					historial(busqueda,word);
					cout<<"Buscar otra palabra? (s/n)"<<endl;
					fflush(stdin);
					cin>>buscarp;
					system("cls");
				}while(buscarp=='s'||buscarp=='S');
				break;
			case 4://Exportar
				system("cls");
				cout<<"Exportando";
				espera();
				exportar(raiz,arch);
				cout<<"Diccionario Exportado con éxito."<<endl;
				cout<<"Presiona cualquier tecla para continuar."<<endl;
				getch();
				system("cls");
				break;
			case 5://Mostrar datos
				system("cls");
				cout<<"Cómo quieres mostrar los datos?"<<endl<<"1.Tabla"<<endl<<"2.Gráfico"<<endl<<"3.Por arboles"<<endl;
				fflush(stdin);
				opgraf=validaEntero();
				switch(opgraf)
				{
					case 1:
						cout<<"Mostrando datos del diccionario";
						espera();
						inOrden(raiz);
						break;
					case 2:
						cout<<"Mostrando datos del diccionario";
						espera();
						impresionArbol(raiz,0);	
						break;
					case 3:
						primero=NULL;
						ultimo=NULL;
						exportarProv(raiz,prov);
						importarArbolitosArchivo(prov);
						cout<<"Cómo quieres mostrar los arboles?"<<endl<<"1.Tabla"<<endl<<"2.Gráfico"<<endl;
						fflush(stdin);
						opgrafarb=validaEntero();
						switch(opgrafarb){
							case 1:
								cout<<"Mostrando datos de los arboles";
								espera();
								mostrar_lista();
								break;
							case 2:
								cout<<"Mostrando datos de los arboles";
								espera();
								mostrar_lista_grafico();
								break;
								default:
									cout<<"Opcion no valida"<<endl;
									Sleep(800);
						}
						break;
					default:
						cout<<"Opcion no valida"<<endl;
						Sleep(800);
				}		
				cout<<"Presiona cualquier tecla para continuar."<<endl;
				getch();
				system("cls");
				break;
			case 6:
				system("cls");
				mostrar_historial(busqueda);
				cout<<"Presiona cualquier tecla para continuar."<<endl;
				getch();
				system("cls");
				break;
			case 7:
				system("cls");
				cout<<"Guardar cambios en el Diccionario? (s/n)"<<endl;
				fflush(stdin);
				cin>>guardar;
				if(guardar=='s'||guardar=='S'){
					system("cls");
					cout<<"Guardando";
					espera();
					exportar(raiz,arch);
					cout<<"Cambios guardados con éxito."<<endl;
				}
				system("cls");
				cout<<"Saliendo";
				break;
			default:
				system("cls");
				cout<<"Opcion no valida";
				Sleep(1500);
				system("cls");
		}	
	}while(op!=7);	
	return 0;
}
