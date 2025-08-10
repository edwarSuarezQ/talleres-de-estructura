#include <iostream>
#include <conio.h>

using namespace std;

struct pasajeros {
    string nombre;
    int documento;
    int cupo;
    pasajeros *sig;
};

pasajeros *primero,*ultimo,*PasajeroNuevo=NULL;

struct avion {
    string ciudadOri;
    string destino;
    int hora,dia,mes,anio;
    int capacidad;
    int sobreVenta,cupoNormal;
    int Nvuelo;
    pasajeros *primePasajeros,*ultimoPasajero;
    avion *izq,*der;
};

avion *raizAvion=NULL, *nuevoAvio=NULL, *aux1=NULL ;

avion aviones[10] = {
    {"Buenaventura", "Barca", 11, 20, 4, 2023, 450, 0, 0, 10, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Berlin", 12, 25, 7, 2023, 350, 0, 0, 5, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Miami", 2, 30, 8, 2023, 400, 0, 0, 4, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Paris", 7, 8, 10, 2023, 300, 0, 0, 6, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Milan", 12, 26, 15, 2023, 500, 0, 0, 25, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Londres", 10, 30, 6, 2023, 380, 0, 0, 15, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Tokio", 5, 15, 9, 2023, 420, 0, 0, 7, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Nueva York", 8, 12, 12, 2023, 320, 0, 0, 18, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Roma", 9, 18, 11, 2023, 280, 0, 0, 22, NULL, NULL, NULL, NULL},
    {"Buenaventura", "Sidney", 14, 10, 5, 2023, 450, 0, 0, 30, NULL, NULL, NULL, NULL}
};

void menu();
void registraAvion();
void posicioAvion(avion *);
void mostrarvuelos(avion *);
void registrarVuelo();
avion *buscar(avion *, int);
void cancelarPasaje();
void vueloCancel();
void eliminar(int);
void liberarTodaLaMemoria(avion*);
void mostrar(avion *, int);

int main() {
    menu();
    return 0;
}

void menu() {
    int opcion=0;

    do {
        cout<<"........!:|:|Menu|:|:!........"<<endl<<endl
            <<"1. registrar aviones"<<endl
            <<"2. ver vuelos disponibles"<<endl
            <<"3. registrar pasajeros"<<endl
            <<"4. ver pasajeros registrados"<<endl
            <<"5. el de cancela"<<endl
            <<"6. cancelar vuelo"<<endl
            <<"7. ver arbol"<<endl
            <<"8. Salir"<<endl<<endl
            <<"opcion: ";
        cin>>opcion;

        switch(opcion) {
        case 1:
            registraAvion();
            break;
        case 2:
            mostrarvuelos(raizAvion);
            break;
        case 3:
            registrarVuelo();
            break;
        case 4:
            break;
        case 5:
            vueloCancel();
            break;
        case 6:
            cancelarPasaje();
            break;
        case 7:
            mostrar(raizAvion,0);
            break;
        }

    } while(opcion != 8);
}

void posicioAvion(avion *aux, avion *nuevo) {
    if (nuevo->anio < aux->anio ||
        (nuevo->anio == aux->anio && nuevo->mes < aux->mes) ||
        (nuevo->anio == aux->anio && nuevo->mes == aux->mes && nuevo->dia < aux->dia) ||
        (nuevo->anio == aux->anio && nuevo->mes == aux->mes && nuevo->dia == aux->dia && nuevo->hora < aux->hora)) {

        if (aux->izq != NULL) {
            posicioAvion(aux->izq, nuevo);
        } else {
            aux->izq = nuevo;
            cout<<"poniendo "<<nuevo->destino<< " a la izq vacia de <- " <<aux->destino<<endl;
        }
    } else if (nuevo->anio > aux->anio ||
        (nuevo->anio == aux->anio && nuevo->mes > aux->mes) ||
        (nuevo->anio == aux->anio && nuevo->mes == aux->mes && nuevo->dia > aux->dia) ||
        (nuevo->anio == aux->anio && nuevo->mes == aux->mes && nuevo->dia == aux->dia && nuevo->hora > aux->hora)) {

        if (aux->der != NULL) {
            posicioAvion(aux->der, nuevo);
        } else {
            aux->der = nuevo;
            cout<<"poniendo "<<nuevo->destino<< " a la dere vacia de -> " <<aux->destino<<endl;
        }
    }
}

