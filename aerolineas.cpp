#include <iostream>
#include <conio.h>

using namespace std;

struct pasajeros {
    string nombre;
    int documento;
    int cupo;
    pasajeros *sig;
};
pasajeros *primero,*ultimo,*PasajeroNuevo;

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
avion *raizAvion, *nuevoAvio, *aux1 ;

avion aviones[5] = {

    {"Buenaventura","Barca", 11, 20, 4, 2023, 450, 0,0,10},
    {"Buenaventura","Berlin", 12, 25, 7, 2023, 350, 0,0,5},
    {"Buenaventura","Miami", 2, 30, 8, 2023, 400, 0,0,4},
    {"Buenaventura","Paris", 7, 8, 10, 2023, 300, 0,0,6},
    {"Buenaventura","Milan", 12, 26, 15, 2023, 500, 0,0,25}
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

int main() {

    menu();

    getch();
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
            <<"7. Salir"<<endl<<endl
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
        }

    } while(opcion != 7);

}

void registraAvion() {
    for(int i=0; i<5; i++) {
        nuevoAvio = (struct avion*)malloc(sizeof(struct avion));
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

        cout <<"vuelo: "<< nuevoAvio->ciudadOri<<" - " << nuevoAvio->destino
             << "| fecha: " << nuevoAvio->dia << "/" << nuevoAvio->mes << "/" << nuevoAvio->anio<<endl
             <<"puestos para cupos normales: "<<nuevoAvio->capacidad*0.80<<endl
             <<"puestos para sobreventas: "<<nuevoAvio->capacidad*0.20<<endl
             <<"numero de vuelo: "<<nuevoAvio->Nvuelo<<endl
             <<"---------------------------------------------"<<endl<<endl;

        if(!raizAvion) {
            cout<<"la raiz es "<< nuevoAvio->destino<<endl;
            raizAvion = nuevoAvio;
        }
        else {
            cout<<"poniendo......"<<nuevoAvio->destino<<endl;
            posicioAvion(raizAvion);
            cout<<"se puso......"<<nuevoAvio->destino<<endl;
        }

    }
}

