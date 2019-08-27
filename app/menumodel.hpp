#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include <QObject>
#include <QMultiHash>
#include <QPair>

typedef QMultiHash<QString, int> PlayerScoreMap;
typedef QPair<QString, int>      PlayerScore;

class MenuModel : public QObject
{
    Q_OBJECT
public:
    MenuModel();
    ~MenuModel();

signals:
     void updateHighScore(PlayerScoreMap::iterator highScoreIterator,
                          int                      size);

public slots:
     void addRecordToHighScore(PlayerScore newPlayerScore);
     void saveHighScore();

protected:
     PlayerScoreMap m_highScore;
};

#endif // MENUMODEL_HPP