void registraAvion() {
    
    int numAviones = sizeof(aviones) / sizeof(aviones[0]); // Obtener el tamaño del arreglo

    for (int i = 0; i < numAviones; i++) {
        //nuevoAvio = (struct avion*)malloc(sizeof(struct avion));
        nuevoAvio = new avion();
        nuevoAvio->ciudadOri = aviones[i].ciudadOri;
        nuevoAvio->destino = aviones[i].destino;
        nuevoAvio->hora = aviones[i].hora;
        nuevoAvio->dia = aviones[i].dia;
        nuevoAvio->mes = aviones[i].mes;
        nuevoAvio->anio = aviones[i].anio;
        nuevoAvio->capacidad = aviones[i].capacidad;
        nuevoAvio->sobreVenta = aviones[i].sobreVenta;
        nuevoAvio->cupoNormal = aviones[i].cupoNormal;
        nuevoAvio->Nvuelo = aviones[i].Nvuelo;
        nuevoAvio->primePasajeros = NULL;
        nuevoAvio->ultimoPasajero = NULL;
        nuevoAvio->der = NULL;
        nuevoAvio->izq = NULL;
        
        if(!raizAvion) {
            cout<<"la raiz es "<<nuevoAvio->destino<<endl;
            raizAvion = nuevoAvio;

        } else {
            cout<<"poniendo....."<<nuevoAvio->destino<<endl;
            posicioAvion(raizAvion, nuevoAvio);
            cout<<"se puso......"<<nuevoAvio->destino;
        }
    }

    cout << "registro completo" << endl;
}

avion *buscar(avion *auxi, int encontrar) {
    if(auxi == NULL || auxi->Nvuelo == encontrar) {
        return auxi;
    }
    if(encontrar < auxi->Nvuelo) {
        return buscar(auxi->izq,encontrar);
    }
    else if(encontrar > auxi->Nvuelo) {
        return buscar(auxi->der,encontrar);
    }
    return NULL;
}

void registrarVuelo() {
    //PasajeroNuevo = (struct pasajeros *)malloc(sizeof(struct pasajeros));
    PasajeroNuevo = new pasajeros();
    cout << "Ingrese su nombre: ";
    cin >> PasajeroNuevo->nombre;
    cout << "Ingrese su ID: ";
    cin >> PasajeroNuevo->documento;
    cin.ignore();
    do {
        cout << "Desea registrar con cupo normal o sobreventa?" << endl;
        cout << "1. Cupo normal" << endl;
        cout << "2. Sobreventa" << endl;
        cout << "Opcion: ";
        cin >> PasajeroNuevo->cupo;

        if (PasajeroNuevo->cupo != 1 && PasajeroNuevo->cupo != 2) {
            cout << "Opcion invalida. Por favor, ingrese 1 para cupo normal o 2 para sobreventa." << endl;
        }
    } while (PasajeroNuevo->cupo != 1 && PasajeroNuevo->cupo != 2);

    int numvuelo;
    do {
        cout << "Ingrese el numero de vuelo: ";
        cin >> numvuelo;
        cout << "Buscando... " << endl;

        aux1 = buscar(raizAvion, numvuelo);

        if (aux1 == NULL) {
            cout << "No se encontro un vuelo con ese numero. Por favor, ingrese un numero de vuelo valido." << endl;
        }
    } while (aux1 == NULL);

    cout << "Vuelo encontrado..." << endl;

    cout << "Registrando pasajero..." << endl;

    if (PasajeroNuevo->cupo == 1) {
        if (aux1->cupoNormal * 100 / aux1->capacidad >= 80) {
            cout << "El limite de cupos normales ha sido alcanzado. No se pueden registrar mas pasajeros con cupo normal." << endl;
            free(PasajeroNuevo);
            return; // Salir de la función en caso de que se alcance el límite de cupos normales
        }
        aux1->cupoNormal++;
    } else if (PasajeroNuevo->cupo == 2) {
        if (aux1->sobreVenta * 100 / aux1->capacidad >= 20) {
            cout << "El limite de cupos de sobreventa ha sido alcanzado. No se pueden registrar mas pasajeros con sobreventa." << endl;
            free(PasajeroNuevo);
            return; // Salir de la función en caso de que se alcance el límite de cupos de sobreventa
        }
        aux1->sobreVenta++;
    }

    PasajeroNuevo->sig = NULL;

    if (aux1->primePasajeros == NULL) {
        aux1->primePasajeros = PasajeroNuevo;
        aux1->ultimoPasajero = PasajeroNuevo;
    } else {
        aux1->ultimoPasajero->sig = PasajeroNuevo;
        aux1->ultimoPasajero = PasajeroNuevo;
    }

    cout << "Se ha registrado en el avion" << endl;
}


