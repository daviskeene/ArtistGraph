#include "ArtistGraph.h"
#include "CSVReader.h"
#include <algorithm>
#include <set>
#include <queue>
#include <map>
#include <algorithm> // for sort function

#include "graph.h"
using namespace std;


std::set<std::string> convertToSet(std::vector<std::string> v) { 
    // Declaring the  set 
    std::set<std::string> s; 
  
    // Traverse the Vector 
    for (std::string x : v) { 
  
        // Insert each element 
        // into the Set 
        s.insert(x); 
    } 
  
    // Return the resultant Set 
    return s; 
}


ArtistGraph::ArtistGraph() : Graph(true) {
    // read from default data
    CSVReader reader(defaultPath);

    std::vector<std::vector<std::string>> data = reader.getFormattedData();
    // Loop through the data once to get the artist names
    for (std::vector<std::string>& row : data) {
      if (row.size() > 0) {
        std::string name = row[0];
        this->insertVertex(name);
      }
    }
    // Loop through again and add edges for each similar artist. Weight edges by the number of different genres.
    for (auto& row : data) {
      // Get necessary data
      if (row.size() > 0) {
        std::string artistName = row[0];
        // Get rid of [ ] 's from the array strings
        std::string genresString = row[1].substr(1, row[1].length() - 2);
        std::string relatedArtistString = row[2].substr(1, row[2].length() - 2);

        genresString.erase(std::remove(genresString.begin(), genresString.end(), '\''), genresString.end());
        relatedArtistString.erase(std::remove(relatedArtistString.begin(), relatedArtistString.end(), '\''), relatedArtistString.end());

        std::vector<std::string> genres = split(genresString, ", ");
        std::vector<std::string> relatedArtistsB = split(relatedArtistString, ", ");
        std::vector<std::string> relatedArtists;

        // Make sure that the related artist exists in the graph before continuing
        for (unsigned i = 0; i < relatedArtistsB.size(); i++) {
          for (unsigned j = 0; j < data.size(); j++) {
            if (relatedArtistsB.at(i) == data.at(j).at(0)) {
              relatedArtists.push_back(relatedArtistsB.at(i));
              break;
            }
          }
        }
        // Make edge for each artist
        for (std::string& artist : relatedArtists) {
          this->insertEdge(artistName, artist);

          // Compute edge weights
          int edgeWeight = 0;
          std::vector<std::string> relatedArtistData = searchForArtist(artist, data);
          if (relatedArtistData.size() > 0) {
            std::string relatedArtistGenreString = relatedArtistData[1].substr(1, relatedArtistData[1].length() - 2);
            relatedArtistGenreString.erase(std::remove(relatedArtistGenreString.begin(), relatedArtistGenreString.end(), '\''), relatedArtistGenreString.end());
            std::vector<std::string> relatedArtistGenres = split(relatedArtistGenreString, ", ");

            // Find how many elements are different between the two
            std::set<std::string> s1 = convertToSet(genres);
            std::set<std::string> s2 = convertToSet(relatedArtistGenres);

            for (const auto& genre : s1) {
              s2.erase(genre);
            }
            // After removing all of the shared genres, concatenate vectors then get size.
            s1.insert(s2.begin(), s2.end());
            edgeWeight = s1.size();
          }
          this->setEdgeWeight(artistName, artist, edgeWeight);
        }
      }
    }

  // Testing purposes
  //std::cout << searchForArtist("Adele", data)[0] << std::endl;
}

int getIndex(vector<Vertex> v, Vertex K) {
    auto it = find(v.begin(), v.end(), K);
 
    // If element was found
    if (it != v.end()) {
        int index = it - v.begin();
        return index;
    }
    return -1;
}

int** createTable(int rows, int columns) {
    int** table = new int*[rows];
    for (int i = 0; i < rows; i++) {
        table[i] = new int[columns]; 
        for (int j = 0; j < columns; j++) {
           table[i][j] = 100000000; 
        }
    }
    return table;
}

void freeTable(int** table, int rows) {
    if (table) {
        for (int i = 0; i < rows; i++) { 
          if(table[i]) { 
            delete[] table[i]; 
          } 
        }
      delete[] table;    
    }
}


int ArtistGraph::computeShortestPath(Vertex a, Vertex b, int** matrix) {
  std::vector<Vertex> verts = this->getVertices();
  int indexA = getIndex(verts, a);
  int indexB = getIndex(verts, b);
  return matrix[indexA][indexB];
}

