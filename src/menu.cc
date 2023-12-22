    #include "usuario.h"
    #include "inicioSesion.h"
    #include "organizador.h"

    using namespace std; 

    int main() {
        // Pedir al usuario que ingrese nombre de usuario y contraseña
        string nombreUsuario;
        string contrasena;

        cout << "Ingrese nombre de usuario: ";
        cin >> nombreUsuario;

        cout << "Ingrese contraseña: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del teclado
        getline(cin, contrasena);

        // Crear instancia de inicioSesion
        inicioSesion usu;

        // Configurar la instancia de Usuario dentro de inicioSesion
        Usuario usuario_log(nombreUsuario, contrasena);

        // Intentar autenticar al usuario
        if (usu.autenticar("log.txt", usuario_log)) {
            cout << "¡Inicio de sesión exitoso!" << endl;

            // Obtener el rol de la instancia de Usuario dentro de inicioSesion
            if (usuario_log.getRol() == "Usuario") {
                menu_usuario(usuario_log);
                cout << "Menú de usuario no implementado aún." << endl;
            } else if (usuario_log.getRol()== "Organizador") {
                menu_actividad();
                cout << "Menú de organizador no implementado aún." << endl;
            }
        } else {
            cout << "Nombre de usuario o contraseña incorrectos." << endl;
            // Puedes manejar la lógica para un inicio de sesión fallido aquí
        }

        return 0;
    }
