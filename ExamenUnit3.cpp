#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

// Estructura para almacenar los datos procesados
struct Registro {
    string nombre;
    float promedio;
};

string obtenerFecha() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", ltm);
    return string(buffer);
}

void decorar(string titulo) {
    cout << "\n==========================================" << endl;
    cout << "      " << titulo << endl;
    cout << "==========================================" << endl;
}

int main() {
    // 1. NÓMINA COMPLETA
    string nomina[] = {
        "ACOSTA SOLIS HANNA AIDE", "ANDRADE SANCHEZ HUGO ALEXANDER", "ATIENCIA CHERRES JOSUE ALEXANDER",
        "BALAREZO PEREZ DIEGO SEBASTIAN", "BARRIONUEVO MONTESDEOCA JOB GABRIEL", "BEDOYA MAZO JUAN MANUEL",
        "BRAVO LOPEZ JORDAN SAMUEL", "CAJIAO VALDIVIESO PAULO ALESSANDRO", "CALVOPIÑA HERRERA BRANDON ISRAEL",
        "CASTELO BERRONES KATHERINE NICOL", "CHACHA CHANGO VICTOR MANUEL", "CHILUIZA QUISHPE DIEGO STEED",
        "DOMINGUEZ LESCANO DANIEL SEBASTIAN", "FREIRE AREBALO ALAN ANDERSON", "GUALLE AUCANSHALA ABISAG LISENIA",
        "GUAMAN CHANAHUANO HAMILTON ALEXANDER", "GUANGA ALTAMIRANO EDWIN SEBASTIAN", "GUANOTOA ESCOBAR KARLA LEONELA",
        "LANDETA TAPIA EDISON PAUL", "LARA BALSECA KAREN ARACELY", "LOOR VELEZ JHON ALEJANDRO",
        "LOPEZ SANCHEZ WASHINGTON STEVEN", "MIRANDA GARCES ALAN IMANOL", "MONAR PARCO JHAIR ALEXANDER",
        "MUYULEMA MOYOLEMA MATEO ALEXANDER", "NARVAEZ GAVILANES ANTONELLA NICOLE", "NUÑEZ ESPIN BRYAN SEBASTIAN",
        "PILCO FLORES MARIO DAVID", "POMAQUERO CHANGO KATHERINE SOLEDAD", "QUEVEDO AJON GINA ANAHI",
        "RIVADENEYRA ULLOA MATIAS SEBASTIAN", "ROCHA ROCHA CAROLINA ESTEFANIA", "SANCHEZ LEMA ISAAC ADRIAN",
        "SEGOVIA GARCIA JOSEPH ANDRE", "SUPE GARCES JOAN SEBASTIAN", "TOAPANTA IZA KEVIN MATIAS",
        "VERDESOTO AZOGUE KEVIN ALEXANDER", "VILLACRES TOALOMBO JOSUE ALEJANDRO", "VITERI CAMINO MAYDELIN SHANTAL"
    };

    // CORRECCIÓN: Calculamos el tamaño real de la lista de nombres
    int totalEstudiantes = sizeof(nomina) / sizeof(nomina[0]);

    // CORRECCIÓN: El arreglo registros ahora tiene tamaño 39 (totalEstudiantes)
    Registro registros[totalEstudiantes];

    int opcion;
    bool notasRegistradas = false;

    do {
        decorar("SISTEMA DE CALIFICACIONES");
        cout << "1. Operaciones Matematicas" << endl;
        cout << "2. Registrar Notas de la Nomina (" << totalEstudiantes << " Estudiantes)" << endl;
        cout << "3. Guardar Reporte Final (TXT)" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione: "; cin >> opcion;

        switch(opcion) {
            case 1: {
                float n1, n2; int op;
                cout << "\n1.Suma 2.Resta 3.Multiplicacion 4.Division: "; cin >> op;
                cout << "Valores: "; cin >> n1 >> n2;
                if(op == 1) cout << "Respuesta: " << n1+n2 << endl;
                else if(op == 2) cout << "Respuesta: " << n1-n2 << endl;
                else if(op == 3) cout << "Respuesta: " << n1*n2 << endl;
                else if(op == 4 && n2 != 0) cout << "Respuesta: " << n1/n2 << endl;
                else cout << "Operacion no valida o Division por cero" << endl;
                break;
            }

            case 2: {
                decorar("REGISTRO DE NOTAS POR ESTUDIANTE");
                for(int i = 0; i < totalEstudiantes; i++) {
                    float suma = 0, nota;
                    cout << "\n[" << (i + 1) << "/" << totalEstudiantes << "] Estudiante: " << nomina[i] << endl;

                    for(int j = 0; j < 5; j++) {
                        do {
                            cout << "  Nota " << (j + 1) << " (0-10): ";
                            cin >> nota;
                            if(nota < 0 || nota > 10) cout << "  [!] Error: La nota debe estar entre 0 y 10." << endl;
                        } while(nota < 0 || nota > 10);
                        suma += nota;
                    }

                    registros[i].nombre = nomina[i];
                    registros[i].promedio = suma / 5;
                    cout << "  [!] Promedio de " << nomina[i] << ": " << fixed << setprecision(2) << registros[i].promedio << endl;
                }
                notasRegistradas = true;
                break;
            }

            case 3: {
                if(!notasRegistradas) {
                    cout << "\n[!] Primero debe registrar las notas en la opcion 2." << endl;
                } else {
                    ofstream archivo("resultados.txt");
                    if(archivo.is_open()) {
                        Registro *mejor = &registros[0];
                        Registro *peor = &registros[0];

                        archivo << "=====================================================================" << endl;
                        archivo << "             REPORTE ACADEMICO DE LA NOMINA" << endl;
                        archivo << "=====================================================================" << endl;
                        archivo << "Fecha: " << obtenerFecha() << " | Lenguaje: C++" << endl;
                        archivo << "---------------------------------------------------------------------" << endl;
                        // Aumentamos setw a 45 para que los nombres largos quepan bien
                        archivo << left << setw(45) << "ESTUDIANTE" << "PROMEDIO" << endl;
                        archivo << "---------------------------------------------------------------------" << endl;

                        for(int i = 0; i < totalEstudiantes; i++) {
                            archivo << left << setw(45) << registros[i].nombre
                                    << fixed << setprecision(2) << registros[i].promedio << endl;

                            if(registros[i].promedio > mejor->promedio) mejor = &registros[i];
                            if(registros[i].promedio < peor->promedio) peor = &registros[i];
                        }

                        archivo << "---------------------------------------------------------------------" << endl;
                        archivo << "RESUMEN FINAL DEL CURSO:" << endl;
                        archivo << "Nota Mayor Total: " << mejor->promedio << " (" << mejor->nombre << ")" << endl;
                        archivo << "Nota Menor Total: " << peor->promedio << " (" << peor->nombre << ")" << endl;
                        archivo << "=====================================================================" << endl;

                        archivo.close();
                        cout << "\n[!] Reporte 'resultados.txt' generado con los " << totalEstudiantes << " estudiantes." << endl;
                    }
                }
                break;
            }
        }
    } while(opcion != 4);

    return 0;
}
