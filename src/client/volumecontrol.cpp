/*
 * Copyright 2013 Giulio Camuffo <giuliocamuffo@gmail.com>
 *
 * This file is part of Orbital
 *
 * Orbital is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nome-Programma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nome-Programma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtQml>

#include "volumecontrol.h"

const int a = qmlRegisterType<VolumeControl>("Orbital", 1, 0, "VolumeControl");

const char *card = "default";
const char *selem_name = "Master";

VolumeControl::VolumeControl(QObject *parent)
             : QObject(parent)
{
    snd_mixer_open(&m_handle, 0);
    snd_mixer_attach(m_handle, card);
    snd_mixer_selem_register(m_handle, NULL, NULL);
    snd_mixer_load(m_handle);

    snd_mixer_selem_id_alloca(&m_sid);
    snd_mixer_selem_id_set_index(m_sid, 0);
    snd_mixer_selem_id_set_name(m_sid, selem_name);
    m_elem = snd_mixer_find_selem(m_handle, m_sid);
    snd_mixer_selem_get_playback_volume_range(m_elem, &m_min, &m_max);
}

VolumeControl::~VolumeControl()
{
    snd_mixer_close(m_handle);
}

void VolumeControl::changeMaster(int change)
{
    setMaster(master() + change);
}

void VolumeControl::setMaster(int volume)
{
    if (volume > 100) volume = 100;
    if (volume < 0) volume = 0;
    snd_mixer_selem_set_playback_volume_all(m_elem, volume * m_max / 100.f);

    emit masterChanged();
}

int VolumeControl::master() const
{
    long vol;
    snd_mixer_selem_get_playback_volume(m_elem, SND_MIXER_SCHN_FRONT_LEFT, &vol);
    vol *= 100.f / (float)m_max;
    return vol;
}