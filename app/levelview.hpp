#ifndef LEVELVIEW_HPP
#define LEVELVIEW_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QLabel>

class LevelView : public QObject
{
    Q_OBJECT
public:
    LevelView();

public slots:
    void update(int value);

protected:
    QGraphicsPixmapItem m_levelGraphic;
    QLabel              m_levelLabel;
};

#endif // LEVELVIEW_HPP
