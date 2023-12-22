#ifndef USUARIO_H
#define USUARIO_H

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
        string getContraseña() const { return contraseña; }
        string getRol() const { return rol; }
        void setRol(const std::string &nuevoRol) { rol = nuevoRol; }

};  

int menu_usuario(Usuario usuario);
#endif