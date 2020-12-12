#include <string>
#include <vector>

#include "ArtistGraph.h"
#include "CSVReader.h"

int main() {
  ArtistGraph graph;
  // graph.BFTraversal("Katy Perry");
  Vertex artist1 = "Taylor Swift";
  Vertex artist2 = "Kanye West";
  std::vector<Vertex> v = graph.getShortestPath(artist1, artist2);
  for (const auto& elem : v) {
    std::cout << elem << " -> ";
  }
  std::cout << artist1 << std::endl;
  return 0;
}
