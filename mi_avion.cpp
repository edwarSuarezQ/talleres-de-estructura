#include <iostream>

using namespace std;

struct pasajero{
    int ID;
    char nombre[100];
    int cupo;
    pasajero *sig;
};

pasajero *nuevo=NULL;

struct avion{
    char ciudadOri[100];
    char destino[100];
    int hora;
    int dia;
    int mes;
    int anio;
    int capacidad;
    int sobreVenta;
    int cupoNormal;
    int Nvuelo;
    pasajero *primero;
    pasajero *ultimo;
    avion *izq;
    avion *der;
    int altura;
};
avion *raiz,*aux,*nuevoAvio;

int obtenerAltura(avion *n){
    if (n == NULL){
        return 0;
    }
    return n->altura;
}

int mayor(int a, int b){
    return (a > b) ? a : b;
}

int obtenerBalance(avion *n){
    if (n == NULL) {
        return 0;
    }
    return obtenerAltura(n->izq) - obtenerAltura(n->der);
}

avion *rotarDerecha(avion *y){
    avion *x = y->izq;
    avion *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;
    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;

    return x;
}

avion *rotarIzquierda(avion *x){
    avion *y = x->der;
    avion *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = mayor(obtenerAltura(x->izq), obtenerAltura(x->der)) + 1;
    y->altura = mayor(obtenerAltura(y->izq), obtenerAltura(y->der)) + 1;

    return y;
}

