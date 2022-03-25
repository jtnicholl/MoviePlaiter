#ifndef MOVIE_H
#define MOVIE_H

#include <string>

namespace model
{

/**
* An immutable object with data representing a movie.
*/
class Movie
{
public:
    /**
    * MPAA movie ratings.
    */
    enum Rating {G, PG, PG13, R, NOT_RATED};

    /**
    * Default constructor.
    *
    * @param name Name of the movie. A copy is made.
    * @param studio Name of the studio. A copy is made.
    * @param year Year of the movie's release.
    * @param rating Rating of the movie.
    * @param length Length of the movie.
    */
    Movie(const std::string& name, const std::string& studio, int year, Rating rating, int length);

    /**
    * Get the name of the movie.
    *
    * @return The name of the movie.
    */
    const std::string& getName() const;
    /**
    * Get the name of the studio.
    *
    * @return The name of the studio.
    */
    const std::string& getStudio() const;
    /**
    * Get the rating of the movie.
    *
    * @return The rating of the movie.
    */
    Movie::Rating getRating() const;
    /**
    * Get the year of the movie.
    *
    * @return The year of the movie.
    */
    int getYear() const;
    /**
    * Get the year of the movie.
    *
    * @return The year of the movie.
    */
    int getLength() const;

private:
    std::string name;
    std::string studio;
    int year;
    Rating rating;
    int length;
};

}

#endif // MOVIE_H
