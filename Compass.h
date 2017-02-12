#ifndef COMPASS_H
#define COMPASS_H

#include <QFrame>
class QwtCompass;

class Compass : public QFrame
{
    Q_OBJECT

public:
    Compass( QWidget *parent = nullptr );
    virtual ~Compass() {}

public slots:
    void setValue(double val);

private:
    QwtCompass *createCompass( int pos );
    QwtCompass *windCompass;
};

#endif // COMPASS_H
