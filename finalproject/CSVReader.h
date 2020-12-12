#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

class CSVReader {

    std::string path;
    std::string delimeter;

    public:

        /**
         * CSVReader constructor
         * @param filepath - path to csv file
         * @param delim - string delimeter
         */
        CSVReader(std::string filepath, std::string delim = ",") :
            path(filepath), delimeter(delim) {

            }

        /** 
         * Reads a CSV File into a 2D vector
         * @return a 2D Vector containing comma separated values
         */
        std::vector<std::vector<std::string>> readData();
        /** 
         * Reads a CSV File into a 2D vector, specifically handles reading array strings
         * @return a 2D Vector containing comma separated values
         */
        std::vector<std::vector<std::string>> readArrays();
        /** 
         * Reads a CSV File into a 2D vector, specifically designed to return Artist data in the shape we want
         * @return a 2D Vector containing comma separated values in the proper format
         */
        std::vector<std::vector<std::string>> getFormattedData();

    private:
        // include any private vars heres
        std::vector<std::vector<std::string>> artistData_;
};

/** 
 * Splits a string by a delimeter.
 * @return a vector of strings split by the delimeter.
 */
std::vector<std::string> split(const std::string& str, const std::string& delim);
/** 
 * Searches for an artist in a table of artist data.
 * @return Artist row (if it exists) of data.
 */
std::vector<std::string> searchForArtist(std::string name, std::vector<std::vector<std::string>> table);