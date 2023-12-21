#ifndef INICIOSESION_H
#define INICIOSESION_H

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "actividad.h"
#include "usuario.h"


class Organizador : public Usuario {
private:
    Actividad actividad; 

public:
    // Constructor de la clase Administrador
    Organizador(string usuario, string pass) : Usuario(usuario, pass) {
        setRol("Administrador");
    }
    // Método estático para crear una nueva actividad
    static Actividad crearActividad();


    // Método estático para editar una actividad
    static void editarActividad(vector<Actividad>& actividades);

    // Método estático para eliminar una actividad
    static void eliminarActividad(vector<Actividad>& actividades);

};

#endif