# Eficiencia-Polinomios-Horner
Análisis comparativo de la eficacia de método de evaluación de polinomios

## Evaluación de Tiempos de Polinomios en C++

Este programa tiene como objetivo comparar el tiempo de evaluación de polinomios utilizando dos métodos distintos:

- **Evaluación estándar**
- **Método de Horner**

El experimento consiste en medir y registrar los tiempos de evaluación promedio de ambos métodos para polinomios de grados desde **10 hasta 1000**, en incrementos de **10**.

**Autor:** María Fernanda Hernández García

---
## Requisitos del sistema para ejecutar el código
 - C++
 - g++


##  Instrucciones de compilación y ejecución:

1. Clonar el repositorio
``` sh
git clone https://github.com/FerHdez08/Eficiencia-Polinomios-Horner.git
```
2. Entrar al directorio del proyecto
```sh
cd Eficiencia-Polinomios-Horner
```
3. Compilar el código 
```sh
g++ "Archivo CPP/Evaluacion-Polinomios.cpp" -o Evaluacion-Polinomios
```
4. Ejecutar código
```sh
Evaluacion-Polinomios

```
*o en su defecto, si no es reconocido, ejecute:*
```bash
   ./Evaluacion-Polinomios
```
<br>

***Alternativa:*** <br>

*Descargar el archivo Evaluacion-Polinomios.cpp y compilar desde un IDE a su preferencia.*

---

## Descripción de los Algoritmos de Evaluación Polinomial

### 1. Método Estándar (Implementado en EvaluarPolinomio())
Evalúa el polinomio como suma de términos independientes:
P(x) = A[0]x^n + A[1]x^[n-1] + ... + A[n-1]x + A[n]

- Calcula cada potencia de x por separado
- Usa multiplicaciones anidadas para potencias
- **Complejidad**: O(n²) operaciones aritméticas

### 2. Esquema de Horner (Implementado en EvaluarPolinomioHorner())
Evalúa el polinomio como una sucesión, donde multiplicas por el valor de x, le sumas un nuevo coeficiente y al resultado se le vuelve a aplicar lo mismo(multiplicar por el valor de x y sumas el nuevo coeficiente). <br>
Reescribe el polinomio en forma anidada:

P(x) = (...((A[0]x + A[1])x + A[2])x + ... + A[n-1])x + A[n]

- **Complejidad**: O(n)

## Resultados experimentales y gráfica comparativa:
  ![7Métodos](Evaluacion.png)
