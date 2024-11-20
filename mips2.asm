.data
    menu_opciones: .asciiz "\nSeleccione una opción:\n1. Convertir Decimal a Binario\n2. Convertir Binario a Decimal\n3. Generar un número aleatorio\n4. Salir\nOpción: "
    mensaje_decimal: .asciiz " Ingrese un número decimal: "
    mensaje_binario: .asciiz " Ingrese un número binario de 8 bits: "
    mensaje_error: .asciiz " Valor no valido. Debes ingresar un número positivo.\n"
    resultado_binario: .asciiz " El número decimal convertido a binario es: "
    resultado_decimal: .asciiz " El número binario convertido a decimal es: "
    mensaje_aleatorio: .asciiz " El número aleatorio en decimal es: "
    linea_nueva: .asciiz "\n"

.text
    main:
        # Mostrar el menú de opciones
        li $v0, 4
        la $a0, menu_opciones
        syscall

        # Leer la opción ingresada por el usuario
        li $v0, 5
        syscall
        move $t0, $v0  # Guardar opción en $t0

        # Verificar la opción ingresada
        beq $t0, 1, opcionDecimalBinario
        beq $t0, 2, opcionBinarioDecimal
        beq $t0, 3, numero_aleatorio
        beq $t0, 4, salir
        j main  # Repetir si la opción es inválida

    opcionDecimalBinario:
        # Pedir al usuario un número decimal
        li $v0, 4
        la $a0, mensaje_decimal
        syscall

        # Leer número decimal
        li $v0, 5
        syscall
        move $t1, $v0  # Guardar número en $t1

        # Validar que el número sea no negativo
        bltz $t1, mostrar_error  # Si $t1 < 0, mostrar error y volver al menú

        # Mostrar el mensaje de resultado
        li $v0, 4
        la $a0, resultado_binario
        syscall

        # Convertir a binario y mostrar
        li $t2, 128  # Valor para enmascarar bits (2^7)
    convertir_a_binario:
        beqz $t2, fin_conversion  # Si $t2 es 0, fin de la conversión

        # Mostrar bit actual
        and $t3, $t1, $t2
        beqz $t3, bit_cero
        li $v0, 11  # syscall para imprimir carácter
        li $a0, '1'
        syscall
        j siguiente_bit

    bit_cero:
        li $v0, 11
        li $a0, '0'
        syscall

    siguiente_bit:
        srl $t2, $t2, 1  # Desplazar $t2 a la derecha (dividir entre 2)
        j convertir_a_binario

    fin_conversion:
        li $v0, 4
        la $a0, linea_nueva
        syscall
        j main

    opcionBinarioDecimal:
        # Pedir al usuario un número binario
        li $v0, 4
        la $a0, mensaje_binario
        syscall

        # Leer número binario (como string)
        li $v0, 8
        la $a0, buffer_binario
        li $a1, 9  # Tamaño del buffer
        syscall

        # Inicializar registros
        li $t4, 0  # $t4 almacenará el valor decimal resultante
        li $t5, 128  # $t5 es el valor de 2^7 (bit más significativo)
        la $t6, buffer_binario  # Apuntador al inicio del string

    convertir_a_decimal:
        lb $t7, 0($t6)  # Cargar el siguiente carácter
        beqz $t7, fin_conversion_binario  # Si es el final del string, terminar

        # Verificar si el carácter es '1'
        li $t8, '1'
        beq $t7, $t8, sumar_a_decimal
        j siguiente_caracter

    sumar_a_decimal:
        add $t4, $t4, $t5  # Sumar el valor de $t5 al resultado decimal

    siguiente_caracter:
        srl $t5, $t5, 1  # Dividir $t5 entre 2 (desplazamiento a la derecha)
        addi $t6, $t6, 1  # Mover al siguiente carácter
        j convertir_a_decimal

    fin_conversion_binario:
        # Mostrar el resultado en decimal
        li $v0, 4
        la $a0, resultado_decimal
        syscall

        move $a0, $t4
        li $v0, 1  # syscall para imprimir entero
        syscall

        li $v0, 4
        la $a0, linea_nueva
        syscall
        j main

    numero_aleatorio:
        # Obtener un valor de tiempo actual para simular aleatoriedad
        li $v0, 30  # syscall para tiempo (seconds)
        syscall
        move $t1, $a0  # Guardar el tiempo en $t1

        # Modificar el valor para que esté entre 10 y 50
        li $t2, 41  # Rango (50 - 10 + 1)
        rem $t1, $t1, $t2  # Resto de la división $t1 / $t2
        addi $t1, $t1, 10  # Ajustar el rango para que sea 10-50

        # Mostrar el número aleatorio en decimal
        li $v0, 4
        la $a0, mensaje_aleatorio
        syscall
        move $a0, $t1
        li $v0, 1  # syscall para imprimir entero
        syscall

        # Mostrar el número en binario
        li $v0, 4
        la $a0, resultado_binario
        syscall

        li $t2, 128  # Valor para enmascarar bits (2^7)
        j convertir_a_binario

    mostrar_error:
        li $v0, 4
        la $a0, mensaje_error
        syscall
        j main

    salir:
        li $v0, 10  # syscall para salir
        syscall

.data
buffer_binario: .space 9  # Espacio para el número binario de 8 bits más nulo.
