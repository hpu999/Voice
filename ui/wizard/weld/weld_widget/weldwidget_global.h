#ifndef __DPL_WELD_WELD_WIDGET_GLOBAL_H__
#define __DPL_WELD_WELD_WIDGET_GLOBAL_H__

#include <QtCore/qglobal.h>

#if defined(WELDWIDGET_LIBRARY)
#  define WELDWIDGETSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WELDWIDGETSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // __DPL_WELD_WELD_WIDGET_GLOBAL_H__
