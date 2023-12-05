#ifndef DDAPOINTS_H
#define DDAPOINTS_H

#include <QPoint>
#include <vector>
#include <cmath>

using namespace std;

class DdaPoints
{
public:
    DdaPoints(){};
    DdaPoints(double x1, double x2, double y1, double y2)
    {
        this-> x10 = x1;
        this->x20=x2;
        this->y10=y1;
        this->y20=y2;
    }

    void setPoints(double x1, double x2, double y1, double y2)
    {
        points.clear();
        double xstart = round(x1);
        double xend = round(x2);
        double ystart = round(y1);
        double yend = round(y2);
        int l = std::max(abs(xend-xstart), abs(yend-ystart));
        if(l==0)
        {
            points.push_back(QPointF(xstart, ystart));
            return;
        }
        for(int i=1; i<=l+1;i++)
        {
            double x = round(x1+(i-1)*(x2-x1)/l);
            double y = round(y1+(i-1)*(y2-y1)/l);
             points.push_back(QPointF(x, y));
        }

    }

    vector <QPointF> getPoints() {return points;}
private:
    vector<QPointF> points;
    double x10,x20,y10,y20;

};

#endif // DDAPOINTS_H