void mostrarvuelos(avion *vuelo) {
    if(vuelo != NULL) {
        mostrarvuelos(vuelo->izq);
        cout<<"vuelo: "<<vuelo->ciudadOri<<" - "<<vuelo->destino<<endl;
        cout<<"fecha: "<<vuelo->dia<<"/"<< vuelo->mes<<"/"<<vuelo->anio<<"- hora de despegue: "<<vuelo->hora<<endl;
        cout<<"numero vuelo: "<<vuelo->Nvuelo<<endl;
        cout<<"pasajeros con cupos normales: "<<vuelo->cupoNormal<<endl;
        cout<<"pasajeros con cupos de sobreventa: "<<vuelo->sobreVenta<<endl;

        if(vuelo->primePasajeros) {
            cout<<"pasajeros registrados: "<< endl;
            pasajeros *auxP = vuelo->primePasajeros;
            while (auxP != NULL) {
                cout << "- " << auxP->nombre << endl;
                auxP = auxP->sig;
            }
        }
        else {
            cout<<"no hay pasajeros registrados: "<< endl;
        }
        cout<<"total pasajeros: "<<vuelo->sobreVenta + vuelo->cupoNormal <<endl;
        cout<<"-------------------------------"<< endl<<endl;
        mostrarvuelos(vuelo->der);
    }
}

void mostrar(avion *arbol, int con) {
    if(arbol==NULL) {
        cout << "Error: arbol vacio" << endl;
    }
    else if(arbol != NULL) {

        if(arbol->der != NULL) {
            mostrar(arbol->der, con + 1);
        }

        for(int i = 0; i < con * 4; i++) {
            cout << " ";
        }
        cout << arbol->Nvuelo << endl;

        if(arbol->izq != NULL) {
            mostrar(arbol->izq, con + 1);
        }
    }

}

void vueloCancel() {
    int busarAvio;
    cout<<"ingrese el numero del vuelo que se cancela: ";
    cin>>busarAvio;

    aux1 = buscar(raizAvion,busarAvio);
    if(aux1 != NULL) {
        cout<<"se encontro.."<< endl;
        eliminar(busarAvio);
    }
    else {
        cout<<"no se encontro"<< endl;
    }
}

