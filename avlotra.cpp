#include <iostream>
#include <cstdlib>

using namespace std;

struct AVL {
    int dato, FE; // factor de equilibrio
    AVL *izq, *der;
};

AVL *raiz = NULL;

int FactorEquilibrio(AVL *nodo) {
    if (nodo == NULL) {
        return -1;
    }
    return nodo->FE;
}

AVL *rotarIZQ(AVL *rota) {
    AVL *aux = rota->izq;
    rota->izq = aux->der;
    aux->der = rota;
    rota->FE = 1 + max(FactorEquilibrio(rota->izq), FactorEquilibrio(rota->der));
    aux->FE = 1 + max(FactorEquilibrio(aux->izq), FactorEquilibrio(aux->der));
    return aux;
}

AVL *rotarDER(AVL *rota) {
    AVL *aux = rota->der;
    rota->der = aux->izq;
    aux->izq = rota;
    rota->FE = 1 + max(FactorEquilibrio(rota->izq), FactorEquilibrio(rota->der));
    aux->FE = 1 + max(FactorEquilibrio(aux->izq), FactorEquilibrio(aux->der));
    return aux;
}

AVL *doblerotarIZQ(AVL *doble) {
    doble->izq = rotarDER(doble->izq);
    return rotarIZQ(doble);
}

AVL *dobleRotarDer(AVL *doble) {
    doble->der = rotarIZQ(doble->der);
    return rotarDER(doble);
}

AVL *encontrarMinimo(AVL *nodo) {
    AVL *actual = nodo;
    while (actual->izq != NULL) {
        actual = actual->izq;
    }
    return actual;
}

AVL *insertarAVL(AVL *nuevo, AVL *subAr) {
    AVL *nuevoPadre = subAr;

    if (nuevo->dato < subAr->dato) {
        if (subAr->izq == NULL) {
            subAr->izq = nuevo;
        } else {
            subAr->izq = insertarAVL(nuevo, subAr->izq);
            if ((FactorEquilibrio(subAr->izq) - FactorEquilibrio(subAr->der)) == 2) {
                if (nuevo->dato < subAr->izq->dato) {
                    nuevoPadre = rotarIZQ(subAr);
                } else {
                    nuevoPadre = doblerotarIZQ(subAr);
                }
            }
        }
    } else if (nuevo->dato > subAr->dato) {
        if (subAr->der == NULL) {
            subAr->der = nuevo;
        } else {
            subAr->der = insertarAVL(nuevo, subAr->der);
            if ((FactorEquilibrio(subAr->der) - FactorEquilibrio(subAr->izq)) == 2) {
                if (nuevo->dato > subAr->der->dato) {
                    nuevoPadre = rotarDER(subAr);
                } else {
                    nuevoPadre = dobleRotarDer(subAr);
                }
            }
        }
    } else {
        cout << endl << "Duplicado" << endl;
    }

    if (subAr->izq == NULL && subAr->der != NULL) {
        subAr->FE = subAr->der->FE + 1;
    } else if (subAr->der == NULL && subAr->izq != NULL) {
        subAr->FE = subAr->izq->FE + 1;
    } else {
        subAr->FE = max(FactorEquilibrio(subAr->der), FactorEquilibrio(subAr->izq)) + 1;
    }

    return nuevoPadre;
}

void registrar() {
    AVL *nuevo = (struct AVL *)malloc(sizeof(struct AVL));
    if (nuevo == NULL) {
        cout << "Error: No se pudo asignar memoria para el nuevo nodo" << endl;
        return;
    }

    cout << "Ingrese el valor del nodo: ";
    cin >> nuevo->dato;
    nuevo->izq = nuevo->der = NULL;
    nuevo->FE = 0;

    if (raiz == NULL) {
        raiz = nuevo;
    } else {
        raiz = insertarAVL(nuevo, raiz);
    }
}

AVL *buscar(AVL *aux, int encon) {
    if (aux == NULL) {
        cout << "El árbol está vacío o el nodo no se encuentra" << endl;
        return NULL;
    } else if (aux->dato == encon) {
        cout << "Nodo encontrado: " << encon << endl;
        return aux;
    } else if (aux->dato < encon) {
        return buscar(aux->der, encon);
    } else {
        return buscar(aux->izq, encon);
    }
}

void mostrar(AVL *arbol, int con) {
    if (arbol != NULL) {
        if (arbol->der != NULL) {
            mostrar(arbol->der, con + 1);
        }

        for (int i = 0; i < con * 4; i++) {
            cout << " ";
        }
        cout << arbol->dato << endl;

        if (arbol->izq != NULL) {
            mostrar(arbol->izq, con + 1);
        }
    }
}

void inorden(AVL *recore) {
    if (recore != NULL) {
        if (recore->izq != NULL) {
            inorden(recore->izq);
        }
        cout << recore->dato << " ";
        if (recore->der != NULL) {
            inorden(recore->der);
        }
    }
}

void preorden(AVL *recore) {
    if (recore != NULL) {
        cout << recore->dato << " ";
        if (recore->izq != NULL) {
            preorden(recore->izq);
        }
        if (recore->der != NULL) {
            preorden(recore->der);
        }
    }
}

void posorden(AVL *recore) {
    if (recore != NULL) {
        if (recore->izq != NULL) {
            posorden(recore->izq);
        }
        if (recore->der != NULL) {
            posorden(recore->der);
        }
        cout << recore->dato << " ";
    }
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

    raiz->FE = 1 + max(FactorEquilibrio(raiz->izq), FactorEquilibrio(raiz->der));
    int equilibrio = FactorEquilibrio(raiz->izq) - FactorEquilibrio(raiz->der);

    if (equilibrio > 1 && FactorEquilibrio(raiz->izq) >= 0) {
        return rotarDER(raiz);
    }

    if (equilibrio > 1 && FactorEquilibrio(raiz->izq) < 0) {
        raiz->izq = rotarIZQ(raiz->izq);
        return rotarDER(raiz);
    }

    if (equilibrio < -1 && FactorEquilibrio(raiz->der) <= 0) {
        return rotarIZQ(raiz);
    }

    if (equilibrio < -1 && FactorEquilibrio(raiz->der) > 0) {
        raiz->der = rotarDER(raiz->der);
        return rotarIZQ(raiz);
    }

    return raiz;
}

void eliminar() {
    int valor;
    cout << "Digite el dato a eliminar: ";
    cin >> valor;

    raiz = eliminarAVL(raiz, valor);

    cout << "Dato eliminado exitosamente." << endl;
}

void menu() {
    int opcion = 0;

    do {
        cout << "........: Menu :......." << endl
             << "1. Insertar nodo" << endl
             << "2. Mostrar arbol" << endl
             << "3. Eliminar" << endl
             << "4. Inorden" << endl
             << "5. Preorden" << endl
             << "6. Posorden" << endl
             << "7. Salir" << endl
             << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrar();
            break;
        case 2:
            mostrar(raiz, 0);
            break;
        case 3:
            eliminar();
            break;
        case 4:
            inorden(raiz);
            cout << endl;
            break;
        case 5:
            preorden(raiz);
            cout << endl;
            break;
        case 6:
            posorden(raiz);
            cout << endl;
            break;
        case 7:
            cout << "Adios..." << endl;
            break;
        default:
            cout << "Error: opcion no disponible" << endl;
            break;
        }
    } while (opcion != 7);
}

int main() {
    menu();
    return 0;
}
