package com.tuyou.tsd.common.v4l2;

import android.support.annotation.NonNull;

import java.util.Locale;

/**
 * Created by XMD on 2017/5/16.
 */

public class V4L2PixelFormat {
    public static int V4L2_PIXEL_FORMAT_YUYV = toPixelFormat("YUYV");
    public static int V4L2_PIXEL_FORMAT_H264 = toPixelFormat("H264");

    public static int toPixelFormat(@NonNull String format){
        if(format.length() != 4){
            throw new IllegalArgumentException("pixelformat should be 4 length String,bug got "+format);
        }
        return (int)format.charAt(0)|(int)format.charAt(1) << 8|(int)format.charAt(2)<<16|(int)format.charAt(3)<<24;
    }

    public static String fromPixelFormat(int pixelformat){
       return String.format(Locale.getDefault(),"%c%c%c%c",pixelformat & 0xFF, (pixelformat >> 8) & 0xFF,
                (pixelformat >> 16) & 0xFF, (pixelformat >> 24) & 0xFF);
    }
}
