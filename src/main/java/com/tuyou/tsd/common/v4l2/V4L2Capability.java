package com.tuyou.tsd.common.v4l2;

import java.util.Arrays;
import java.util.Locale;

/**
 * Created by XMD on 2017/5/15.
 */

public class V4L2Capability {
    /**
     * The device supports the video capture interface.
     */
    public static final int V4L2_CAP_VIDEO_CAPTURE=0x00000001;
    /**
     * The device supports the video output interface.
     */
    public static final int V4L2_CAP_VIDEO_OUTPUT=0x00000002;
    /**
     * The device supports the video overlay interface.
     * Overlay typically stores captured images directly
     * in the video memory of a graphics card, with support for clipping.
     */
    public static final int V4L2_CAP_VIDEO_OVERLAY=0x00000004;
    /**
     * The device supports the VBI capture interface
     */
    public static final int V4L2_CAP_VBI_CAPTURE=0x00000010;
    /**
     * The device supports the VBI output interface
     */
    public static final int V4L2_CAP_VBI_OUTPUT=0x00000020;

    public static final int V4L2_CAP_SLICED_VBI_CAPTURE=0x00000040;
    public static final int V4L2_CAP_SLICED_VBI_OUTPUT=0x00000080;

    /**
     * to be deﬁned
     */
    public static final int V4L2_CAP_RDS_CAPTURE=0x00000100;

    /**
     * The device has some sort of tuner or modulator to receive or emit RF-modulated video signals
     */
    public static final int V4L2_CAP_TUNER=0x00010000;

    /**
     * The device has audio inputs or outputs.
     * It may or may not support PCM sampling or output,
     * this function must be implemented as ALSA or OSS PCM interface.
     */
    public static final int V4L2_CAP_AUDIO=0x00020000;


    public static final int V4L2_CAP_RADIO=0x00040000;

    /**
     * The device supports the read() and/or write() I/O methods.
     */
    public static final int V4L2_CAP_READWRITE=0x01000000;

    /**
     * The device supports the asynchronous I/O methods.
     */
    public static final int V4L2_CAP_ASYNCIO=0x02000000;

    /**
     * The device supports the streaming I/O method.
     */
    public static final int V4L2_CAP_STREAMING=0x04000000;

    private static final int[] CAPS_INT = {
            V4L2_CAP_VIDEO_CAPTURE,
            V4L2_CAP_VIDEO_OUTPUT,
            V4L2_CAP_VIDEO_OVERLAY,
            V4L2_CAP_VBI_CAPTURE,
            V4L2_CAP_VBI_OUTPUT,
            V4L2_CAP_SLICED_VBI_CAPTURE,
            V4L2_CAP_SLICED_VBI_OUTPUT,
            V4L2_CAP_RDS_CAPTURE,

            V4L2_CAP_TUNER,
            V4L2_CAP_AUDIO,
            V4L2_CAP_RADIO,

            V4L2_CAP_READWRITE,
            V4L2_CAP_ASYNCIO,
            V4L2_CAP_STREAMING,

    };

    private static final String[] CAPS_STRING = {
            "V4L2_CAP_VIDEO_CAPTURE",
            "V4L2_CAP_VIDEO_OUTPUT",
            "V4L2_CAP_VIDEO_OVERLAY",
            "V4L2_CAP_VBI_CAPTURE",
            "V4L2_CAP_VBI_OUTPUT",
            "V4L2_CAP_SLICED_VBI_CAPTURE",
            "V4L2_CAP_SLICED_VBI_OUTPUT",
            "V4L2_CAP_RDS_CAPTURE",

            "V4L2_CAP_TUNER",
            "V4L2_CAP_AUDIO",
            "V4L2_CAP_RADIO",

            "V4L2_CAP_READWRITE",
            "V4L2_CAP_ASYNCIO",
            "V4L2_CAP_STREAMING",

    };



    private final String driver;
    private final String card;
    private final String bus_info;
    private final int version; //#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
    private final int capabilities;//check linux/videodev2.h
    private final int[] reserved;


    V4L2Capability(String driver, String card, String bus_info, int version, int capabilities, int[] reserved) {
        this.driver = driver;
        this.card = card;
        this.bus_info = bus_info;
        this.version = version;
        this.capabilities = capabilities;
        this.reserved = reserved;
    }

    public String getDriver() {
        return driver;
    }

    public String getCard() {
        return card;
    }

    public String getBus_info() {
        return bus_info;
    }

    public int getVersion() {
        return version;
    }

    public String getVersionString() {
        return String.format(Locale.getDefault(),"%d.%d.%d",(version>>16) & 0x00FF,(version >> 8) & 0x00FF,version & 0x00FF);
    }

    public int getCapabilities() {
        return capabilities;
    }

    public int[] getReserved() {
        return reserved;
    }

    public String getCapabilitiesString(){
        StringBuilder stringBuilder = new StringBuilder();
        for(int i=0;i<CAPS_INT.length;i++){
            if((capabilities & CAPS_INT[i]) != 0){
                stringBuilder.append(CAPS_STRING[i]).append(",");
            }
        }
        return stringBuilder.toString().substring(0,stringBuilder.length()-1);
    }

    @Override
    public String toString() {
        return "V4L2Capability{" +
                "driver='" + driver + '\'' +
                ", card='" + card + '\'' +
                ", bus_info='" + bus_info + '\'' +
                ", version=" + getVersionString() +
                ", capabilities=" + getCapabilitiesString() +
                ", reserved=" + Arrays.toString(reserved) +
                '}';
    }
}
