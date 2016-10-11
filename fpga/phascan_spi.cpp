#include "phascan_spi.h"
#include "gpio.h"
#include <QDebug>

QMutex PhascanSpi::s_mutex;
PhascanSpi* PhascanSpi::s_spi = NULL;

PhascanSpi* PhascanSpi::get_spi(void)
{
    QMutexLocker l(&s_mutex);
    if (s_spi == NULL) {
        s_spi = new PhascanSpi();
        s_spi->setFileName("/dev/spidev1.0");
        s_spi->open(QIODevice::ReadWrite);
        s_spi->set_mode(Spi::MODE0);
        Gpio *gpio = Gpio::get_gpio();
        gpio->set(Gpio::PIN_61, Gpio::LOW);
        gpio->set(Gpio::PIN_61, Gpio::HIGHT);
        gpio->set(Gpio::PIN_43, Gpio::LOW);
        gpio->set(Gpio::PIN_43, Gpio::HIGHT);
    }

    return s_spi;
}

void PhascanSpi::little_to_big(quint32 *data, int n)
{
    quint32 *p = data;
    for (int i = 0; i < n; ++i) {
        *p = ((*p)<<24) | ((*p<<8) & 0xff0000) | ((*p>>8)&0xff00) | ((*p)>>24);
        ++p;
    }
}

bool PhascanSpi::send(const char *data, int len)
{
    QMutexLocker l(&s_mutex);
    if ( ! isOpen()
         || data == NULL
         || len <= 0) {
//        qWarning("spi send data failed:open(%d), data(0x%08x), len(%d)", isOpen(), (unsigned int)data, len);
        return false;
    }

    char buf[len+1];
    memcpy(buf, data, len);
    buf[len] = 0;
    little_to_big((quint32 *)buf, len/4);
    return (!! Spi::write(buf, len));
}

PhascanSpi::PhascanSpi()
{

}
