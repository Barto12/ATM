#include <stdio.h>
#include <time.h>

// Función para mostrar el menú
void mostrarMenu() {
    printf("Cajero Automático\n");
    printf("1. Consultar saldo\n");
    printf("2. Retirar dinero\n");
    printf("3. Depositar dinero\n");
    printf("4. Salir\n");
    printf("Seleccione una opción: ");
}

// Función para imprimir recibo
void imprimirRecibo(const char* operacion, float cantidad, float saldo) {
    FILE *recibo = fopen("recibo.txt", "a");
    if (recibo == NULL) {
        printf("No se pudo abrir el archivo para imprimir el recibo.\n");
        return;
    }

    time_t ahora = time(NULL);
    char *dt = ctime(&ahora);

    fprintf(recibo, "Fecha y hora: %s", dt);
    fprintf(recibo, "Operación: %s\n", operacion);
    fprintf(recibo, "Cantidad: $%.2f\n", cantidad);
    fprintf(recibo, "Saldo actual: $%.2f\n", saldo);
    fprintf(recibo, "-----------------------------------\n");

    fclose(recibo);
    printf("Recibo impreso en 'recibo.txt'\n");
}

// Función principal
int main() {
    int opcion;
    float saldo = 1000.0;  // Saldo inicial

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Su saldo actual es: $%.2f\n", saldo);
                imprimirRecibo("Consulta de saldo", 0, saldo);
                break;
            case 2: {
                float retiro;
                printf("Ingrese la cantidad a retirar: ");
                scanf("%f", &retiro);
                if (retiro > saldo) {
                    printf("Saldo insuficiente.\n");
                } else {
                    saldo -= retiro;
                    printf("Ha retirado: $%.2f\n", retiro);
                    printf("Su saldo actual es: $%.2f\n", saldo);
                    imprimirRecibo("Retiro", retiro, saldo);
                }
                break;
            }
            case 3: {
                float deposito;
                printf("Ingrese la cantidad a depositar: ");
                scanf("%f", &deposito);
                saldo += deposito;
                printf("Ha depositado: $%.2f\n", deposito);
                printf("Su saldo actual es: $%.2f\n", saldo);
                imprimirRecibo("Depósito", deposito, saldo);
                break;
            }
            case 4:
                printf("Gracias por usar el cajero automático.\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
                break;
        }
    } while (opcion != 4);

    return 0;
}
