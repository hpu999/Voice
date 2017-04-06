/**
 * @file focallawer.h
 * @brief 聚焦法则计算器
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-03-30
 */

#ifndef __FOCALLAWER_H__
#define __FOCALLAWER_H__

#include "point.h"

#include "pa_probe.h"
#include "ut_probe.h"

#include "wedge.h"

#include "true_depth_focus.h"
#include "half_path_focus.h"

#include "flat.h"
#include "cylinder.h"

#include "beam.h"

namespace DplFocallaw {

class FocallawerPrivate;
class FOCALLAWSHARED_EXPORT Focallawer : public QObject
{
    Q_DECLARE_PRIVATE(Focallawer)
    Q_OBJECT
public:
    explicit Focallawer(QObject *parent = 0);
    ~Focallawer();

    const ProbePointer &probe() const;

    void set_probe(const ProbePointer &probe);

    /**
     * @brief wedge 获取锲块
     * @return      锲块对象
     */
    const WedgePointer &wedge() const;

    /**
     * @brief set_wedge 设置锲块
     * @param w         锲块对象
     * @return          成功返回true，否则false
     */
    bool set_wedge(const WedgePointer &w);

    /**
     * @brief specimen  获取工件
     * @return          工件对象
     */
    const SpecimenPointer &specimen() const;

    /**
     * @brief set_specimen  设置工件
     * @param s             工件对象
     */
    void set_specimen(const SpecimenPointer &s);

    /**
     * @brief focus_configure   获取焦点配置对象
     * @return                  焦点配置对象
     */
    const FocusCnfPointer &focus_configure() const;

    /**
     * @brief set_focus_configure   设置焦点配置对象
     * @param cnf                   焦点配置对象
     */
    void set_focus_configure(const FocusCnfPointer &cnf);

    /**
     * @brief beams     获取聚焦后声束延迟信息
     * @return          延迟信息
     */
    const QList<BeamPointer> &beams() const;

    /**
     * @brief beam_qty  声束数量
     * @return          数量
     */
    uint beam_qty() const;

signals:
    void beam_qty_changed(int);

public slots:
    void update();

private:
    FocallawerPrivate *d_ptr;
};

typedef QSharedPointer<Focallawer> FocallawerPointer;

}

#endif // __FOCALLAWER_H__
