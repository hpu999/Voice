/**
 * @file group_config.cpp
 * @brief Group Config
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */

#include "group.h"
#include "fpga/fpga.h"
#include "device.h"

#include <QReadWriteLock>
#include <QDebug>

namespace DplDevice {

class GroupPrivate
{
public:
    GroupPrivate();

    /**
     * @brief max_beam_delay    获取最大的BeamDelay
     * @return                  BeamDelay值，　单位(采样精度)
     */
    int max_beam_delay();

    /* variables */
    int m_start;                /* 声程轴起始点,单位(采样精度) */
    int m_range;                /* 范围值, 单位(采样精度) */
    int m_wedgeDelay;           /* 楔块延迟时间，单位(采样精度) */
    Group::UtUnit m_utUnit;     /* Ut Unit */

    double m_velocity;          /* 声速， 单位(m/s) */
    double m_currentAngle;      /* 声速入射角度, 单位(度) */

    Group::PointQtyMode m_pointQtyMode; /* 采样点模式 */

    QReadWriteLock m_rwlock;
};

GroupPrivate::GroupPrivate()
{
    m_start = 0;
    m_range = 57020;
    m_wedgeDelay = 0;
    m_utUnit = Group::SoundPath;
    m_velocity = 3240;
    m_currentAngle = 30;

    m_pointQtyMode = Group::PointQtyAuto;
}

int GroupPrivate::max_beam_delay()
{
    qDebug()<<__FILE__<<__func__<<"Unimplement";
    return 0;
}

/* Group */
Group::Group(int index) :
    DplFpga::Group(index),
    d(new GroupPrivate())
{

}

Group::~Group()
{
    delete d;
}

Group::UtUnit Group::ut_unit()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_utUnit;
}

void Group::set_ut_unit(Group::UtUnit type)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_utUnit = type;
}

int Group::start()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_start;
}

void Group::set_start(int value)
{
    QWriteLocker l(&d->m_rwlock);
    if (value == d->m_start) {
        return;
    }
    d->m_start = value;

    update_sample();
}

int Group::range()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_range;
}

void Group::set_range(int value)
{
    QWriteLocker l(&d->m_rwlock);

    int maxPointQty = value;
    int curPointQty = point_qty();
    int widthPointQty = 640;

    if (PointQtyAuto == d->m_pointQtyMode) {
        if (maxPointQty <= widthPointQty) {
            curPointQty = maxPointQty;
        } else {
            int compressRate = maxPointQty / widthPointQty;
            if (maxPointQty%widthPointQty) {
                ++compressRate;
            }
            curPointQty = maxPointQty / compressRate;
        }
    }

    if (! maxPointQty%curPointQty) {
        /* 类似四舍五入 */
        maxPointQty = ((maxPointQty + curPointQty/2)/curPointQty)*curPointQty;
    }

    if (maxPointQty*fpga->sample_precision() == d->m_range) {
        return;
    }
    d->m_range = maxPointQty;

    set_point_qty(curPointQty);
    if (maxPointQty/curPointQty) {
        set_compress_ratio(maxPointQty/curPointQty, true);
    } else {
        set_compress_ratio(1, true);
    }
    update_sample();
}

double Group::velocity()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_velocity;
}

void Group::set_velocity(double value)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_velocity = value;
}

int Group::wedge_delay()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_wedgeDelay;
}

void Group::set_wedge_delay(int value)
{
    QWriteLocker l(&d->m_rwlock);
    if (d->m_wedgeDelay == value) {
        return;
    }
    d->m_wedgeDelay = value;
    update_sample();
}

double Group::current_angle()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_currentAngle;
}

Group::PointQtyMode Group::point_qty_mode()
{
    QReadLocker l(&d->m_rwlock);
    return d->m_pointQtyMode;
}

bool Group::set_point_qty_mode(Group::PointQtyMode mode)
{
    QWriteLocker l(&d->m_rwlock);
    d->m_pointQtyMode = mode;
    return true;
}

int Group::beam_qty()
{
    qDebug()<<__FILE__<<__func__<<"unimplement";
    return 1;
}

int Group::max_sample_time()
{
    DplFpga::Fpga *fpga = DplFpga::Fpga::get_instance();
    int beamQty = Device::get_instance()->beam_qty();
    // prf为1即(1s)时，rx_time时间为最大
    // 1_000_000_000 / 4    idle_time + rx_time >= 4 * rx_time
    // one beam cycle = loading time +  beam delay + wedge delay + sample start + sample range + 50 /* 单位 ns */
    int beamCycle =  (250*1000*1000) / fpga->sample_precision() / beamQty;
    int max = beamCycle - (fpga->loading_time()  - d->max_beam_delay() - d->m_wedgeDelay - 5);
    if(max > 1000*1000/fpga->sample_precision()) {
        max = 1000*1000/fpga->sample_precision();
    }
    return max ;
}

void Group::update_sample()
{
    set_sample_start(d->m_wedgeDelay + d->m_start, true);
    set_sample_range(d->m_wedgeDelay + d->m_start + d->m_range, true);
    set_rx_time(d->max_beam_delay() + d->m_wedgeDelay + d->m_start + d->m_range + 50, true);
}

}
