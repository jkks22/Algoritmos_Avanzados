#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//! define a class Point to represent a point in 2D space
class Point {
public:
    double x;
    double y;
};  

//! function to calculate the distance between two points
double calculateDistance(vector<Point> p) {
    double distance = 0.0;
    if (p.size() <= 1) {
        return distance;
    } 
    return sqrt(pow(p[1].x - p[0].x, 2) + pow(p[1].y - p[0].y, 2));
}

//! function to sort points based on their x-coordinate
void sortPointX(vector<Point>& points) {
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < points.size() - 1; ++j) {
            if (points[j].x > points[j + 1].x) {
                swap(points[j], points[j + 1]);
            }
        }
    }
}

//! function to split the array of points into two halves
vector<Point> halfArrayL(vector<Point>& points) {
    vector<Point> left(points.begin(), points.begin() + points.size() / 2);

    cout << "Left half of the array:" << endl;
    for (const auto& p : left) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }           

    return left;
}

//! function to split the array of points into two halves
vector<Point> halfArrayR(vector<Point>& points) {
    
    vector<Point> right(points.begin() + points.size() / 2, points.end());

    cout << "Right half of the array:" << endl;
    for (const auto& p : right) {
        cout << "(" << p.x << ", " << p.y << ")" << endl;
    }           

    return right;

}


int main() {
    vector<Point> points = {{2, 4}, {1, 1}, {2, 3}, {3, 1}}; //? vector of points
    int val1, val2;

    vector<Point> left = halfArrayL(points);
    vector<Point> right = halfArrayR(points);

    sortPointX(left);
    sortPointX(right);

    val1 = calculateDistance(left, left);
    val2 = calculateDistance(right, right);

    return 0;
}