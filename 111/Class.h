#pragma once
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class CVector
{	
public:
    double *v;
    size_t n;
    
    CVector() { SetZero(); }
    CVector(const int &n) { this->n = n; v = new double[this->n]; for(size_t i = 0; i < n; i++) v[i] = 0; }
    CVector(const CVector &rhs) { SetZero(); CopyOnly(rhs); }
    CVector(const char* filename) { SetZero(); loadFromFile(filename); }
    virtual ~CVector() { Clean(); }
    
    static CVector *create(int Type, const double *b, const int &nn);
    
    CVector &operator=(const CVector &rhs) { if(this != &rhs) { Clean(); CopyOnly(rhs); } return *this; }
    CVector &operator=(CVector &&rhs) { if(this != &rhs) { delete[] v; n = rhs.n; v = rhs.v; rhs.SetZero(); } return *this; }
    
    virtual void show(const char *sf) = 0;
    virtual void loadFromFile(const char* filename) = 0;
    double &operator[](size_t i) { return v[i]; }
    const double &operator[](size_t i) const { return v[i]; }
    
    void SetZero() { v = nullptr; n = 0; }
    void Clean() { delete[] v; SetZero(); }
    void CopyOnly(const CVector &rhs) { if(this != &rhs) { v = new double[n = rhs.n]; memcpy(v, rhs.v, n * sizeof(double)); } }
    void CopyOnly(const double *rhs, const int &n) { this->n = n; memcpy(v = new double[this->n], rhs, n * sizeof(double)); }
    
    void saveToFile(const char* filename) const;
};

class CVector0 : public CVector
{
public:
    CVector0() : CVector() {}
    CVector0(const size_t &n) : CVector(n) {}
    CVector0(const double *rhs, const int &n) { CopyOnly(rhs, n); }
    CVector0(const CVector0 &rhs) : CVector(rhs) {}
    CVector0(CVector0 &&rhs) { n = rhs.n; v = rhs.v; rhs.SetZero(); }
    CVector0(const char* filename) : CVector(filename) {}
    
    CVector &operator=(const CVector &rhs) { if(this != &rhs) { Clean(); CopyOnly(rhs); } return *this; }
    CVector &operator=(CVector &&rhs) { if(this != &rhs) { delete[] v; n = rhs.n; v = rhs.v; rhs.SetZero(); } return *this; }
    
    virtual void show(const char *sf);
    virtual void loadFromFile(const char* filename);
};

class CVector1 : public CVector
{
public:
    CVector1() : CVector() {}
    CVector1(const size_t &n) : CVector(n) {}
    CVector1(const double *rhs, const int &n) { CopyOnly(rhs, n); }
    CVector1(const CVector1 &rhs) : CVector(rhs) {}
    CVector1(CVector1 &&rhs) { n = rhs.n; v = rhs.v; rhs.SetZero(); }
    CVector1(const char* filename) : CVector(filename) {}
    
    CVector &operator=(const CVector &rhs) { if(this != &rhs) { Clean(); CopyOnly(rhs); } return *this; }
    CVector &operator=(CVector &&rhs) { if(this != &rhs) { delete[] v; n = rhs.n; v = rhs.v; rhs.SetZero(); } return *this; }
    
    virtual void show(const char *sf);
    virtual void loadFromFile(const char* filename);
};

CVector1 operator+(const CVector &lhs, const CVector &rhs);
CVector1 operator-(const CVector &lhs, const CVector &rhs);
double operator*(const CVector &lhs, const CVector &rhs);

ostream &operator<<(ostream &stream, const CVector &vector);