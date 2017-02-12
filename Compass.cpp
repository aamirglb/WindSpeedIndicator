#include <QLayout>
#include <qwt_compass.h>
#include <qwt_compass_rose.h>
#include <qwt_dial_needle.h>

#include "Compass.h"

void Compass::setValue(double val)
{
    windCompass->setValue(val);
}

Compass::Compass(QWidget *parent) :
    QFrame(parent)
{
    QPalette p = palette();
    p.setColor( backgroundRole(), Qt::gray );
    setPalette( p );

    //this->resize(QSize(100, 100));
    setAutoFillBackground( true );

    QHBoxLayout *layout = new QHBoxLayout();
    windCompass = createCompass( 2 );
    layout->addWidget(windCompass);
}

QwtCompass *Compass::createCompass( int pos )
{
    int c;

    QPalette palette0;
    for ( c = 0; c < QPalette::NColorRoles; c++ )
    {
        const QPalette::ColorRole colorRole =
            static_cast<QPalette::ColorRole>( c );

        palette0.setColor( colorRole, QColor() );
    }

    palette0.setColor( QPalette::Base,
        palette().color( backgroundRole() ).light( 120 ) );
    palette0.setColor( QPalette::WindowText,
        palette0.color( QPalette::Base ) );

    QwtCompass *compass = new QwtCompass( this );
    compass->setLineWidth( 4 );
    compass->setFrameShadow(
        pos <= 2 ? QwtCompass::Sunken : QwtCompass::Raised );
    compass->setGeometry(10, 0, 250, 260);
    compass->setStyleSheet("font-weight: bold");
    switch( pos )
    {
        case 0:
        {
            /*
              A compass with a rose and no needle. Scale and rose are
              rotating.
             */
            compass->setMode( QwtCompass::RotateScale );

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose( 16, 2 );
            rose->setWidth( 0.15 );

            compass->setRose( rose );
            break;
        }
        case 1:
        {
            /*
              A windrose, with a scale indicating the main directions only
             */
//            QMap<double, QString> map;
//            map.insert( 0.0, "N" );
//            map.insert( 90.0, "E" );
//            map.insert( 180.0, "S" );
//            map.insert( 270.0, "W" );

            QMap<double, QString> map{ {0.0, "N"}, {90.0, "E"}, {180.0, "S"}, {270.0, "W"} };

            compass->setScaleDraw( new QwtCompassScaleDraw( map ) );

            QwtSimpleCompassRose *rose = new QwtSimpleCompassRose( 4, 1 );
            compass->setRose( rose );

            compass->setNeedle(
                new QwtCompassWindArrow( QwtCompassWindArrow::Style2 ) );
            compass->setValue( 60.0 );
            break;
        }
        case 2:
        {
            /*
              A compass with a rotating needle in darkBlue. Shows
              a ticks for each degree.
             */

            palette0.setColor( QPalette::Base, Qt::darkBlue );
            palette0.setColor( QPalette::WindowText,
                               QColor( Qt::darkBlue ).dark( 120 ) );
            palette0.setColor( QPalette::Text, Qt::white );

            QwtCompassScaleDraw *scaleDraw = new QwtCompassScaleDraw();
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Ticks, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Labels, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, false );
            scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 1 );
            scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 1 );
            scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 3 );

            compass->setScaleDraw( scaleDraw );

            compass->setScaleMaxMajor( 36 );
            compass->setScaleMaxMinor( 5 );

//            compass->setNeedle(
//                new QwtCompassMagnetNeedle( QwtCompassMagnetNeedle::ThinStyle ) );

            compass->setNeedle( new QwtCompassWindArrow( QwtCompassWindArrow::Style2 )
                                /*new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                                true, Qt::white )*/ );

            compass->setValue( 0.0 );
            compass->setReadOnly(true);

            break;
        }
        case 3:
        {
            /*
              A compass without a frame, showing numbers as tick labels.
              The origin is at 220.0
             */
            palette0.setColor( QPalette::Base,
                palette().color( backgroundRole() ) );
            palette0.setColor( QPalette::WindowText, Qt::blue );

            compass->setLineWidth( 0 );

            QMap<double, QString> map;
            for ( double d = 0.0; d < 360.0; d += 60.0 )
            {
                QString label;
                label.sprintf( "%.0f", d );
                map.insert( d, label );
            }

            QwtCompassScaleDraw *scaleDraw =
                new QwtCompassScaleDraw( map );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Ticks, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Labels, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, true );
            scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
            scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 0 );
            scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 3 );

            compass->setScaleDraw( scaleDraw );

            compass->setScaleMaxMajor( 36 );
            compass->setScaleMaxMinor( 5 );

            compass->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                true, Qt::white ) );
            compass->setOrigin( 220.0 );
            compass->setValue( 20.0 );
            break;
        }
        case 4:
        {
            /*
             A compass showing another needle
             */
            QwtCompassScaleDraw *scaleDraw = new QwtCompassScaleDraw();
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Ticks, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Labels, true );
            scaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, false );
            scaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
            scaleDraw->setTickLength( QwtScaleDiv::MediumTick, 0 );
            scaleDraw->setTickLength( QwtScaleDiv::MajorTick, 3 );

            compass->setScaleDraw( scaleDraw );

            compass->setNeedle( new QwtCompassWindArrow( QwtCompassWindArrow::Style2 )
                                /*new QwtCompassMagnetNeedle(
                QwtCompassMagnetNeedle::TriangleStyle, Qt::white, Qt::red )*/ );
            compass->setValue( 220.0 );
            break;
        }
        case 5:
        {
            /*
             A compass with a yellow on black ray
             */
            palette0.setColor( QPalette::WindowText, Qt::black );

            compass->setNeedle( new QwtDialSimpleNeedle( QwtDialSimpleNeedle::Ray,
                false, Qt::yellow ) );
            compass->setValue( 315.0 );
            break;
        }
    }

    QPalette newPalette = compass->palette();
    for ( c = 0; c < QPalette::NColorRoles; c++ )
    {
        const QPalette::ColorRole colorRole =
            static_cast<QPalette::ColorRole>( c );

        if ( palette0.color( colorRole ).isValid() )
            newPalette.setColor( colorRole, palette0.color( colorRole ) );
    }

    for ( int i = 0; i < QPalette::NColorGroups; i++ )
    {
        const QPalette::ColorGroup colorGroup =
            static_cast<QPalette::ColorGroup>( i );

        const QColor light =
            newPalette.color( colorGroup, QPalette::Base ).light( 170 );
        const QColor dark = newPalette.color( colorGroup, QPalette::Base ).dark( 170 );
        const QColor mid = compass->frameShadow() == QwtDial::Raised
            ? newPalette.color( colorGroup, QPalette::Base ).dark( 110 )
            : newPalette.color( colorGroup, QPalette::Base ).light( 110 );

        newPalette.setColor( colorGroup, QPalette::Dark, dark );
        newPalette.setColor( colorGroup, QPalette::Mid, mid );
        newPalette.setColor( colorGroup, QPalette::Light, light );
    }

    compass->setPalette( newPalette );

    return compass;
}
