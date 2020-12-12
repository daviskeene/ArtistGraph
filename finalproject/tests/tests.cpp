#include <string>
#include <vector>

#include "../catch/catch.hpp"
// #include "../readFromFile.hpp"

#include "../ArtistGraph.h"
#include "../CSVReader.h"

// Universal Graph
ArtistGraph ag;
int** floydWarshallMatrix = ag.floydWarshall();

TEST_CASE("Get Shortest Path") {
  std::vector<Vertex> v = ag.getShortestPath("Kid Cudi", "Future");
  REQUIRE(v[0] == "Future");
  REQUIRE(v[1] == "Meek Mill");
}

TEST_CASE("Verify that appropriate artists are loaded into the graph.") {
  REQUIRE(ag.vertexExists("Adele")); // Check if Adele is loaded
  REQUIRE(!ag.vertexExists("Barack Obama")); // Check that Obama is not
  REQUIRE(ag.edgeExists("Adele", "Sia")); // Check that the similar artist connections are working
  REQUIRE(ag.getVertices().size() == 738); // Require that there are 738 artists in the graph
}

TEST_CASE("Make sure that Floyd-Warshall Algorithm works") {
  std::vector<Vertex> verts = ag.getVertices();
  int adeleIndex = getIndex(verts, "Adele");
  int siaIndex = getIndex(verts, "Sia");
  REQUIRE(floydWarshallMatrix[adeleIndex][siaIndex] == 8);
  REQUIRE(floydWarshallMatrix[adeleIndex][adeleIndex] == 0);
}

// TEST_CASE("Check that shortest paths exist between artists") {
//   int shortestPath = ag.computeShortestPath("Troye Sivan", "Dillon Francis", floydWarshallMatrix);
//   std::cout << shortestPath << std::endl;
// }

TEST_CASE("Test write matrix to text file") {
  const int n = ag.getVertices().size();
  std::ofstream outputfile;
  outputfile.open("matrix.txt");
  serialize(outputfile, floydWarshallMatrix, n, n);
  outputfile.close();
  std::ifstream f("matrix.txt");
  REQUIRE(f.good());
}

// This is computationally expensive, only run if you want to re-compute centralities.
// TEST_CASE("Betweenness Centrality Checks") {
//   std::vector<ArtistGraph::centralityGroup> v = ag.computeBetweennessCentrality(floydWarshallMatrix);
//   for (const ArtistGraph::centralityGroup group : v) {
//     if (group.name == "Bruno Mars") {
//       REQUIRE(group.centrality == 15021);
//     }
//   }
// }

TEST_CASE("Breadth First Traversal") {
  std::cout << ag.getVertices().size() << std::endl;
  std::vector<Vertex> traversal = ag.BFTraversal("Katy Perry");
  REQUIRE(traversal[0] == "Katy Perry");
  REQUIRE(traversal[traversal.size() - 1] == "Ski Mask The Slump God");
}

TEST_CASE("Free Table") {
  freeTable(floydWarshallMatrix, ag.getVertices().size());
}