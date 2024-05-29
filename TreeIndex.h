#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "DataVector.h"

using namespace std;

class TreeIndex
{
protected:
    TreeIndex() {}
    ~TreeIndex() {}

public:
    static TreeIndex &GetInstance();
};