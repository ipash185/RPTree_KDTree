#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "DataVector.h"
#include "VectorDataset.h"

using namespace std;

// Calculate the k-nearest neighbors for a given query vector.
VectorDataset VectorDataset::knearestneighbor(int queryidx, int k, const VectorDataset& train) {
    // Ensure k is within the valid range
    vector<DataVector> traindataset = train.getDataset();
    k = min(k, static_cast<int>(dataset.size()));
    
    // Check if the query index is within the dataset bounds
    if (queryidx >= dataset.size()) {
        cerr << "Invalid query index" << endl;
        return VectorDataset();
    }

    // Retrieve the query vector from the dataset
    DataVector query = dataset[queryidx];
    
    // Vector to store distances and corresponding indices
    vector<pair<double, int>> distances;

    // Calculate distances from the query vector to all vectors in the dataset
    for (int i = 0; i < traindataset.size(); ++i) {
        // Skip the query vector itself
        // if (i == queryidx) {
        //     continue;
        // }
        double distance = query.dist(traindataset[i]);
        distances.push_back({distance, i});
    }

    // Sort the distances in ascending order
    sort(distances.begin(), distances.end());

    // Create a new VectorDataset to store the top k nearest neighbors
    VectorDataset result;

    // Populate the result dataset with the top k nearest neighbors
    cout<<"distances of nearest neighbors"<<endl;
    for (int i = 0; i < k; ++i) {
        int index = distances[i].second;
        result.push_back(traindataset[index]);
        cout<<distances[i].first<<endl;
    }

    return result;
}