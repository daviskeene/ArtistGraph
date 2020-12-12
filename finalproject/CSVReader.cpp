#include "CSVReader.h"

std::vector<std::string> split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

std::vector<std::vector<std::string>> CSVReader::readData() {

    std::ifstream file(path);

    std::vector<std::vector<std::string>> dataAsVector;

    std::string line("");

    while (getline(file, line)) {
        std::vector<std::string> data = split(line, delimeter);
        // std::cout << data.size() << std::endl;
        dataAsVector.push_back(data);
    }

    file.close();
    return dataAsVector;
}

std::vector<std::vector<std::string>> CSVReader::readArrays() {

    std::ifstream file(path);

    std::vector<std::vector<std::string>> dataAsVector;

    std::string line("");

    int counter = 0;
    while (getline(file, line)) {
        if (counter == 0) {
            counter++;
            continue;
        }
        std::vector<std::string> data = split(line, "\"");
        // std::cout << data.size() << std::endl;
        dataAsVector.push_back(data);
    }

    file.close();
    return dataAsVector;
}

std::vector<std::string> searchForArtist(std::string name, std::vector<std::vector<std::string>> data) {

    for (std::vector<std::string>& row : data) {
        if (row[0] == name) {
            return row;
        }
    }

    return std::vector<std::string>();
}

std::vector<std::vector<std::string>> CSVReader::getFormattedData() {
    std::vector<std::vector<std::string>> data = readArrays();
    // Pull the artist name, genres, and related artists.
    std::vector<std::vector<std::string>> output;
    for (auto& row : data) {
      std::vector<std::string> fmtrow;
      for (unsigned int i = 0; i < row.size(); i++) {
        if (i == 0) {
            std::vector<std::string> tingz = split(row[i], ",");
            fmtrow.push_back(tingz[1]);
        }
        if (i == 1) {
            fmtrow.push_back(row[i]);
        } else if (i == 3) {
            fmtrow.push_back(row[i]);
        } else {
            continue;
        }
      }
    output.push_back(fmtrow);
    }
    artistData_ = output;
    return output;
}