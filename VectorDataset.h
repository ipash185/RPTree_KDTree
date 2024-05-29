/*  
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    __________________________*VectorDataset* : The VectorDataset class__________________________
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    VectorDataset.cpp file contains the implementation of the VectorDataset class, which represents a dataset  of 
    DataVectors (vector<DataVector>). It provides functionality for managing and processing vector datasets, including 
    reading data from CSV files and calculating k-nearest neighbors.

    File Structure:

    - Constructors and Destructors:

        - VectorDataset():
            Description:
                Constructor to initialize an empty dataset.

            Function Explanation:
                - Initializes the dataset vector.

        - ~VectorDataset():
            Description:
                Destructor to handle memory cleanup.

            Function Explanation:
                - Automatically destructs the dataset vector when the object goes out of scope.

        - VectorDataset(const VectorDataset& other):
            Description:
                Copy constructor to create a new VectorDataset as a copy of another.

            Parameters:
                - other: Reference to another VectorDataset to be copied.

            Function Explanation:
                - Initializes the dataset vector with the values of the specified VectorDataset (other).

        - VectorDataset& operator=(const VectorDataset& other):
            Description:
                Copy assignment operator for assigning values from another VectorDataset.

            Parameters:
                - other: Reference to another VectorDataset from which values are assigned.

            Return Type:
                VectorDataset& (Reference to the current object)

            Function Explanation:
                - Checks if the current object is not the same as the specified VectorDataset (other).
                - If different, assigns the dataset vector values from the specified VectorDataset.
                - Allows for chaining of assignments.

    - Member Functions:

        - void setDataset(const vector<DataVector>& d):
            Description:
                Set the dataset vector.

            Parameters:
                - d: Vector of DataVectors containing the dataset.

            Return Type:
                Void

            Function Explanation:
                - Assigns the dataset vector with the specified vector of DataVectors.

        - vector<DataVector> getDataset() const:
            Description:
                Get the dataset vector.

            Parameters:
                None

            Return Type:
                Vector of DataVectors representing the dataset.

            Function Explanation:
                - Returns a copy of the dataset vector.

        - void push_back(const DataVector& d):
            Description:
                Add a DataVector to the dataset.

            Parameters:
                - d: DataVector to be added to the dataset.

            Return Type:
                Void

            Function Explanation:
                - Adds the specified DataVector to the end of the dataset vector.

        - void readCSV(const string& filename):
            Description:
                Reads data from a CSV file into the VectorDataset, populating it with DataVector instances.

            Parameters:
            - filename: Path to the CSV file containing the dataset.

            Return Type:
            Void

            Function Explanation:
            - Attempts to open the specified CSV file using an input file stream (ifstream).
            - Displays an error message and returns if the file cannot be opened.
            - Initializes variables to read each line and row from the CSV file.
            - Skips the header row of the CSV file using getline.
            - Iterates through each line of the CSV file.
            - Initializes a DataVector instance (r) to represent a row in the dataset.
            - Initializes a vector (row) to store the values of the current row.
            - Uses a stringstream (ss) to tokenize the line by commas and extract each cell.
            - Converts each cell to a double and adds it to the row vector.
            - Catches and handles exceptions (invalid_argument and out_of_range) if cell conversion fails.
            - Sets the dimension and vector values for the DataVector instance (r).
            - Checks for consistent dimensions if the dataset is not empty.
            - Adds the DataVector instance to the dataset if it passes validation.
            - Closes the file after reading all lines.

            Note: The function assumes that the CSV file is formatted correctly, and each row has the same number of columns.

        - void printDataset() const:
            Description:
                Print the dataset to the console.

            Parameters:
                None

            Return Type:
                Void

            Function Explanation:
                - Prints the index and values of each DataVector in the dataset to the console.

        - int size() const:
            Description:
                Get the size of the dataset.

            Parameters:
                None

            Return Type:
                Integer representing the number of DataVectors in the dataset.

            Function Explanation:
                - Returns the size of the dataset vector.

        - VectorDataset knearestneighbor(int queryidx, int k):
            Description:
                Calculates the k-nearest neighbors for a given query vector within the VectorDataset.

            Parameters:
            - queryidx: Index of the query vector in the dataset.
            - k: Number of neighbors to retrieve.

            Return Type:
            VectorDataset representing the k-nearest neighbors.

            Function Explanation:
            - Ensures that the requested number of neighbors (k) does not exceed the dataset size.
            - Checks if the specified query index (queryidx) is within the bounds of the dataset.
            - Retrieves the query vector from the dataset.
            - Initializes a vector of pairs to store distances along with corresponding indices.
            - Calculates the Euclidean distance between the query vector and each vector in the dataset.
            - Sorts the distances in ascending order.
            - Creates a new VectorDataset to store the top k nearest neighbors.
            - Populates the result dataset with the corresponding vectors from the original dataset.
            - Returns the result dataset containing the k-nearest neighbors.

            Note: The function utilizes the Euclidean distance calculated by the 'dist' method of the DataVector class. It considers all vectors in the dataset, excluding the query vector itself during the distance calculation.

*/

