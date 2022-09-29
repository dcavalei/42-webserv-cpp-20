#include <iostream>
#include "app/serverApp/serverApp.h"

int main(int argc, char *argv[]) {
    app::ServerApp &app = app::ServerApp::instance();

    app.start(argc, argv);
    return EXIT_SUCCESS;
}
