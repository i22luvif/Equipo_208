#ifndef INICIOSESION_H
#define INICIOSESION_H

#include "actividad.h"
#include "usuario.h"

class inicioSesion {
private:
    Usuario usuario;

public:
    inicioSesion(); // Constructor
    Usuario getUsuario() { return usuario; }
    bool autenticar(const std::string &archivoUsuarios, Usuario &usuario);
};

#endif