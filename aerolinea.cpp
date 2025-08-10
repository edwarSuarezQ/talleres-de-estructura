#include <iostream>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct pasajeros {
    string nombre;
    int documento;
    int cupo;
    pasajeros *sig;
};
pasajeros *primero, *ultimo, *PasajeroNuevo = NULL;

struct avion {
    string ciudadOri;
    string destino;
    int hora, dia, mes, anio;
    int capacidad;
    int sobreVenta, cupoNormal;
    int Nvuelo;
    pasajeros *primePasajeros, *ultimoPasajero;
    avion *izq, *der;
};
avion *raizAvion = NULL, *nuevoAvio = NULL, *aux1 = NULL;

avion aviones[10] = {
    {"B/tura", "Barcelona", 11, 20, 4, 2023, 450, 0, 0, 10, NULL, NULL, NULL, NULL},
    {"B/tura", "Berlin", 12, 25, 7, 2023, 350, 0, 0, 5, NULL, NULL, NULL, NULL},
    {"B/tura", "Miami", 2, 30, 8, 2023, 400, 0, 0, 4, NULL, NULL, NULL, NULL},
    {"B/tura", "Paris", 7, 8, 10, 2023, 300, 0, 0, 6, NULL, NULL, NULL, NULL},
    {"B/tura", "Milan", 12, 26, 15, 2023, 500, 0, 0, 25, NULL, NULL, NULL, NULL},
    {"B/tura", "Londres", 10, 30, 6, 2023, 380, 0, 0, 15, NULL, NULL, NULL, NULL},
    {"B/tura", "Tokio", 5, 15, 9, 2023, 420, 0, 0, 7, NULL, NULL, NULL, NULL},
    {"B/tura", "New York", 8, 12, 12, 2023, 320, 0, 0, 18, NULL, NULL, NULL, NULL},
    {"B/tura", "Roma", 9, 18, 11, 2023, 280, 0, 0, 22, NULL, NULL, NULL, NULL},
    {"B/tura", "Buenos Aires", 14, 10, 5, 2023, 450, 0, 0, 30, NULL, NULL, NULL, NULL}
};

void posicioAvion(avion *aux) {
    if (nuevoAvio->anio < aux->anio ||
        (nuevoAvio->anio == aux->anio && nuevoAvio->mes < aux->mes) ||
        (nuevoAvio->anio == aux->anio && nuevoAvio->mes == aux->mes && nuevoAvio->dia < aux->dia) ||
        (nuevoAvio->anio == aux->anio && nuevoAvio->mes == aux->mes && nuevoAvio->dia == aux->dia && nuevoAvio->hora < aux->hora)) {

        if (aux->izq != NULL) {
            posicioAvion(aux->izq);
            cout << "poniendo "<<nuevoAvio->destino<< " a la izq de <- "<<aux->destino<<endl;
        } else {
            aux->izq = nuevoAvio;
            cout << "poniendo "<<nuevoAvio->destino<<" a la izq vacia de <- "<<aux->destino<<endl;
        }
    } else if (nuevoAvio->anio > aux->anio ||
               (nuevoAvio->anio == aux->anio && nuevoAvio->mes > aux->mes) ||
               (nuevoAvio->anio == aux->anio && nuevoAvio->mes == aux->mes && nuevoAvio->dia > aux->dia) ||
               (nuevoAvio->anio == aux->anio && nuevoAvio->mes == aux->mes && nuevoAvio->dia == aux->dia && nuevoAvio->hora > aux->hora)) {

        if (aux->der != NULL) {
            posicioAvion(aux->der);
            cout << "poniendo "<<nuevoAvio->destino<< " a la dere de -> "<<aux->destino<<endl;;
        } else {
            aux->der = nuevoAvio;
            cout<<"poniendo "<<nuevoAvio->destino<< " a la dere vacia de -> " <<aux->destino<< endl;;
        }
    }
}

void registraAvion() {
    for (int i = 0; i < 10; i++) {
        nuevoAvio = (struct avion *)malloc(sizeof(struct avion));
        nuevoAvio = &aviones[i];

        if (!raizAvion) {
            cout << "la raiz es "<<nuevoAvio->destino<<endl;
            raizAvion = nuevoAvio;
        } else {
            cout << "poniendo....."<<nuevoAvio->destino<<endl;
            posicioAvion(raizAvion);
            cout << "se puso......"<<nuevoAvio->destino<<endl;
        }
    }
    cout<<"registro completo"<<endl;
    
}

