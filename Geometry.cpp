#include <bits/stdc++.h>
using namespace std;

struct point
{
    double x, y;
    point()
    {
    }

    point (double a, double b)
    {
        x = a;
        y = b;
    }
};

struct line
{
    double a, b, c; // a*x + b*y + c = 0
};

struct vec
{
    double x, y;
    vec(double X, double Y)
    {
        x = X;
        y = Y;
    }
};

double dot(vec a, vec b)
{
    return (a.x*b.x + a.y*b.y);
}
double norm_sq(vec v)
{
    return v.x*v.x + v.y*v.y;
}
double dist(point p1, point p2)
{
    return hypot(p1.x-p2.x, p1.y-p2.y);
}
vec scale (vec v, double s)
{
    return vec(v.x*s, v.y*s);
}
point translate (point p, vec v)
{
    return point(p.x + v.x, p.y + v.y);
}
vec toVec (point a, point b)
{
    return vec(b.x-a.x, b.y-a.y);
}

// Returns True if lines are parallel
bool areParallel (line l1, line l2)
{
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

// Returns True if Lines are Same
bool areSame (line l1, line l2)
{
    return areParallel(l1, l2) && (fabs(l1.c-l2.c) < EPS);
}



// Returns true and Saves in point p if lines intersect
bool areIntersect (line l1, line l2, point &p)
{
    if (areParallel(l1, l2)) return false;
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true;
}

// Makes line l1 with two point p1 and p2
void pointsToLine(point p1, point p2, line &l)
{
    if (p1.x == p2.x)   // vertical line is handled nicely here
    {
        l.a = 1.0;
        l.b = 0.0;
        l.c = -p1.x;
    }
    else
    {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}


// Returns Distance from point p to Segment (a, b). c is for storing coordinate on segment and c can be anywhere on "ab" line
double distToline (point p, point a, point b, point &c)
{
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));
    return dist(p, c);
}

// Returns Distance from point p to Segment (a, b). c is for storing coordinate on segment c is exact on "ab" segment
double distToLineSegment (point p, point a, point b, point &c)
{
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0)
    {
        c = point(a.x, a.y);
        return dist(p, a);
    }
    if (u > 1.0)
    {
        c = point(b.x, b.y);
        return dist(p, b);
    }
    return distToline(p, a, b, c);
}
