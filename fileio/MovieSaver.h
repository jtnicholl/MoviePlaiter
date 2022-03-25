#ifndef MOVIESAVER_H_INCLUDED
#define MOVIESAVER_H_INCLUDED

#include <string>
#include "../model/MovieList.h"

using namespace model;

/**
 * Write a list of movies to a file.
 * 
 * @precondition movies != nullptr
 * @postcondition file is written
 * 
 * @param filename Path to save the file
 * @param movies List of movies to save
 */
void writeMoviesToFile(const std::string& filename, const MovieList* movies);

#endif // MOVIESAVER_H_INCLUDED
