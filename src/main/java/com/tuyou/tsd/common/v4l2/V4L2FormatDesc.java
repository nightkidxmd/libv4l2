package com.tuyou.tsd.common.v4l2;

import java.util.Arrays;

/**
 * Created by XMD on 2017/5/16.
 */

public class V4L2FormatDesc {
    public int index;
    public int flags;
    public String description;
    public int pixelformat;
    public int[] reserved;

    public V4L2FormatDesc(int index, int flags, String description, int pixelformat, int[] reserved) {
        this.index = index;
        this.flags = flags;
        this.description = description;
        this.pixelformat = pixelformat;
        this.reserved = reserved;
    }

    @Override
    public String toString() {
        return "V4L2FormatDesc{" +
                "index=" + index +
                ", flags=" + flags +
                ", description='" + description + '\'' +
                ", pixelformat=" + V4L2PixelFormat.fromPixelFormat(pixelformat)+
                ", reserved=" + Arrays.toString(reserved) +
                '}';
    }
}
