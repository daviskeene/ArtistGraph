#include "graph.h"
#include <vector>

class ArtistGraph : public Graph {
    
    public:
        struct centralityGroup {
          string name;
          double centrality;
        } ;

        /**
            * The constructor for our ArtistGraph, constructs the edges and vectors
        */
        ArtistGraph();
        // ~ArtistGraph();

        /**
        * Computes betweenness centrality by passing in a floyd warshall matrix. 
        * @return - returns the number of shortest paths passed through an artist in that graph. 
        */
        std::vector<centralityGroup> computeBetweennessCentrality();

        /**
        * Computes betweenness centrality by passing in a floyd warshall matrix. 
        * @param int** matrix- a 2d matrix computed from the floydWarshall function
        * @return - returns the number of shortest paths passed through an artist in that graph. 
        */
        std::vector<centralityGroup> computeBetweennessCentrality(int** matrix);

        /**
         * Computes the Floyd-Warshall matrix and uses it to calculate shortest distance between a and b.
         * @param Vertex a - the source vertex
         * @param Vertex b - the destination vertex
         * @return - the value of the shortest distance between verticies a and b.
        */

        int computeShortestPath(Vertex a, Vertex b);
        /**
         * Uses a floyd warshall matrix to compute the shortest distance.
         * @param Vertex a - the source vertex
         * @param Vertex b - the destination vertex
         * @param int** matrix - the computed floydwarshall 2d matrix
         * @return - the value of the shortest distance between verticies a and b.
        */
        int computeShortestPath(Vertex a, Vertex b, int** matrix);

        /** uses dijkstra's algorithm to return a vector of Vertexs
         * @param Vertex a - source vertex
         * @param Vertex b - destination vertex
         * @return - a vector of vertices showing the shortest path of artists from a to b
         */
        std::vector<Vertex> getShortestPath(Vertex a, Vertex b);

        /** Computes the floydWarshall algorithm for shortest path
         * @return - a 2d matrix that has the shortest path of two artists as the intersection of their points. 
         * 
         */
        int** floydWarshall();

    private:
        // The default path to the artist data csv file.
        std::string defaultPath = "../data/artist_data.csv";
};

/**
 * @param v - passed in vector of strings to put into the set
 * @return - a set of strings 
 */
std::set<std::string> convertToSet(std::vector<std::string> v);

/**
 * Creates a 2D matrix of size row x column
 * @param rows - the rows of the table
 * @param columns - the columns of the table
 * @return - the 2d matrix
 */
int** createTable(int rows, int columns);

/**
 * Frees a table with rows number of rows
 * @param rows - the rows of the table
 * @param table - the table to free in memory
 */
void freeTable(int** table, int rows);

/**
 * @param v - the vector of vertices where K is in
 * @param K - the specific vertex we are trying to find in v 
 * @return - the index at which the element is found
 */
int getIndex(vector<Vertex> v, Vertex K);

/**
 * writes the floyd warshall matrix to the output file
 * serializes it to a text file
 * @param outfile - a pointer to the output file 
 * @param arr - the 2d matrix passed in
 * @param rows - the number of rows in the matrix
 * @param cols - the number of columns in the matrix
 * @return - the output file
 */
std::ostream& serialize(std::ostream& outfile, int** arr, int rows, int cols);