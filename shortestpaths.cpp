/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Marjan Chowdhury
 * Description : Solves the all pairs shortest path problem with floyd's algorithm.
 ******************************************************************************/

/*
- Read text file with initial distance matrix for graph = W = D0
	- First line in the file is an int between 1 and 26, represents # of vertices in graph (also # of rows and collumns of our matrix)
	- Each following line: 1) start vertex (column), 2) end vertex (row), 3) the weight of the edge connecting the two vertices // THIS SUGGESTS WEIGHTED GRAPH
*/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <iomanip>  


using namespace std;

unsigned short int numSpaces(string input) { // need this for checking the number of elements on each line. numElements = numSpaces + 1
	// returns the number of space character in a given string
	unsigned short int spaces = 0;
	for (unsigned short int i = 0; i < input.size(); ++i) {
		if (input[i] == ' ') {
			++spaces;
		}
	}
	return spaces;
}

void cerrLine(string line) {
	// cerrs all characters in a string besides newline characters
	for (unsigned int i = 0; i < line.size(); ++i) {
		if (int(line[i]) != 10 && int(line[i]) != 13) {
			cout << line[i];
		}
	}
}

/*
Returns the character count in a base 10 representation of a number
*/
int len(long int input) {
	if (input == 0) {
		return 1;
	}
	else if (input < 0) {
		return 1 + len(-input);
	}
	else {
		// return the floor of (one plus log base 10 of input)
		return floor(1 + log10(input));
	}
}

