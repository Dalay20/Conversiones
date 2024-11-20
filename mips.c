#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void decimal_a_binario(int num) {
    if (num < 0) {
        printf("Valor no valido. Debes ingresar un número positivo.\n");
        return;
    }

    printf("El número decimal convertido a binario es: ");
    for (int i = 7; i >= 0; i--) {
        int bit = (num >> i) & 1;  // Obtener el bit en la posición i
        printf("%d", bit);
    }
    printf("\n");
}

int binario_a_decimal(const char* binario) {
    int decimal = 0;
    int longitud = strlen(binario);

    // Validar que el binario tenga 8 caracteres
    if (longitud != 8) {
        printf("Valor no valido. El número binario que ingreses debe ser de 8 bits.\n");
        return -1;
    }

    for (int i = 0; i < longitud; i++) {
        if (binario[i] == '1') {
            decimal += (1 << (7 - i));  // Sumar el valor correspondiente al bit en la posición i
        } else if (binario[i] != '0') {
            printf("¡Ocurrio un error! El valor binario debe contener solo '1' o '0'.\n");
            return -1;
        }
    }

    return decimal;
}

int numero_aleatorio() {
    // Número aleatorio entre 10 y 50
    return rand() % 41 + 10;
}

int main() {
    srand(time(NULL));  // Inicializar la semilla para la generación de números aleatorios

    int opcion;
    int numDecimal;
    char numBinario[9];  // Cadena de 8 bits más el carácter nulo a conveniencia
    int resultado_decimal;

    while (1) {
        // Mostrar el menú de opciones
        printf("\nSeleccione una opción:\n");
        printf("1. Convertir Decimal a Binario\n");
        printf("2. Convertir Binario a Decimal\n");
        printf("3. Generar un número aleatorio\n");
        printf("4. Salir\n");
        printf("Opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese un número decimal: ");
                scanf("%d", &numDecimal);
        
                decimal_a_binario(numDecimal);
                break;

            case 2:
                printf("Ingrese un número binario de 8 bits: ");
                scanf("%s", numBinario);  // Leer la cadena de 8 bits
                resultado_decimal = binario_a_decimal(numBinario);
                if (resultado_decimal != -1) {
                    printf("El número binario convertido a decimal es: %d\n", resultado_decimal);
                }
                break;

            case 3:
                numDecimal = numero_aleatorio();
                printf("El número aleatorio es: %d\n", numDecimal);

                // Mostrar el número aleatorio en binario
                decimal_a_binario(numDecimal);
                break;

            case 4:
                printf("Programa finalizado.\n");
                return 0;

            default:
                printf("La opción ingresada no es valida. Intente nuevamente.\n");
                break;
        }
    }

    return 0;
}