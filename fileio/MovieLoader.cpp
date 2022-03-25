#include "MovieLoader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "../utils/Utils.h"
#include "../model/Movie.h"

#define DIAGNOSTIC_OUTPUT

std::string parseStringEntry(const std::string& line, int& position)
{
    std::stringstream output;
    while (line[position] != ',')
    {
        if (line[position] == 0 || line[position] == '\n')
        {
            return "";
        }
        output << line[position];
        position++;
    }
    position++;
    return output.str();
}

int parseIntEntry(const std::string& line, int& position, char delimiter)
{
    int output = 0;
    while (line[position] != delimiter && line[position] != '\0')
    {
        if (!std::isdigit(line[position]))
        {
            return 0;
        }
        output *= 10;
        output += line[position] - '0';
        position++;
    }
    position++;
    return output;
}

Movie::Rating parseRatingEntry(const std::string& line, int& position)
{
    std::string entry = parseStringEntry(line, position);
    return parseRating(entry);
}

Movie* parseLine(const std::string& line)
{
    std::string name;
    std::string studio;
    int year;
    Movie::Rating rating;
    int length;

    int position = 0;
    name = parseStringEntry(line, position);
    if (name == "")
    {
        return nullptr;
    }
    studio = parseStringEntry(line, position);
    if (studio == "")
    {
        return nullptr;
    }
    year = parseIntEntry(line, position, ',');
    if (year == 0)
    {
        return nullptr;
    }
    rating = parseRatingEntry(line, position);
    if (rating == Movie::Rating::NOT_RATED)
    {
        return nullptr;
    }
    length = parseIntEntry(line, position, '\n');
    if (length == 0)
    {
        return nullptr;
    }

    return new Movie(name, studio, year, rating, length);
}

MovieList* loadMoviesFromFile(const std::string& filename)
{
    MovieList* output = new MovieList();
    std::ifstream infile;

    infile.open(filename, std::ios::in);
    while (infile)
    {
        std::string line;
        std::getline(infile, line);
#ifdef DIAGNOSTIC_OUTPUT
        std::cout << line << std::endl;
#endif // DIAGNOSTIC_OUTPUT
        Movie* toAdd = parseLine(line);
        if (toAdd != nullptr)
        {
            output->insertMovie(toAdd);
        }
    }
    infile.close();
    return output;
}
