#ifndef __CONFIG_CONFIGURATION_H__
#define __CONFIG_CONFIGURATION_H__

#include <QString>
#include <QMap>
#include "msgpack.hpp"

namespace Config {

class BaseItemConfig;
class ConfigurationPrivate;

namespace Config_Group {

    enum E_Group {
        General,
        Gate,
        UT,
        Focallawer,
        TCGS,
        Cursor,
        Scan
    };

    enum E_Gate {
        Gate_Type,
        Gate_Switch,
        Gate_Start,
        Gate_Width,
        Gate_Height,
        Gate_Synchro,
        Gate_Measure,
        Gate_Mode,
        Gate_Color,
    };

    enum E_UT {
        UT_Sample,
        UT_Transceiver
    };

    enum E_Transceiver {
        Transceiver_Mode,
        Transceiver_PW,
        Transceiver_Filter,
        Transceiver_Rectifier,
        Transceiver_VideoFilter,
        Transceiver_Averaging
    };

    enum E_Sample {
        Sample_Precision,
        Sample_Gain,
        Sample_Start,
        Sample_Range,
        Sample_PointQty,
        Sample_AutoSet
    };

    enum E_Focallawer {
        Probe,
        Wedge,
        Specimen,
        FocusCnf
    };

    enum E_Probe {
        Probe_PA,
        Probe_FileName,
        Probe_Serial,
        Probe_Model,
        Probe_Type,
        Probe_Freq,
        Probe_PulserIndex,
        Probe_ReceiverInex,
    };

   enum E_Wedge {
        Wedge_FileName,
        Wedge_Serial,
        Wedge_Model,
        Wedge_Angle,
        Wedge_RootAngle,
        Wedge_Velocity,
        Wedge_PrimaryOffset,
        Wedge_SecondaryOffset,
        Wedge_FirstElementHeight,
        Wedge_Length,
        Wedge_Width,
        Wedge_Height,
        Wedge_Orientation,
        Wedge_delay
    };

   enum E_Specimen{
       Specimen_Type,
       Specimen_WaveType,
       Specimen_Velocity
    };

   enum E_FocusCnf {
        FocusCnf_Mode
    };

   enum E_TCGS {
       TCGS_Enable,
       TCGS_CurrentTcg,
       TCGS_Gain,
       TCGS_Point,
       TCGS_CurrentPoint,
   };

   enum E_Point {
       Point_Index,
       Point_Position
   };

   enum E_Cursor {
       Cursor_AmplitudeMeasurement,
       Cursor_UltrasoundReference,
       Cursor_UltrasoundMeasurement,
       Cursor_ScanReference,
       Cursor_ScanMeasurement,
       Cursor_IndexReference,
       Cursor_IndexMeasurement,
       Cursor_Visible
   };

   enum E_Scan {
       Scan_StartX,
       Scan_StopX,
       Scan_StartY,
       Scan_StopY,
       Scan_Width,
       Scan_Height
   };

    enum E_General {
        General_Mode,
        General_UTUnit,
        General_CurrentAngle
    };
}


enum E_MainConfig {
    Preference,
    Group,
    WaveData,
};

namespace Config_Preference {
    enum E_Preference {
        Bright,
        Opacity,
        Language,
        StartingPage,
        GateMode,
    };
}


typedef std::map<int, BaseItemConfig*>  UnpackerMap;

class Configuration
{
public:

    Configuration();
    ~Configuration();

    static Configuration *instance();

    bool load_config(const QString &configFilePath = s_defaultConfigFilePath);
    bool save_config(const QString &configFilePath = s_defaultConfigFilePath);

private:
    ConfigurationPrivate        *d;
    static Configuration        *s_configuration;
    static QString              s_defaultConfigFilePath;

    void deal_object(const msgpack::object &object);

    Q_DISABLE_COPY(Configuration)
};

}

#endif // __CONFIG_CONFIGURATION_H__
