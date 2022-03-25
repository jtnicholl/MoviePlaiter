#ifndef MODEL_MOVIENODE_H
#define MODEL_MOVIENODE_H

#include "Movie.h"

namespace model
{

class MovieNode
{
public:
    /**
     * Default constructor.
     *
     * @precondition movieInfo != nullptr
     * @postcondition none
     *
     * @param movieInfo Pointer to movie to store. It is NOT copied
     */
    MovieNode(Movie* movieInfo);
    /**
     * Destructor.
     */
    virtual ~MovieNode();
    /**
     * Get the movie stored.
     *
     * @return Pointer to stored movie
     */
    Movie* getMovie() const;
    /**
     * Get the next movie in the list by name.
     *
     * @return Pointer to next movie, nullptr if reached the end
     */
    MovieNode* getNextName() const;
    /**
     * Get the next movie in the list by length.
     *
     * @return Pointer to next movie, nullptr if reached the end
     */
    MovieNode* getNextLength() const;
    /**
     * Get the next movie in the list by rating.
     *
     * @return Pointer to next movie, nullptr if reached the end
     */
    MovieNode* getNextRating() const;
    /**
     * Set the next movie in the list by name.
     *
     * @precondition none
     * @postcondition this->getNextName() == node
     *
     * @param node Pointer to next movie, nullptr to mark the end
     */
    void setNextName(MovieNode* node);
    /**
     * Set the next movie in the list by length.
     *
     * @precondition none
     * @postcondition this->getNextLength() == node
     *
     * @param node Pointer to next movie, nullptr to mark the end
     */
    void setNextLength(MovieNode* node);
    /**
     * Set the next movie in the list by rating.
     *
     * @precondition none
     * @postcondition this->getNextRating() == node
     *
     * @param node Pointer to next movie, nullptr to mark the end
     */
    void setNextRating(MovieNode* node);
    /**
     * Compare sorting order of this node to another by name.
     *
     * @precondition compareTo != nullptr
     * @postcondition none
     *
     * @param compareTo Pointer to node to compare
     * @return <0 if this movie's name is less, 0 if equal, >0 if greater
     */
    int compareName(MovieNode* compareTo) const;
    /**
     * Compare sorting order of this node to another by length.
     *
     * @precondition compareTo != nullptr
     * @postcondition none
     *
     * @param compareTo Pointer to node to compare
     * @return <0 if this movie's length is less, 0 if equal, >0 if greater
     */
    int compareLength(MovieNode* compareTo) const;
    /**
     * Compare sorting order of this node to another by rating.
     *
     * @precondition compareTo != nullptr
     * @postcondition none
     *
     * @param compareTo Pointer to node to compare
     * @return <0 if this movie's rating is less, 0 if equal, >0 if greater
     */
    int compareRating(MovieNode* compareTo) const;
    /**
     * Check if the movie name equals the provided name, case insensitive.
     *
     * @return true if name is equal
     */
    bool nameEquals(const std::string& name) const;
    /**
     * Get text summary of this node's movie.
     *
     * @param firstColumnWidth Width of the first column
     * @param secondColumnWidth Width of the second column
     * @param thirdColumnWidth Width of the third column
     * @return Text summary of this node's movie
     */
    std::string textDisplay(int firstColumnWidth, int secondColumnWidth, int thirdColumnWidth) const;

private:
    Movie* movieInfo;
    MovieNode* nextName;
    MovieNode* nextLength;
    MovieNode* nextRating;
};

} // namespace model

#endif // MODEL_MOVIENODE_H
