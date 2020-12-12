## NETID's cf8-thomasg3-wfoster3-davisk2

# Spotify Artist Graph: Modeling the Connection Between Artists on Spotify

Spotify as a platform is becoming way more than just a streaming service. Over the past few years, Spotify
is one of the leading data platforms for musical signal processing, and with that additional manpower comes metrics
and insights that are helpful for music and artist discovery. One of these features that Spotify offers is the idea of
"related artists", to give people artist recommendations if they are enjoying one musician's songs.

Artists on Spotify are related by their genres, and what listeners of one artist are also listening to. We aren't sure how
related ariststs are actually calculated, but we do know that every artist has related artists. In this way, we can imagine
Spotify Related Artists as a Network Graph, with edges that connect artists of a similar genre.

Using this information, we can download Spotify Artist data from Spotify and model it as a connected graph. With this in mind, we can
perform algorithms and analysis on the data to answer some of the following questions:

1. What is the shortest path between two artists?
2. Which artists have the most shortest paths that go between them (signifies musical diversity)?
3. How can we traverse the network graph by genre, visiting related artists one at a time going from one end of the musical spectrum to another?

Our final project attempts to answer these ideas and more!

## Loading the Data
The Data that we gathered is pulled directly from the Spotify API. Davis wrote some python code to pull artist and related artist data into a CSV,
and we read this CSV when creating a default `ArtistGraph`. There is an ArtistGraph constructor that takes in a filepath, just in case someone has
a larger dataset for related artists.

This data is parsed by `CSVReader`, a class that we had to create in order to read artist data. This `CSVReader` contains generic methods for parsing any type of CSV,
and methods that are specifically designed to pull artist data based on the format of the data.

`ArtistGraph` is a sub-class of `Graph`, the same class from `lab_ml`. `ArtistGraph` contains methods and constructors that are used to carry out the algorithms below.
The edges of an ArtistGraph are weighted based on the number of different genres between two artists (so, if two artists have many genres in common, they will be 'closer' than
artists with many genres that differ).

## Algorithms
Now that we have the data loaded, we can do things with it! After talking with the team (and with superior leadership from @gcevans), we were able to come up with a few different
ideas for things we wanted to do with the data.

1. Djikstra's Algorithm for computing the shortest path between two artists.
2. Betweenness Centrality for finding the number of shortest paths that pass between nodes (to determine musical diversity and connections).
3. A Breadth First Search of the Graph to traverse similar artists first, and then slowly traverse the graph to artists of increasingly different genres.

## Process
To coordinate all of our efforts, we used Trello and Google Docs to track the status of initiatives, as well as our [DEVELOPMENT](https://github-dev.cs.illinois.edu/cs225-fa20/cf8-thomasg3-wfoster3-davisk2/blob/master/DEVELOPMENT.md) doc.

For communication, we made an iMessage group chat and hosted Zoom calls every other day to make sure that we were making appropriate progress.

## Running the Code
To run the code, first change directories to the `finalproject` folder:

`cd finalproject/`

Afterwards, you can run two different `make` commands to hit two different targets:

- `make test && ./test` will make and run all test cases (this is mostly for the devleopers)

- `make finalproj && ./finalproj` will make and run a demonstration of the `ArtistGraph` and its methods. Namely, you can save a Breadth First Traversal from an artist of your choosing.