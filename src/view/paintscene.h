#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class PaintScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit PaintScene(QObject *parent = nullptr);
  ~PaintScene();

 private:
  QPointF previousPoint_;
  void mousePressEvent(QGraphicsSceneMouseEvent *event);
  void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif  // PAINTSCENE_H
