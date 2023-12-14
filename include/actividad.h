#ifndef ACTIVIDAD_H
#define ACTIVIDAD_H

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Actividad {
private:
    string nombre;
    string descripcion;
    string ponente;  // Nuevo atributo
    string fecha_hora;
    string ubicacion;
    int plazas_disponibles;
    string categoria;
    double precio;

public:
    // Constructor de la clase
    Actividad(string nom, string desc, string pon, string fecha, string ubic, int plazas, string cat, double prec)
        : nombre(nom), descripcion(desc), ponente(pon), fecha_hora(fecha), ubicacion(ubic), plazas_disponibles(plazas), categoria(cat), precio(prec) {}
    
    //Funciones getters()
    string getNombre() const { return nombre; }
    string getDescripcion() const { return descripcion; }
    string getPonente() const { return ponente; }
    string getFechaHora() const { return fecha_hora; }
    string getUbicacion() const { return ubicacion; }
    int getPlazasDisponibles() const { return plazas_disponibles; }
    string getCategoria() const { return categoria; }
    double getPrecio() const { return precio; }


    void setPlazasDisponibles(int nuevasPlazasDisponibles) { plazas_disponibles = nuevasPlazasDisponibles; }

    // Método para obtener detalles de una actividad
    static void mostrar(const vector<Actividad>& actividades);

    // Método estático para mostrar actividades desde un archivo
    static vector<Actividad> obtenerDetalles(const string& nombreArchivo);
    
    // Método estático para crear una nueva actividad
    static Actividad crearActividad();

    // Método estático para guardar una actividad en un archivo
    static void guardarActividad(const Actividad& nuevaActividad, const string& nombreArchivo);

    // Método estático para editar una actividad
    static void editarActividad(vector<Actividad>& actividades);

    // Método estático para eliminar una actividad
    static void eliminarActividad(vector<Actividad>& actividades);

    // Método estático para mostrar las personas inscritas en una actividad
    static void mostrarInscritos(const string& nombreActividad);
};


#endif
int menu_actividad();
