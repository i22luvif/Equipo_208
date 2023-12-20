#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "organizador.h"
#include "actividad.h"

// Método estático para crear una nueva actividad
Actividad Organizador::crearActividad() {
    string nombre, descripcion, ponente, fecha_hora, ubicacion, categoria;
    int plazas_disponibles;
    double precio;
    cout << "\n";
    cout << "Ingrese el nombre de la actividad: ";
    getline(cin >> ws, nombre);

    cout << "Ingrese la descripción de la actividad: ";
    getline(cin >> ws, descripcion);

    cout << "Ingrese el ponente de la actividad: ";
    getline(cin >> ws, ponente);

    cout << "Ingrese la fecha y hora de la actividad: ";
    getline(cin >> ws, fecha_hora);

    cout << "Ingrese la ubicación de la actividad: ";
    getline(cin >> ws, ubicacion);

    cout << "Ingrese la categoría de la actividad: ";
    getline(cin >> ws, categoria);

    cout << "Ingrese el número de plazas disponibles: ";
    while (!(cin >> plazas_disponibles) || plazas_disponibles < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido de plazas: ";
    }

    cout << "Ingrese el precio de la actividad: ";
    while (!(cin >> precio) || precio < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un precio válido: ";
    }

    return Actividad(nombre, descripcion, ponente, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
}


// Método estático para editar una actividad
void Organizador::editarActividad(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades para editar." << endl;
        return;
    }
    //Solicita al usuraio el nombre de la actividad
    cout << "\n";
    cout << "Ingrese el nombre de la actividad que desea editar: ";
    string nombreEditar;
    getline(cin >> ws, nombreEditar);

    //Busca el nombre de la actividad y la edita si la encuentra
    for (Actividad& actividad : actividades) {
        if (actividad.getNombre() == nombreEditar) {
            cout << "Ingrese nuevos datos para la actividad '" << actividad.getNombre() << "':" << endl;
            Actividad nuevaActividad = Organizador::crearActividad();
            actividad = nuevaActividad;
            cout << "Actividad editada correctamente." << endl;
            return;
        }
    }

    cout << "No se encontró ninguna actividad con el nombre '" << nombreEditar << "'." << endl;
}

// Método estático para eliminar una actividad
void Organizador::eliminarActividad(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades para eliminar." << endl;
        return;
    }
    cout << "\n";
    //Solicita al usuario el nombre de la actividad que desea eliminar
    cout << "Ingrese el nombre de la actividad que desea eliminar: ";
    string nombreEliminar;
    getline(cin >> ws, nombreEliminar);

    //Busca la actividad por nombre y la elimina si la encuentra
    auto it = std::remove_if(actividades.begin(), actividades.end(),
                             [&nombreEliminar](const Actividad& actividad) {
                                 return actividad.getNombre() == nombreEliminar;
                             });

    if (it != actividades.end()) {
        actividades.erase(it, actividades.end());
        cout << "Actividad eliminada correctamente." << endl;
    } else {
        cout << "No se encontró ninguna actividad con el nombre '" << nombreEliminar << "'." << endl;
    }
}


int menu_organizador(){
    while (true) {
        cout << "\n====== Menú: ======\n"
             << "1. Mostrar actividades\n"
             << "2. Crear nueva actividad\n"
             << "3. Editar actividad\n"
             << "4. Eliminar actividad\n"
             << "5. Salir\n"
             << "Seleccione una opción: ";

        int opcion;
        while (!(cin >> opcion) || opcion < 1 || opcion > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción no válida. Ingrese un número del 1 al 5: ";
        }

        cout << "=====================\n";

        switch (opcion) {
            //Leer y mostrar actividades
            case 1:
                {
                vector<Actividad> actividades = Actividad::obtenerDetalles("actividades.txt");
                Actividad::mostrar(actividades); 
                break;
                }

            //Crear una actividad
            case 2:
                {
                    Actividad nuevaActividad = Organizador::crearActividad();
                    vector<Actividad> actividades = Actividad::obtenerDetalles("actividades.txt");
                    Actividad::mostrar(actividades); 
                    actividades.push_back(nuevaActividad);
                    Actividad::guardarActividad(nuevaActividad, "actividades.txt");
                    cout << "Nueva actividad creada y guardada." << endl;
                }
                break;
            //Editar actividad
            case 3:
                {
                    vector<Actividad> actividades = Actividad::obtenerDetalles("actividades.txt");
                    Actividad::mostrar(actividades);                    
                    Organizador::editarActividad(actividades);
                    ofstream archivo("actividades.txt");
                    for (const Actividad& actividad : actividades) {
                        Actividad::guardarActividad(actividad, "actividades.txt");
                    }
                }
                break;

            //Eliminar actividad
            case 4:
                {
                    vector<Actividad> actividades = Actividad::obtenerDetalles("actividades.txt");
                    Actividad::mostrar(actividades);
                    Organizador::eliminarActividad(actividades);
                    ofstream archivo("actividades.txt");
                    for (const Actividad& actividad : actividades) {
                        Actividad::guardarActividad(actividad, "actividades.txt");
                    }
                }
                break;
            
            //Salir
            case 5:
                cout << "Saliendo del programa." << endl;
                return 0;

            default:
                cout << "Opción no válida." << endl;
        }
    }
}

