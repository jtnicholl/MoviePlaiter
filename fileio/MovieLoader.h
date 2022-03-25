#ifndef MOVIELOADER_H_INCLUDED
#define MOVIELOADER_H_INCLUDED

#include <string>
#include "../model/MovieList.h"

using namespace model;

/**
 * Load movies from a file. Invalid lines are ignored.
 * 
 * @param filename Path to the file to load
 * @return List with all the movies in the file
 */
MovieList* loadMoviesFromFile(const std::string& filename);

#endif // MOVIELOADER_H_INCLUDED
