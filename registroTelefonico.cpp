#include <iostream>
#include <conio.h>

using namespace std;

struct celular {

    char nombre[100];
    int numero;
    int llamadas;
    celular *sig;

};

celular *toPila,*nuevo,*topDuplica,*aux;

void menu();
void push();
void mostrarllamadas();
void repetidos();
void popllamada();
void pop();

int main() {

    menu();

    getch();
    return 0;
}

void menu() {

    int opcion = 0;

    do {
         system("CLS");
        cout<<"........: Menu :......."<<endl
            <<"1. Registrar numeros"<<endl
            <<"2. Mostrar registro de llamadas"<<endl
            <<"3. Duplicados"<<endl
            <<"4. Eliminar llamadas"<<endl
            <<"5. Eliminar ultimas llamadas"<<endl
            <<"6. Salir"<<endl<<endl
            <<"opcion: ";
        cin>>opcion;

        switch(opcion) {

        case 1:
            push();
            system("PAUSE");
            break;
        case 2:
            mostrarllamadas();
            system("PAUSE");
            break;
        case 3:
            repetidos();
            system("PAUSE");
            break;
        case 4:
            popllamada();
            system("PAUSE");
            break;
        case 5:
            pop();
            system("PAUSE");
            break;
        default:
            cout << "¡ERROR! opcion no disponible" << endl;
            break;
        }

    } while (opcion!=6);
}

void push() {

    nuevo=((struct celular* ) malloc(sizeof(struct celular)));

    cout << "digite el numero de telefono: ";
    cin>>nuevo->numero;

    while(toPila) {
        if(nuevo->numero == toPila->numero) {
            cout << "El número ya está registrado"<<endl;
            nuevo->sig = topDuplica;
            topDuplica = nuevo;
        }
        toPila = toPila->sig;
    }

    cout << "Ingrese el nombre de contacto: ";
    cin>>nuevo->nombre;

    cout << "Llamadas realizadas: ";
    cin>>nuevo->llamadas;

    if(toPila == NULL) {
        toPila = nuevo;
        toPila->sig = NULL;
    }
    else {
        nuevo->sig = toPila;
        toPila = nuevo;
    }

    nuevo = NULL;
    free(nuevo);

}

void mostrarllamadas() {

    if(!toPila) {
        cout << "no hay contactos" << endl;
    }
    else {

        int busca;
        cout << "Digite el número del celular: " << endl;
        cin>>busca;

        aux = toPila;

        while(aux) {

            if(aux->numero == busca) {
                cout << "el numero de llamadas realizas fue de: " <<aux->llamadas <<endl;
                return;
            }
            aux = aux->sig;
        }
    }

}

void repetidos() {

    if(!topDuplica) {
        cout << "no hay contactos" << endl;
    }
    else {
        for(nuevo=topDuplica; nuevo != NULL; nuevo=nuevo->sig) {
            cout << "numero" <<nuevo->numero<<endl
                 <<"_________________________"<<endl;
        }
    }

}

void popllamada() {

    if(!toPila) {
        cout << "no hay contactos" << endl;
    }
    else {

        int busca;
        cout << "Digite el número del celular: ";
        cin>>busca;

        aux= toPila;

        while(toPila) {
            if(aux->numero == busca) {
                cout << "el numero de llamadas realizas fue de: " <<aux->llamadas <<endl;
                aux->llamadas--;
                cout << "total llamadas actuales es de: "<<aux->llamadas << endl;
                return;
            }
            aux = aux->sig;
        }
    }
}

void pop(){

  if(!toPila){
    cout << "no hay contactos" << endl;
  }
  else{
  
      aux = toPila;
      toPila = toPila->sig;
      free(aux);
      cout << "llamadas eliminadas" << endl;
  
  }
}