avion *insertar(avion *nodo, avion *nuevoAvio){
    if(nodo == NULL){
        return nuevoAvio;
    }

    if(nuevoAvio->Nvuelo < nodo->Nvuelo){
        nodo->izq = insertar(nodo->izq,nuevoAvio);
    } else if(nuevoAvio->Nvuelo > nodo->Nvuelo){
        nodo->der = insertar(nodo->der,nuevoAvio);
    } else{
        return nodo;
    }

    nodo->altura = 1 + mayor(obtenerAltura(nodo->izq), obtenerAltura(nodo->der));

    int balance = obtenerBalance(nodo);

    if(balance > 1 && nuevoAvio->Nvuelo < nodo->izq->Nvuelo){
        return rotarDerecha(nodo);
    }

    if(balance < -1 && nuevoAvio->Nvuelo > nodo->der->Nvuelo){
        return rotarIzquierda(nodo);
    }

    if(balance > 1 && nuevoAvio->Nvuelo > nodo->izq->Nvuelo){
        nodo->izq = rotarIzquierda(nodo->izq);
        return rotarDerecha(nodo);
    }

    if(balance < -1 && nuevoAvio->Nvuelo < nodo->der->Nvuelo){
        nodo->der = rotarDerecha(nodo->der);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

int registrarAvion(){
    nuevoAvio = (struct avion*)malloc(sizeof(struct avion));
    
    cout<<"Ingrese el numero del vuelo: ";
    cin>>nuevoAvio->Nvuelo;
    cout<<"Ingrese la ciudad de origon: ";
    cin.ignore();
    cin.getline(nuevoAvio->ciudadOri, 100);
    cout<<"Ingrese la ciudad de destino: ";
    cin.getline(nuevoAvio->destino, 100);
    cout<<"Ingrese la hora de salida(formato militar): ";
    cin>>nuevoAvio->hora;
    cout<<"Ingrese la fecha (DD/MM/AAAA): ";
    cin>>nuevoAvio->dia>>nuevoAvio->mes>>nuevoAvio->anio;
    cout<<"Ingrese la capacida total del avion: ";
    cin>>nuevoAvio->capacidad;
    double normal = (int)(nuevoAvio->capacidad * 0.80);
    cout<<"capacidad total para cupos normales: "<<normal<<endl;
    double sobreV = (int)(nuevoAvio->capacidad - normal);
    cout<<"capacidad total para cupos sobrevuelo: "<<sobreV<<endl;

    nuevoAvio->primero = nuevoAvio->ultimo = NULL;
    nuevoAvio->cupoNormal = nuevoAvio->sobreVenta = 0;
    nuevoAvio->izq = nuevoAvio->der = NULL;

    nuevoAvio->altura = 1;

    raiz = insertar(raiz,nuevoAvio);
    return 0;
}

void asientos(avion *vuelo){
    int capacidad = vuelo->capacidad;
    int filas = 1;
    while(filas * filas < capacidad){
        filas++;
    }
    int columnas = (capacidad + filas - 1) / filas;
    
    string matriz [filas][columnas];

    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            matriz[i][j] = "[]";
        }
    }

    if(vuelo->primero != NULL){
        pasajero *auxP = vuelo->primero;
        int i = 0, j = 0;
        while(auxP != NULL && i < filas){
            matriz[i][j] = "[" + string(auxP->nombre) + "]";
            auxP = auxP->sig;
            j++;
            if(j == columnas){
                j = 0;
                i++;
            }
        }
    }

    cout<<"Matriz de pasajeros:"<<endl;
    for(int i = 0; i < filas; ++i){
        for(int j = 0; j < columnas; ++j){
            if(i * columnas + j < capacidad){
                cout << matriz[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void mostrar(avion *arbol, int con){
    if(arbol==NULL){
        cout << "Error: arbol vacio" << endl;
    }
    else if(arbol != NULL){

        if(arbol->der != NULL){
            mostrar(arbol->der, con + 1);
        }

        for(int i = 0; i < con * 2; i++){
            cout << " ";
        }
        cout << arbol->Nvuelo << endl;

        if(arbol->izq != NULL){
            mostrar(arbol->izq, con + 1);
        }
    }
}

avion *buscar(avion *auxi, int encontrar) {
    if(auxi == NULL){
        cout<<"No hay aviones registrados"<<endl;
        return NULL;
    }
    if(auxi == NULL || auxi->Nvuelo == encontrar){
        return auxi;
    }
    if(encontrar < auxi->Nvuelo){
        return buscar(auxi->izq, encontrar);
    } else if(encontrar > auxi->Nvuelo){
        return buscar(auxi->der, encontrar);
    }
    
    return NULL;
}

int registrarPasa(){
    int buscarA = 0;
    cout<<"Ingrese el numero del vuelo:";
    cin>>buscarA;
    avion *encontrado = buscar(raiz,buscarA);
    if(encontrado == NULL){
        cout<<"No se encontro el vuelo"<<endl;
        return 0;
    }
    if( (encontrado->cupoNormal + encontrado->sobreVenta ) >= encontrado->capacidad ){
        cout<<"avion lleno"<<endl;
        return 0;
    }
    double normal = (int)(encontrado->capacidad * 0.80);
    double sobreV = (int)(encontrado->capacidad - normal);

    nuevo = (struct pasajero*)malloc(sizeof(struct pasajero));
    cout<<"Ingrese su nombre: ";
    cin.ignore();
    cin.getline(nuevo->nombre,100);
    cout<<"Ingrese su ID: ";
    cin>>nuevo->ID;
    do{
        cout<<"Ingrese su tipo de cupo: "<<endl;
        cout<<"1.Normal"<<endl;
        cout<<"2.Sobreventa"<<endl;
        cout<<"cual?: ";
        cin>>nuevo->cupo;
    }while(nuevo->cupo != 2 && nuevo->cupo != 1);
        
    if(nuevo->cupo == 1){
        if(encontrado->cupoNormal >= normal){
            cout<<"No hay cupo normal disponible"<<endl;
            free(nuevo);
            return 0;
        }
        encontrado->cupoNormal++;
    }
    if(nuevo->cupo == 2){
        if(encontrado->sobreVenta >= sobreV){
            cout<<"No hay cupo de sobreventa disponible"<<endl;
            free(nuevo);
            return 0;
        }
        encontrado->sobreVenta++;
    }
    nuevo->sig = NULL;
    if(encontrado->primero == NULL){
        encontrado->primero = nuevo;
    }
    else{
        pasajero *ultimo = encontrado->primero;
        while(ultimo->sig != NULL){
            ultimo = ultimo->sig;
        }
        ultimo->sig = nuevo;
    }

    return 0;
}

void mostrarAvion(){
    int buscarAvion = 0;
    cout<<"Ingrese el numero del vuelo a buscar:";
    cin>>buscarAvion;
    avion *vuelo = buscar(raiz , buscarAvion);
    if(vuelo != NULL){
        cout<<"vuelo: "<<vuelo->ciudadOri<<" "<<vuelo->destino<<endl
        <<"fecha: "<<vuelo->dia<<"/"<< vuelo->mes<<"/"<<vuelo->anio
        <<"- hora de despegue: "<<vuelo->hora<<endl
        <<"numero vuelo: "<<vuelo->Nvuelo<<endl
        <<"pasajeros con cupos normales: "<<vuelo->cupoNormal<<endl
        <<"pasajeros con cupos de sobreventa: "<<vuelo->sobreVenta<<endl;

        if(vuelo->primero != NULL){
            cout<<"pasajeros registrados: "<<endl;
            pasajero *auxP = vuelo->primero;
            while (auxP != NULL){
                cout<< "- " <<auxP->nombre
                <<" - cupo:"<<auxP->cupo<<endl;
                auxP = auxP->sig;
            }
        }
        else{
            cout<<"no hay pasajeros registrados"<<endl;
        }
        cout<<"total pasajeros: "<<vuelo->sobreVenta + vuelo->cupoNormal <<endl;
        cout<<"-------------------------------"<<endl<<endl;

        cout<<"asientos del vuelo"<<endl;
        asientos(vuelo);
    
    }
}

avion *minimo(avion *nodo){
    avion *actual = nodo;
    while(actual->izq != NULL){
        actual = actual->izq;
    }
    return actual;
}

avion *eliminar(avion *raiz, int numeroVuelo){
    if(raiz == NULL){
        cout<<"No se encontro el vuelo a cancelar"<<endl;
        return raiz;
    }

    if(numeroVuelo < raiz->Nvuelo){
        raiz->izq = eliminar(raiz->izq, numeroVuelo);
    }else if(numeroVuelo > raiz->Nvuelo){
        raiz->der = eliminar(raiz->der, numeroVuelo);
    }else{

        if(raiz->izq == NULL){
            avion *temp = raiz->der;
            free(raiz);
            return temp;
        }else if(raiz->der == NULL){
            avion *temp = raiz->izq;
            free(raiz);
            return temp;
        }

        avion *temp = minimo(raiz->der);

        raiz->Nvuelo = temp->Nvuelo;

        raiz->der = eliminar(raiz->der, temp->Nvuelo);
    }

    raiz->altura = 1 + mayor(obtenerAltura(raiz->izq), obtenerAltura(raiz->der));

    int balance = obtenerBalance(raiz);

    if(balance > 1 && obtenerBalance(raiz->izq) >= 0){
        return rotarDerecha(raiz);
    }
    if(balance > 1 && obtenerBalance(raiz->izq) < 0){
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }
    if(balance < -1 && obtenerBalance(raiz->der) <= 0){
        return rotarIzquierda(raiz);
    }
    if(balance < -1 && obtenerBalance(raiz->der) > 0){
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }
    return raiz;
}

int eliminarVuelo(){
    int numeroVuelo;
    cout<<"Ingrese el numero de vuelo que desea cancelar: ";
    cin >> numeroVuelo;
    raiz = eliminar(raiz, numeroVuelo);
    return 0;
}

int BajarPasajero(){
    int cancelar = 0, BuscarID = 0;
    cout<<"Ingrese el numero de su vuelo: ";
    cin >> cancelar;

    avion *auxAv = buscar(raiz, cancelar);

    if(auxAv == NULL){
        cout<<"No se encontro el vuelo"<<endl;
        return 0;
    }

    pasajero *nuevo = auxAv->primero;
    pasajero *auxP = NULL;

    if(nuevo == NULL){
        cout<<"No hay pasajeros en este vuelo"<<endl;
        return 0;
    }

    cout << "Ingrese el ID del pasajero: ";
    cin >> BuscarID;
    cout<<"Buscando pasajero..."<<BuscarID<<endl;

    while(nuevo != NULL){
        cout<<"no es usted pasajero..."<<nuevo->nombre<<endl;
        if(nuevo->ID == BuscarID){
            if(auxP == NULL){
                auxAv->primero = nuevo->sig;
            }
            else{
                auxP->sig = nuevo->sig;
            }
            cout<<"es usted...."<<nuevo->nombre<<endl;
            if(nuevo->cupo == 1){
                cout<<"Cupo normal cancelado..."<<endl;
                auxAv->cupoNormal--;
            }
            else if(nuevo->cupo == 2){
                cout<<"Sobreventa cancelada..."<<endl;
                auxAv->sobreVenta--;
            }
            cout<<"se bajo a el pasajero: "<<nuevo->nombre<<endl;
            free(nuevo);
            return 0;
        }
        auxP = nuevo;
        nuevo = nuevo->sig;
    }
    return 0;
}

void menu(){
    int opcion = 0;

    do{
        cout<<"........!:|:|Menu|:|:!........"<<endl<<endl
        <<"1. registrar aviones"<<endl
        <<"2. buscar vuelos"<<endl
        <<"3. registrar pasajeros"<<endl
        <<"4. eliminar vuelos"<<endl
        <<"5. bajar pasajero"<<endl
        <<"6. ver arbol"<<endl
        <<"7. Salir"<<endl<<endl
        <<"opcion: ";
        cin >> opcion;

        switch (opcion){
            case 1:registrarAvion();break;
            case 2: mostrarAvion();break;
            case 3:registrarPasa();break;
            case 4:eliminarVuelo(); break;
            case 5:BajarPasajero(); break;
            case 6:mostrar(raiz,0);break;
            case 7:cout<<"adios"<<endl;break;
            default:cout<<"ERROR: opcion no valida"<<endl;break;
        }
    }while(opcion != 7);
}

int main(){
    menu();
    return 0;
}