#ifndef LABEL_HPP
#define LABEL_HPP

#include <QLabel>
#include <QString>
#include <QWidget>

class Label : private QLabel
{
public:
    Label(const QString& text, QWidget* parent);
    virtual ~Label() {}
    void    setPosition(int x, int y);
    void    setSize(int width, int height);
    void    setAlignment(Qt::AlignmentFlag alignment);
    void    setFontSizeInPx(int fontSize);
    void    setText(QString text);
    QString getText();
    void    show();
    void    hide();
};

#endif // LABEL_HPP
