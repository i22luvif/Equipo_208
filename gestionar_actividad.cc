#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Actividad {
public:
    string nombre;
    string descripcion;
    string fecha_hora;
    string ubicacion;
    int plazas_disponibles;
    string categoria;
    double precio;

    // Constructor de la clase
    Actividad(string nom, string desc, string fecha, string ubic, int plazas, string cat, double prec)
        : nombre(nom), descripcion(desc), fecha_hora(fecha), ubicacion(ubic), plazas_disponibles(plazas), categoria(cat), precio(prec) {}

    // Método para obtener detalles de una actividad
    string obtenerDetalles() const;

    // Método estático para mostrar actividades desde un archivo
    static vector<Actividad> mostrar(const string& nombreArchivo);
    
    // Método estático para crear una nueva actividad
    static Actividad crearActividad();

    // Método estático para guardar una actividad en un archivo
    static void guardarActividadEnArchivo(const Actividad& nuevaActividad, const string& nombreArchivo);

    // Método estático para editar una actividad
    static void editarActividad(vector<Actividad>& actividades);

    // Método estático para eliminar una actividad
    static void eliminarActividad(vector<Actividad>& actividades);
};

// Método para obtener detalles de una actividad
string Actividad::obtenerDetalles() const {
    stringstream detalles;
    detalles << "Nombre: " << nombre << "\n"
             << "Descripción: " << descripcion << "\n"
             << "Fecha y Hora: " << fecha_hora << "\n"
             << "Ubicación: " << ubicacion << "\n"
             << "Plazas Disponibles: " << plazas_disponibles << "\n"
             << "Categoría: " << categoria << "\n"
             << "Precio: " << precio << "\n";

    return detalles.str();
}   

// Método estático para mostrar actividades desde un archivo
vector<Actividad> Actividad::mostrar(const string& nombreArchivo) {
    vector<Actividad> actividades;
    ifstream archivo(nombreArchivo);

    // Verifica si el archivo se pudo abrir
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return actividades;
    }

    // Lee y muestra actividades desde el archivo
    while (archivo.peek() != EOF) {
        string nombre, descripcion, fecha_hora, ubicacion, categoria;
        int plazas_disponibles;
        double precio;

        // Lee datos de la actividad desde el archivo
        if (getline(archivo >> ws, nombre) &&
            getline(archivo >> ws, descripcion) &&
            getline(archivo >> ws, fecha_hora) &&
            getline(archivo >> ws, ubicacion) &&
            getline(archivo >> ws, categoria) &&
            (archivo >> plazas_disponibles) &&
            (archivo >> precio)) {

            // Crea una nueva actividad y la añade al vector
            Actividad nueva_actividad(nombre, descripcion, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
            actividades.push_back(nueva_actividad);
            
            // Muestra la actividad inmediatamente después de leerla
            cout << nueva_actividad.obtenerDetalles() << endl;
        } else {
            cerr << "Error al leer datos de actividad desde el archivo." << endl;
            break;
        }

        // Consume el carácter de nueva línea después de leer el precio
        archivo.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Cierra el archivo
    archivo.close();
    return actividades;
}

// Método estático para crear una nueva actividad
Actividad Actividad::crearActividad() {
    string nombre, descripcion, fecha_hora, ubicacion, categoria;
    int plazas_disponibles;
    double precio;

    // Solicita al usuario ingresar datos para la nueva actividad
    cout << "Ingrese el nombre de la actividad: ";
    getline(cin >> ws, nombre);

    cout << "Ingrese la descripción de la actividad: ";
    getline(cin >> ws, descripcion);

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

    // Crea y devuelve una nueva actividad con los datos ingresados
    return Actividad(nombre, descripcion, fecha_hora, ubicacion, plazas_disponibles, categoria, precio);
}

// Método estático para guardar una actividad en un archivo
void Actividad::guardarActividadEnArchivo(const Actividad& nuevaActividad, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app); // Modo de apertura: ios::app para agregar al final del archivo

    // Verifica si el archivo se pudo abrir
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo '" << nombreArchivo << "'." << endl;
        return;
    }

    // Escribe los datos de la nueva actividad en el archivo
    archivo << nuevaActividad.nombre << endl
            << nuevaActividad.descripcion << endl
            << nuevaActividad.fecha_hora << endl
            << nuevaActividad.ubicacion << endl
            << nuevaActividad.categoria << endl
            << nuevaActividad.plazas_disponibles << endl
            << nuevaActividad.precio << endl;

    // Cierra el archivo
    archivo.close();
}

// Método estático para editar una actividad
void Actividad::editarActividad(vector<Actividad>& actividades) {
    if (actividades.empty()) {
        cout << "No hay actividades para editar." << endl;
        return;
    }

    // Solicita al usuario el nombre de la actividad a editar
    cout << "Ingrese el nombre de la actividad que desea editar: ";
    string nombreEditar;
    getline(cin >> ws, nombreEditar);

    // Busca la actividad por nombre y la edita si la encuentra
    for (Actividad& actividad : actividades) {
        if (actividad.nombre == nombreEditar) {
            cout << "Ingrese nuevos datos para la actividad '" << actividad.nombre << "':" << endl;
            // Utiliza la función existente para crear una nueva actividad
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

    // Solicita al usuario el nombre de la actividad a eliminar
    cout << "Ingrese el nombre de la actividad que desea eliminar: ";
    string nombreEliminar;
    getline(cin >> ws, nombreEliminar);

    // Busca la actividad por nombre y la elimina si la encuentra
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

int main() {
    while (true) {
        // Menú principal
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


        // Realiza la acción correspondiente según la opción seleccionada
        switch (opcion) {
            case 1:
                // Leer y mostrar actividades
                Actividad::mostrar("actividades.txt");
                break;

            case 2:
                // Crear nueva actividad
                {
                    Actividad nuevaActividad = Actividad::crearActividad();
                    vector<Actividad> actividades = Actividad::mostrar("actividades.txt");
                    actividades.push_back(nuevaActividad);
                    Actividad::guardarActividadEnArchivo(nuevaActividad, "actividades.txt");
                    cout << "Nueva actividad creada y guardada." << endl;
                }
                break;

            case 3:
                // Editar actividad
                {
                    vector<Actividad> actividades = Actividad::mostrar("actividades.txt");
                    Actividad::editarActividad(actividades);
                    ofstream archivo("actividades.txt");
                    for (const Actividad& actividad : actividades) {
                        Actividad::guardarActividadEnArchivo(actividad, "actividades.txt");
                    }
                }
                break;

            case 4:
                // Eliminar actividad
                {
                    vector<Actividad> actividades = Actividad::mostrar("actividades.txt");
                    Actividad::eliminarActividad(actividades);
                    ofstream archivo("actividades.txt");
                    for (const Actividad& actividad : actividades) {
                        Actividad::guardarActividadEnArchivo(actividad, "actividades.txt");
                    }
                }
                break;

            case 5:
                // Salir del programa
                cout << "Saliendo del programa." << endl;
                return 0;

            default:
                cout << "Opción no válida." << endl;
        }
    }
}
