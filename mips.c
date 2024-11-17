#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void convertir_decimal_a_binario(int num) {
    if (num < 0) {
        printf("¡Error! Debe ser un número positivo.\n");
        return;
    }

    printf("El número en binario es: ");
    for (int i = 7; i >= 0; i--) {
        int bit = (num >> i) & 1;  // Obtener el bit en la posición i
        printf("%d", bit);
    }
    printf("\n");
}

int convertir_binario_a_decimal(const char* binario) {
    int decimal = 0;
    int longitud = strlen(binario);

    // Validar que el binario tenga 8 caracteres
    if (longitud != 8) {
        printf("¡Error! El número binario debe ser de 8 bits.\n");
        return -1;
    }

    for (int i = 0; i < longitud; i++) {
        if (binario[i] == '1') {
            decimal += (1 << (7 - i));  // Sumar el valor correspondiente al bit en la posición i
        } else if (binario[i] != '0') {
            printf("¡Error! El valor binario debe contener solo '1' o '0'.\n");
            return -1;
        }
    }

    return decimal;
}

int generar_numero_aleatorio() {
    // Generar un número aleatorio entre 10 y 50
    return rand() % 41 + 10;
}

int main() {
    srand(time(NULL));  // Inicializar la semilla para la generación de números aleatorios

    int opcion;
    int numero_decimal;
    char numero_binario[9];  // Cadena de 8 bits más el carácter nulo
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
                // Convertir decimal a binario
                printf("Ingrese un número decimal: ");
                scanf("%d", &numero_decimal);
                convertir_decimal_a_binario(numero_decimal);
                break;

            case 2:
                // Convertir binario a decimal
                printf("Ingrese un número binario de 8 bits: ");
                scanf("%s", numero_binario);  // Leer la cadena de 8 bits
                resultado_decimal = convertir_binario_a_decimal(numero_binario);
                if (resultado_decimal != -1) {
                    printf("El número en decimal es: %d\n", resultado_decimal);
                }
                break;

            case 3:
                // Generar un número aleatorio entre 10 y 50
                numero_decimal = generar_numero_aleatorio();
                printf("El número aleatorio en decimal es: %d\n", numero_decimal);

                // Mostrar el número aleatorio en binario
                convertir_decimal_a_binario(numero_decimal);
                break;

            case 4:
                // Salir
                printf("Saliendo del programa...\n");
                return 0;

            default:
                printf("¡Error! Opción no válida. Intente nuevamente.\n");
                break;
        }
    }

    return 0;
}