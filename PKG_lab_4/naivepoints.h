#ifndef NAIVEPOINTS_H
#define NAIVEPOINTS_H

#include <QPoint>
#include <vector>
#include <cmath>
#include <QString>

using namespace std;

class NaivePoints
{
public:
    NaivePoints(){};
    NaivePoints(double x1, double x2, double y1, double y2)
    {
        this-> x10 = x1;
        this->x20=x2;
        this->y10=y1;
        this->y20=y2;
    }

    void setPoints(double x1, double x2, double y1, double y2)
    {
        points.clear();
        double dx = ((double)x2-(double)x1);
        double dy = ((double)y2-(double)y1);
        if(dx == 0 && dy == 0){
            QPointF p;
            p.setX(0);
            p.setY(0);
            this->points.push_back(p);
        }
        else if(qAbs(dx)>=qAbs(dy)){
            double a = dy/dx;
            double x,y;
            if(x1<=x2){
                x = x1;
                y = y1;
            }else{
                x = x2;
                y = y2;
                x2 = x1;
                y2 = y1;
            }
            while(x <= x2){
                QPointF p;
                p.setX(round(x));
                p.setY(round(y));
                points.push_back(p);
                x++;
                y = y + a;
            }

        }else{
            double a = dx/dy;
            double x,y;
            if(y1<=y2){
                x = x1;
                y = y1;
            }else{
                x = x2;
                y = y2;
                x2 = x1;
                y2 = y1;
            }
            while(y <= y2){
                QPointF p;
                p.setX(round(x));
                p.setY(round(y));
                points.push_back(p);
                y++;
                x = x + a;
            }

        }

    }

    vector <QPointF> getPoints() {return points;}
private:
    vector<QPointF> points;
    double x10,x20,y10,y20;


};

#endif // NAIVEPOINTS_H
