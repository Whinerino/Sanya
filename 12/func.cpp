#include "Class.h"

void CVector::saveToFile(const char* filename) const
{
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    file << n << endl;
    for (size_t i = 0; i < n; i++) {
        file << v[i] << " ";
    }
    file << endl;
    file.close();
}

void CVector0::show(const char *sf)
{
    if (sf)
    {
        ofstream outputFile;
        outputFile.open(sf, ios::out | ios::app);
        if (!outputFile) {
            cout << "Error opening file!" << endl;
            return;
        }
        outputFile << "{" << endl;
        for (size_t i = 0; i < n; i++)
        {
            outputFile << v[i] << endl;
        }
        outputFile << "}" << endl;
        outputFile.close();
    }
}

void CVector1::show(const char *sf)
{
    if (sf)
    {
        ofstream outputFile;
        outputFile.open(sf, ios::out | ios::app);
        if (!outputFile) {
            cout << "Error opening file!" << endl;
            return;
        }
        outputFile << "{ ";
        for (size_t i = 0; i < n; i++)
        {
            outputFile << v[i] << ", ";
        }
        outputFile << "}" << endl;
        outputFile.close();
    }
}

void CVector0::loadFromFile(const char* filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    Clean();
    file >> n;
    v = new double[n];
    
    for (size_t i = 0; i < n; i++) {
        file >> v[i];
    }
    file.close();
}

void CVector1::loadFromFile(const char* filename)
{
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file for reading!" << endl;
        return;
    }
    
    Clean();
    file >> n;
    v = new double[n];
    
    for (size_t i = 0; i < n; i++) {
        file >> v[i];
    }
    file.close();
}

CVector1 operator+(const CVector &lhs, const CVector &rhs)
{
    if (lhs.n > rhs.n)
    {
        CVector1 result(lhs.n);
        for (size_t i = 0; i < rhs.n; i++) {
            result.v[i] = lhs[i] + rhs[i];
        }
        for (size_t i = rhs.n; i < lhs.n; i++) {
            result.v[i] = lhs[i];
        }
        return result;
    }
    else
    {
        CVector1 result(rhs.n);
        for (size_t i = 0; i < lhs.n; i++) {
            result.v[i] = lhs[i] + rhs[i];
        }
        for (size_t i = lhs.n; i < rhs.n; i++) {
            result.v[i] = rhs[i];
        }
        return result;
    }
}

CVector1 operator-(const CVector &lhs, const CVector &rhs)
{
    if (lhs.n > rhs.n)
    {
        CVector1 result(lhs.n);
        for (size_t i = 0; i < rhs.n; i++) {
            result.v[i] = lhs[i] - rhs[i];
        }
        for (size_t i = rhs.n; i < lhs.n; i++) {
            result.v[i] = lhs[i];
        }
        return result;
    }
    else
    {
        CVector1 result(rhs.n);
        for (size_t i = 0; i < lhs.n; i++) {
            result.v[i] = lhs[i] - rhs[i];
        }
        for (size_t i = lhs.n; i < rhs.n; i++) {
            result.v[i] = -rhs[i];
        }
        return result;
    }
}

double operator*(const CVector &lhs, const CVector &rhs)
{
    double result = 0;
    size_t minSize = (lhs.n < rhs.n) ? lhs.n : rhs.n;
    for (size_t i = 0; i < minSize; i++) {
        result += lhs[i] * rhs[i];
    }
    return result;
}

CVector *CVector::create(int Type, const double *b, const int &nn)
{
    CVector *t;
    if (Type == 1) {
        t = new CVector0(b, nn);
        return t;
    }
    else {
        t = new CVector1(b, nn);
        return t;
    }
}

ostream &operator<<(ostream &stream, const CVector &vector)
{
    stream << "{ ";
    for (size_t i = 0; i < vector.n; i++) {
        stream << vector.v[i] << " ";
    }
    stream << "}";
    return stream;
}