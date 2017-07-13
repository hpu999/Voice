#include "a_scan_scene.h"

#include <QPainter>

AscanScene::AscanScene(Qt::Orientation orientation, QObject *parent) :
    QGraphicsScene(parent),
    m_color("#ffff77"),
    m_orientation(orientation)
{

}

QPainterPath AscanScene::wave_path(const QByteArray &wave, int w, int h)
{
    QPainterPath path;

    float xRatio1 = 1.0;
    float xRatio2 = 1.0;
    float yRatio = h / 255.0;

    int drawPoints = 0;
    if ( wave.size() < w) {
        xRatio1 = w / 1.0 / wave.size();
        drawPoints = wave.size();
    } else {
        xRatio2 = wave.size() / 1.0 / w;
        drawPoints = w;
    }

    for (int i = 0; i < drawPoints; ++i) {
        path.lineTo( i*xRatio1,
                     ((quint8)(wave.at((int)(i*xRatio2)))) * yRatio + 0.5);
    }

    return path;
}

void AscanScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (m_orientation == Qt::Horizontal) {
        painter->translate(0, rect.height());
    }

    QTransform form = painter->transform();
    if (m_orientation == Qt::Vertical) {
        form.rotate(90);
    }
    form.rotate(180, Qt::XAxis);
    painter->setTransform(form);

    painter->setPen(m_color);

    if (m_orientation == Qt::Vertical) {
        painter->drawPath(wave_path(m_beam,
                                    rect.size().toSize().height(),
                                    rect.size().toSize().width()));
    } else {
        painter->drawPath(wave_path(m_beam,
                                    rect.size().toSize().width(),
                                    rect.size().toSize().height()));
    }
}
