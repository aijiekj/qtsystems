/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtSystems module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativedeviceinfo_p.h"

QT_BEGIN_NAMESPACE

/*!
    \qmlclass DeviceInfo QDeclarativeDeviceInfo
    \inmodule QtSystems
    \ingroup qml-systeminfo
    \brief The DeviceInfo element provides various information of the device.
*/

/*!
    \internal
*/
QDeclarativeDeviceInfo::QDeclarativeDeviceInfo(QObject *parent)
    : QObject(parent)
    , deviceInfo(new QDeviceInfo(this))
    , isMonitorActivatedLocks(false)
    , isMonitorEnabledLocks(false)
    , isMonitorThermalState(false)
{
}

/*!
    \internal
 */
QDeclarativeDeviceInfo::~QDeclarativeDeviceInfo()
{
}

/*!
    \qmlproperty bool DeviceInfo::monitorActivatedLocks

    This property holds whether or not monitor the change of activated locks.
 */
bool QDeclarativeDeviceInfo::monitorActivatedLocks() const
{
    return isMonitorActivatedLocks;
}

void QDeclarativeDeviceInfo::setMonitorActivatedLocks(bool monitor)
{
    if (monitor != isMonitorActivatedLocks) {
        isMonitorActivatedLocks = monitor;
        if (monitor) {
            connect(deviceInfo, SIGNAL(activatedLocksChanged(QDeviceInfo::LockTypeFlags)),
                    this, SIGNAL(activatedLocksChanged()));
        } else {
            disconnect(deviceInfo, SIGNAL(activatedLocksChanged(QDeviceInfo::LockTypeFlags)),
                       this, SIGNAL(activatedLocksChanged()));
        }
        emit monitorActivatedLocksChanged();
    }
}

/*!
    \qmlproperty flag DeviceInfo::activatedLocks

    This property holds the activated locks. Available locks include:
    \list
    \o NoLock               No lock, or unknown lock type.
    \o PinLock              Device can be locked by PIN code or password.
    \o TouchOrKeyboardLock  Device can be locked by touch or keyboard.
    \endlist
*/
QDeclarativeDeviceInfo::LockTypeFlags QDeclarativeDeviceInfo::activatedLocks() const
{
    QDeviceInfo::LockTypeFlags locks(deviceInfo->activatedLocks());
    LockTypeFlags declarativeLocks(NoLock);
    if (locks.testFlag(QDeviceInfo::PinLock))
        declarativeLocks |= PinLock;
    if (locks.testFlag(QDeviceInfo::TouchOrKeyboardLock))
        declarativeLocks |= TouchOrKeyboardLock;
    return declarativeLocks;
}

/*!
    \qmlproperty bool DeviceInfo::monitorEnabledLocks

    This property holds whether or not monitor the change of enabled locks.
 */
bool QDeclarativeDeviceInfo::monitorEnabledLocks() const
{
    return isMonitorEnabledLocks;
}

void QDeclarativeDeviceInfo::setMonitorEnabledLocks(bool monitor)
{
    if (monitor != isMonitorEnabledLocks) {
        isMonitorEnabledLocks = monitor;
        if (monitor) {
            connect(deviceInfo, SIGNAL(enabledLocksChanged(QDeviceInfo::LockTypeFlags)),
                    this, SIGNAL(enabledLocksChanged()));
        } else {
            disconnect(deviceInfo, SIGNAL(enabledLocksChanged(QDeviceInfo::LockTypeFlags)),
                       this, SIGNAL(enabledLocksChanged()));
        }
        emit monitorActivatedLocksChanged();
    }
}

/*!
    \qmlproperty flag DeviceInfo::enabledLocks

    This property holds the enabled locks. Available locks include:
    \list
    \o NoLock               No lock, or unknown lock type.
    \o PinLock              Device can be locked by PIN code or password.
    \o TouchOrKeyboardLock  Device can be locked by touch or keyboard.
    \endlist
*/
QDeclarativeDeviceInfo::LockTypeFlags QDeclarativeDeviceInfo::enabledLocks() const
{
    QDeviceInfo::LockTypeFlags locks(deviceInfo->enabledLocks());
    LockTypeFlags declarativeLocks(NoLock);
    if (locks.testFlag(QDeviceInfo::PinLock))
        declarativeLocks |= PinLock;
    if (locks.testFlag(QDeviceInfo::TouchOrKeyboardLock))
        declarativeLocks |= TouchOrKeyboardLock;
    return declarativeLocks;
}

/*!
    \qmlproperty bool DeviceInfo::monitorThermalState

    This property holds whether or not monitor the change of thermal state.
 */
