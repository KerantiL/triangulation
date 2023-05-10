#ifndef TRIANGULATIONCONTROLLER_H
#define TRIANGULATIONCONTROLLER_H

#include "delaunay.h"
#include <vector>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <random>
#include <QDebug>

using namespace delaunay;

class TriangulationController: public QObject
{
    Q_OBJECT
public:
    TriangulationController();

    const std::vector<Point<double>>& points();
    const std::vector<Edge<double>>& edges();

    Q_INVOKABLE void addPoint(double x, double y);
    Q_INVOKABLE void randomizePoints(int size);
    Q_INVOKABLE void clear();
    Q_INVOKABLE void openFromFile(const QString& url);
    Q_INVOKABLE void saveToFile(const QString& url);

signals:
    void updated();

private:
    void supRandomizePoints(double x, double y, double width, double height, double size, bool isHorizontalDelimiter);

    std::vector<Point<double>> points_;
    Delaunay<double> triangulation_;
    double width_;
    double height_;
    std::mt19937 randGenerator_;
};
#endif // TRIANGULATIONCONTROLLER_H
