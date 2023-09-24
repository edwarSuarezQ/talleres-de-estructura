//Jhon Edwar Suarez Quiñonez
//Cristian David Garcia Valderrama

#include <iostream>
#include <conio.h>

using namespace std;

struct clientes{

    char Nombre[100];
    float Cupo_Credito;
    float Cupo_usado;
    clientes *sigienteCli;

};

clientes *primero,*ultimo,*auxil;
float credito=0.0;

void menu();
void RegistrarClientes();
void MostrarCli();
void CreditoUsado();
void Disponible();
void OrdenAsendente();

int main(){

    menu();

    getch();
    return 0;
}

void menu(){

    int opcion=0;

    do{
        cout<<"\n----------Menu----------"<<endl
        <<"1.Registrar Cliente"<<endl
        <<"2.Mostrar Clientes Registrados"<<endl
        <<"3.Clientes con cupo Usado superior al 80%"<<endl
        <<"4.Clientes con cupo disponible al 20%"<<endl
        <<"5.lista de clientes en orden asendente"<<endl
        <<"6.Salir"<<endl<<endl
        <<"opcion: ";
        cin>>opcion;

        switch(opcion){

            case 1:
                RegistrarClientes();
            break;

            case 2:
                MostrarCli();
            break;

            case 3:
                CreditoUsado();
            break;

            case 4:
                Disponible();
            break;

            case 5:
                OrdenAsendente();
            break;

            case 6:
               cout<<"...Adios...";
               system("cls");
            break;

            default: cout<<"!ERROR¡Opcion no disponible";
            break;
            
        }

    }while(opcion != 6);

}

void RegistrarClientes(){

    ultimo = (struct clientes *) malloc(sizeof(struct clientes));
    ultimo->sigienteCli = NULL;
    cout<<"Ingrese los datos del cliente:"<<endl;
    cout<<"Nombre: ";
    cin>> ultimo->Nombre;
    cout<<"Cupo de credito: ";
    cin>> ultimo->Cupo_Credito;
    cout<<"Cupo usado: ";
    cin>> ultimo->Cupo_usado;

    if(!primero){

        primero = ultimo;
        ultimo = NULL;
        free(ultimo);
    }
    else{

        auxil = primero;
        while(auxil->sigienteCli != NULL){
            auxil = auxil->sigienteCli;
        }
        auxil->sigienteCli = ultimo;
        auxil = ultimo = NULL;
        free(ultimo);
        free(auxil);
    }
}

void MostrarCli(){
    int posicion=1;

    if(primero == NULL){
        cout<<"No hay clientes registrados"<<endl;
    }
    else{
        for(ultimo = primero; ultimo != NULL;ultimo=ultimo->sigienteCli){
        cout<<"------------------------------"<<endl
        <<"Datos del cliente N"<<posicion++<<endl
        <<"Nombre: "<<ultimo->Nombre<<endl
        <<"Cupo de crdito: "<<ultimo->Cupo_Credito<<endl
        <<"Cupo usado: "<<ultimo->Cupo_usado<<endl
        <<"------------------------------"<<endl;
        }
    }
}

void CreditoUsado(){
    int posicion=1;
    bool band=false;
    if(primero == NULL){
        cout<<"No hay clientes registrados"<<endl;
    }else{
        for(ultimo = primero; ultimo != NULL;ultimo=ultimo->sigienteCli){
        credito=(ultimo->Cupo_usado / ultimo->Cupo_Credito);
        if(credito > 0.8){
            cout<<"------------------------------"<<endl;
            cout<<"Datos de cliente N"<<posicion++<<endl;
            cout<<"El cliente: "<<ultimo->Nombre<<" Tiene un credito mayor al 80%: "<<endl;
            cout<<"Con un total de: "<<credito<<endl;
            cout<<"------------------------------"<<endl;
            band=true;
            }
        }

    }
    if(!band){
        cout<<"No hay clientes que exedan el 80% del crito";
    }
    
}

void Disponible(){
    bool band=false;
    if(primero == NULL){
        cout<<"No hay clientes registrados"<<endl;
    }else{
        for(ultimo = primero; ultimo != NULL;ultimo=ultimo->sigienteCli){
        if((ultimo->Cupo_usado / ultimo->Cupo_Credito) < 0.2){
            cout<<"------------------------------"<<endl;
            cout<<"El cliente: "<<ultimo->Nombre<<" Tiene un credito diponible del 20%: "<<endl;
            cout<<"con un total de: "<<credito<<endl;
            cout<<"------------------------------"<<endl;
            band=true;
            }
        }
    }
    if(!band){
        cout<<"No hay clientes con credito menor a el 20% ";
    }
}

void OrdenAsendente(){
    cout<<"funcion no disponible por el momemto, por favor elija otar opcion."<<endl;
    /*int posicion=1;
    if(primero == NULL){
        cout<<"No hay clientes registrados"<<endl;
    }else{
        for(ultimo = primero; ultimo != NULL;ultimo=ultimo->sigienteCli){
            if(primero->Cupo_Credito > primero->sigienteCli->Cupo_Credito){
                cout<<"------------------------------"<<endl
                <<"Datos del cliente N"<<posicion++<<endl
                <<"Nombre: "<<primero->sigienteCli->Nombre<<endl
                <<"Cupo de crdito: "<<primero->sigienteCli->Cupo_Credito<<endl
                <<"Cupo usado: "<<primero->sigienteCli->Cupo_usado<<endl
                <<"------------------------------"<<endl;

            }
        }
    }
    */
}