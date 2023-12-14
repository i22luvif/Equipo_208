#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "actividad.h"

using namespace std;

// Método para mostrar detalles de una actividad
void Actividad::mostrar(const vector<Actividad>& actividades) {
    for (const Actividad& actividad : actividades) {
        cout << "\n"
             << "Nombre: " << actividad.nombre << "\n"
             << "Descripción: " << actividad.descripcion << "\n"
             << "Ponente: " << actividad.ponente << "\n"
             << "Fecha y Hora: " << actividad.fecha_hora << "\n"
             << "Ubicación: " << actividad.ubicacion << "\n"
             << "Plazas Disponibles: " << actividad.plazas_disponibles << "\n"
             << "Categoría: " << actividad.categoria << "\n"
             << "Precio: " << actividad.precio << "\n";
    }
}



// Método estático para mostrar actividades desde un archivo
vector<Actividad> Actividad::obtenerDetalles(const string& nombreArchivo) {
    vector<Actividad> actividades;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return actividades;
    }

    while (archivo.peek() != EOF) {
        string nombre, descripcion, ponente, fecha_hora, ubicacion, categoria;
        int plazas_disponibles;
        double precio;

        //Lee datos de la actividad desde el archivo
        if (getline(archivo >> ws, nombre) &&
            getline(archivo >> ws, descripcion) &&
            getline(archivo >> ws, ponente) &&
            getline(archivo >> ws, fecha_hora) &&
            getline(archivo >> ws, ubicacion) &&
            getline(archivo >> ws, categoria) &&
            (archivo >> plazas_disponibles) &&
            (archivo >> precio)) {

            Actividad nueva_actividad(nombre, descripcion, ponente, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
            actividades.push_back(nueva_actividad);
        } else {
            cerr << "Error al leer datos de actividad desde el archivo." << endl;
            break;
        }

        //Consume el carácter de nueva línea después de leer el precio
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    archivo.close();
    return actividades;
}

// Método estático para crear una nueva actividad
Actividad Actividad::crearActividad() {
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

// Método estático para guardar una actividad en un archivo
void Actividad::guardarActividad(const Actividad& nuevaActividad, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);
    
    //Verifica si se pudo abrir el fichero
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    //Escribe los datos de la nueva actividad en el archivo
    archivo << nuevaActividad.nombre << endl
            << nuevaActividad.descripcion << endl
            << nuevaActividad.ponente << endl  // Nuevo campo
            << nuevaActividad.fecha_hora << endl
            << nuevaActividad.ubicacion << endl
            << nuevaActividad.categoria << endl
            << nuevaActividad.plazas_disponibles << endl
            << nuevaActividad.precio << endl;

    archivo.close();
}

// Método estático para editar una actividad
void Actividad::editarActividad(vector<Actividad>& actividades) {
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
        if (actividad.nombre == nombreEditar) {
            cout << "Ingrese nuevos datos para la actividad '" << actividad.nombre << "':" << endl;
            Actividad nuevaActividad = Actividad::crearActividad();
            actividad = nuevaActividad;
            cout << "Actividad editada correctamente." << endl;
            return;
        }
    }

    cout << "No se encontró ninguna actividad con el nombre '" << nombreEditar << "'." << endl;
}

// Método estático para eliminar una actividad
void Actividad::eliminarActividad(vector<Actividad>& actividades) {
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
                                 return actividad.nombre == nombreEliminar;
                             });

    if (it != actividades.end()) {
        actividades.erase(it, actividades.end());
        cout << "Actividad eliminada correctamente." << endl;
    } else {
        cout << "No se encontró ninguna actividad con el nombre '" << nombreEliminar << "'." << endl;
    }
}

// Método estático para mostrar las personas inscritas en una actividad
void Actividad::mostrarInscritos(const string& nombreActividad) {
    ifstream archivoPreinscritos("preinscritos.txt");

    // Verifica si el archivo se pudo abrir
    if (!archivoPreinscritos.is_open()) {
        cerr << "No se pudo abrir el archivo de preinscritos." << endl;
        return;
    }

    // Muestra las personas inscritas en la actividad
    cout << "Personas inscritas en la actividad '" << nombreActividad << "':\n";
    string linea;
    while (getline(archivoPreinscritos, linea)) {
        size_t pos = linea.find(" - ");
        if (pos != string::npos) {
            string nombreUsuario = linea.substr(0, pos);
            string actividad = linea.substr(pos + 3);
            if (actividad == nombreActividad) {
                cout << "Usuario: " << nombreUsuario << endl;
            }
        }
    }

    // Cierra el archivo
    archivoPreinscritos.close();
}



int menu_actividad() {
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
                    Actividad nuevaActividad = Actividad::crearActividad();
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
                    Actividad::editarActividad(actividades);
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
                    Actividad::eliminarActividad(actividades);
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
