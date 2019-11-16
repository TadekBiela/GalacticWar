#ifndef GRAPHICSVIEW_HPP
#define GRAPHICSVIEW_HPP

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView();
    GraphicsView(QGraphicsScene* scene, QWidget* parent = nullptr);
    virtual ~GraphicsView();
    void setGraphicsEffects(qreal opacity, qreal blurRadius);
    void startAllItems();
    void stopAllItems();

signals:
    void mousePressed(QMouseEvent* event);
    void mouseReleased(QMouseEvent* event);
    void mouseMoved(QMouseEvent* event);

public slots:
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // GRAPHICSVIEW_HPP