void eliminar(int cancela) {
    avion *aux3 = raizAvion;
    avion *padre = NULL;

    cout << "cancelando vuelo...." << endl;

    while (aux3 != NULL && aux3->Nvuelo != cancela) {
        padre = aux3;
        if (cancela < aux3->Nvuelo) {
            aux3 = aux3->izq;
        } else if (cancela > aux3->Nvuelo) {
            aux3 = aux3->der;
        }
    }

    if (aux3 == NULL) {
        cout << "avion no registrado" << endl;
    } else if (aux3 != NULL) {
        cout << "vuelo " << cancela << " encontrado" << endl;
    }

    if (aux3->primePasajeros != NULL) {
        // Liberar pasajeros
        while (aux3->primePasajeros != NULL) {
            pasajeros *temp = aux3->primePasajeros;
            aux3->primePasajeros = aux3->primePasajeros->sig;
            free(temp);
        }

        // Mensaje solo si había pasajeros
        cout << "Pasajeros bajados exitosamente." << endl;
    } else {
        // Mensaje en caso de que no haya pasajeros
        cout << "No hay pasajeros para bajar." << endl;
    }

    if (aux3->izq == NULL && aux3->der == NULL) {
        cout << "vuelo " << cancela << " es hoja" << endl;
        if (padre != NULL) {
            if (padre->izq == aux3) {
                padre->izq = NULL;
            } else if (padre->der == aux3) {
                padre->der = NULL;
            }
        } else {
            raizAvion = NULL;
        }
        free(aux3);
    } else if (((aux3->der == NULL) && (aux3->izq != NULL)) || ((aux3->der != NULL) && (aux3->izq == NULL))) {
        cout << "vuelo " << cancela << " tiene un hijo" << endl;

        avion *hijo;
        if (aux3->izq != NULL) {
            hijo = aux3->izq;
        } else if (aux3->der != NULL) {
            hijo = aux3->der;
        }

        if (padre != NULL) {
            if (padre->izq == aux3) {
                padre->izq = hijo;
            } else {
                padre->der = hijo;
            }
        } else {
            raizAvion = hijo;
        }
        free(aux3);
    } else if (aux3->izq != NULL && aux3->der != NULL) {
        cout << "vuelo " << cancela << " con dos hijos" << endl;

        avion *heredero = aux3->der;
        avion *raizPadre = aux3;
        avion *raizHijoAnterior = NULL;

        while (heredero->izq) {
            raizHijoAnterior = heredero;
            raizPadre = heredero;
            heredero = heredero->izq;
        }

        aux3->Nvuelo = heredero->Nvuelo;

        if (raizPadre == aux3) {
            raizPadre->der = heredero->der;
        } else {
            raizHijoAnterior->izq = heredero->der;
        }

        free(heredero);
    }
}

void cancelarPasaje() {
    int cancelar, ID;

    cout << "Ingrese el número de su vuelo: ";
    cin >> cancelar;

    avion *auxAv = buscar(raizAvion, cancelar);

    if (auxAv != NULL) {
        cout << "Ingrese el ID del pasajero: ";
        cin >> ID;
        pasajeros *nuevo = auxAv->primePasajeros;
        pasajeros *auxP = NULL;
        int band = 0;

        cout << "Buscando pasajero..." << ID << endl;

        while ((band == 0) && nuevo != NULL) {
            cout << "Buscando pasajero..." << nuevo->documento << endl;
            if (nuevo->documento == ID) {
                band = 1;
                cout << "Encontrado..." << endl;
            } else {
                auxP = nuevo;
                nuevo = nuevo->sig;
            }
        }

        if (nuevo != NULL) {
            if (auxP == NULL) {
                auxAv->primePasajeros = nuevo->sig;
            } else {
                auxP->sig = nuevo->sig;
            }

            if (nuevo->cupo == 1) {
                cout << "Sobreventa cancelada..." << endl;
                auxAv->sobreVenta--;
            } else if (nuevo->cupo == 2) {
                cout << "Cupo normal cancelado..." << endl;
                auxAv->cupoNormal--;
            }

            free(nuevo);
            cout << "Pasajero cancelado..." << endl;
        } else {
            cout << "Pasajero no encontrado..." << endl;
            free(auxAv);
        }

        cout << "..." << endl;
    } else {
        cout << "No se encuentra el avión..." << endl;
        free(auxAv);
    }

    cout << "..." << endl;
}