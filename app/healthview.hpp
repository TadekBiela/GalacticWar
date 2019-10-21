#ifndef HEALTHVIEW_HPP
#define HEALTHVIEW_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QProgressBar>

class HealthView : public QObject
{
    Q_OBJECT
public:
    HealthView();
    virtual ~HealthView();

public slots:
    void update(int value);

protected:
    QGraphicsPixmapItem m_healthGraphic;
    QProgressBar        m_healthBar;
};

#endif // HEALTHVIEW_HPP
