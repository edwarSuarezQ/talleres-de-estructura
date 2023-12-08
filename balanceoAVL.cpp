#include<iostream>
#include <conio.h>

using namespace std;


struct AVL {
    int dato, fe;//factor de equilibrio
    AVL *izq, *der;
};


AVL *raiz;


void menu();
AVL *obtenRaiz();
void registrar();
AVL *buscar( AVL *, int );
int factorEqui(AVL *);
AVL *rotaIZQ(AVL *);
AVL *rotaDER(AVL *);
AVL *dobleRotaIzq(AVL *);
AVL *dobleRotaDer(AVL *);
AVL *insertarAVL(AVL *, AVL *);
void mostrar(AVL *, int);
void inorden(AVL *);
void preorden(AVL *);
void posorden(AVL *);
void eliminarNodo();
AVL *eliminarAVL(AVL *, int );
AVL *encontrarMinimo(AVL *);


int main() {

    menu();

    getch();
    return 0;
}


void menu() {

    int opcion=0;

    do {
        system("CLS");
        cout<<"........: Menu :......."<<endl
            <<"1. insertar nodo"<<endl
            <<"2. mostrar arbol"<<endl
             <<"3. eliminar"<<endl
            <<"4. inorden"<<endl
            <<"5. preorden"<<endl
            <<"6. posorden"<<endl
            <<"7. Salir"<<endl<<endl
            <<"opcion: ";
        cin>>opcion;

        switch(opcion) {

        case 1:
            registrar();
            system("PAUSE");
            break;
        case 2:
            mostrar(raiz, 0);
            system("PAUSE");
            break;
         case 3:
            eliminarNodo();
            system("PAUSE");
            break;
        case 4:
            inorden(raiz);
            system("PAUSE");
            break;
        case 5:
            preorden(raiz);
            system("PAUSE");
            break;
        case 6:
            posorden(raiz);
            system("PAUSE");
            break;
        case 7:
            cout<<"Adios..."<<endl;
            break;
        }

    } while(opcion != 7);

}

AVL *obtenRaiz() {
    cout << "obteniendo la raiz del arbol" << endl;
    return raiz;
}

void registrar() {

    AVL *nuevo = (struct AVL *)malloc(sizeof(struct AVL));
    cout<<"ingrese el valor del nodo: ";
    cin>>nuevo->dato;
    if(raiz == NULL) {
        raiz = nuevo;
        cout<<" la raiz es : "<<nuevo->dato<<endl;
    }
    else {
        raiz = insertarAVL(nuevo, raiz);
    }
}



AVL *buscar(AVL *aux, int encon ) {
    if(raiz == NULL) {
        cout << "el arbol esta vacio  no se puede buscar" << endl;
        return NULL;
    }
    else if(aux->dato == encon) {
        cout << "nodo encontrado: " << encon << endl;
        return aux;
    }
    else if(aux->dato < encon) {
        cout << "buscando a la derecha de " << aux->dato << endl;
        return buscar(aux->der,  encon);
    }
    else if(aux->dato > encon) {
        cout << "Buscando a la izquierda de " << aux->dato << endl;
        return buscar(aux->izq,  encon);
    }
}


int factorEqui(AVL *X) {
    if(X == NULL) {
        cout << "el nodo es nulo factor de equilibrio: -1" << endl;
        return -1;
    }
    else {
        cout << "factor de equilibrio del nodo " << X->dato << ": " << X->fe << endl;
        return X->fe;
    }
}


AVL *rotaIZQ(AVL *rota) {
   cout << "Realizando rotación a la izquierda en el nodo " << rota->dato << endl;
   
    AVL *aux = rota->izq;
    rota->izq = aux->der;
    aux->der = rota;
    rota->fe = max(factorEqui(rota->izq),  factorEqui(rota->der)) + 1;
    aux->fe = max(factorEqui(aux->izq),  factorEqui(aux->der)) + 1;
    
    cout << "Rotación a la izquierda finalizada en el nodo " << rota->dato << endl;


    return aux;

}


AVL *rotaDER(AVL *rota) {
	
	cout << "Realizando rotación a la derecha en el nodo " << rota->dato << endl;

    AVL *aux = rota->der;
    rota->der = aux->izq;
    aux->izq = rota;
    rota->fe = max(factorEqui(rota->izq),  factorEqui(rota->der)) + 1;
    aux->fe = max(factorEqui(aux->izq),  factorEqui(aux->der)) + 1;
    
    cout << "Rotación a la derecha finalizada en el nodo " << rota->dato << endl;

    return aux;

}


AVL *dobleRotaIzq(AVL *doble) {
    cout << "Realizando doble rotación a la izquierda en el nodo " << doble->dato << endl;
    AVL *aux;
    doble->izq = rotaDER(doble->izq);
    aux = rotaIZQ(doble);
    return doble;
    
    cout << "Doble rotación a la izquierda finalizada en el nodo " << doble->dato << endl;

}


