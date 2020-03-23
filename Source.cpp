#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <list>
#include <chrono>
using namespace std;

class Graph {
	public:
		Graph(int numVertices) : adjancencyList(numVertices), visited(numVertices, false), numVisited(0){
		}

		void addEdge(int nodeOne, int nodeTwo) {
			adjancencyList[nodeOne].push_back(nodeTwo);
			adjancencyList[nodeTwo].push_back(nodeOne);
		}

		void DFS() {

		}

		int BFS(int startVertex) {
			//Create a queue to process all of the nodes
			queue<int> nodeQueue;

			//create a variable to hold the largest variable in a series of conencted nodes.
			int biggestSoFar = startVertex;

			nodeQueue.push(startVertex);
			visited[startVertex] = true;
			while (!nodeQueue.empty()) {
				//cout << nodeQueue.front() << endl;
				startVertex = nodeQueue.front();
				if (startVertex > biggestSoFar)
					biggestSoFar = startVertex;
				nodeQueue.pop();

				for (int vertex : adjancencyList[startVertex]) {
					if (visited[vertex] == false) {
						nodeQueue.push(vertex);
						visited[vertex] = true;
						numVisited++;
					}
				}
			}

			//in order to account for subtracting one from the vertex to prevent going out of bounds, add one back to the
			//largest element.
			return biggestSoFar + 1;
		}

		int getNumVertices() const {
			return adjancencyList.size();
		}

		int getNumVerticesVisited() const {
			return numVisited;
		}

		const vector<bool> &getVisited() const {
			return visited;
		}

		void resetVisited() {
			numVisited = 0;
			for (size_t i = 0; i < visited.size(); i++)
				visited[i] = false;
		}
	private:
		int numVisited;
		vector< vector<int> > adjancencyList;
		vector<bool> visited;
};

vector<int> networkSums(int cNodes, vector<int> cFrom, vector<int> cTo) {
	int totalSum = 0;
	vector<int> sums;
	Graph g(cNodes);

	//Processing the entire cFrom/cTo vector
	for (size_t i = 0; i < cFrom.size(); i++){
		//First, we will add an edge from cFrom[i] to cTo[i].
		g.addEdge(cFrom[i] - 1, cTo[i] - 1);

		int stopped = 0;
		for (size_t j = 0; j < g.getNumVertices() /*and g.getNumVerticesVisited() < g.getNumVertices()*/ ; j++){
			stopped++;
			//if a node had been visited already, skip it and move onto the next one.
			if (g.getVisited()[j])
				continue;

	
			int biggest = g.BFS(j);
			cout << "biggest: " << biggest << endl;
			totalSum += biggest;
		}
		cout << "sum at level: " << i << ": " << totalSum << endl;
		sums.push_back(totalSum);
		cout << "stopped at: " << stopped << "\n\n";

		//To prepare for the next BFS on the next node, reset both the totalSum and the visited variables.
		totalSum = 0;
		g.resetVisited(); 
	}

	return sums;
}

int main() {
	auto start = chrono::system_clock::now();
	auto l = networkSums(10, { 1, 2, 1, 4, 5, 8, 9, 10, 7, 2 }, { 2, 3, 3, 5, 6, 9, 6, 8, 4, 8 });
	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end - start;

	cout << "finding network sums took: " << elapsed_seconds.count() << " seconds" << endl;

	cout << "\n\n";
	for (auto num : l)
		cout << num << " ";
}