#include "triangulationview.h"

void TriangulationView::paint(QPainter* painter) {
    if (!controller_) {
        return;
    }

    painter->save();

    painter->setBrush(Qt::black);
    painter->setRenderHint(QPainter::Antialiasing);

    for (auto& p : controller_->points()) {
        painter->drawEllipse(p.x * width() - 2, p.y * height() - 2, 2, 2);
    }

    for (auto& e : controller_->edges()) {
        painter->drawLine(e.p0.x * width(), e.p0.y * height(), e.p1.x * width(), e.p1.y * height());
    }

    painter->restore();
}

TriangulationController* TriangulationView::model() {
    return controller_;
}

void TriangulationView::setModel(TriangulationController* model) {
    controller_ = model;

    QObject::connect(model, &TriangulationController::updated,
                     this, &QQuickItem::update);

    emit modelChanged();
}
