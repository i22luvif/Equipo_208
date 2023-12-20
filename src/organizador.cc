#include "../include/organizador.h"

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

// Método estático para editar una actividad por número
void Organizador::editarActividad(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades para editar." << endl;
        return;
    }

    // Muestra la lista de actividades con sus números
    cout << "Lista de actividades disponibles:" << endl;
    for (size_t i = 0; i < actividades.size(); ++i) {
        cout << i + 1 << ". " << actividades[i].getNombre() << endl;
    }

    // Solicita al usuario el número de la actividad que desea editar
    cout << "Ingrese el número de la actividad que desea editar: ";
    size_t numeroEditar;
    while (!(cin >> numeroEditar) || numeroEditar < 1 || numeroEditar > actividades.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido de actividad: ";
    }

    // Edita la actividad correspondiente al número proporcionado
    cout << "Ingrese nuevos datos para la actividad '" << actividades[numeroEditar - 1].getNombre() << "':" << endl;
    Actividad nuevaActividad = Organizador::crearActividad();
    actividades[numeroEditar - 1] = nuevaActividad;
}

// Método estático para eliminar una actividad por número
void Organizador::eliminarActividad(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades para eliminar." << endl;
        return;
    }

    // Muestra la lista de actividades con sus números
    cout << "Lista de actividades disponibles:" << endl;
    for (size_t i = 0; i < actividades.size(); ++i) {
        cout << i + 1 << ". " << actividades[i].getNombre() << endl;
    }

    // Solicita al usuario el número de la actividad que desea eliminar
    cout << "Ingrese el número de la actividad que desea eliminar: ";
    size_t numeroEliminar;
    while (!(cin >> numeroEliminar) || numeroEliminar < 1 || numeroEliminar > actividades.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Por favor, ingrese un número válido de actividad: ";
    }

    // Elimina la actividad correspondiente al número proporcionado
    actividades.erase(actividades.begin() + numeroEliminar - 1);
}



int menu_organizador() {
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
                    Organizador::editarActividad(actividades);
                    cout << "Actividad editada correctamente." << endl;
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
                    Organizador::eliminarActividad(actividades);
                    ofstream archivo("actividades.txt");
                    for (const Actividad& actividad : actividades) {
                        Actividad::guardarActividad(actividad, "actividades.txt");
                    }
                    cout << "Actividad eliminada correctamente." << endl;
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
