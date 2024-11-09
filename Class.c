#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void decimal_a_binario(int decimal) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (decimal >> i) & 1);
    }
    printf("\n");
}

int binario_a_decimal(char binario[]) {
    int decimal = 0;
    int longitud = strlen(binario);
    
    for (int i = 0; i < longitud; i++) {
        if (binario[i] == '1') {
            decimal += (1 << (longitud - i - 1));
        }
    }
    return decimal;
}

void generar_aleatorio() {
    int num = rand() % 41 + 10;  // Genera un número aleatorio entre 10 y 50
    printf("Número aleatorio en decimal: %d\n", num);
    printf("Número aleatorio en binario: ");
    decimal_a_binario(num);
}

int main() {
    srand(time(NULL));  // Inicializa la semilla para los números aleatorios
    int opcion;
    
    do {
        // Menú principal
        printf("\n--- Menú ---\n");
        printf("1. Convertir Decimal a Binario\n");
        printf("2. Convertir Binario a Decimal\n");
        printf("3. Generar un Número Aleatorio\n");
        printf("0. Salir\n");
        printf("Elija una opción: ");
        scanf("%d", &opcion);
        
        if (opcion == 1) {
            int num_decimal;
            printf("Ingrese un número decimal: ");
            scanf("%d", &num_decimal);
            printf("El número en binario es: ");
            decimal_a_binario(num_decimal);
        } 
        else if (opcion == 2) {
            char binario[9];
            printf("Ingrese un número binario de 8 bits: ");
            scanf("%s", binario);
            
            // Validación de binario
            int valido = 1;
            for (int i = 0; i < 8; i++) {
                if (binario[i] != '0' && binario[i] != '1') {
                    valido = 0;
                    break;
                }
            }
            }
            
            if (valido) {
                int decimal = binario_a_decimal(binario);
                printf("El número en decimal es: %d\n", decimal);
            } else {
                printf("Error: El número binario ingresado no es válido. Asegúrese de que tenga 8 bits.\n");
            }
        } 
        else if (opcion == 3) {
            generar_aleatorio();
        } 
        else if (opcion != 0) {
            printf("Opción no válida, intente nuevamente.\n");
        }
    } while (opcion != 0);
    
    return 0;
}