#ifndef MENUMODEL_HPP
#define MENUMODEL_HPP

#include <QObject>
#include <QMultiHash>
#include <QPair>

typedef QMultiHash<int, QString>           PlayerScoreMap;
typedef QMultiHash<int, QString>::iterator PlayerScoreMapIterator;
typedef QPair<int, QString>                PlayerScore;

class MenuModel : public QObject
{
    Q_OBJECT
public:
    MenuModel();
    ~MenuModel();

signals:
     void updateHighScore(PlayerScoreMapIterator highScoreIterator,
                          int                    size);

public slots:
     void addRecordToHighScore(PlayerScore newPlayerScore);
     void saveHighScore();

protected:
     PlayerScoreMap m_highScore;
};

#endif // MENUMODEL_HPP
