#ifndef MODEL_MOVIELIST_H
#define MODEL_MOVIELIST_H

#include <string>
#include <vector>

#include "MovieNode.h"
#include "../utils/Utils.h"

namespace model
{

/**
 * An object that stores a list of movies in multiple sorted orders.
 */
class MovieList
{
public:
    /**
     * Default constructor.
     */
    MovieList();
    /**
     * Destructor.
     */
    virtual ~MovieList();
    /**
     * Gets the size of the list.
     *
     * @return the number of movies in the list.
     */
    int getSize() const;
    /**
     * Add a movie to the list.
     *
     * @precondition movie != nullptr
     * @postcondition movie is inserted
     *
     * @param movie Pointer to movie to insert.
     */
    void insertMovie(Movie* movie);
    /**
     * Remove a movie from the list.
     *
     * @precondition None
     * @postcondition Movie is removed, if found.
     * @param movieName Name of the movie to remove, case sensitive.
     * @return true if the movie was removed, false if not found
     */
    bool removeMovie(const std::string& movieName);
    /**
     * Return a vector of movies in the list in order of name.
     *
     * @return A vector of movie pointers.
     */
    std::vector<Movie*> getMoviesByName() const;
    /**
     * Get the string display for output.
     *
     * @param sortOrder Order of the movies in the output.
     * @return Text summary of movies in the list.
     */
    std::string getOutputDisplay(SortOrder sortOrder) const;

private:
    const int FIRST_COLUMN_WIDTH = 30;
    const int SECOND_COLUMN_WIDTH = 23;
    const int THIRD_COLUMN_WIDTH = 5;
    int size;
    MovieNode* nameHead;
    MovieNode* lengthHead;
    MovieNode* ratingHead;
    void insertName(MovieNode* node);
    void insertLength(MovieNode* node);
    void insertRating(MovieNode* node);
    MovieNode* removeName(const std::string& movieName);
    bool removeLength(const std::string& movieName);
    bool removeRating(const std::string& movieName);
    std::string nameAscendingDisplay(MovieNode* start) const;
    std::string nameDescendingDisplay(MovieNode* start) const;
    std::string lengthAscendingDisplay(MovieNode* start) const;
    std::string lengthDescendingDisplay(MovieNode* start) const;
    std::string ratingAscendingDisplay(MovieNode* start) const;
    std::string ratingDescendingDisplay(MovieNode* start) const;
};

} // namespace model

#endif // MODEL_MOVIELIST_H
