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
             << "Precio: " << actividad.precio << " €" <<"\n";
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


