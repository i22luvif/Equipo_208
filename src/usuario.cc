#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "actividad.h"
#include "usuario.h"

using namespace std;

void Usuario::preinscribirse(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades disponibles para preinscribirse." << endl;
        return;
    }

    // Muestra las actividades disponibles
    cout << "Actividades disponibles para preinscribirse:\n";
    for (const Actividad& actividad : actividades) {
        cout << actividad.getNombre() << endl;
    }

    cout << "\n";
    // Solicita al usuario el nombre de la actividad en la que desea preinscribirse
    cout << "Ingrese el nombre de la actividad en la que desea preinscribirse: ";
    string nombreActividad;
    getline(cin >> ws, nombreActividad);

    // Busca la actividad por nombre
    auto it = find_if(actividades.begin(), actividades.end(),
                      [&nombreActividad](const Actividad& actividad) {
                          return actividad.getNombre() == nombreActividad;
                      });

    if (it != actividades.end()) {
        // Verifica si hay plazas disponibles utilizando el método de acceso
        if (it->getPlazasDisponibles() > 0) {
            // Realiza la preinscripción y actualiza la cantidad de plazas disponibles
            cout << "¡Preinscripción exitosa para la actividad '" << nombreActividad << "'!" << endl;
            // Actualiza las plazas disponibles utilizando el método de acceso
            it->setPlazasDisponibles(it->getPlazasDisponibles() - 1);  // Resta 1 a las plazas disponibles

            // Obtén el nombre de usuario utilizando el método de acceso
            string nombreUsuarioActual = getNombreUsuario();

            // Guarda la información en el archivo de preinscritos
            ofstream archivoPreinscritos("preinscritos.txt", ios::app);
            if (archivoPreinscritos.is_open()) {
                archivoPreinscritos << nombreUsuarioActual << " - " << nombreActividad << endl;
                archivoPreinscritos.close();
            } else {
                cerr << "No se pudo abrir el archivo de preinscritos." << endl;
            }
        } else {
            cout << "No hay plazas disponibles para la actividad '" << nombreActividad << "'." << endl;
        }
    } else {
        cout << "No se encontró ninguna actividad con el nombre '" << nombreActividad << "'." << endl;
    }
}



bool Usuario::autenticar(const string &archivoUsuarios) {
    ifstream archivo(archivoUsuarios);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo 'log.txt'." << endl;
        return false;
    }

    string lineaUsuario;
    string lineaContrasena;
    string lineaRol;

    while (getline(archivo, lineaUsuario) && getline(archivo, lineaContrasena) && getline(archivo, lineaRol)) {
        // Compara con el nombre de usuario almacenado en la instancia
        if (lineaUsuario == nombreUsuario) {
            // Compara con la contraseña almacenada en la instancia
            if (lineaContrasena == contraseña) {
                // Almacena el rol encontrado en la instancia
                rol = lineaRol;

                archivo.close();
                return true; // Autenticación exitosa
            }
        }
    }

    archivo.close();
    return false; // No se encontró coincidencia
}


int menu_usuario(Usuario usuario) {
     // Crear un usuario con nombre, nombre de usuario, contraseña y rol

    // Vector para almacenar las actividades
    vector<Actividad> actividades; 

    while (true) {
        // Menú principal
        cout << "\n====== Menú: ======\n"
             << "1. Mostrar actividades\n"
             << "2. Preinscribirse en una actividad\n"
             << "3. Mostrar personas inscritas en una actividad\n"
             << "4. Salir\n"
             << "Seleccione una opción: ";

        int opcion;
        while (!(cin >> opcion) || opcion < 1 || opcion > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción no válida. Ingrese un número del 1 al 4: ";
        }

        cout << "=====================\n";

        // Realiza la acción correspondiente según la opción seleccionada
        switch (opcion) {
            case 1:
                // Leer y mostrar actividades

                actividades = Actividad::obtenerDetalles("actividades.txt");
                Actividad::mostrar(actividades);
                break;

            case 2:
                // Preinscribirse en una actividad
                actividades = Actividad::obtenerDetalles("actividades.txt");
                usuario.preinscribirse(actividades);
                break;

            case 3:
                // Mostrarusuario_log.getRol() == "Usuario") personas inscritas en una actividad
                {
                    cout << "Ingrese el nombre de la actividad para mostrar las personas inscritas: ";
                    string nombreActividad;
                    getline(cin >> ws, nombreActividad);
                    Actividad::mostrarInscritos(nombreActividad);
                }
                break;

            case 4:
                // Salir del programa
                cout << "Saliendo del programa." << endl;
                return 0;

            default:
                cout << "Opción no válida." << endl;
        }
    }
}
 