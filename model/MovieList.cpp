#include "model/MovieList.h"

#include <assert.h>
#include <sstream>

#include "../utils/Utils.h"

namespace model
{

MovieList::MovieList()
{
    this->size = 0;
    this->nameHead = nullptr;
    this->lengthHead = nullptr;
    this->ratingHead = nullptr;
}

MovieList::~MovieList()
{
    MovieNode* toDelete = this->nameHead;
    while (toDelete != nullptr)
    {
        MovieNode* next = toDelete->getNextName();
        delete toDelete;
        toDelete = next;
    }
}

int MovieList::getSize() const
{
    return this->size;
}

void MovieList::insertMovie(Movie* movie)
{
    MovieNode* node = new MovieNode(movie);
    insertName(node);
    insertLength(node);
    insertRating(node);
    this->size++;
}

bool MovieList::removeMovie(const std::string& movieName)
{
    MovieNode* removedNode = removeName(movieName);
    if (removedNode != nullptr)
    {
        bool lengthRemoved = removeLength(movieName);
        bool ratingRemoved = removeRating(movieName);
        assert(lengthRemoved && ratingRemoved);
        this->size--;
        delete removedNode;
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<Movie*> MovieList::getMoviesByName() const
{
    std::vector<Movie*> output;
    MovieNode* currentNode = this->nameHead;
    while (currentNode != nullptr)
    {
        output.push_back(currentNode->getMovie());
        currentNode = currentNode->getNextName();
    }
    return output;
}

std::string MovieList::getOutputDisplay(SortOrder sortOrder) const
{
    if (sortOrder == NAME_ASCENDING)
    {
        return nameAscendingDisplay(this->nameHead);
    }
    else if (sortOrder == NAME_DESCENDING)
    {
        return nameDescendingDisplay(this->nameHead);
    }
    else if (sortOrder == LENGTH_ASCENDING)
    {
        return lengthAscendingDisplay(this->lengthHead);
    }
    else if (sortOrder == LENGTH_DESCENDING)
    {
        return lengthDescendingDisplay(this->lengthHead);
    }
    else if (sortOrder == RATING_ASCENDING)
    {
        return ratingAscendingDisplay(this->ratingHead);
    }
    else if (sortOrder == RATING_DESCENDING)
    {
        return ratingDescendingDisplay(this->ratingHead);
    }
    else
    {
        return "";
    }
}

void MovieList::insertName(MovieNode* node)
{
    if (this->nameHead == nullptr || this->nameHead->compareName(node) > 0)
    {
        node->setNextName(this->nameHead);
        this->nameHead = node;
    }
    else
    {
        MovieNode* currentNode = this->nameHead;
        while (currentNode->getNextName() != nullptr && currentNode->getNextName()->compareName(node) < 0)
        {
            currentNode = currentNode->getNextName();
        }
        node->setNextName(currentNode->getNextName());
        currentNode->setNextName(node);
    }
}

void MovieList::insertLength(MovieNode* node)
{
    if (this->lengthHead == nullptr || this->lengthHead->compareLength(node) > 0)
    {
        node->setNextLength(this->lengthHead);
        this->lengthHead = node;
    }
    else
    {
        MovieNode* currentNode = this->lengthHead;
        while (currentNode->getNextLength() != nullptr && currentNode->getNextLength()->compareLength(node) < 0)
        {
            currentNode = currentNode->getNextLength();
        }
        node->setNextLength(currentNode->getNextLength());
        currentNode->setNextLength(node);
    }
}

void MovieList::insertRating(MovieNode* node)
{
    if (this->ratingHead == nullptr || this->ratingHead->compareRating(node) > 0)
    {
        node->setNextRating(this->ratingHead);
        this->ratingHead = node;
    }
    else
    {
        MovieNode* currentNode = this->ratingHead;
        while (currentNode->getNextRating() != nullptr && currentNode->getNextRating()->compareRating(node) < 0)
        {
            currentNode = currentNode->getNextRating();
        }
        node->setNextRating(currentNode->getNextRating());
        currentNode->setNextRating(node);
    }
}

MovieNode* MovieList::removeName(const std::string& movieName)
{
    if (this->nameHead == nullptr)
    {
        return nullptr;
    }
    else if (this->nameHead->nameEquals(movieName))
    {
        MovieNode* toDelete = this->nameHead;
        this->nameHead = toDelete->getNextName();
        return toDelete;
    }
    else
    {
        MovieNode* currentNode = this->nameHead;
        MovieNode* nextNode = currentNode->getNextName();
        while (nextNode != nullptr)
        {
            if (nextNode->nameEquals(movieName))
            {
                currentNode->setNextName(nextNode->getNextName());
                return nextNode;
            }
            currentNode = nextNode;
            nextNode = currentNode->getNextName();
        }
        return nullptr;
    }
}

bool MovieList::removeLength(const std::string& movieName)
{
    if (this->lengthHead == nullptr)
    {
        return false;
    }
    else if (this->lengthHead->nameEquals(movieName))
    {
        MovieNode* toDelete = this->lengthHead;
        this->lengthHead = toDelete->getNextLength();
        return true;
    }
    else
    {
        MovieNode* currentNode = this->lengthHead;
        MovieNode* nextNode = currentNode->getNextLength();
        while (nextNode != nullptr)
        {
            if (nextNode->nameEquals(movieName))
            {
                currentNode->setNextLength(nextNode->getNextLength());
                return true;
            }
            currentNode = nextNode;
            nextNode = currentNode->getNextLength();
        }
        return false;
    }
}

bool MovieList::removeRating(const std::string& movieName)
{
    if (this->ratingHead == nullptr)
    {
        return false;
    }
    else if (this->ratingHead->nameEquals(movieName))
    {
        MovieNode* toDelete = this->ratingHead;
        this->ratingHead = toDelete->getNextRating();
        return true;
    }
    else
    {
        MovieNode* currentNode = this->ratingHead;
        MovieNode* nextNode = currentNode->getNextRating();
        while (nextNode != nullptr)
        {
            if (nextNode->nameEquals(movieName))
            {
                currentNode->setNextRating(nextNode->getNextRating());
                return true;
            }
            currentNode = nextNode;
            nextNode = currentNode->getNextRating();
        }
        return false;
    }
}

std::string MovieList::nameAscendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
        output << nameAscendingDisplay(start->getNextName());
    }
    return output.str();
}

std::string MovieList::nameDescendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << nameDescendingDisplay(start->getNextName());
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
    }
    return output.str();
}

std::string MovieList::lengthAscendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
        output << lengthAscendingDisplay(start->getNextLength());
    }
    return output.str();
}

std::string MovieList::lengthDescendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << lengthDescendingDisplay(start->getNextLength());
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
    }
    return output.str();
}

std::string MovieList::ratingAscendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
        output << ratingAscendingDisplay(start->getNextRating());
    }
    return output.str();
}

std::string MovieList::ratingDescendingDisplay(MovieNode* start) const
{
    std::stringstream output;
    if (start != nullptr)
    {
        output << ratingDescendingDisplay(start->getNextRating());
        output << start->textDisplay(FIRST_COLUMN_WIDTH, SECOND_COLUMN_WIDTH, THIRD_COLUMN_WIDTH);
        output << std::endl;
    }
    return output.str();
}

} // namespace model
