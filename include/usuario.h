#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "actividad.h"

using namespace std;


class Usuario {

    private:
        string nombreUsuario;
        string contraseña; 
        string rol;

    public:
        // Constructor de la clase
        Usuario(string usuario, string pass)
            : nombreUsuario(usuario), contraseña(pass) {}

        // Método para preinscribirse en una actividad
        void preinscribirse(vector<Actividad>& actividades);
        string getNombreUsuario() const { return nombreUsuario; }
        string getRol() const { return rol; }
        bool autenticar(const string &archivoUsuarios);

};  

int menu_usuario(Usuario usuario);
#endif
