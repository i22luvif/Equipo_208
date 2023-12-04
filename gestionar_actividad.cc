#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;


// Declaración de la clase Actividad
class Actividad {
public:
    string nombre;
    string descripcion;
    string fecha_hora;
    string ubicacion;
    int plazas_disponibles;
    string categoria;
    double precio;

    // Constructor de la clase Actividad
    Actividad(string nom, string desc, string fecha, string ubic, int plazas, string cat, double prec) {
        nombre = nom;
        descripcion = desc;
        fecha_hora = fecha;
        ubicacion = ubic;
        plazas_disponibles = plazas;
        categoria = cat;
        precio = prec;
    }

    // Método para obtener detalles de la actividad
    string obtenerDetalles() const {
    stringstream detalles;
    detalles << "Nombre: " << nombre << "\nDescripción: " << descripcion << "\nFecha y Hora: " << fecha_hora
             << "\nUbicación: " << ubicacion << "\nPlazas Disponibles: " << plazas_disponibles
             << "\nCategoría: " << categoria << "\nPrecio: " << precio << "\n\n";
    return detalles.str();
    }

};
// Función para crear una nueva actividad
Actividad crearActividad() {
    string nombre, descripcion, fecha_hora, ubicacion, categoria;
    int plazas_disponibles;
    double precio;

    cout << "Ingrese el nombre de la actividad: ";
    getline(cin, nombre);

    cout << "Ingrese la descripción de la actividad: ";
    getline(cin, descripcion);

    cout << "Ingrese la fecha y hora de la actividad (formato: dd/mm/aaaa hh:mm): ";
    getline(cin, fecha_hora);

    cout << "Ingrese la ubicación de la actividad: ";
    getline(cin, ubicacion);

    cout << "Ingrese el número de plazas disponibles: ";
    cin >> plazas_disponibles;
    cin.ignore();

    cout << "Ingrese la categoría de la actividad: ";
    getline(cin, categoria);

    cout << "Ingrese el precio de la actividad: ";
    cin >> precio;

    Actividad nueva_actividad(nombre, descripcion, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
    return nueva_actividad;
}

// Función para obtener actividades desde un archivo
vector<Actividad> obtenerActividades() {
    vector<Actividad> actividades;
    ifstream archivo("actividades.txt");

    if (archivo.is_open()) {
        while (true) {
            string nombre, descripcion, fecha_hora, ubicacion, categoria;
            int plazas_disponibles;
            double precio;

            // Intenta leer cada componente de la actividad
            if (getline(archivo, nombre) &&
                getline(archivo, descripcion) &&
                getline(archivo, fecha_hora) &&
                getline(archivo, ubicacion) &&
                archivo >> plazas_disponibles &&
                archivo.ignore() &&
                getline(archivo, categoria) &&
                archivo >> precio) {

                Actividad nueva_actividad(nombre, descripcion, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
                actividades.push_back(nueva_actividad);
            } else {
                break;  // Sale del bucle si no se pueden leer más líneas
            }
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo 'actividades.txt'." << endl;
    }

    return actividades;
}


// Función para mostrar actividades
void mostrarActividades(const vector<Actividad>& actividades) {
    for (size_t i = 0; i < actividades.size(); ++i) {
        cout << "Actividad " << i + 1 << ":\n" << actividades[i].obtenerDetalles() << endl;
    }
}

// Función para editar actividad
void editarActividad(vector<Actividad>& actividades) {
    string nombre_buscar;
    cout << "Ingrese el nombre de la actividad que desea editar: ";
    getline(cin, nombre_buscar);

    bool actividad_encontrada = false;

    for (size_t i = 0; i < actividades.size(); ++i) {
        if (actividades[i].nombre == nombre_buscar) {
            actividad_encontrada = true;

            // Mostrar los detalles de la actividad encontrada
            cout << "Detalles de la actividad:\n";
            cout << actividades[i].obtenerDetalles() << endl;

            // Pedir al usuario los nuevos datos
            Actividad nueva_actividad = crearActividad();

            // Actualizar los datos de la actividad encontrada
            actividades[i].nombre = nueva_actividad.nombre;
            actividades[i].descripcion = nueva_actividad.descripcion;
            actividades[i].fecha_hora = nueva_actividad.fecha_hora;
            actividades[i].ubicacion = nueva_actividad.ubicacion;
            actividades[i].plazas_disponibles = nueva_actividad.plazas_disponibles;
            actividades[i].categoria = nueva_actividad.categoria;
            actividades[i].precio = nueva_actividad.precio;

            // Actualizar el archivo con los datos actualizados
            ofstream archivo("actividades.txt");
            if (archivo.is_open()) {
                for (const Actividad& actividad : actividades) {
                    archivo << actividad.obtenerDetalles();
                }
                archivo.close();
                cout << "La actividad ha sido editada y los cambios se han guardado en 'actividades.txt'." << endl;
            } else {
                cout << "No se pudo abrir el archivo para guardar los cambios." << endl;
            }

            break; // Terminar el bucle al encontrar la actividad
        }
    }

    if (!actividad_encontrada) {
        cout << "No se encontró ninguna actividad con ese nombre." << endl;
    }
}



void eliminarActividad(vector<Actividad>& actividades, const string& nombre_actividad) {
    bool eliminado = false;
    for (auto it = actividades.begin(); it != actividades.end();) {
        if (it->nombre == nombre_actividad) {
            it = actividades.erase(it);
            eliminado = true;
        } else {
            ++it;
        }
    }

    if (eliminado) {
        ofstream archivo("actividades.txt");
        if (archivo.is_open()) {
            for (const Actividad& actividad : actividades) {
                archivo << actividad.obtenerDetalles();
            }
            archivo.close();
            cout << "La actividad ha sido eliminada y los cambios se han guardado en 'actividades.txt'." << endl;
        } else {
            cout << "No se pudo abrir el archivo para guardar los cambios." << endl;
        }
    } else {
        cout << "No se encontró ninguna actividad con ese nombre." << endl;
    }
}


// Función principal
int main() {
    vector<Actividad> actividades = obtenerActividades();

    char opcion;
    do {
        cout << "Selecciona una opción:\n";
        cout << "1. Mostrar actividades\n";
        cout << "2. Crear actividad\n";
        cout << "3. Editar actividad\n";
        cout << "4. Eliminar actividad\n";
        cout << "5. Salir\n";
        cout << "Ingrese su opción: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case '1':
                mostrarActividades(actividades);
                break;
            case '2': {
                Actividad nueva_actividad = crearActividad();
                actividades.push_back(nueva_actividad);

                ofstream archivo("actividades.txt", ios::app);
                if (archivo.is_open()) {
                    archivo << nueva_actividad.obtenerDetalles();
                    archivo.close();
                    cout << "La actividad ha sido creada y los cambios se han guardado en 'actividades.txt'." << endl;
                } else {
                    cout << "No se pudo abrir el archivo para guardar los cambios." << endl;
                }
                break;
            }
            case '3':
                editarActividad(actividades);
                break;
            case '4': {
                string nombre_actividad;
                cout << "Ingrese el nombre de la actividad que desea eliminar: ";
                getline(cin, nombre_actividad);
                eliminarActividad(actividades, nombre_actividad);
                break;
            }
            case '5':
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }
    } while (opcion != '5');

    return 0;
}