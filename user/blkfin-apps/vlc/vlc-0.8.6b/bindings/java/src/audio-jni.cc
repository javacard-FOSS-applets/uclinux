/*****************************************************************************
 * audio-jni.cc: JNI native audio functions for VLC Java Bindings
 *****************************************************************************
 * Copyright (C) 1998-2006 the VideoLAN team
 *
 * Authors: Filippo Carone <filippo@carone.org>
 *
 *
 * $Id $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 *****************************************************************************/

/* These are a must*/
#include <jni.h>

#include <vlc/libvlc.h>

/* JVLC internal imports, generated by gcjh */
#include "../includes/Audio.h"
#include "utils.h"

JNIEXPORT jboolean JNICALL Java_org_videolan_jvlc_Audio__1getMute (JNIEnv *env, jobject _this) 
{
    INIT_FUNCTION;
    jboolean res;

    res = (jboolean) libvlc_audio_get_mute( ( libvlc_instance_t * ) instance, exception );

    CHECK_EXCEPTION;

    return res;
    
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Audio__1setMute (JNIEnv *env, jobject _this, jboolean value) 
{
    INIT_FUNCTION;

    libvlc_audio_set_mute( ( libvlc_instance_t * ) instance, value, exception );

    CHECK_EXCEPTION;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Audio__1toggleMute (JNIEnv *env, jobject _this) 
{
    INIT_FUNCTION;

    libvlc_audio_get_mute( ( libvlc_instance_t * ) instance, exception );
    
    CHECK_EXCEPTION;
}

JNIEXPORT jint JNICALL Java_org_videolan_jvlc_Audio__1getVolume (JNIEnv *env, jobject _this)
{
    INIT_FUNCTION;
    jint res = 0;

    res = libvlc_audio_get_volume( ( libvlc_instance_t * ) instance, exception );

    CHECK_EXCEPTION;

    return res;
}

JNIEXPORT void JNICALL Java_org_videolan_jvlc_Audio__1setVolume (JNIEnv *env, jobject _this, jint volume)
{
    INIT_FUNCTION;

    libvlc_audio_set_volume( ( libvlc_instance_t * ) instance, volume, exception );

    CHECK_EXCEPTION;
}