AVL *dobleRotaDer(AVL *doble) {
    cout << "Realizando doble rotación a la derecha en el nodo " << doble->dato << endl;
    
    AVL *aux;
    doble->der = rotaIZQ(doble->der);
    aux = rotaDER(doble);
    return doble;
    
    cout << "Doble rotación a la derecha finalizada en el nodo " << doble->dato << endl;

}


AVL *insertarAVL(AVL *nuevo, AVL *subAr) {

    AVL *nuevoPadre = subAr;

    if(nuevo->dato < subAr->dato) {

        if(subAr->izq == NULL) {
            subAr->izq = nuevo;
        }
        else {
            subAr->izq = insertarAVL(nuevo, subAr->izq);
            if( ( factorEqui(subAr->izq) ) -  ( factorEqui(subAr->der) ) == 2) {
                if(nuevo->dato < subAr->izq->dato) {
                    nuevoPadre = rotaIZQ(subAr);
                    cout << "haciedo rotacion simple a la izquierda en el nodo " << subAr->dato << endl;
                }
                else {
                    nuevoPadre = dobleRotaIzq(subAr);
                    cout << "haciendo doble rotacion a la izquierda en el nodo " << subAr->dato << endl;
                }
            }
        }
    }
    else if(nuevo->dato > subAr->dato) {
        if(subAr->der == NULL) {
            subAr->der = nuevo;
        }
        else {
            subAr->der = insertarAVL(nuevo, subAr->der);
            if( ( factorEqui(subAr->der) ) -  ( factorEqui(subAr->izq) ) ==2) {
                if(nuevo->dato > subAr->der->dato) {
                    nuevoPadre = rotaDER(subAr);
                    cout << "haciendo rotacion simple a la derecha en el nodo " << subAr->dato << endl;
                }
                else {
                    nuevoPadre = dobleRotaDer(subAr);
                    cout << "haciendo doble rotacion a la derecha en el nodo " << subAr->dato << endl;
                }
            }
        }
    }
    else {
        cout<<endl<<" duplicado"<<endl;
    }
    //actualizar altura

    if( (subAr->izq == NULL) && (subAr->der != NULL)) {
        subAr->fe = subAr->der->fe+1;
    }
    else if( (subAr->der == NULL) && (subAr->izq != NULL)) {
        subAr->fe = subAr->izq->fe+1;
    }
    else {
        subAr->fe = max(factorEqui(subAr->izq),factorEqui(subAr->izq))+1;
    }

    return nuevoPadre;
}


void mostrar(AVL *arbol, int con) {
    if(arbol != NULL) {
        mostrar(arbol->der, con + 1);
        for(int i = 0; i < con * 4; i++) {
            cout << " ";
        }
        cout << arbol->dato << endl;
        mostrar(arbol->izq, con + 1);
    }
}


void inorden(AVL *recore) {
    if(recore != NULL) {
        inorden(recore->izq);
        cout<<recore->dato<<", ";
        inorden(recore->der);
    }
}


void preorden(AVL *recore) {
    if(recore != NULL) {
        cout<<recore->dato<<", ";
        preorden(recore->izq);
        preorden(recore->der);
    }
}


void posorden(AVL *recore) {
    if(recore != NULL) {
        posorden(recore->izq);
        posorden(recore->der);
        cout<<recore->dato<<", ";
    }

}

void eliminarNodo() {
    int valor;
    cout << "digite el dato a eliminar: ";
    cin >> valor;
    
    raiz = eliminarAVL(raiz, valor);
    cout << "dato eliminado exitosamente." << endl;
}

AVL *eliminarAVL(AVL *raiz, int valor) {
    if (raiz == NULL) {
        return raiz;
    }

    if (valor < raiz->dato) {
        raiz->izq = eliminarAVL(raiz->izq, valor);
    } else if (valor > raiz->dato) {
        raiz->der = eliminarAVL(raiz->der, valor);
    } else {
        if (raiz->izq == NULL || raiz->der == NULL) {
            AVL *temp = raiz->izq ? raiz->izq : raiz->der;

            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            AVL *temp = encontrarMinimo(raiz->der);
            raiz->dato = temp->dato;
            raiz->der = eliminarAVL(raiz->der, temp->dato);
        }
    }

    if (raiz == NULL) {
        return raiz;
    }

    raiz->fe = 1 + max(factorEqui(raiz->izq), factorEqui(raiz->der));

    int equilibrio = factorEqui(raiz);

    if (equilibrio > 1 && factorEqui(raiz->izq) >= 0) {
        return rotaDER(raiz);
    }

    if (equilibrio > 1 && factorEqui(raiz->izq) < 0) {
        raiz->izq = rotaIZQ(raiz->izq);
        return rotaDER(raiz);
    }

    if (equilibrio < -1 && factorEqui(raiz->der) <= 0) {
        return rotaIZQ(raiz);
    }

    if (equilibrio < -1 && factorEqui(raiz->der) > 0) {
        raiz->der = rotaDER(raiz->der);
        return rotaIZQ(raiz);
    }

    return raiz;
}

AVL *encontrarMinimo(AVL *raiz) {
    AVL *actual = raiz;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}>izq;
    }
    return actual;
}

