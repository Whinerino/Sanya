#include "Class.h"
int main()
{
int size1, size2;
cout << "size vector1: ";
cin >> size1;
CComplexVector1 vector1(size1);
cout << "print elements of vector1 (a+-bi):\n ";
for (int i = 0; i < size1; ++i){cout << "element " << i + 1 << ": ";cin >> vector1[i]; }
cout << "size vector2: ";
cin >> size2;
CComplexVector1 vector2(size2);
cout << "elements of vector2 (a+-bi):\n ";
for (int i = 0; i < size2; ++i){std::cout << "element " << i + 1 << ": ";cin >> vector2[i]; }
CComplexVector1 sum = vector1 + vector2;
CComplexVector1 difference = vector1 - vector2;
const char* filename = "res.txt";
cout << "res sum of diff in res.txt " << filename << endl;
sum.show(filename);
difference.show(filename);
return 0;
}