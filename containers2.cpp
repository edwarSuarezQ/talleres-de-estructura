#include <iostream>
#include <conio.h>

using namespace std;

struct contenedor {

    int codigo, prioridad;
    contenedor *izq, *der;
};

contenedor *raiz, *nuevo, *aux1;

void menu();
int posicionar(contenedor *);
int insertar();
int recorre(contenedor *);
int mostrarPriorida(contenedor *);
contenedor *busca(contenedor *, int);
int eliminar();
int sinhijos();
int conhijo();
int condoshijos();
int buspadre(contenedor *);

int main() {

    menu();

    getch();
    return 0;
}

void menu() {

    int op=0;

    do {
        system("CLS");
        cout<<"--------Menu----------"<<endl
            <<"1.Regitrar contenedor"<<endl
            <<"2.mostrar contenedo po orden"<<endl
            <<"3.mostrar por  prioridades"<<endl
            <<"4.eliminar contenedor"<<endl
            <<"5.salir"<<endl<<endl
            <<"opcion: ";
        cin>>op;

        switch(op) {
        case 1:
            insertar();
            system("PAUSE");
            break;
        case 2:
            recorre(raiz);
            system("PAUSE");
            break;
        case 3:
            mostrarPriorida(raiz);
            system("PAUSE");
            break;
        case 4:
            eliminar();
            system("PAUSE");
            break;
        case 5:
            cout<<"ADIOS...."<<endl;
            break;
        default:
            cout<<"¡¡ERROR OPCION NO DISPONIBLE!!."<<endl;
            break;
        }
    } while(op != 5);
}

int posicionar(contenedor *tempo) {

    if(nuevo->prioridad == tempo->prioridad) {
        (nuevo->prioridad = tempo->prioridad)-1;

    }
    if(nuevo->prioridad < tempo->prioridad ) {
        if(tempo->izq != NULL) {
            posicionar(tempo->izq);
        }
        else {
            tempo->izq = nuevo;
        }
    }
    if(nuevo->prioridad > tempo->prioridad) {
        if(tempo->der != NULL) {
            posicionar(tempo->der);
        }
        else {
            tempo->der = nuevo;
        }
    }

    return 0;
}

int insertar() {

    nuevo = (struct contenedor * )malloc(sizeof(struct contenedor));
    nuevo->izq = nuevo->der= NULL;
    cout<<"Ingrese el codigo del contenedor: ";
    cin>>nuevo->codigo;
    cout<< "Dentro del rango del 1 al 100 ingrese la prioridad: ";
    cin>>nuevo->prioridad;

    if(!raiz) {
        raiz = nuevo;
        nuevo = NULL;
        free(nuevo);
    }
    else {
        posicionar(raiz);
    }

    nuevo = NULL;
    free(nuevo);

    return 0;
    system("PAUSE");
}

int recorre(contenedor *itera) {

    if(itera == NULL) {
        cout << "No hay contenedores" << endl;
    }
    else if(itera != NULL) {

        cout<<"Codigo del contendor: "<<itera->codigo<<endl;
        cout<<"prioridad: "<<itera->prioridad<<endl;
        cout<<"--------------------------------"<<endl;

        if(itera->izq != NULL) {
            recorre(itera->izq);
        }
        if(itera->der != NULL) {
            recorre(itera->der);
        }

    }
    return 0;
    system("PAUSE");
}

int mostrarPriorida(contenedor *aux2) {

    if(aux2 != NULL) {

        if(aux2->der != NULL) {
            mostrarPriorida(aux2->der);
        }
        cout<<"Codigo del contendor: "<<aux2->codigo<<endl;
        cout<<"prioridad: "<<aux2->prioridad<<endl;
        cout<<"--------------------------------"<<endl;
        if(aux2->izq != NULL) {
            mostrarPriorida(aux2->izq);
        }
    }

    return 0;
    system("PAUSE");
}

contenedor *busca(contenedor *aux2, int encontrado) {
    if(aux2->codigo == encontrado) {
        nuevo = aux2;
        return 0;
    } else {
        if(aux2->izq != NULL) {
            busca(aux2->izq, encontrado);
        }
        if(aux2->der != NULL) {
            busca(aux2->der, encontrado);
        }
    }
    aux2 = NULL;
    return aux2;
}

int buspadre(contenedor *itera) {

    if((itera->izq != NULL) && (itera->izq != nuevo)) {
        buspadre(itera->izq);
    }
    if(itera->izq == nuevo) {
        aux1 = itera;
    }
    if((itera->der != NULL) && (itera->der != nuevo)) {
        buspadre(itera->der);
    }
    if(itera->der == nuevo) {
        aux1 = itera;
    }

    return 0;
}

int sinhijos() {
    if(nuevo != raiz) {
        buspadre(raiz);
    }
    if(aux1->izq == nuevo) {
        aux1->izq = NULL;
    }
    else if(aux1->der == nuevo) {
        aux1->der = NULL;
    }
    free(nuevo);
    return 0;
}

int conhijo() {
    if(nuevo != raiz) {
        buspadre(raiz);
    }
    if(aux1->izq == nuevo) {
        if(nuevo->izq != NULL) {
            aux1->izq = nuevo->izq;
        }
        else if(nuevo->der != NULL) {
            aux1->izq = nuevo->der;
        }
    }
    else if(aux1->der == nuevo) {
        if(nuevo->izq != NULL) {
            aux1->der = nuevo->izq;
        }
        else if(nuevo->der != NULL) {
            aux1->der = nuevo->der;
        }
    }

    free(nuevo);
    return 0;
}

int condoshijos() {

    contenedor *padre = NULL;
    contenedor *sucesor = nuevo->der;

    while (sucesor->izq != NULL) {
        padre = sucesor;
        sucesor = sucesor->izq;
    }

    if (padre != NULL) {
        padre->izq = sucesor->der;
        sucesor->der = nuevo->der;
    }

    sucesor->izq = nuevo->izq;

    if (nuevo != raiz) {
        buspadre(raiz);
        if (aux1->izq == nuevo) {
            aux1->izq = sucesor;
        } else if (aux1->der == nuevo) {
            aux1->der = sucesor;
        }
    } else {
        raiz = sucesor;
    }

    free(nuevo);
    return 0;
}

int eliminar() {

    int buscar = 0;

    cout<<"Ingrese el codigo del contenedor: ";
    cin>>buscar;

    busca(raiz,buscar);
    if(nuevo != NULL) {

        if((nuevo->der == NULL) && (nuevo->izq == NULL) ) {
            sinhijos();
            cout<<endl<<"contenedor eliminado"<<endl;
        }
        else if( ((nuevo->der == NULL) && (nuevo->izq != NULL)) || ((nuevo->der != NULL) && (nuevo->izq == NULL)) ) {
            conhijo();
            cout<<endl<<"contenedor eliminado"<<endl;
        }
        else if(nuevo->izq != NULL && nuevo->der != NULL) {
            cout<<endl<<"contenedor eliminado"<<endl;
            condoshijos();
        }
        if(nuevo == raiz) {
            raiz = NULL;
        }
    }

    return 0;
    system("PAUSE");
}