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
// Pre Code For Geometry


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
