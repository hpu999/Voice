#ifndef __FPGA_H__
#define __FPGA_H__

#include <QMutex>
#include <QReadWriteLock>

struct GlobalData;

class AlarmOutput
{
public:
    AlarmOutput(Fpga *fpga, int index) : m_fpga(fpga), m_index(index) {}

    bool is_valid() const;
    bool set_valid(bool flag, bool reflesh = false);

    quint16 logic_group() const;
    bool set_logic_group(quint16 groups, bool reflesh = false);

    enum Operator {
        AND,
        OR
    };
    Operator op(int output) const;
    bool set_op(Operator op, bool reflesh = false);

    enum Condition {
        CONDITION_NONE,
        CONDITION_GATE_A        = 0b0001,
        CONDITION_GATE_B        = 0b0010,
        CONDITION_GATE_I        = 0b0011,
        CONDITION_NOT_GATE_A    = 0b0100,
        CONDITION_NOT_GATE_B    = 0b0101,
        CONDITION_NOT_GATE_I    = 0b0110,
        CONDITION_MAX_THICKNESS = 0b0111,
        CONDITION_MIN_THICKNESS = 0b1000
    };
    Condition condition(int index) const;
    bool set_condition(int index, Condition cond, bool reflesh = false);

    quint32 count() const;
    bool set_count(quint32 count, bool reflesh = false);

    int delay() const;                                  /* 延迟时间，单位us */
    bool set_delay(int delay, bool reflesh = false);

    int hold_time() const;                              /* 保持时间，单位us */
    bool set_hold_time(int time, bool reflesh = false);

private:
    Fpga *m_fpga;
    int m_index;
};

class Fpga
{
    friend class AlarmOutput;
public:

    static Fpga* get_fpga(void);

    bool reset();

    /* Global */
    int pa_law_qty() const;                     /* PA聚焦法则数 */
    bool set_pa_law_qty(int qty, bool reflesh = false);

    int ut_law_qty() const;                     /* UT(虚拟)聚焦法则数 */
    bool set_ut_law_qty(int qty, bool reflesh = false);

    enum EncoderPolarity {
        Normal  = 0,
        Inverse = 0b1000
    };
    enum EncoderMode {
        QUAD    = 0b011,
        UP      = 0b010,
        DOWN    = 0b001,
        OFF     = 0b000,
        PAUSE   = 0b100
    };
    EncoderPolarity encoder_x_polarity() const; /* 编码器X极性 */
    EncoderPolarity encoder_y_polarity() const; /* 编码器Y极性 */
    EncoderMode encoder_x_mode() const;         /* 编码器X模式 */
    EncoderMode encoder_y_mode() const;         /* 编码器Y模式 */
    bool set_encoder_x(EncoderMode type, EncoderPolarity polarity = Normal, bool reflesh = false);
    bool set_encoder_y(EncoderMode type, EncoderPolarity polarity = Normal, bool reflesh = false);

    /* UT双晶状态 */
    bool ut1_twin() const;
    bool set_ut1_twin(bool enable);
    bool ut2_twin() const;
    bool set_ut2_twin(bool enable);

    /* UT阻尼 */
    enum DampingType {
        R50  = 0b00,
        R100 = 0b01,
        R200 = 0b10,
        R500 = 0b11
    };
    DampingType ut1_damping() const;
    bool set_ut1_damping(DampingType type, bool reflesh = false);
    DampingType ut2_damping() const;
    bool set_ut2_damping(DampingType type, bool reflesh = false);

    /* PA/UT发射电压 */
    enum VoltageType {
        VOLTAGE_LOW     = 0b00,
        VOLTAGE_MIDDLE  = 0b01,
        VOLTAGE_HIGHT   = 0b10
    };
    VoltageType ut_voltage() const;
    bool set_ut_voltage(VoltageType type, bool reflesh = false);
    VoltageType pa_voltage() const;
    bool set_pa_voltage(VoltageType type, bool reflesh = false);

    /* 控制省电 */
    enum PowerMode {
        NONE_POWER_MODE
    };
    PowerMode power() const;
    bool set_power(PowerMode mode, bool reflesh = false);

    /* 接收通道使能组 */
    quint32 rx_channels() const;
    bool set_rx_channels(quint32 channels, bool reflesh = false);

    /* 冻结 */
    bool is_freeze() const;
    bool set_freeze(bool freeze, bool reflesh = false);

    /* 蜂鸣器频率 */
    enum SoundMode {
        SOUND_OFF   = 0b000,
        SOUND_300HZ = 0b001,
        SOUND_600HZ = 0b010,
        SOUND_1000HZ= 0b011,
        SOUND_5000HZ= 0b100,
    };
    SoundMode sound() const;
    bool set_sound(SoundMode mode, bool reflesh = false);

    /* 输出报警使能 */
    bool is_alarm_analog1() const;
    bool is_alarm_analog2() const;
    bool set_alarm_analog1(bool flag, bool reflesh = false);
    bool set_alarm_analog2(bool flag, bool reflesh = false);

    /* 16组报警逻辑组使能位 */
    quint16 alarm_analog1_logic_group() const;
    quint16 alarm_analog2_logic_group() const;
    bool set_alarm_analog1_logic_group(quint16 groups, bool reflesh = false);
    bool set_alarm_analog2_logic_group(quint16 groups, bool reflesh = false);

    bool set_alarm_output1_operator(OutputOperator op, bool reflesh = false);
    bool set_alarm_output2_operator();
    bool set_alarm_output3_operator();

    int alarm_output1_delay() const;
    int alarm_output2_delay() const;            /* 延迟时间，单位us */
    int alarm_output3_delay() const;            /* 延迟时间，单位us */
    int alarm_output1_hold_time() const;        /* 保持时间，单位us */
    int alarm_output2_hold_time() const;        /* 保持时间，单位us */
    int alarm_output3_hold_time() const;        /* 保持时间，单位us */

//    short alarm_analog1_logic_group() const;    /* 16组报警逻辑组使能位 */
//    short alarm_analog2_logic_group() const;    /* 16组报警逻辑组使能位 */

    enum AnalogType {
        ANALOG_GATE_A       = 0b001,                        /* A闸门峰值 */
        ANALOG_GATE_B       = 0b010,                        /* B闸门峰值 */
        ANALOG_THINKNESS    = 0b100                         /* 厚度 */
    };
    AnalogType alarm_analog1_type() const;
    AnalogType alram_analog2_type() const;

    int factor_echo() const;                    /* 回波数 */

protected:
    Fpga();
    ~Fpga();

private:
    static QMutex m_mutex;
    static Fpga *m_fpga;
    GlobalData *m_global;
    QReadWriteLock m_lock;
};

Fpga *Fpga::get_fpga(void)
{
    QMutexLocker locker(&m_mutex);
    if (m_fpga == NULL) {
        m_fpga = new Fpga();
    }

    return m_fpga;
}

#endif // __FPGA_H__
