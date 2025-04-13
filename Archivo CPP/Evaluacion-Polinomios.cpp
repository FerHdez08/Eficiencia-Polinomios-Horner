#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <fstream>


#define TAM_MAXIMO 1000
#define TAM_MINIMO 10
#define INCREMENTO 10
#define VECES 1000
#define NUM_ALGORITMOS 2

using namespace std;

void generar_x(int x[TAM_MAXIMO]);
void generar_coefs(int j, int coeficientes[TAM_MAXIMO+1]);

void tiempo(auto start, auto end, int k, long double *suma_estandar, long double *suma_horner);

long double EvaluarPolinomioHorner(int cof[TAM_MAXIMO+1], int grado, int x);
long double EvaluarPolinomio(int cof[TAM_MAXIMO+1], int grado, int x);

int aleatorio(int inicio, int fin);

int main()
{
    srand(time(NULL));

    long double promedio_estandar , promedio_horner ;
    int j;

    ofstream archivo("resultados.csv");
    archivo << "Grado,T. Promedio Estandar (ns),T. Promedio Horner (ns)\n";

    // Ciclo que va a recorrer los grados de los polinomios, desde 10 hasta 1000, de 10 en 10
    for(j = TAM_MINIMO; j <= TAM_MAXIMO; j+=INCREMENTO){
        
        int coeficientes[TAM_MAXIMO+1]; 
        int x[TAM_MAXIMO]; 

        generar_x(x); // arreglo que almacena las mil x, que se usarán en las mil evaluaciones de cada uno de los grados

        long double suma_estandar = 0; //suma de los tiempos
        long double suma_horner = 0; 

        // Ciclo que recorre las 1000 repeticiones para cada grado
        int i;
        for(i = 0; i < TAM_MAXIMO; ++i){
          
            generar_coefs(j,coeficientes); // manda a generar y almacenar un arreglo de j coeficientes mas uno del polinomio

            // Ciclo para medir los tiempos de evaluacion del mismo polinomio, pero con los 2 métodos
            for(int k = 0; k < NUM_ALGORITMOS; ++k){
                
                auto start = chrono::high_resolution_clock::now();
                if(k ==0)
                {
                    EvaluarPolinomio(coeficientes,j,x[i]);
                }else{
                    EvaluarPolinomioHorner(coeficientes,j,x[i]);
                }
                auto end = chrono::high_resolution_clock::now();

                tiempo(start, end, k, &suma_estandar, &suma_horner);
            }  
        }

        //Calcula el tiempo promedio para cada método en cada uno de los grados
        promedio_estandar = suma_estandar / TAM_MAXIMO;
        promedio_horner = suma_horner / TAM_MAXIMO;

        archivo << j << "," << promedio_estandar << "," << promedio_horner << "\n";  
        
        cout << "Evaluaciones para polinomios de grado " << j << " listas" << endl;
    }

    archivo.close();

    system("pause");
    return 0;
}

// Calcula el tiempo de una evaluación para cada método
void tiempo(auto start, auto end, int k, long double *suma_estandar, long double *suma_horner){

    chrono::duration<double, nano> duration = end - start;

    if(k == 0){
        *suma_estandar = *suma_estandar + duration.count();
    }else{
        *suma_horner = *suma_horner + duration.count();
    }
}

// Genera de forma aleatoria las mil x que se usaran para las mil repeticiones que corresponden a un grado
void generar_x(int x[TAM_MAXIMO])
{
    for(int i = 0; i < TAM_MAXIMO; ++i){
        x[i] = aleatorio(-10,10);
    }
}

// Genera de forma aleatoria los coeficientes del polinomio de grado j, incluyendo al término independiente
void generar_coefs(int j, int coeficientes[TAM_MAXIMO+1])
{
    for(int i = 0; i <= j; ++i){
        coeficientes[i] = aleatorio(-10,10);
    }
}

// Evalúa un polinomio en x usando el método de Horner
long double EvaluarPolinomioHorner(int cof[TAM_MAXIMO+1], int grado, int x)
{
    // Inicializa el valor con el coeficiente del término de mayor grado
    double valor = cof[0];

    // Aplica el esquema de Horner para evaluar el polinomio
    for(int i = 1 ; i <= grado ; ++i){
       valor = valor*x + cof[i];
    }

    return valor;
}


long double EvaluarPolinomio(int cof[TAM_MAXIMO+1], int grado, int x)
{
    // Inicializa el valor con el coeficiente del término independiente
    double poliVal = cof[grado];
    double term;

    // Recorre todos los términos restantes del polinomio
    for(int i = 1; i <= grado; ++i){
        term = cof[grado - i];

        // Calcula x elevado a la potencia correspondiente
        for(int j = 1 ; j <= i; ++j){
            term = term*x;
        }

        // Suma el término actual al valor total del polinomio
        poliVal = poliVal + term;
    }

    return poliVal;
}

int aleatorio(int inicio, int fin)
{
    return inicio + rand()% (fin-inicio+1);
}