void printMatrix(vector<vector<long int>> matrix, int numVertices, string label, bool use_letters = false) {
	cout << label << endl;
	// we need the max value to determine the max width
	long int max_val = 0;
	for (int i = 0; i < numVertices; i++) {
		for (int j = 0; j < numVertices; j++) {
			long int cell = matrix[i][j];
			if (cell != -1 && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	//int max_cell_width = use_letters ? len(max_val) : len(max(static_cast<long>(numVertices), max_val)); 
	int max_cell_width;
	if (use_letters) {
		max_cell_width = len(max_val);
	}
	else {
		max_cell_width = len(max(static_cast<long>(numVertices), max_val));
	}
	cout << ' ';
	for (int j = 0; j < numVertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < numVertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < numVertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == -1) {
				cout << "-";
			}
			else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			}
			else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<long int>> createMatrix(int numVertices, bool zeroDiagonals) {
	// infinity will be -1
	vector<vector<long int>> matrix(numVertices);
	for (int i = 0; i < numVertices; ++i) {
		matrix[i] = vector<long int>(numVertices);
	}
	for (int i = 0; i < numVertices; ++i) {
		for (int j = 0; j < numVertices; ++j) {
			if (i == j && zeroDiagonals) {
				matrix[i][i] = 0;
			}
			else {
				matrix[i][j] = -1;
			}
		}
	}
	return matrix;
}
void printpath(vector<vector<long int>> distanceMatrix, vector<vector<long int>> pathlengthMatrix, vector<vector<long int>> intermediateMatrix){
	for(size_t i = 0; i < distanceMatrix.size(); ++i){
		for(size_t j = 0; j < distanceMatrix.size(); ++j){
			int ii = i;
			int lookingfor;
			vector<int> intermediates;
			if(i !=j){
				if (pathlengthMatrix[i][j] == -1) {
					cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: infinity, path: none";
				}
				else {
					cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: " << pathlengthMatrix[i][j] << ", path: " << static_cast<char>(i + 'A');
					long int letter = intermediateMatrix[i][j];
					while (letter != -1){
						if (intermediateMatrix[ii][letter] != -1) {
							bool wild = false;
							while (intermediateMatrix[ii][letter] != -1) {
								lookingfor = letter;
								wild = true;
								intermediates.push_back(letter);
								letter = intermediateMatrix[ii][letter];
							}
							if (wild) {
								if (intermediateMatrix[letter][lookingfor] != -1) {
									intermediates.push_back(intermediateMatrix[letter][lookingfor]);
								}
							}
						}
						else {
							if (find(intermediates.begin(), intermediates.end(), letter) == intermediates.end()) {
								cout << " -> " << static_cast<char>(letter + 'A');
							}
							letter = intermediateMatrix[letter][j];
							ii = letter;
						}
					}
					for (int i = intermediates.size() - 1; i >= 0; --i) {
						cout << " -> " << static_cast<char>(intermediates[i] + 'A');
					}
					cout << " -> " << static_cast<char>(j + 'A');
				}
				
			}
			else {
				cout << static_cast<char>(i + 'A') << " -> " << static_cast<char>(j + 'A') << ", distance: " << pathlengthMatrix[i][j] << ", path: " << static_cast<char>(i + 'A');
			}
			cout << endl;
		}
	}
}

	int main(int argc, char *argv[])
{
	// Checking for no command line arguments or too many command line arguments:
	if (argc != 2) {
		cerr << "Usage: ./shortestpaths <filename>" << endl; // Should this be cerr? should it instead throw an error? should it be cout?
		return 1;
	}

	// reading in file:
	ifstream inFile; // ifstream for reading the file
	istringstream input; // stringstream for parsing command line input representing file name
	input.str(argv[1]);
	string matrixFile;
	input >> matrixFile; // could something go wrong here? should we put this in a if loop? try to break it. Make the commandline arg something that can't be put in a string.
	inFile.open(matrixFile);
	if (!inFile) {
		cerr << "Error: Cannot open file '" << matrixFile << "'.";
		return 1;
	}
	
	// reading in the first line
	string thisLine;
	getline(inFile, thisLine);
	int numvertices;
	
	// assert validity of first line
	if (!(istringstream(thisLine) >> numvertices)) {
		cerr << "Error: Invalid number of vertices '";
		cerrLine(thisLine);
		cerr << "' on line 1." << endl;
		return 1;
	}

	// assert numvertices between 1 and 26
	if (numvertices < 1 || numvertices > 26) {
		cerr << "Error: Invalid number of vertices '" << numvertices << "' on line 1.";
		return 1;
	}

	int maxAsciiCode = 64 + numvertices; // this is the max ascii code a vertex can have. If we have 2 vertices, our vertices can only be called 'A', 65, and 'B', 66	

	// creating and initializing the matrixes
	vector<vector<long int>> distanceMatrix = createMatrix(numvertices, true);
	vector<vector<long int>> pathlengthMatrix = createMatrix(numvertices, true);
	vector<vector<long int>> intermediateMatrix = createMatrix(numvertices, false);


	// parsing each subsequent line
	int currentLine = 2;
	string prevLine = thisLine;
	getline(inFile, thisLine);
	while (thisLine != prevLine && !inFile.eof()) {
		// assert line has three components:
		if (numSpaces(thisLine) != 2) {
			cerr << "Error: Invalid edge data '";
			cerrLine(thisLine);
			cerr << "' on line " << currentLine << "." << endl;
			return 1;
		}

		// assert starting vertex is in range
		// ascii code for A = 65, Z = 90
		// Max ascii code of vertices = 64 + numvertices
		int fromIndex = int(thisLine[0]);
		if (fromIndex < 65 || fromIndex > maxAsciiCode) {
			cerr << "Error: Starting vertex '";
			int i = 0;
			while (thisLine[i] != ' ') {
				cerr << thisLine[i++];
			}
			cerr << "' on line " << currentLine << " is not among valid values A-";
			cerr << char(maxAsciiCode) << "." << endl;
			return 1;
		}
		fromIndex -= 65;

		// assert ending vertex is in range
		int toIndex = int(thisLine[2]);
		if (toIndex < 65 || toIndex > maxAsciiCode) {
			cerr << "Error: Ending vertex '";
			int i = 2;
			while (thisLine[i] != ' ') {
				cerr << thisLine[i++];
			}
			cerr << "' on line " << currentLine << " is not among valid values A-";
			cerr << char(maxAsciiCode) << "." << endl;
			return 1;
		}
		toIndex -= 65;

		// assert edge weight is positive intiger
		stringstream ews; // Edge Weight Stream, a stringstream for building a string that is just the edge weight
		stringstream ews2;
		for (unsigned int i = 4; i < thisLine.size(); ++i) {
			ews << thisLine[i];
			ews2 << thisLine[i];
		}
		int edgeWeight;
		if (!(ews >> edgeWeight)) {
			string weight;
			ews2 >> weight;
			cerr << "Error: Invalid edge weight '" << weight << "' on line " << currentLine << "." << endl;
			return 1;
		} else if (edgeWeight <= 0 ) {
			cerr << "Error: Invalid edge weight '" << edgeWeight << "' on line " << currentLine << "." << endl;
			return 1;
		}

		// add the edge to the distanceMatrix
		distanceMatrix[fromIndex][toIndex] = edgeWeight;
		pathlengthMatrix[fromIndex][toIndex] = edgeWeight;

		// advance to next line
		prevLine = thisLine;
		getline(inFile, thisLine);
		currentLine++;
	}

	pathlengthMatrix = distanceMatrix;

	// performing Floyd's Algorithm
	for (int k = 0; k < numvertices; ++k) {
		for (int i = 0; i < numvertices; ++i) {
			for (int j = 0; j < numvertices; ++j) {
				if (!(k == 0 && (i == 0 || j == 0))) {
					if (pathlengthMatrix[i][j] == -1) {
						if (pathlengthMatrix[i][k] != -1 && pathlengthMatrix[k][j] != -1) {
							pathlengthMatrix[i][j] = pathlengthMatrix[i][k] + pathlengthMatrix[k][j];
							intermediateMatrix[i][j] = k;
						}
					}
					else if (pathlengthMatrix[i][k] != -1 && pathlengthMatrix[k][j] != -1) {
						if ((pathlengthMatrix[i][k] + pathlengthMatrix[k][j]) < pathlengthMatrix[i][j]) {
							pathlengthMatrix[i][j] = pathlengthMatrix[i][k] + pathlengthMatrix[k][j];
							intermediateMatrix[i][j] = k;

						}
					}
				}
			}
		}
	}

	printMatrix(distanceMatrix, numvertices, "Distance matrix:");
	printMatrix(pathlengthMatrix, numvertices, "Path lengths:");
	printMatrix(intermediateMatrix, numvertices, "Intermediate vertices:", true);
	printpath(distanceMatrix, pathlengthMatrix, intermediateMatrix); 
	return 0;
}
