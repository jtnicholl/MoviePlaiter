#ifndef UTILS_H
#define UTILS_H

#include <string>

#include "../model/Movie.h"

using namespace model;

#define ENUM_TO_STR(ENUM) std::string(#ENUM)

/**
 * Sort order for movies.
 */
enum SortOrder {NAME_ASCENDING, NAME_DESCENDING, RATING_ASCENDING, RATING_DESCENDING, LENGTH_ASCENDING, LENGTH_DESCENDING};

/**
 * Convert a string to uppercase.
 * 
 * @param text String to convert
 * @return String converted to uppercase
 */
const std::string toUpperCase(std::string text);
/**
 * Parse an integer from a string.
 * 
 * @precondition text represents an integer
 * @postcondition none
 * 
 * @param text String to convert
 * @param errorMessage Text to use for exception message
 * 
 * @throws Exception if string does not represent an integer
 * @return Integer value of the string
 */
int toInt(const std::string& text, const char* errorMessage);
/**
 * Convert a movie rating to a string representation.
 * 
 * @param from Rating to convert
 * 
 * @return String representation of the rating
 */
const std::string ratingToString(Movie::Rating from);
/**
 * Parses a movie rating from a string.
 * 
 * @param from String to parse
 * 
 * @return Rating represented by the string, NOT_RATED if string is not valid
 */
Movie::Rating parseRating(const std::string& from);

#endif // UTILS_H
