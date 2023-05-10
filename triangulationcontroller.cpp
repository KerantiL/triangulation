#include "triangulationcontroller.h"

TriangulationController::TriangulationController()
{
    points_.reserve(0);
    randomizePoints(0);
}

void TriangulationController::randomizePoints(int size) {
    points_ = std::vector<Point<double>>{};
    points_.reserve(size);
    supRandomizePoints(0, 0, 1, 1, points_.capacity(), true);
    triangulation_ = triangulate(points_);
    emit updated();
}

void TriangulationController::clear()
{
    points_ = std::vector<Point<double>>{};
    triangulation_ = triangulate(points_);
    emit updated();
}

void TriangulationController::openFromFile(const QString& url)
{
    QFile file(url.right(url.size() - 7));

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        points_ = std::vector<Point<double>>{};

        while (!stream.atEnd()) {
            auto res = stream.readLine().split(" ");
            points_.push_back({res[0].toDouble(), res[1].toDouble()});
        }

        triangulation_ = triangulate(points_);
        emit updated();
    } else {
        qDebug() << file.errorString();
    }

    file.close();
}

void TriangulationController::saveToFile(const QString &url)
{
    QFile file(url.right(url.size() - 7));

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        for (auto i : points_) {
            stream << i.x << " " << i.y << "\n";
        }
    } else {
        qDebug() << file.errorString();
    }

    file.close();
}

void TriangulationController::supRandomizePoints(
    double x,
    double y,
    double width,
    double height,
    double size,
    bool isHorizontalDelimiter
) {
    std::uniform_real_distribution<> widthDis(x, x + width);
    std::uniform_real_distribution<> heightDis(y, y + height);

    if (size == 0) {
        return;
    } else if (size == 1) {
        points_.push_back({widthDis(randGenerator_), heightDis(randGenerator_)});
        return;
    }

    auto firstPart = std::ceil(size / 2.0);

    if (isHorizontalDelimiter) {
        supRandomizePoints(x, y, width, height / 2, firstPart, !isHorizontalDelimiter);
        supRandomizePoints(x, y + height / 2, width, height / 2, size - firstPart, !isHorizontalDelimiter);
    } else {
        supRandomizePoints(x, y, width / 2, height, firstPart, !isHorizontalDelimiter);
        supRandomizePoints(x + width / 2, y, width / 2, height, size - firstPart, !isHorizontalDelimiter);
    }
}

const std::vector<Point<double>>& TriangulationController::points()
{
    return points_;
}

const std::vector<Edge<double>>& TriangulationController::edges()
{
    return triangulation_.edges;
}

void TriangulationController::addPoint(double x, double y)
{
    points_.push_back({x, y});
    triangulation_ = triangulate(points_);
    emit updated();
}
