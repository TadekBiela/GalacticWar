#ifndef GRAPHICSVIEW_HPP
#define GRAPHICSVIEW_HPP

#include <QGraphicsView>
#include <QWidget>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QWidget* displayWidget);
    virtual ~GraphicsView();
    virtual void setGraphicsEffects(qreal opacity, qreal blurRadius);
    virtual void startAllItems() = 0;
    virtual void stopAllItems() = 0;

public slots:
    virtual void activate() = 0;
    virtual void deactivate() = 0;

protected:
    QGraphicsScene m_scene;
};

#endif // GRAPHICSVIEW_HPP
