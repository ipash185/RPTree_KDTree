/*  
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    _____________________________*DataVector* : The DataVector class_____________________________
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    DataVector.cpp file contains the implementation of the DataVector class, which represents a mathematical vector
    in n-dimensional space. It provides functionality for vector operations such as addition, subtraction,
    dot product, Euclidean norm, and distance calculation.

    File Structure:

    - Constructors and Destructors:

        - DataVector(int dimension):
            Description:
                Constructor that initializes the vector with a specified dimension.

            Parameters:
                - dimension: Integer specifying the dimension of the vector.

            Function Explanation:
                - Initializes the vector (v) with a size equal to the specified dimension.

        - DataVector(const vector<double>& vec):
            Description:
                Constructor that initializes the vector with a vector of values.

            Parameters:
                - vec: Reference to a vector of double values.

            Function Explanation:
                - Initializes the vector (v) with the values of the specified vector.

        - ~DataVector():
            Description:
                Destructor to handle memory cleanup.

            Function Explanation:
                - Ensures proper cleanup of dynamically allocated memory.
                - The vector (v) is automatically deallocated when the object goes out of scope.

        - DataVector(const DataVector& other):
            Description:
                Copy constructor to create a new DataVector as a copy of another.

            Parameters:
                - other: Reference to another DataVector to be copied.

            Function Explanation:
                - Initializes the vector (v) with the values of the vector in the specified DataVector (other).

        - DataVector& operator=(const DataVector& other):
            Description:
                Copy assignment operator for assigning values from another DataVector.

            Parameters:
                - other: Reference to another DataVector from which values are assigned.

            Return Type:
                DataVector& (Reference to the current object)

            Function Explanation:
                - Checks if the current object is not the same as the specified DataVector (other).
                - If different, assigns the vector values from the specified DataVector.
                - Allows for chaining of assignments.

        - DataVector& operator=(const vector<double>& vec):
            Description:
                Assignment operator for vector<double>: assigns the values of a vector<double> to this DataVector

            Parameters:
                - vec: Reference to a vector of double values.

            Return Type:
                DataVector& (Reference to the current object)

            Function Explanation:
                - Assigns the vector values from the specified vector (vec).
                - Allows for chaining of assignments.

    - Member Functions:

        - Setters and Getters

            - void setDimension(int dimension):
                Description:
                    Set the dimension of the vector.

                Parameters:
                    - dimension: Integer specifying the new dimension of the vector.

                Return Type:
                    Void

                Function Explanation:
                    - Resizes the vector (v) to the specified dimension.

            - int getDimension() const:
                Description:
                    Get the dimension of the vector.

                Parameters:
                    None

                Return Type:
                    Integer representing the dimension of the vector.

                Function Explanation:
                    - Returns the size of the vector (v), which represents its dimension.

            - void setVector(const vector<double>& vec):
                Description:
                    Set the vector values.

                Parameters:
                    - vec: Reference to a vector of doubles containing the new values.

                Return Type:
                    Void

                Function Explanation:
                    - Assigns the vector (v) with the values from the specified vector (vec).

            - vector<double> getVector() const:
                Description:
                    Get the vector values.

                Parameters:
                    None

                Return Type:
                    Vector of doubles representing the values of the vector.

                Function Explanation:
                    - Returns a copy of the vector (v), containing its values.


        - Mathematical Operations
            - DataVector operator+(const DataVector& other) const:
                Description:
                    Vector addition.

                Parameters:
                    - other: Reference to another DataVector for addition.

                Return Type:
                    DataVector representing the result of the addition.

                Function Explanation:
                    - Initializes a result DataVector with the same dimension.
                    - Adds corresponding elements of the vectors to compute the result.

            - DataVector operator-(const DataVector& other) const:
                Description:
                    Vector subtraction.

                Parameters:
                    - other: Reference to another DataVector for subtraction.

                Return Type:
                    DataVector representing the result of the subtraction.

                Function Explanation:
                    - Initializes a result DataVector with the same dimension.
                    - Subtracts corresponding elements of the vectors to compute the result.

            - double operator*(const DataVector& other) const:
                Description:
                    Dot product of two vectors.

                Parameters:
                    - other: Reference to another DataVector for dot product calculation.

                Return Type:
                    Double representing the dot product.

                Function Explanation:
                    - Initializes a variable (dot) to accumulate the dot product.
                    - Multiplies corresponding elements of the vectors and adds to dot.


        - Logical Operations
            - bool operator==(const DataVector& other) const:
                Description:
                    Comparison operator overloading.

                Parameters:
                    - other: Reference to another DataVector.

                Return Type:
                    Boolean value indicating if the vectors are equal.

                Function Explanation:
                    - Returns true if the vectors are equal, false otherwise.

        - Utility Functions
            - void printVector() const:
                Description:
                    Print the vector values to the console.

                Parameters:
                    None

                Return Type:
                    Void

                Function Explanation:
                    - Iterates through the elements of the vector (v) and prints each to the console.
                    - Values are separated by tabs for better readability.

            - double norm() const:
                Description:
                    Calculate the Euclidean norm of the vector.

                Parameters:
                    None

                Return Type:
                    Double representing the Euclidean norm.

                Function Explanation:
                    - Utilizes the dot product operator to calculate the square of the norm.
                    - Takes the square root to obtain the Euclidean norm.

            - double dist(const DataVector& other) const:
                Description:
                    Calculate the Euclidean distance to another vector.

                Parameters:
                    - other: Reference to another DataVector for distance calculation.

                Return Type:
                    Double representing the Euclidean distance.

                Function Explanation:
                    - Utilizes the subtraction and norm functions to calculate the distance.

*/

#ifndef DATAVECTOR_H
#define DATAVECTOR_H

using namespace std;

class DataVector {
    vector<double> v;
    public:
    DataVector(int dimension=0);
    DataVector(const vector<double>& vec);
    ~DataVector();
    DataVector(const DataVector& other);
    DataVector& operator=(const DataVector& other);
    DataVector& operator=(const vector<double>& vec);
    void setDimension(int dimension=0);
    int getDimension() const;
    void setVector(const vector<double>& vec);
    vector<double> getVector() const;
    DataVector operator+(const DataVector& other) const;
    DataVector operator-(const DataVector& other) const;
    double operator*(const DataVector& other) const;
    bool operator==(const DataVector& other) const;
    void printVector() const;
    void push_back(const double& d);
    double norm() const;
    double dist(const DataVector& other) const;
};

#endif