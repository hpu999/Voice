#ifndef __CURSOR_ITEM_H__
#define __CURSOR_ITEM_H__

#include <QGraphicsItem>

#include <global.h>
#include <measure/cursor.h>

class CursorItem : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CursorItem(const DplMeasure::CursorPointer &cursor,
                        Qt::Orientation orientation,
                        QColor color,
                        QColor bgColor = YellowColor);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_size(const QSize size);

    QSize size() const;

    DplMeasure::CursorPointer cursor() const;

    Qt::Orientation orientation() const;

    bool moving() const;

    void set_background_color(const QColor &color);

    enum Direction {
        NORMAL,
        REVERSE
    };
    Direction direction() const;
    void set_direction(Direction dir);

signals:
    void size_changed();

public slots:
    void setVisible(bool flag);
    void set_text(const QString &text);

protected slots:
    void update_position();
    virtual void position_event() = 0;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual double ratio() const = 0;

private:
    DplMeasure::CursorPointer m_cursor;
    Qt::Orientation m_orientation;
    QSize m_size;
    QColor m_color;
    QColor m_bgColor;
    bool m_movingFlag;
    QString m_text;
    Direction m_direction;
};

inline void CursorItem::set_size(const QSize size)
{
    if (m_size != size) {
        m_size = size;
        emit size_changed();
    }
}

inline QSize CursorItem::size() const
{
    return m_size;
}

inline DplMeasure::CursorPointer CursorItem::cursor() const
{
    return m_cursor;
}

inline Qt::Orientation CursorItem::orientation() const
{
    return m_orientation;
}

inline bool CursorItem::moving() const
{
    return m_movingFlag;
}

inline void CursorItem::set_background_color(const QColor &color)
{
    m_bgColor = color;
}

inline CursorItem::Direction CursorItem::direction() const
{
    return m_direction;
}

inline void CursorItem::set_direction(CursorItem::Direction dir)
{
    m_direction = dir;
}

inline void CursorItem::set_text(const QString &text)
{
    m_text = text;
}

#endif // __CURSOR_ITEM_H__
