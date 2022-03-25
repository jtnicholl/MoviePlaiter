#include "model/MovieNode.h"

#include <string>
#include <sstream>

#define DIAGNOSTIC_OUTPUT
#ifdef DIAGNOSTIC_OUTPUT
#include <iostream>
#endif

#include "../utils/Utils.h"

namespace model
{

MovieNode::MovieNode(Movie* movieInfo)
{
    this->movieInfo = movieInfo;
    this->nextName = nullptr;
    this->nextLength = nullptr;
    this->nextRating = nullptr;
}

MovieNode::~MovieNode()
{
    delete this->movieInfo;
}

Movie* MovieNode::getMovie() const
{
    return this->movieInfo;
}

MovieNode* MovieNode::getNextName() const
{
    return this->nextName;
}

MovieNode* MovieNode::getNextLength() const
{
    return this->nextLength;
}

MovieNode* MovieNode::getNextRating() const
{
    return this->nextRating;
}

void MovieNode::setNextName(MovieNode* node)
{
    this->nextName = node;
}

void MovieNode::setNextLength(MovieNode* node)
{
    this->nextLength = node;
}

void MovieNode::setNextRating(MovieNode* node)
{
    this->nextRating = node;
}

int MovieNode::compareName(MovieNode* compareTo) const
{
    std::string otherName = compareTo->getMovie()->getName();
    return this->movieInfo->getName().compare(otherName);
}

int MovieNode::compareLength(MovieNode* compareTo) const
{
    int otherLength = compareTo->getMovie()->getLength();
    return this->movieInfo->getLength() - otherLength;
}

int MovieNode::compareRating(MovieNode* compareTo) const
{
    int otherRating = (int)compareTo->getMovie()->getRating();
    return (int)this->movieInfo->getRating() - otherRating;
}

bool MovieNode::nameEquals(const std::string& name) const
{
    return toUpperCase(this->movieInfo->getName()) == toUpperCase(name);
}

std::string MovieNode::textDisplay(int firstColumnWidth, int secondColumnWidth, int thirdColumnWidth) const
{
    std::stringstream output;

    output << this->movieInfo->getName() << '-' << this->movieInfo->getYear();
    for (int i = firstColumnWidth - output.str().length(); i > 0; i--)
    {
        output << ' ';
    }
    output << this->movieInfo->getStudio();
    for (int i = secondColumnWidth - this->movieInfo->getStudio().length(); i > 0; i--)
    {
        output << ' ';
    }
    std::string rating = ratingToString(this->movieInfo->getRating());
    output << rating;
    for (int i = thirdColumnWidth - rating.length(); i > 0; i--)
    {
        output << ' ';
    }
    output << this->movieInfo->getLength();

    return output.str();
}

} // namespace model
