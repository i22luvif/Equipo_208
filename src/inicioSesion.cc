#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "inicioSesion.h"

inicioSesion::inicioSesion() : usuario("", "") {}

bool inicioSesion::autenticar(const std::string &archivoUsuarios, Usuario &usuario) {
    std::ifstream archivo(archivoUsuarios);

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo '" << archivoUsuarios << "'." << std::endl;
        return false;
    }

    std::string lineaUsuario;
    std::string lineaContrasena;
    std::string lineaRol;

    while (getline(archivo, lineaUsuario) && getline(archivo, lineaContrasena) && getline(archivo, lineaRol)) {
        // Compara con el nombre de usuario almacenado en el objeto Usuario
        if (lineaUsuario == usuario.getNombreUsuario()) {
            // Compara con la contraseña almacenada en el objeto Usuario
            if (lineaContrasena == usuario.getContraseña()) {
                // Almacena el rol encontrado en el objeto Usuario
                usuario.setRol(lineaRol);

                archivo.close();
                return true; // Autenticación exitosa
            }
        }
    }

    archivo.close();
    return false; // No se encontró coincidencia
}
