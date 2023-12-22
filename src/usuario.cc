#include "../include/usuario.h"

using namespace std;
void Usuario::preinscribirse(std::vector<Actividad>& actividades) {
    if (actividades.empty()) {
        std::cout << "No hay actividades disponibles para preinscribirse." << std::endl;
        return;
    }

    // Muestra las actividades disponibles numeradas
    std::cout << "Actividades disponibles para preinscribirse:\n";
    for (size_t i = 0; i < actividades.size(); ++i) {
        std::cout << i + 1 << ". " << actividades[i].getNombre() << std::endl;
    }

    std::cout << "\n";
    // Solicita al usuario el número de la actividad en la que desea preinscribirse
    int numeroActividad;
    std::cout << "Ingrese el número de la actividad en la que desea preinscribirse: ";
    std::cin >> numeroActividad;

    // Verifica que el número esté dentro del rango válido
    if (numeroActividad >= 1 && static_cast<size_t>(numeroActividad) <= actividades.size()) {
        // Obtiene la actividad correspondiente
        Actividad& actividadSeleccionada = actividades[static_cast<size_t>(numeroActividad) - 1];

        // Verifica si hay plazas disponibles utilizando el método de acceso
        if (actividadSeleccionada.getPlazasDisponibles() > 0) {
            // Realiza la preinscripción y actualiza la cantidad de plazas disponibles
            std::cout << "¡Preinscripción exitosa para la actividad '"
                      << actividadSeleccionada.getNombre() << "'!" << std::endl;

            // Actualiza las plazas disponibles utilizando el método de acceso
            actividadSeleccionada.setPlazasDisponibles(actividadSeleccionada.getPlazasDisponibles() - 1);

            // Obtén el nombre de usuario utilizando el método de acceso
            std::string nombreUsuarioActual = getNombreUsuario();

            // Guarda la información en el archivo de preinscritos
            std::ofstream archivoPreinscritos("preinscritos.txt", std::ios::app);
            if (archivoPreinscritos.is_open()) {
                archivoPreinscritos << nombreUsuarioActual << " - " << actividadSeleccionada.getNombre() << std::endl;
                archivoPreinscritos.close();
            } else {
                std::cerr << "No se pudo abrir el archivo de preinscritos." << std::endl;
            }
        } else {
            std::cout << "No hay plazas disponibles para la actividad '"
                      << actividadSeleccionada.getNombre() << "'." << std::endl;
        }
    } else {
        std::cout << "Número de actividad no válido." << std::endl;
    }
}

int menu_usuario(Usuario usuario) {
    // Vector para almacenar las actividades
    vector<Actividad> actividades; 

    while (true) {
        // Menú principal
        cout << "\n====== Menú: ======\n"
             << "1. Mostrar actividades\n"
             << "2. Preinscribirse en una actividad\n"
             << "3. Mostrar personas inscritas en una actividad\n"
             << "4. Salir\n"
             << "Seleccione una opción: ";

        int opcion;
        while (!(cin >> opcion) || opcion < 1 || opcion > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción no válida. Ingrese un número del 1 al 4: ";
        }

        cout << "=====================\n";

        // Realiza la acción correspondiente según la opción seleccionada
        switch (opcion) {
            case 1:
                // Leer y mostrar actividades
                actividades = Actividad::obtenerDetalles("actividades.txt");
                Actividad::mostrar(actividades);
                break;

            case 2:
                // Preinscribirse en una actividad
                actividades = Actividad::obtenerDetalles("actividades.txt");
                usuario.preinscribirse(actividades);
                break;

            case 3: {
                // Mostrar personas inscritas en una actividad
                actividades = Actividad::obtenerDetalles("actividades.txt");

                // Muestra las actividades disponibles numeradas
                cout << "Actividades disponibles:\n";
                for (size_t i = 0; i < actividades.size(); ++i) {
                    cout << i + 1 << ". " << actividades[i].getNombre() << endl;
                }

                // Solicita al usuario el número de la actividad en la que desea ver los inscritos
                int numeroActividad;
                cout << "Ingrese el número de la actividad para mostrar las personas inscritas: ";
                while (!(cin >> numeroActividad) || numeroActividad < 1 || numeroActividad > actividades.size()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Por favor, ingrese un número válido de actividad: ";
                }

                // Obtiene la actividad correspondiente al número proporcionado
                const Actividad& actividadSeleccionada = actividades[static_cast<size_t>(numeroActividad) - 1];

                // Muestra las personas inscritas en la actividad
                Actividad::mostrarPreinscritos(actividadSeleccionada.getNombre());
            }
                break;

            case 4:
                // Salir del programa
                cout << "Saliendo del programa." << endl;
                return 0;

            default:
                cout << "Opción no válida." << endl;
        }
    }
}
