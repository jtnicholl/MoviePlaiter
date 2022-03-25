#include "MovieSaver.h"

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

#include "../model/Movie.h"
#include "../utils/Utils.h"

std::string movieToLine(Movie* movie)
{
    std::stringstream output;
    output << movie->getName() << ',' << movie->getStudio() << ',' << movie->getYear() << ',';
    output << ratingToString(movie->getRating()) << ',' << movie->getLength();
    return output.str();
}

void writeMoviesToFile(const std::string& filename, const MovieList* movies)
{
    std::vector<Movie*> movieVector = movies->getMoviesByName();
    std::ofstream outfile;
    outfile.open(filename, std::ios::out | std::ios::trunc);
    for (unsigned int i = 0; i < movieVector.size(); i++)
    {
        outfile << movieToLine(movieVector[i]) << std::endl;
    }
    outfile.close();
}
