#include <stdio.h>
#include <string.h>

#define N_EMPLEADOS 20
#define MAX_NOMBRE 20

/*

typedef struct {
    char nombre[MAX_NOMBRE];
    char tipo;
    int horas;
    int estado;
} Trabajador;

void inicializarFichero(FILE* fp) {
    Trabajador t;
    memset(&t, 0, sizeof(Trabajador));
    t.estado = 1;

    for (int i = 0; i < N_EMPLEADOS; i++) {
        fwrite(&t, sizeof(Trabajador), 1, fp);
    }

    printf("Fichero inicializado correctamente\n");
}

int buscarPosicion(FILE* fp) {
    Trabajador t;
    int pos = -1;

    fseek(fp, 0, SEEK_SET);

    for (int i = 0; i < N_EMPLEADOS; i++) {
        fread(&t, sizeof(Trabajador), 1, fp);

        if (t.estado == 1) {
            pos = i;
            break;
        }
    }

    return pos;
}

void altaEmpleado(FILE* fp) {
    Trabajador t;
    int pos;

    pos = buscarPosicion(fp);

    if (pos == -1) {
        printf("No hay posiciones disponibles\n");
        return;
    }

    printf("Introduce el nombre del empleado: ");
    scanf("%s", t.nombre);
    printf("Introduce el tipo de tarea (A, B o C): ");
    scanf(" %c", &t.tipo);
    printf("Introduce las horas acumuladas: ");
    scanf("%d", &t.horas);

    t.estado = 0;

    fseek(fp, pos * sizeof(Trabajador), SEEK_SET);
    fwrite(&t, sizeof(Trabajador), 1, fp);

    printf("Empleado dado de alta correctamente\n");
}

void bajaEmpleado(FILE* fp) {
    int pos;

    printf("Introduce la posicion del empleado: ");
    scanf("%d", &pos);

    if (pos < 0 || pos >= N_EMPLEADOS) {
        printf("Posicion invalida\n");
        return;
    }

    fseek(fp, pos * sizeof(Trabajador), SEEK_SET);

    Trabajador t;
    fread(&t, sizeof(Trabajador), 1, fp);

    if (t.estado == 1) {
        printf("La posicion ya esta disponible\n");
        return;
    }

    t.estado = 1;

    fseek(fp, pos * sizeof(Trabajador), SEEK_SET);
    fwrite(&t, sizeof(Trabajador), 1, fp);

    printf("Empleado dado de baja correctamente\n");
}
void AltaEmpleado(FILE* fichero) {
    Trabajador trabajador;
    int pos = BuscarPosicionLibre(fichero);
    if (pos == -1) {
        printf("Error: no hay posiciones libres.\n");
        return;
    }
    printf("Introduzca los datos del nuevo empleado:\n");
    printf("Nombre: ");
    scanf("%19s", trabajador.nombre);
    printf("Tipo (A/B/C): ");
    scanf(" %c", &trabajador.tipo);
    trabajador.horas = 0;
    trabajador.estado = 1;
    fseek(fichero, pos * sizeof(Trabajador), SEEK_SET);
    fwrite(&trabajador, sizeof(Trabajador), 1, fichero);
    printf("Empleado dado de alta en la posición %d.\n", pos);
}

void AcumularHoras(FILE* fichero) {
    int codigo, horas;
    char categoria;
    printf("Introduzca el código de empleado: ");
    scanf("%d", &codigo);
    if (!ExisteEmpleado(fichero, codigo)) {
        printf("Error: no existe empleado con ese código.\n");
        return;
    }
    printf("Introduzca la categoría de la tarea (A/B/C): ");
    scanf(" %c", &categoria);
    if (categoria != 'A' && categoria != 'B' && categoria != 'C') {
        printf("Error: categoría inválida.\n");
        return;
    }
    printf("Introduzca las horas de la tarea: ");
    scanf("%d", &horas);
    Trabajador trabajador;
    int pos = BuscarEmpleado(fichero, codigo);
    fseek(fichero, pos * sizeof(Trabajador), SEEK_SET);
    fread(&trabajador, sizeof(Trabajador), 1, fichero);
    if (trabajador.tipo == categoria) {
        trabajador.horas += horas;
        fseek(fichero, pos * sizeof(Trabajador), SEEK_SET);
        fwrite(&trabajador, sizeof(Trabajador), 1, fichero);
        printf("Horas acumuladas correctamente.\n");
    }
    else {
        printf("Error: la categoría del empleado no coincide con la introducida.\n");
    }
}

*/