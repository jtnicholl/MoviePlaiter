#include "Utils.h"

#include <algorithm>
#include <sstream>

const std::string toUpperCase(std::string text)
{
    std::transform(text.begin(), text.end(), text.begin(), ::toupper);

    return text;
}


int toInt(const std::string& text, const char* errorMessage)
{
    std::stringstream streamConversion(text);
    int value = 0;
    if (!(streamConversion >> value))
    {
        throw errorMessage;
    }

    return value;
}

const std::string ratingToString(Movie::Rating from)
{
    if (from == Movie::Rating::G)
    {
        return ENUM_TO_STR(G);
    }
    else if (from == Movie::Rating::PG)
    {
        return ENUM_TO_STR(PG);
    }
    else if (from == Movie::Rating::PG13)
    {
        return ENUM_TO_STR(PG13);
    }
    else if (from == Movie::Rating::R)
    {
        return ENUM_TO_STR(R);
    }
    else
    {
        return ENUM_TO_STR(NOT_RATED);
    }
}

Movie::Rating parseRating(const std::string& from)
{
    if (from == ENUM_TO_STR(G))
    {
        return Movie::Rating::G;
    }
    else if (from == ENUM_TO_STR(PG))
    {
        return Movie::Rating::PG;
    }
    else if (from == ENUM_TO_STR(PG13))
    {
        return Movie::Rating::PG13;
    }
    else if (from == ENUM_TO_STR(R))
    {
        return Movie::Rating::R;
    }
    else
    {
        return Movie::Rating::NOT_RATED;
    }
}
