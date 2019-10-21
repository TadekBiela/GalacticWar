#ifndef SCOREVIEW_HPP
#define SCOREVIEW_HPP

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QProgressBar>

class ScoreView : public QObject
{
    Q_OBJECT
public:
    ScoreView();
    virtual ~ScoreView();

public slots:
    void update(int value);

protected:
    QGraphicsPixmapItem m_scoreGraphic;
    QProgressBar        m_scoreBar;
};

#endif // SCOREVIEW_HPP