avion *buscar(avion *auxi, int encontrar) {
    if (auxi == NULL || auxi->Nvuelo == encontrar) {
        return auxi;
    }
    if (encontrar < auxi->Nvuelo) {
        return buscar(auxi->izq, encontrar);
    } else if (encontrar > auxi->Nvuelo) {
        return buscar(auxi->der, encontrar);
    }
    return NULL;
}

void registrarVuelo() {
    
    PasajeroNuevo = (struct pasajeros *)malloc(sizeof(struct pasajeros));
    
    cout << "ingrese su nombre: ";
     cin.ignore();
    getline(cin, PasajeroNuevo->nombre);
    //cin >> PasajeroNuevo->nombre;
    cout << "digite su ID: ";
    cin >> PasajeroNuevo->documento;
    cout << "cupo de sobreventa?(1:si / 2:no): ";
    cin >> PasajeroNuevo->cupo;

    if (PasajeroNuevo->cupo == 1 || PasajeroNuevo->cupo == 2) {
        int numvuelo;
        cout << "ingrese el numero de vuelo: ";
        cin >> numvuelo;
        cout << "buscando........ " << endl;

        aux1 = buscar(raizAvion, numvuelo);

        if (aux1 != NULL) {
            cout << "........ " << endl;

            if (PasajeroNuevo->cupo == 1) {
                cout << "cupo sobreventa......" << endl;
                aux1->sobreVenta++;
            } else if (PasajeroNuevo->cupo == 2) {
                cout << "cupo normal......" << endl;
                aux1->cupoNormal++;
            }

            PasajeroNuevo->sig = NULL;

            if (aux1->primePasajeros == NULL) {
                aux1->primePasajeros = PasajeroNuevo;
                aux1->ultimoPasajero = PasajeroNuevo;
            } else {
                aux1->ultimoPasajero->sig = PasajeroNuevo;
                aux1->ultimoPasajero = PasajeroNuevo;
            }
            cout << "se monto a el avion" << endl;
        } else {
            cout << "no se enconto un vuelo con ese numero" << endl;
            free(PasajeroNuevo);
        }
    } else {
        cout << "consiga un cupo" << endl;
        free(PasajeroNuevo);
    }
}

void mostrarvuelos(avion *vuelo) {
    if (vuelo != NULL) {
        mostrarvuelos(vuelo->izq);
        cout << "vuelo: " << vuelo->ciudadOri << " - " << vuelo->destino;
        cout << " fecha: " << vuelo->dia << "/" << vuelo->mes << "/" << vuelo->anio << " - hora de despegue: " << vuelo->hora << endl;
        cout << "numero vuelo: " << vuelo->Nvuelo << endl;
        cout << "pasajeros con cupos normales: " << vuelo->cupoNormal << endl;
        cout << "pasajeros con cupos de sobreventa: " << vuelo->sobreVenta << endl;

        if (vuelo->primePasajeros) {
            cout << "pasajeros registrados: " << endl;
            pasajeros *auxP = vuelo->primePasajeros;
            while (auxP != NULL) {
                cout << "- " << auxP->nombre << endl;
                auxP = auxP->sig;
            }
        } else {
            cout << "no hay pasajeros registrados: " << endl;
        }
        cout << "total pasajeros: " << vuelo->sobreVenta + vuelo->cupoNormal << endl;
        cout << "-------------------------------" << endl << endl;
        mostrarvuelos(vuelo->der);
    }
}

avion* buscarPadre(avion* raiz, avion* nodo) {
    if (raiz == NULL || raiz == nodo) {
        return NULL;
    }
    if ((raiz->izq != NULL && raiz->izq == nodo) || (raiz->der != NULL && raiz->der == nodo)) {
        return raiz;
    }
    avion* izq = buscarPadre(raiz->izq, nodo);
    if (izq != NULL) {
        return izq;
    }
    return buscarPadre(raiz->der, nodo);
}

// Función cuando el nodo no tiene hijos
int sinHijo() {
    avion* nodo = nuevoAvio;
    avion* padre = buscarPadre(raizAvion, nodo);
    if (padre) {
        if (padre->izq == nodo) {
            padre->izq = NULL;
        } else {
            padre->der = NULL;
        }
    } else {
        raizAvion = NULL;
    }
    free(nodo);
    return 0;
}

