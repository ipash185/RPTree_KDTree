#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>
#include "TreeIndex.h"
#include "VectorDataset.h"
#include "DataVector.h"

using namespace std;
using namespace chrono;

const int MINSIZE = 2;

struct Node
{
    vector<DataVector> v;
    Node* left;
    Node* right;
    double medianval;
    vector<double> axis;
};

class RPTreeIndex : public TreeIndex
{
    Node* root;

    // generate random dimension
    vector<double> randomUnitDirection(size_t dimensions) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(-1.0, 1.0);

        vector<double> direction(dimensions, 0.0);
        double sum = 0.0;
        for (size_t i = 0; i < dimensions; ++i) {
            direction[i] = dis(gen);
            sum += direction[i] * direction[i];
        }
        double norm = sqrt(sum);
        for (size_t i = 0; i < dimensions; ++i) {
            direction[i] /= norm;
        }
        return direction;
    }

    int randomX(int k){
        return rand()%k;
    }

    // initial call to build tree
    Node* buildTree(vector<DataVector>& points)
    {
        if (points.empty())
        {
            return NULL;
        }

        return buildTree(points.begin(), points.end());
    }

    // Overloaded buildTree function for iterators (actual implementation)
    Node *buildTree(vector<DataVector>::iterator begin, vector<DataVector>::iterator end)
    {
        int k = begin->getDimension();
        //Here k is dimension
        vector<double> axis = randomUnitDirection(k);

        if (end - begin <= MINSIZE)
        {
            Node *newnode = new Node;
            newnode->axis = axis;
            newnode->left = NULL;
            newnode->right = NULL;
            newnode->medianval = -1;
            newnode->v = vector<DataVector>(begin, end); // Store the points in leaf nodes
            return newnode;
        }

        DataVector x = *( begin + randomX(end - begin) );

        DataVector y;
        double maxdist = 0;

        for (auto it = begin; it != end; it++)
        {
            double dist = 0;
            dist = (*it)*x;
            if(dist > maxdist){
                maxdist = dist;
                y = *it;
            }
        }

        
        Node *newnode = new Node;
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(-1.0, 1.0);
        double delta = dis(gen)*6*(x.dist(y))/sqrt(k);

        newnode->axis = axis;

        sort(begin, end, [axis](const DataVector &a, const DataVector &b)
             { return a*axis < b*axis; });
             
        auto medianiter = begin + (end - begin) / 2;

        newnode->medianval = *medianiter*axis + delta;
        for(auto it = begin; it != end; it++){
            newnode->v.push_back(*it);
        }
        newnode->left = buildTree(begin, medianiter + 1);
        newnode->right = buildTree(medianiter + 1, end);

        return newnode;
    }
    vector<DataVector> search(const DataVector &point, Node* node, int k=1)
    {
        if (node == NULL)
        {
            return vector<DataVector>();
        }
        if (node->medianval == -1)
        {
            return node->v;
        }

        double compareval = point*(DataVector(node->axis));
        vector<DataVector> nneighbours, sibling;
        Node *temp;
        if (compareval <= node->medianval)
        {
            temp = node->left;
            nneighbours = search(point, node->left,k);
            sibling = node->right->v;
        }
        else
        {
            temp = node->right;
            nneighbours = search(point, node->right,k);
            sibling = node->left->v;
        }

        //if the distance of the given point from the farthest point in the current subtree is less than the perpendicular distance of the given point from the median, then return the left subtree else return the current node
        double maxdist = -1;
        for(auto it = nneighbours.begin(); it != nneighbours.end(); it++)
        {
            if (it->dist(point) > maxdist)
            {
                maxdist = it->dist(point);
            }
        }
        double mediandist = abs(node->medianval - point*(DataVector(temp->axis)));

        if (maxdist > mediandist || nneighbours.size() < k) {
            for (auto it = sibling.begin(); it != sibling.end(); it++)
            {
                nneighbours.push_back(*it);
            }
        }
        return nneighbours;

    }
    RPTreeIndex() : root(nullptr) {}
    static RPTreeIndex *instance;

public:
    static RPTreeIndex *GetInstance()
    {
        if (!instance)
        {
            instance = new RPTreeIndex();
        }
        return instance;
    }

    vector<DataVector> query_search(const DataVector &point, int k)
    {
         return search(point, root, k);
    }

    void maketree(vector<DataVector> &points)
    {
        root = buildTree(points);
    }

    //AddData
    void AddData(DataVector &newpoint, vector<DataVector> &points)
    {
        points.push_back(newpoint);
        maketree(points);
    }

    //DeleteData
    void DeleteData(DataVector &newpoint, vector<DataVector> &points)
    {
        points.erase(remove(points.begin(), points.end(), newpoint), points.end());
        maketree(points);
    }
};
RPTreeIndex *RPTreeIndex::instance = nullptr;

int main()
{    
    string testfilename = "";
    cout<<"Enter only the test filename (location) in a line:\n";
    cin>>testfilename;

    string trainfilename = "";
    cout<<"Enter only the train filename (location) in a line:\n";
    cin>>trainfilename;

    int k = 5;
    cout<<"Enter the value of k:\n";
    cin>>k;

    string outfile;
    cout<<"Enter only the output filename (location) in a line:\n";
    cin>>outfile;
    ofstream file(outfile, ios::app);
    if (file.is_open()) {
    } else {
        cout << "Unable to open file" << endl;
    }
    
    VectorDataset test;
    test.readCSV(testfilename);
    VectorDataset train;
    train.readCSV(trainfilename);
    
    vector<DataVector> myData = train.getDataset();

    RPTreeIndex::GetInstance()->maketree(myData);

    auto start = high_resolution_clock::now();
    for (int i = 0; i < 2; i++) {
        file<<"index of vector: "<<i<<endl;
        auto start2 = high_resolution_clock::now();
        vector<DataVector> smallset = RPTreeIndex::GetInstance()->query_search(test.getDataset()[i], k);

        VectorDataset smalldataset;
        smalldataset.setDataset(smallset);

        VectorDataset d = test.knearestneighbor(i, k, smalldataset);
        auto stop2 = high_resolution_clock::now();
        auto duration2 = duration_cast<milliseconds>(stop2 - start2);
        cout << "Neighbour of vector: " << i << endl;
        d.printDataset();
        file << "Time taken to calculate nearest neighbors: " << duration2.count() << " milliseconds\n\n";
    }
    file.close();

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "\nTotal time taken to calculate nearest neighbors: " << duration.count() << " milliseconds\n\n";


    return 0;
}