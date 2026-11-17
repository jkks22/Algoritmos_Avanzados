/*
! AI declaration: Claude was used to print the names of the closest points.
Prompt: hey, how can I pass the variables I use in calculateDistance to print them on line 58?
Answer: You can't use p1 and p2 from calculateDistance directly in main: they are local parameters and 
they disappear when the function returns. Also, calculateDistance doesn't know which pair ends up being the minimum. 
Only findTheMin knows that. The solution: pass two variables by reference (Point&) to findTheMin. 
Every time it finds a smaller distance, it saves the pair there. Since they are references, the change reaches main.
And in main, use a pair of general variables for each half and then keep the pair of the half that won
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//? define a class Point to represent a point in 2D space
class Point {
public:
    double x;
    double y;
    char name;
};  

//? it receives 2 points, calculate the distance between them and returns a double
double calculateDistance(Point& p1, Point& p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

//? function to sort points based on their x-coordinate
void sortPointX(vector<Point>& points) {
    for (size_t i = 0; i < points.size(); ++i) {  
        for (size_t j = 0; j < points.size() - 1; ++j) {
            if (points[j].x > points[j + 1].x) {
                swap(points[j], points[j + 1]);
            }
        }
    }
}

//? compares every pair inside one half
//! best1 and best2 came from Claude's idea
double findTheMin(vector<Point>& points, int curr, int next, int end,
     Point& best1, Point& best2, double minDistance = 1000000) {
    //base case: curr is the last point so there are no more pairs
    if (curr >= end - 1) {
        return minDistance;
    }
    //next reached the end, so we move curr one step and start next right after
    if (next == end) {
        return findTheMin(points, curr + 1, curr + 2, end, best1, best2, minDistance);
    }
    //compare the pair (curr, next)
    double currDistance = calculateDistance(points[curr], points[next]);
    if (currDistance < minDistance) {  //check for the min
        minDistance = currDistance;
        best1 = points[curr];  //save the closest pair
        best2 = points[next];
    }
    return findTheMin(points, curr, next + 1, end, best1, best2, minDistance);  //for every point in the vector
}

int main() {
    vector<Point> points = {{2, 4, 'A'}, {1, 1, 'B'}, {2, 3, 'C'}, {3, 1, 'D'}}; //? vector of points

    sortPointX(points);  //sort by x

    int middle = points.size() / 2;  
    int size = points.size();

    Point leftP1, leftP2, rightP1, rightP2;  //! closest pair of each side, now they're "empty"
    double leftMin = findTheMin(points, 0, 1, middle, leftP1, leftP2);   //min of the left side
    double rightMin = findTheMin(points, middle, middle + 1, size, rightP1, rightP2);   //min of the right side

    //! min between both sides, keeping the points 
    double globalMin;
    Point p1, p2;
    if (leftMin < rightMin) {
        globalMin = leftMin;
        p1 = leftP1;
        p2 = leftP2;
    } else {
        globalMin = rightMin;
        p1 = rightP1;
        p2 = rightP2;
    }

    cout << "The minimum distance between the points is " << globalMin << " and is between the points " << p1.name << " " << p2.name << endl;

    return 0;
}