void posicioAvion(avion *aux) {

    if((nuevoAvio->anio < aux->anio) || (nuevoAvio->mes < aux->mes) || (nuevoAvio->dia < aux->dia) ||
    (nuevoAvio->hora < aux->hora)) {
            
        if(aux->izq != NULL) {
            posicioAvion(aux->izq);
            cout<<"poniendo "<<nuevoAvio->destino<<" a la izq de <-"<<aux->destino<<endl;
        }
        else{
            aux->izq = nuevoAvio;
            cout<<"poniendo "<<nuevoAvio->destino<<" a la izq vacia de <-"<<aux->destino<<endl;
        }
    }
    else if((nuevoAvio->anio > aux->anio) || (nuevoAvio->mes > aux->mes) || (nuevoAvio->dia > aux->dia) || 
    (nuevoAvio->hora > aux->hora)) {
    
        
        if(aux->der != NULL) {
            posicioAvion(aux->der);
            cout<<"poniendo "<<nuevoAvio->destino<<" a la derc de ->"<<aux->destino<<endl;
        }
        else{
            aux->der = nuevoAvio;
            cout<<"poniendo "<<nuevoAvio->destino<<" a la der vacia de ->"<<aux->destino<<endl;
        }
    }

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

    PasajeroNuevo = (struct pasajeros *)malloc(sizeof(struct pasajeros));
    cout <<"ingrese su nombre: ";
    cin>>PasajeroNuevo->nombre;
    cout <<"digite su ID: ";
    cin>> PasajeroNuevo->documento;
    cout <<"cupo de sobreventa?(1:si / 2:no): ";
    cin >> PasajeroNuevo->cupo;

    if(PasajeroNuevo->cupo == 1 || PasajeroNuevo->cupo == 2) {
        int numvuelo;
        cout<<"ingrese el numero de vuelo: ";
        cin>>numvuelo;
        cout<<"buscando........ "<<endl;

        aux1 = buscar(raizAvion, numvuelo);

        if (aux1 != NULL) {
            cout<<"........ "<<endl;
            
            if (PasajeroNuevo->cupo == 1) {
                cout<<"cupo sobreventa......"<<endl;
                aux1->sobreVenta++;
            }
            else if(PasajeroNuevo->cupo == 2) {
                cout<<"cupo normal......"<<endl;
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
            cout<<"se monto a el avion" <<endl;
            /*if (primero == NULL) {
                primero = PasajeroNuevo;
                ultimo = primero;
            }
            else {
                ultimo->sig = PasajeroNuevo;
                ultimo = PasajeroNuevo;
            }
            
            */
        }
        else {
            cout << "no se enconto un vuelo con ese numero" << endl;
            free(PasajeroNuevo);
        }
    }
    else {
        cout<<"consiga un cupo"<<endl;
        free(PasajeroNuevo);
    }
}

void mostrarvuelos(avion *vuelo) {

    if(vuelo != NULL){
        mostrarvuelos(vuelo->izq);
        cout<<"vuelo: "<<vuelo->ciudadOri<<" - "<<vuelo->destino<<endl;
        cout<<"fecha: "<<vuelo->dia<<"/"<< vuelo->mes<<"/"<<vuelo->anio<<"- hora de despegue: "<<vuelo->hora<<endl;
        cout<<"numero vuelo: "<<vuelo->Nvuelo<<endl;
        cout<<"pasajeros con cupos normales: "<<vuelo->cupoNormal<<endl;
        cout<<"pasajeros con cupos de sobreventa: "<<vuelo->sobreVenta<<endl;

        if(vuelo->primePasajeros){
            cout<<"pasajeros registrados: "<< endl;
            pasajeros *auxP = vuelo->primePasajeros;
            while (auxP != NULL) {
                cout << "- " << auxP->nombre << endl;
                auxP = auxP->sig;
            }
        }
        else{
            cout<<"no hay pasajeros registrados: "<< endl;
        }
        cout<<"total pajero: "<<vuelo->sobreVenta + vuelo->cupoNormal <<endl;
        cout<<"-------------------------------"<< endl<<endl;
        mostrarvuelos(vuelo->der);
    }

}


void vueloCancel(){
    int busarAvio;
    cout<<"ingrese el numero del vuelo que se cancela: ";
    cin>>busarAvio;

    aux1 = buscar(raizAvion,busarAvio);
    if(aux1 != NULL){
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

    cout<<"cancelando vuelo...."<<endl;

    while (aux3 != NULL && aux3->Nvuelo != cancela) {
        padre = aux3;
        if(cancela < aux3->Nvuelo) {
            aux3 = aux3->izq;
        }
        else if(cancela > aux3->Nvuelo){
            aux3 = aux3->der;
        }
    }

    if(aux3 == NULL) {
        cout << "avion no registrado" << endl;
    }
    else if(aux3 != NULL){
        cout<<"vuelo "<<cancela<<" envontrado" << endl;
    }


    if (aux3->izq == NULL && aux3->der == NULL) {
        cout << "vuelo " << cancela << " es hoja" << endl;
        if (padre != NULL) {
            if (padre->izq == aux3) {
                padre->izq = NULL;
            }
            else if (padre->der == aux3){
                padre->der = NULL;
            }
        }
        else{
            raizAvion = NULL;
        }
        free(aux3);
    }

    else if( ((aux3->der == NULL) && (aux3->izq != NULL)) || ((aux3->der != NULL) && (aux3->izq == NULL)) ) {
        cout << "vuelo " << cancela << " tiene un hijo" << endl;

        avion *hijo;
        if(aux3->izq != NULL){
            hijo = aux3->izq;
        }
        else if(aux3->der != NULL){
            hijo = aux3->der;
        }

        if (padre != NULL) {
            if (padre->izq == aux3) {
                padre->izq = hijo;
            } else {
                padre->der = hijo;
            }
        }
        else{
            raizAvion = hijo;
        }
        free(aux3);
    }

    else if (aux3->izq != NULL && aux3->der != NULL) {
        cout << "vuelo " << cancela << " con dos hijos" << endl;
        
        avion *heredero = aux3->der;
        avion *raizPadre = aux3;

        while (heredero->izq) {
            raizPadre = heredero;
            heredero = heredero->izq;
        }

        aux3->Nvuelo = heredero->Nvuelo;

        if (raizPadre == aux3) {
            raizPadre->der = heredero->der;
        } else {
            raizPadre->izq = heredero->der;
        }

        free(heredero);
    }

}

void cancelarPasaje() {
    int cancelar, ID;

    cout<<"ingrese el numero de su vuelo: ";
    cin>>cancelar;

    avion *auxAv = buscar(raizAvion,cancelar);

    if(auxAv != NULL) {
        cout<<"ingrese el ID del pasajero: ";
        cin>>ID;
        pasajeros *nuevo = auxAv->primePasajeros;
        pasajeros *auxP = NULL;
        int band = 0;
        cout<<"buscando....."<<ID<<endl;
        while((band == 0) && nuevo != NULL) {
            cout<<"buscando pasajero....."<<nuevo->documento<<endl;
            if(nuevo->documento == ID) {
                band = 1;
                cout<<"encontrado....."<<endl;

            }
            else {
                auxP = nuevo;
                nuevo = nuevo->sig;
            }
        }
        if(nuevo != NULL) {
            if(auxP == NULL) {
                auxAv->primePasajeros = nuevo->sig;

            }
            else {
                auxP->sig = nuevo->sig;
            }


            if(nuevo->cupo == 1) {
                cout<<"sobreventa......"<<endl;
                auxAv->sobreVenta--;
            }
            else if(nuevo->cupo == 2) {
                cout<<"normal......"<<endl;
                auxAv->cupoNormal--;
            }

            free(nuevo);
            cout<<"cancelado..."<<endl;
        }
        else {
            cout<<"pasajero no se encontro......"<<endl;
            free(auxAv);

        }
        cout << "......" << endl;

    }
    else {
        cout<<"no se encontra avion"<<endl;
        free(auxAv);
    }
    cout << "......" << endl;

}