#ifndef BRCPOINTS_H
#define BRCPOINTS_H

#include <QPoint>
#include <vector>
#include <cmath>

using namespace std;

class BrcPoints
{
public:
   BrcPoints(){};
    BrcPoints(double x, double y, double radius)
    {
        this-> xc = x;
        this->yc=y;
        this->radius=radius;
    }

    double getx() {return xc;}
    double gety() {return yc;}
    double getrad() {return radius;}

    void setPoints(double x0, double y0, double r)
    {
        points.clear();
        double x =0;
        double y=r;
        points.push_back(QPointF(x0+x, y0+y));
        points.push_back(QPointF(x0-x, y0+y));
        points.push_back(QPointF(x0+x, y0-y));
        points.push_back(QPointF(x0-x, y0-y));
        points.push_back(QPointF(x0+y, y0+x));
        points.push_back(QPointF(x0-y, y0+x));
        points.push_back(QPointF(x0+y, y0-x));
        points.push_back(QPointF(x0-y, y0-x));
        while(x<y)
        {
           double dg = (x+1)*(x+1)+y*y-r*r;
           double dd = (x+1)*(x+1)+(y-1)*(y-1)-r*r;
           x+=1;
           if(abs(dd)<abs(dg)) y-=1;
           points.push_back(QPointF(x0+x, y0+y));
           points.push_back(QPointF(x0-x, y0+y));
           points.push_back(QPointF(x0+x, y0-y));
           points.push_back(QPointF(x0-x, y0-y));
           points.push_back(QPointF(x0+y, y0+x));
           points.push_back(QPointF(x0-y, y0+x));
           points.push_back(QPointF(x0+y, y0-x));
           points.push_back(QPointF(x0-y, y0-x));
        }




    }

    vector <QPointF> getPoints() {return points;}
private:
    vector<QPointF> points;
    double xc,yc,radius;

};
#endif // BRCPOINTS_H
