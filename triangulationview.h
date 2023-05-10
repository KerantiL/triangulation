#ifndef TRIANGULATIONVIEW_H
#define TRIANGULATIONVIEW_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QPointF>
#include <QObject>

#include "triangulationcontroller.h"

using Edge = std::pair<QPointF, QPointF>;

class TriangulationView : public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(TriangulationController* model READ model WRITE setModel NOTIFY modelChanged)

public:
    TriangulationView() {};

    void paint(QPainter *painter) override;

    TriangulationController* model();
    void setModel(TriangulationController* model);

signals:
    void modelChanged();

private:
    TriangulationController* controller_ = nullptr;
};

#endif // TRIANGULATIONVIEW_H