#ifndef VECTORDATASET_H
#define VECTORDATASET_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "DataVector.h"

using namespace std;

class VectorDataset {
    vector<DataVector> dataset;

    public:
    // Constructors and Destructors-----------------------------------------

    // Constructor to initialize an empty dataset.
    VectorDataset() : dataset() {}

    // Destructor to handle memory cleanup.
    ~VectorDataset() {}

    // Copy constructor to create a new VectorDataset as a copy of another.
    VectorDataset(const VectorDataset& other) : dataset(other.dataset) {}

    // Copy assignment operator for assigning values from another VectorDataset.
    VectorDataset& operator=(const VectorDataset& other) {
        if (this != &other) {
            dataset = other.dataset;
        }
        return *this;
    }

    // Member Functions------------------------------------------------------

    // Set the dataset vector.
    void setDataset(const vector<DataVector>& d) {
        dataset = d;
    }

    // Get the dataset vector.
    const vector<DataVector>& getDataset() const {
        return dataset;
    }

    // Add a DataVector to the dataset.
    void push_back(const DataVector& d) {
        dataset.push_back(d);
    }

    // Read data from a CSV file into a vector of DataVectors.
    void readCSV(const string& filename) {
        ifstream file(filename);

        // Check if the file is open
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Skip the header row

        while (getline(file, line)) {
            DataVector r;
            vector<double> row;
            stringstream ss(line);

            string cell;
            while (getline(ss, cell, ',')) {
                try {
                    double value = stod(cell);
                    row.push_back(value);
                } catch (const invalid_argument& e) {
                    cerr << "Invalid argument in line: " << line << endl;
                } catch (const out_of_range& e) {
                    cerr << "Out of range in line: " << line << endl;
                }
            }

            r.setDimension(row.size());
            r.setVector(row);

            // Check for consistent dimension if the dataset is not empty
            if (dataset.size() != 0) {
                if (dataset[0].getDimension() != r.getDimension()) {
                    cerr << "Inconsistent dimension in line: " << line << endl;
                } else {
                    dataset.push_back(r);
                }
            } else {
                dataset.push_back(r);
            }
        }

        file.close();
    }

    // Print the dataset to the console.
    void printDataset() const {
        int i = 0;
        cout << "Index\t";
        for (int j = 0; j < dataset[0].getDimension(); j++) {
            cout << j << "\t";
        }
        cout << endl;

        for (const DataVector& row : dataset) {
            cout << i << "\t";
            row.printVector();
            i++;
        }
    }

    // Get the size of the dataset.
    int size() const {
        return dataset.size();
    }

    VectorDataset knearestneighbor(int queryidx, int k, const VectorDataset& train);

};



#endif