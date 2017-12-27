#include "report_wedge.h"

namespace DplReport {

ReportWedge::ReportWedge()
    : BaseReport(),
      m_model("-"),
      m_angle("-")
{

}

bool ReportWedge::save(lua_State *lua)
{
    m_lua = lua;
    set_kv(lua, "WedgeModel", m_model);
    set_kv(lua, "WedgeAngle", m_angle);
    return true;
}

}