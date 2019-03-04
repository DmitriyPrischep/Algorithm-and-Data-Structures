#include <iostream>
#include <math.h>
#include <assert.h>

using namespace std;

class Point
{
public:
    int X;
    int Y;
    Point() {X = 0; Y = 0;}
};


double square(const Point* polygon, const int size){
    assert(size > 0);
    double result = 0;
    for(int i = 0; i < size; i++){
        Point p1 = i ? polygon[i-1] : polygon[size - 1];
        Point p2 = polygon[i];

        result += (p1.X + p2.X) * (p1.Y - p2.Y);
    }
    return fabs(result) /2;
}

int main()
{
    int n = 0;
    cin >> n;
    if(n < 1)
        return 0;

    Point* array = new Point[n];

    for(int i = 0; i < n; i++){
        Point p;
        cin >> p.X >> p.Y;
        array[i] = p;
    }

    cout << square(array, n);
    return 0;
}