int ArtistGraph::computeShortestPath(Vertex a, Vertex b) {
  int** matrix = floydWarshall();
  int shortest = computeShortestPath(a, b, matrix);
  // Free memory
  freeTable(matrix, this->getVertices().size());
  return shortest;
}

std::vector<ArtistGraph::centralityGroup> ArtistGraph::computeBetweennessCentrality(int** floyd) {
    vector<ArtistGraph::centralityGroup> centralityVec;
    std::map<Vertex, centralityGroup> centralityMap;
    vector<Vertex> vert = this->getVertices();
    // computing shortest path from every point to every point
    for (unsigned i = 0; i < vert.size(); i++) {
      std::cout << i << std::endl;
      for (unsigned j = i; j < vert.size(); j++) {
        // If a shortest path exists
        if (floyd[i][j] != 100000000) {
          std::vector<Vertex> shortest = getShortestPath(vert.at(i), vert.at(j));
          std::vector<Vertex>::iterator it;
          // find every artist in the current shortest path
          for (it = shortest.begin(); it != shortest.end(); it++) {
              if (centralityMap.find(*it) != centralityMap.end()) {
                centralityMap[*it].centrality++;
              } else {
                centralityMap[*it].centrality = 1;
                centralityMap[*it].name = *it;
              }
          }
        }
    }
  }
  // sort the vector from highest to lowest centrality
  // sort(centralityMap.begin(), centralityMap.end(), cmp);
  for (std::map<Vertex, ArtistGraph::centralityGroup>::iterator it = centralityMap.begin(); it != centralityMap.end(); ++it) {
    centralityVec.push_back(it->second);
  }
  return centralityVec;
}

int** ArtistGraph::floydWarshall() {
  // Get all of the verticies
  std::vector<Vertex> verts = this->getVertices();
  const int n = verts.size();
  // Next, we need to make a matrix that is nxn, where n is the number of verticies
  int** matrix = createTable(n, n);

  std::cout << "matrix size: " << n * n << std::endl;

  for (int i = 0 ; i < n; i++) {
    for (int j = 0; j < n; j++) {
      // Get edge weight
      int artist1 = getIndex(verts, verts[i]);
      int artist2 = getIndex(verts, verts[j]);

      if (artist1 != -1 && artist2 != -1 && this->edgeExists(verts[artist1], verts[artist2])) {
          matrix[i][j] = this->getEdgeWeight(verts[artist1], verts[artist2]);
      } else if (artist1 != -1 && artist2 != -1 && artist1 == artist2) {
          matrix[i][j] = 0;  // Shortest path between an artist and themself is 0
      }
    }
  }

  // Adding vertices
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][k] + matrix[k][j] < matrix[i][j]) {
          matrix[i][j] = matrix[i][k] + matrix[k][j];
        }
      }
    }
  }

  return matrix;
}
 
std::vector<Vertex> ArtistGraph::getShortestPath(Vertex a, Vertex b) {
  // Start at one vertex on the graph.
  std::vector<Vertex> result;
  std::unordered_map<Vertex, Vertex> pred;


  std::queue<Vertex> bfs_tra;
  vector<Vertex> traversal;
  bfs_tra.push(a);
  unordered_map<Vertex, bool> iwasHere;

  for (Vertex v : getVertices()) {
      iwasHere[v] = false;
  }

  iwasHere[a] = true;
  while (!bfs_tra.empty()) {
      Vertex now = bfs_tra.front();
      iwasHere[now] = true;
      bfs_tra.pop();
      traversal.push_back(now);
      auto i = this->getAdjacent(now);
      for (Vertex v : i) {
          if (!iwasHere[v]) {
              bfs_tra.push(v);
              iwasHere[v] = true;
              pred[v] = now;
              if (v == b) {
                // If this node is what we want, then we need to backtrack our previous nodes
                Vertex curr = v;
                while (v != a) {
                  result.push_back(v);
                  v = pred[v];
                }
                return result;
              }
          }
      }
  }
  return result;
}

std::ostream& serialize(std::ostream& outfile, int** arr, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
      for(int j = 0; j < cols; j++) {
        outfile << arr[i][j] << " ";
      }
      outfile << std::endl;
    }
    return outfile;
}