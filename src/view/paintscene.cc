#include "paintscene.h"

PaintScene::PaintScene(QObject *parent) : QGraphicsScene(parent) {}

PaintScene::~PaintScene() {}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  addEllipse(event->scenePos().x() - 22, event->scenePos().y() - 22, 44, 44,
             QPen(Qt::white), QBrush(Qt::white));
  previousPoint_ = event->scenePos();
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
  addLine(previousPoint_.x(), previousPoint_.y(), event->scenePos().x(),
          event->scenePos().y(),
          QPen(Qt::white, 44, Qt::SolidLine, Qt::RoundCap));
  previousPoint_ = event->scenePos();
}
