#ifndef BRSPOIRTS_H
#define BRSPOIRTS_H

#include <QPoint>
#include <vector>
#include <cmath>

using namespace std;

class BrsPoints
{
public:
    BrsPoints(){};
    BrsPoints(double x1, double x2, double y1, double y2)
    {
        this-> x10 = x1;
        this->x20=x2;
        this->y10=y1;
        this->y20=y2;
    }

    void setPoints(double x1, double x2, double y1, double y2)
    {
        double movx=0;
        double movy=0;
        bool swapped = 0;
        bool inverted = 0;
        points.clear();
        if(x1==0&&x2==0&&y1==0&&y2==0)
        {
            points.push_back(QPointF(0,0));
            return;
        }
        double sx1,sx2,sy1,sy2;
        if(x1==0&&y1==0&&x2>y2&&y2>0)
        {
            sx1 = x1;
            sy1 = y1;
            sx2 = x2;
            sy2 = y2;
        }
        else if (x2==0&&y2==0&&x1>y1&&y1>0)
        {
            sx1 = x2;
            sy1 = y2;
            sx2 = x1;
            sy2 = y1;
        }
        else
        {
            if(x1<x2)
            {
            movx = 0 -x1;
            movy=0-y1;
            sx1=0;
            sy1=0;
            sx2 = x2-x1;
            sy2 = y2-y1;
            }
            else
            {
            movx = 0 -x2;
            movy=0-y2;
            sx1=0;
            sy1=0;
            sx2 = x1-x2;
            sy2 = y1-y2;
            }

            if(sy2<0)
            {
                inverted =1;
                sy2*=-1;
            }
            if(sx2<sy2)
            {
                swapped =1;
                std::swap(sx2,sy2);
            }


        }

        double realx, realy;
        realx = sx1;
        realy = sy1;
        if(swapped) std::swap(realx,realy);
        if(inverted) realy*=-1;
        realx-=movx;
        realy-=movy;
        points.push_back(QPointF());
        double prevd;
        vector<QPointF> realPoints;
        realPoints.push_back(QPointF(realx,realy));
        for(int i=0;i<sx2;i++)
        {
            QPointF p = points[i];
            double d;
            if(i==0) d = 2* sy2 - sx2;
            else if(prevd>=0) d = prevd+ 2* sy2 - 2*sx2;
            else d = prevd+ 2*sy2;
            prevd = d;
            double deltay;
            if(d<0) deltay =0;
            else deltay =1;
            points.push_back(QPointF(p.x()+1, p.y()+deltay));
            realx =p.x()+1;
            realy = p.y()+deltay;
            if(swapped) std::swap(realx,realy);
            if(inverted) realy*=-1;
            realx-=movx;
            realy-=movy;
            realPoints.push_back(QPointF(realx,realy));
        }
        points = realPoints;

    }

    vector <QPointF> getPoints() {return points;}
private:
    vector<QPointF> points;
    double x10,x20,y10,y20;

};

#endif // BRSPOIRTS_H
