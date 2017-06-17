package com.tuyou.tsd.common.v4l2.constant;

/**
 * Created by XMD on 2017/5/16.
 */

public class V4L2_BUF_TYPE {
    /**
     * Buffer of a video capture stream
     */
    public static final int V4L2_BUF_TYPE_VIDEO_CAPTURE = 0;

    /**
     * Buffer of a video output stream
     */
    public static final int V4L2_BUF_TYPE_VIDEO_OUTPUT = 1;

    /**
     * Buffer for video overlay
     */
    public static final int V4L2_BUF_TYPE_VIDEO_OVERLAY = 2;

    /**
     * Buffer of a raw VBI capture stream
     */
    public static final int V4L2_BUF_TYPE_VBI_CAPTURE = 3;

    /**
     * Buffer of a raw VBI output stream
     */
    public static final int V4L2_BUF_TYPE_VBI_OUTPUT = 4;

    public static final int V4L2_BUF_TYPE_SLICED_VBI_CAPTURE = 5;
    public static final int V4L2_BUF_TYPE_SLICED_VBI_OUTPUT = 6;

    /**
     * This and higher values are reserved for custom (driver deﬁned) buffer types
     */
    public static final int V4L2_BUF_TYPE_PRIVATE = 7;
}
