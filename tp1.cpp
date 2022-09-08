#include <iostream>
#include <fstream>
using namespace std;

int mayor_vec(int vec[], int tam){                  // funcion para buscar la posicion del valor maximo de un vector

    int mayor = vec[0];
    int pos{0};

    for (int i = 1; i < tam; i++)
    {
        if (vec[i] > mayor)
        {
            mayor = vec[i];
            pos = i;
        }
    }
    
    return pos;
}

void ordenar(float vec[], int tam, int vec_pos[]){  // algoritmo de ordenamiento por seleccion

    for(int pos = 0; pos < tam; pos++){
        int min = pos;
        for(int i = pos + 1; i < tam; i++){
            if(vec[i] < vec[min]){
                min = i;
            }
        }

        swap(vec[pos], vec[min]); 
        swap(vec_pos[pos], vec_pos[min]); 
    } 
}

int main(){

    ifstream archivo;

    archivo.open("Nombres.txt");
    if(!archivo){
        cout << "Error" << endl;
        return 1;
    }

    const int ncli{8};                         // numero de clientes
    const int nprod{5};                        // numero de productos
    string nomcliente[ncli]{};                 // nombre de clientes
    string nomproducto[nprod]{};               // nombre de productos

    for(int i = 0; i < ncli; i++){
        archivo >> nomcliente[i];
    }

    for(int i = 0; i < nprod; i++){
        archivo >> nomproducto[i];
    }

    archivo.close();

    archivo.open("Datos.txt");
    if(!archivo){
        cout << "Error" << endl;
        return 1;
    }

    float entregas_kg[ncli][nprod]{};           // entregas por kilogramos
    float entregas_km[ncli][nprod]{};           // entregas por kilometros
    int entregas_producto[nprod]{};             // contador de entregas por producto 
    int cantmax[ncli]{};                        // contador para el cliente con mayor cantidad tipos de productos que hayan superado los 13000 kg

    int cliente{}, producto{};
    float kg{}, km{};
    
    while(archivo >> cliente >> producto >> kg >> km){
        entregas_kg[cliente][producto] += kg;
        entregas_km[cliente][producto] += km;
        entregas_producto[producto]++;
    }

    bool control;                                  // variable que al recorrer la matriz controla la salida del listado de clientes y sus productos con sus ","

	for(int i = 0; i < ncli; i++){    
        control = true;             
        for(int j = 0; j < nprod; j++){
			if (entregas_kg[i][j] > 13000)
			{                
                if(control){                  
                    cout << nomcliente[i] << ": ";    
                    control = false;
                } else {
                    cout << ", ";
                }
                cout << nomproducto[j];  

                cantmax[i]++;
			}
		}
        cout << endl;	
	}
    
    int mayorcant = mayor_vec(cantmax, ncli);   // posicion del cliente con mayor cantidad tipos de productos que hayan superado los 13000 kg

    cout << endl << "El cliente con mayor cantidad de tipos de productos que superaron los 13000 kg es: " << nomcliente[mayorcant] << endl;

    float producto_km[nprod];                  // kilometros recorridos por tipo de producto
    int vec_pos[nprod];                        // vector de posiciones de los productos

    for (int i = 0; i < nprod; i++)
    {
        producto_km[i] = entregas_km[mayorcant][i];
        vec_pos[i] = i;
    }

    ordenar(producto_km, nprod, vec_pos);

    cout << "Listado de Km recorridos por tipo de producto (ascendente): " << endl;

    for (int i = 0; i < nprod; i++)
    {
        cout << nomproducto[vec_pos[i]] << ": " << producto_km[i] << endl; 
    }

    int pos_prod = vec_pos[nprod - 1];         //posicion del producto con mas entregas

    cout << endl << "Cantidad de entregas para el tipo de producto " << nomproducto[pos_prod] << ": " <<  entregas_producto[pos_prod];

    archivo.close();

	return 0;
}


