#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <QVector>
#include <QSharedPointer>
#include <QReadWriteLock>

#include <display/palette_color.h>
#include <source/beams.h>
#include <source/axis.h>

static const double ENCODER_ORIGIN  = 11.0;     /* 编码其起始位置 */
static const int STORE_BUFFER_SIZE = 256 * 1024 * 1024 ;    /* 256MB */

static double DEFAULT_PIX_PER_BEAM = 1.0;       /* 默认每条beam占1pix */

class BscanScene : public QGraphicsScene
{
    Q_OBJECT

public:

    struct S_CommonProperties {
        float   ratio;      /* 每个像素代表beam中的多少个点数据 */
        double  pixCount;   /* 每条beam占多少像素,采用double进行计算具体数据 */
        int     maxIndex;   /* 最大的beam数，超出后滚动显示 */
        int     align;      /* 对齐数据（例子：width为20， pixCount为3， 则align为 width % pixCount = 2）*/
    };

    struct S_RedrawProperties {
        unsigned int currentFrameIndex; /* 当前显示的最后一帧数据的index */
        int totalFrameCount;            /* 整个storeBuffer可存放的帧数 */
        int redrawCount;                /* 需要重画的帧数 */
        int beginShowIndex;             /* 从第beginShowIndex帧开始重画 */
    };


    explicit BscanScene(const DplDisplay::PaletteColorPointer &palette, int group, QObject *parent = 0);
    ~BscanScene();

    void set_beams(const DplSource::BeamsPointer &beamPointer);
    void reset();
    bool set_pix_per_beam(double ratio);

    bool set_current_beam(unsigned int index);
    bool redraw_beams();
    inline void set_scroll_window(bool flag) { m_scrolling = flag; }
    inline DplSource::Axis::Driving     driving() { return m_driving;}

    virtual bool need_refresh();

signals:
    void image_changed();

public slots:
    void set_size(const QSize &size);


protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

    /**
     * @brief draw_vertical_beam    B扫的垂直显示
     */
    virtual void draw_vertical_beam();


    /**
     * @redraw_horizontal_beam 当显示大小改变，重新画垂直B扫
     */
    virtual void redraw_vertical_beam();


    /**
     * @brief calculate_common_properties   计算画B扫的参数
     * @param commonProperties
     */
    void calculate_common_properties(BscanScene::S_CommonProperties &commonProperties);


    /**
     * @brief calculate_redraw_properties   计算改变显示大小后，重画B扫的参数
     * @param commonProperties
     * @param redrawProperites
     */
    void calculate_redraw_properties(BscanScene::S_CommonProperties &commonProperties,
                                     BscanScene::S_RedrawProperties &redrawProperites);

    /**
     * @brief set_vertical_image_data   设置时间B扫的垂直显示image数据
     * @param beamsShowedCount
     * @param commonProperties
     * @param waveData
     */
    virtual void set_vertical_image_data(int beamsShowedCount,
                        const BscanScene::S_CommonProperties &commonProperties,
                        const quint8 *waveData);

    /**
     * @brief scroll_vertical_image     时间B扫的垂直滚动image滚动实现
     * @param commonProperties
     * @param waveData
     */
    void scroll_vertical_image(const BscanScene::S_CommonProperties &commonProperties,
                               const quint8 *waveData);

    /**
     * @brief check_scroll_window   检查是否滚动窗口
     * @param oldSize               改变前的size
     */
    void check_scroll_window(const QSize &oldSize);

    QImage                          *m_image;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamsPointer         m_beamsPointer;
    QSize                           m_size;
    double                          m_pixPerBeamRatio;      /* 针对编码器，一个beam占多少像素，
                                                             * 与扫查分辨率、扫查起始点有关，最小值为1. */
    int                             m_group;
    QReadWriteLock                  m_rwLock;
    volatile bool                   m_redrawFlag;           /* set_size后重画标志 */

    volatile    bool                m_scrolling;            /* 标志当前窗口是否卷动 */
    volatile    int                 m_beamsShowedCount;     /* 当前已显示多少条beam */
    volatile    int                 m_maxBeamsCount;        /* 显示区最大beam数 */
    int                             m_currentIndex;         /* 显示第index的beam数据 */

    volatile DplSource::Axis::Driving        m_driving;

};


#endif // __B_SCAN_SCENE_H__
