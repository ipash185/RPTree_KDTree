#include <iostream>
#include <vector>
#include <cmath>
#include "DataVector.h"

using namespace std;

// Constructors and Destructors-----------------------------------------

// Constructor that initializes the vector with a specified dimension.
DataVector::DataVector(int dimension) : v(vector<double>(dimension)) {}

// Constructor that initializes the vector with a vector of values.
DataVector::DataVector(const vector<double>& vec) : v(vec) {}

// Destructor to handle memory cleanup.
DataVector::~DataVector() {}

// Copy constructor to create a new DataVector as a copy of another.
DataVector::DataVector(const DataVector& other) : v(other.v) {}

// Copy assignment operator for assigning values from another DataVector.
DataVector& DataVector::operator=(const DataVector& other) {
    if (this != &other) {
        v = other.v;
    }
    return *this;
}

// Assignment operator for vector<double>: assigns the values of a vector<double> to this DataVector
DataVector& DataVector::operator=(const vector<double>& vec) {
    v = vec;
    return *this;
}

// Setters and Getters--------------------------------------------------

// Set the dimension of the vector.
void DataVector::setDimension(int dimension) {
    v.resize(dimension);
}

// Get the dimension of the vector.
int DataVector::getDimension() const {
    return v.size();
}

// Set the vector values.
void DataVector::setVector(const vector<double>& vec) {
    v = vec;
}

// Get the vector values.
vector<double> DataVector::getVector() const {
    return v;
}

// Mathematical Operations----------------------------------------------

// Vector addition.
DataVector DataVector::operator+(const DataVector& other) const {
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++) {
        result.v[i] = v[i] + other.v[i];
    }
    return result;
}

// Vector subtraction.
DataVector DataVector::operator-(const DataVector& other) const {
    DataVector result(v.size());
    for (int i = 0; i < v.size(); i++) {
        result.v[i] = v[i] - other.v[i];
    }
    return result;
}

// Dot product of two vectors.
double DataVector::operator*(const DataVector& other) const {
    double dot = 0;
    for (int i = 0; i < v.size(); i++) {
        dot += v[i] * other.v[i];
    }
    return dot;
}

// Logical Operators---------------------------------------------------

// Equality operator.
bool DataVector::operator==(const DataVector& other) const {
    return v == other.v;
}

// Utility Functions---------------------------------------------------

// Print the vector values to the console.
void DataVector::printVector() const {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << "\t";
    }
    cout << endl;
}

// Push a double value to the vector.
void DataVector::push_back(const double& value) {
    v.push_back(value);
}

// Calculate the Euclidean norm of the vector.
double DataVector::norm() const {
    return sqrt(operator*(*this));
}

// Calculate the Euclidean distance to another vector.
double DataVector::dist(const DataVector& other) const {
    return (*this - other).norm();
}