// Función cuando el nodo tiene un hijo
int conHijo() {
    avion* nodo = nuevoAvio;
    avion* padre = buscarPadre(raizAvion, nodo);
    avion* hijo = (nodo->izq != NULL) ? nodo->izq : nodo->der;
    if (padre) {
        if (padre->izq == nodo) {
            padre->izq = hijo;
        } else {
            padre->der = hijo;
        }
    } else {
        raizAvion = hijo;
    }
    free(nodo);
    return 0;
}

// Función cuando el nodo tiene dos hijos
int conDosHijos() {
    avion* nodo = nuevoAvio;
    avion* sucesor = nodo->der;
    avion* padre = nodo;
    while (sucesor->izq != NULL) {
        padre = sucesor;
        sucesor = sucesor->izq;
    }
    nodo->Nvuelo = sucesor->Nvuelo;
    if (padre != nodo) {
        padre->izq = sucesor->der;
    } else {
        padre->der = sucesor->der;
    }
    free(sucesor);
    return 0;
}

// Función para eliminar un nodo
int eliminar(int buscarA) {

    if (nuevoAvio != NULL) {
        if (nuevoAvio->izq == NULL && nuevoAvio->der == NULL) {
            sinHijo();
            cout << "Avion eliminado" << endl;
        } else if (nuevoAvio->izq == NULL || nuevoAvio->der == NULL) {
            conHijo();
            cout << "Avion eliminado" << endl;
        } else {
            conDosHijos();
            cout << "Avion eliminado" << endl;
        }
        if (nuevoAvio == raizAvion) {
            raizAvion = NULL;
        }
    }

    return 0;
}


void vueloCancel() {
    int busarAvio;
    cout << "ingrese el numero del vuelo que se cancela: ";
    cin >> busarAvio;

    aux1 = buscar(raizAvion, busarAvio);
    if (aux1 != NULL) {
        cout << "se encontro.." << endl;
        eliminar(busarAvio);
    } else {
        cout << "no se encontro" << endl;
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


void menu() {
    int opcion = 0;

    do {
        cout << "........!:|:|Menu|:|:!........" << endl << endl
            << "1. registrar aviones" << endl
            << "2. ver vuelos disponibles" << endl
            << "3. registrar pasajeros" << endl
            << "4. ver pasajeros registrados" << endl
            << "5. el de cancela" << endl
            << "6. cancelar vuelo" << endl
            << "7. Salir" << endl << endl
            << "opcion: ";
        cin >> opcion;

        switch (opcion) {
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
        }

    } while (opcion != 7);
}

void liberarMemoria(avion* nodo) {
    if (nodo != NULL) {
        liberarMemoria(nodo->izq);
        liberarMemoria(nodo->der);

        // Libera la lista de pasajeros asociada a este avión
        pasajeros* auxP = nodo->primePasajeros;
        while (auxP != NULL) {
            pasajeros* temp = auxP;
            auxP = auxP->sig;
            free(temp);
        }

        // Libera la estructura del avión
        free(nodo);
    }

    cout << "memoria liberada" << endl;
}

int main() {
    menu();
    return 0;
}

/*
int sinHijo() {
    avion* nodo = nuevoAvio;
    avion* padre = buscarPadre(raizAvion, nodo);
    if (padre) {
        if (padre->izq == nodo) {
            padre->izq = NULL;
        } else {
            padre->der = NULL;
        }
    } else {
        raizAvion = NULL;
    }
    free(nodo);
    return 0;
}

int conHijo() {
    avion* nodo = nuevoAvio;
    avion* padre = buscarPadre(raizAvion, nodo);
    avion* hijo = NULL;
    if (nodo->izq != NULL) {
        hijo = nodo->izq;
    } else {
        hijo = nodo->der;
    }
    if (padre) {
        if (padre->izq == nodo) {
            padre->izq = hijo;
        } else {
            padre->der = hijo;
        }
    } else {
        raizAvion = hijo;
    }
    free(nodo);
    return 0;
}

int conDosHijos() {
    avion* nodo = nuevoAvio;
    avion* padre = buscarPadre(raizAvion, nodo);
    avion* sucesor = nodo->der;
    while (sucesor->izq) {
        padre = sucesor;
        sucesor = sucesor->izq;
    }
    nodo->Nvuelo = sucesor->Nvuelo;
    if (padre == nodo) {
        padre->der = sucesor->der;
    } else {
        padre->izq = sucesor->der;
    }
    free(sucesor);
    return 0;
}

*/