bool QDeclarativeDeviceInfo::monitorThermalState() const
{
    return isMonitorThermalState;
}

void QDeclarativeDeviceInfo::setMonitorThermalState(bool monitor)
{
    if (monitor != isMonitorThermalState) {
        isMonitorThermalState = monitor;
        if (monitor) {
            connect(deviceInfo, SIGNAL(thermalStateChanged(QDeviceInfo::ThermalState)),
                    this, SIGNAL(thermalStateChanged()));
        } else {
            disconnect(deviceInfo, SIGNAL(thermalStateChanged(QDeviceInfo::ThermalState)),
                       this, SIGNAL(thermalStateChanged()));
        }
        emit monitorThermalStateChanged();
    }
}

/*!
    \qmlproperty enum DeviceInfo::thermalState

    This property holds the thermal state. Possible values are:
    \list
    \o UnknownThermal
    \o NormalThermal
    \o WarningThermal
    \o AlertThermal
    \o ErrorThermal
    \endlist
*/
QDeclarativeDeviceInfo::ThermalState QDeclarativeDeviceInfo::thermalState() const
{
    return static_cast<ThermalState>(deviceInfo->thermalState());
}

/*!
    Returns true if the \a feature is supported, otherwise false. The following features can be
    queried:
    \list
    \o Bluetooth      Bluetooth feature.
    \o Camera         Camera feature.
    \o FmRadio        Frequency modulation (FM) radio feature.
    \o FmTransmitter  Frequency modulation (FM) radio transmitter feature.
    \o Infrared       Infrared communication feature.
    \o Led            Light-emitting diode (LED) feature.
    \o MemoryCard     Memory card feature.
    \o Usb            Universal system bus (USB) feature.
    \o Vibration      Vibration feature.
    \o Wlan           Wireless local area network (WLAN) feature.
    \o Sim            Subscriber identity module (SIM) feature.
    \o Positioning    Positioning feature, e.g. Global Positioning System (GPS).
    \o VideoOut       Video out feature.
    \o Haptics        Haptics feature, the platform can provide audio and/or visual and/or vibration feedback.
    \o Nfc            Near Field Communication (NFC) feature
    \endlist
*/
bool QDeclarativeDeviceInfo::hasFeature(QDeclarativeDeviceInfo::Feature feature) const
{
    return deviceInfo->hasFeature(static_cast<QDeviceInfo::Feature>(feature));
}

/*!
    Returns the count of available International Mobile Equipment Identity (IMEI) of the device. In
    case of error, or the information is not available, -1 is returned.
*/
int QDeclarativeDeviceInfo::imeiCount() const
{
    return deviceInfo->imeiCount();
}

/*!
    Returns the International Mobile Equipment Identity (IMEI) of the given \a interface on the device.
    In case of error, or the information is not available, an empty string is returned.
*/
QString QDeclarativeDeviceInfo::imei(int interface) const
{
    return deviceInfo->imei(interface);
}

/*!
    Returns the name of the manufacturer of this device, or the name of the vendor of the motherboard
    as a fallback. In case of error, or the information is not available, an empty string is returned.
*/
QString QDeclarativeDeviceInfo::manufacturer() const
{
    return deviceInfo->manufacturer();
}

/*!
    Returns the model information of the device, e.g. N8, or the CPU architect as a fallback. In case
    of error, or the information is not available, an empty string is returned.
*/
QString QDeclarativeDeviceInfo::model() const
{
    return deviceInfo->model();
}

/*!
    Returns the internal product name of the device, e.g. RM-774. In case of error, or the information
    is not available, an empty string is returned.

    For Linux, it returns the codename of the distribution if any.
*/
QString QDeclarativeDeviceInfo::productName() const
{
    return deviceInfo->productName();
}

/*!
    Returns a unique identifier for the device, or an empty string if on error or not available.
*/
QString QDeclarativeDeviceInfo::uniqueDeviceID() const
{
    return deviceInfo->uniqueDeviceID();
}

/*!
    Returns the version of \a type. In case of error, or the version is unknown, an empty string
    is returned. The following versions can be queried:
    \list
    \o Os        Operating system version. For Linux, it returns the version of the
                 distribution if any.
    \o Firmware  Version of (flashable) system as a whole. For Linux, it's the version
                 of the kernel.
    \endlist
*/
QString QDeclarativeDeviceInfo::version(QDeclarativeDeviceInfo::Version type) const
{
    return deviceInfo->version(static_cast<QDeviceInfo::Version>(type));
}

QT_END_NAMESPACE