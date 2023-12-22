#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "actividad.h"
#include "usuario.h"

using namespace std; 



int main() {
    // Pedir al usuario que ingrese nombre de usuario y contraseña
    string nombreUsuario;
    string contrasena;

    cout << "Ingrese nombre de usuario: ";
    cin >> nombreUsuario;

    cout << "Ingrese contraseña: ";
    cin >> contrasena;

    Usuario usuario_log(nombreUsuario, contrasena);

    // Intentar autenticar al usuario
    if (usuario_log.autenticar("log.txt")) {
        cout << "¡Inicio de sesión exitoso!" << endl;

    } else {
        cout << "Nombre de usuario o contraseña incorrectos." << endl;
        // Puedes manejar la lógica para un inicio de sesión fallido aquí
    }

    if (usuario_log.getRol() == "Usuario"){
        menu_usuario(usuario_log);
    }
    else if(usuario_log.getRol() == "Organizador"){
        menu_actividad();
    }


    return 0;
}

