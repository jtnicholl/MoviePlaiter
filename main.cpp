#include "view/MovieLibraryWindow.h"

using namespace view;

int main(int argc, char ** argv)
{
    MovieLibraryWindow mainWindow(540, 375, "Jonathan Nicholl's Movie Database");
    mainWindow.show();

    int exitCode = Fl::run();
    return exitCode;
}
