#include "report_data.h"

#include "report.h"
#include "report_group.h"
#include "report_groups.h"
#include <QSharedPointer>
#include <device/group.h>
#include <device/device.h>
#include <source/scan.h>
#include <source/axis.h>

namespace DplReport {

static int g_precision = 2;

ReportData::ReportData(Report *report, QObject *parent)
    : QObject(parent),
      m_report(report)
{

}

void ReportData::fill(const QString &reportFile)
{
    m_report->set_template_file(tr("/home/tt/TT/source/system/Template/Report/Complete.html"));

    fill_report_header(reportFile);

    fill_report_users();

    fill_report_groups();

    fill_report_defects();
}

void ReportData::fill_report_header(const QString &reportFile)
{
    ReportHeaderPointer header = m_report->report_header();

    QString dateTime = QDateTime::currentDateTime().toString("yyyy/MM/dd");

    header->set_device_type(tr("Phascan II"));
    header->set_report_file(reportFile);
    header->set_setup_file(tr("TODO"));
    header->set_report_date_time(dateTime);
    header->set_inspection_date_time(dateTime);
    header->set_save_mode(tr("TODO"));
}

void ReportData::fill_report_users()
{
    ReportUsersPointer users = m_report->report_users();
    ReportUsers::S_USER user;

    /* TODO */
    for (int i = 0; i < 10; ++i) {
        user.name       = tr("name") + QString::number(i + 1);
        user.content    = tr("content") + QString::number(i + 1);
        users->add_user(user);
    }
}

void ReportData::fill_report_groups()
{
    ReportGroupsPointer reportGroups = m_report->report_groups();

    DplDevice::Device *device = DplDevice::Device::instance();
    const QVector<DplDevice::GroupPointer> &groups= device->groups();
    QVector<DplDevice::GroupPointer>::const_iterator it = groups.begin();


    while(it != groups.end()) {
        m_currentGroup = (*it).data();
        reportGroups->add_group((*it)->index());
        fill_report_group(reportGroups.data());
        ++it;
    }
}

void ReportData::fill_report_defects()
{
    ReportDefectsPointer defects = m_report->report_defects();

    for(int i = 0; i < MAX_FIELDS; ++i) {
        defects->set_field_name(i, tr("name") + QString::number(i + 1));
    }
    ReportDefects::S_ReportDefect reportDefect;
    reportDefect.channel        = tr("TODO");
    reportDefect.comments       = tr("TODO");
    reportDefect.fieldValues[0] = tr("TODO");
    reportDefect.fieldValues[1] = tr("TODO");
    reportDefect.fieldValues[2] = tr("TODO");
    reportDefect.fieldValues[3] = tr("TODO");
    reportDefect.fieldValues[4] = tr("TODO");
    reportDefect.fieldValues[5] = tr("TODO");
    reportDefect.fieldValues[6] = tr("TODO");
    reportDefect.fieldValues[7] = tr("TODO");
    reportDefect.group          = tr("TODO");
    reportDefect.image          = tr("TODO");
    reportDefect.index          = tr("TODO");
    reportDefect.scan           = tr("TODO");

    defects->add_defect(reportDefect);
}

void ReportData::fill_report_group(ReportGroups *reportGroups)
{
    ReportGroupPointer group = reportGroups->current_group();

    fill_report_group_probe(group.data());
    fill_report_group_wedge(group.data());
    fill_report_group_fft(group.data());
    fill_report_group_setup(group.data());

    if (m_currentGroup->mode() == DplDevice::Group::PA) {
        fill_report_group_law(group.data());
    }

    fill_report_group_part(group.data());
    fill_report_group_scan(group.data());
}

void ReportData::fill_report_group_probe(ReportGroup *group)
{
    ReportProbePointer probe = group->get_probe();

    const DplFocallaw::FocallawerPointer &focallawer = m_currentGroup->focallawer();
    const DplFocallaw::ProbePointer &probePointer = focallawer->probe();

    /* TODO */
    probe->set_aperture(tr("TODO"));
    probe->set_freq(QString::number(probePointer->freq(), 'f', g_precision));
    probe->set_model(probePointer->model());
    probe->set_serial(probePointer->serial());
}

void ReportData::fill_report_group_wedge(ReportGroup *group)
{
    ReportWedgePointer wedge = group->get_wedge();

    const DplFocallaw::FocallawerPointer &focallawer = m_currentGroup->focallawer();
    const DplFocallaw::WedgePointer &wedgePointer = focallawer->wedge();

    wedge->set_angle(QString::number(wedgePointer->angle(), 'f', g_precision));
    wedge->set_model(wedgePointer->model());
}

void ReportData::fill_report_group_fft(ReportGroup *group)
{
    ReportFFTPointer fft = group->get_fft();

    fft->set_peak_freq(tr("TODO"));

    fft->set_band_width_6_dB(tr("TODO"));
    fft->set_band_width_percent_6_dB(tr("TODO"));
    fft->set_center_freq_6_dB(tr("TODO"));
    fft->set_heigher_freq_6_dB(tr("TODO"));
    fft->set_lower_freq_6_dB(tr("TODO"));

    fft->set_band_width_20_dB(tr("TODO"));
    fft->set_band_width_percent_20_dB(tr("TODO"));
    fft->set_center_freq_20_dB(tr("TODO"));
    fft->set_heigher_freq_20_dB(tr("TODO"));
    fft->set_lower_freq_20_dB(tr("TODO"));
}

void ReportData::fill_report_group_setup(ReportGroup *group)
{
    ReportSetupPointer setup = group->get_setup();

    setup->set_averaging_factor(tr("TODO"));
    setup->set_band_pass_filter(tr("TODO"));
    setup->set_beam_delay(tr("TODO"));
    setup->set_gain(tr("TODO"));
    setup->set_half_path_range(tr("TODO"));
    setup->set_half_path_start(tr("TODO"));
    setup->set_index_offset(tr("TODO"));
    setup->set_inspection_type(tr("TODO"));
    setup->set_prf(tr("TODO"));
    setup->set_pulse_width(tr("TODO"));
    setup->set_rectification(tr("TODO"));
    setup->set_rx_tx_mode(tr("TODO"));
    setup->set_scale_factor(tr("TODO"));
    setup->set_scan_offset(tr("TODO"));
    setup->set_skew(tr("TODO"));
    setup->set_sound_velocity(tr("TODO"));
    setup->set_video_filter(tr("TODO"));
    setup->set_voltage(tr("TODO"));
    setup->set_wave_type(tr("TODO"));

    ReportGatePointer gateA = setup->get_gate(ReportGate::Gate_A);
    gateA->set_enable(true);
    gateA->set_start(tr("TODO"));
    gateA->set_synchro(tr("TODO"));
    gateA->set_width(tr("TODO"));
    gateA->set_threshold(tr("TODO"));

    ReportGatePointer gateB = setup->get_gate(ReportGate::Gate_B);
    gateB->set_enable(true);
    gateB->set_start(tr("TODO"));
    gateB->set_synchro(tr("TODO"));
    gateB->set_width(tr("TODO"));
    gateB->set_threshold(tr("TODO"));

    ReportGatePointer gateI = setup->get_gate(ReportGate::Gate_I);
    gateI->set_enable(true);
    gateI->set_start(tr("TODO"));
    gateI->set_synchro(tr("TODO"));
    gateI->set_width(tr("TODO"));
    gateI->set_threshold(tr("TODO"));
}

void ReportData::fill_report_group_law(ReportGroup *group)
{
    ReportLawPointer law = group->get_law();

    const DplFocallaw::FocallawerPointer &focallawer =  m_currentGroup->focallawer();

    law->set_enable(true);

    law->set_angle_resolution(tr("TODO"));
    law->set_element_qty(tr("TODO"));
    law->set_element_resolution(tr("TODO"));
    law->set_first_rx_element(tr("TODO"));
    law->set_first_tx_element(tr("TODO"));
    law->set_focal_type(tr("TODO"));
    law->set_last_rx_element(tr("TODO"));
    law->set_last_tx_element(tr("TODO"));
    law->set_start_angle(tr("TODO"));
    law->set_stop_angle(tr("TODO"));
    law->set_type(tr("TODO"));

    for(int i = 0; i < FOCAL_FIELDS_MAX; ++i) {
        law->set_focal_field_names(i, tr("NameTODO-") + QString::number(i + 1));
        law->set_focal_field_values(i, tr("ValueTODO-") + QString::number(i + 1));
    }
}

void ReportData::fill_report_group_part(ReportGroup *group)
{
    ReportPartPointer part = group->get_part();
    part->set_geometry(tr("TODO"));
    part->set_material(tr("TODO"));
    part->set_thickness(tr("TODO"));
}

void ReportData::fill_report_group_scan(ReportGroup *group)
{
    ReportScanPointer scan = group->get_scan();

    const DplSource::AxisPointer &scanAxis = DplSource::Scan::instance()->scan_axis();
    const DplSource::AxisPointer &indexAxis = DplSource::Scan::instance()->index_axis();

    scan->set_index_resolution(QString::number(indexAxis->resolution(), 'f', g_precision));
    scan->set_index_start(QString::number(indexAxis->start(), 'f', g_precision));
    scan->set_index_stop(QString::number(indexAxis->end(), 'f', g_precision));

    scan->set_scan_resolution(QString::number(scanAxis->resolution(), 'f', g_precision));
    scan->set_scan_speed(tr("TODO"));
    scan->set_scan_start(QString::number(scanAxis->start(), 'f', g_precision));
    scan->set_scan_stop(QString::number(scanAxis->end(), 'f', g_precision));
    scan->set_scan_synchro(tr("TODO"));

    ReportEncoderPointer scanEncoder = scan->get_encoder(ReportEncoder::ScanEncoder);
    scanEncoder->set_enable(true);
    scanEncoder->set_name(tr("TODO"));
    scanEncoder->set_polarity(tr("TODO"));
    scanEncoder->set_resolution(tr("TODO"));
    scanEncoder->set_type(tr("TODO"));

    ReportEncoderPointer indexEncoder = scan->get_encoder(ReportEncoder::IndexEncoder);
    indexEncoder->set_enable(true);
    indexEncoder->set_name(tr("TODO"));
    indexEncoder->set_polarity(tr("TODO"));
    indexEncoder->set_resolution(tr("TODO"));
    indexEncoder->set_type(tr("TODO"));
}

}
