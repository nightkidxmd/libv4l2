package com.tuyou.tsd.common.v4l2;

import android.graphics.Rect;
import android.support.annotation.Nullable;

import com.tuyou.tsd.common.v4l2.constant.V4L2_BUF_TYPE;
import com.tuyou.tsd.common.v4l2.constant.V4L2_FIELD;
import com.tuyou.tsd.common.v4l2.constant.V4L2_MEMORY;

/**
 * Created by XMD on 2017/5/15.
 */

public class V4L2 {
    static {
        System.loadLibrary("v4l2");
    }

    /**
     *
     * @param deviceNo  /dev/video<b>%d</b>
     * @return  -1 error else return fd No.
     */
    public native int openDevice(int deviceNo);


    /**
     *
     * @param fd
     * @return 0 success, -1 error
     */
    public native int closeDevice(int fd);

    /**
     *
     * @param fd
     * @return null if Fail
     */
    public native @Nullable
    V4L2Capability queryCapability(int fd);

    /**
     *
     * @param fd
     * @param type {@link V4L2_BUF_TYPE}
     * @return
     */
    public native @Nullable V4L2CropCap queryCropCapability(int fd,int type);


    /**
     *
     * @param fd
     * @param type {@link V4L2_BUF_TYPE}
     * @param rect
     * @return
     */
    public native int setCrop(int fd,int type,Rect rect);

    /**
     *
     * @param fd
     *
     * @return
     */
    public native @Nullable Rect getCrop(int fd);

    /**
     *
     * @param type {@link V4L2_BUF_TYPE}
     * @return
     */
    public native @Nullable V4L2FormatDesc[] queryFormat(int fd,int type);


    /**
     *
     * @param fd
     * @param type   {@link V4L2_BUF_TYPE}
     * @param width
     * @param height
     * @param pixelformat
     * @param field   {@link V4L2_FIELD}
     * @return
     */
    public native int setFormat(int fd,int type,int width,int height,int pixelformat,int field);

    /**
     *
     * @param fd
     * @param count
     * @param type  {@link V4L2_BUF_TYPE}
     * @param memory {@link V4L2_MEMORY}
     * @return
     */
    public native int initmmap(int fd,int count,int type,int memory);


    /**
     *
     * @param fd
     * @return
     */
    public native int uninitmmap(int fd);


    /**
     *
     * @param fd
     * @param type  {@link V4L2_BUF_TYPE}
     * @param memory {@link V4L2_MEMORY}
     * @return
     */
    public native int streamon(int fd,int type,int memory);


    /**
     *
     * @param fd
     * @param type  {@link V4L2_BUF_TYPE}
     * @return
     */

    public native int streamoff(int fd,int type);


    /**
     *
     * @param fd
     * @param type  {@link V4L2_BUF_TYPE}
     * @param memory {@link V4L2_MEMORY}
     * @param buffer
     * @return
     */
    public native int readFrame(int fd,int type,int memory,byte[] buffer);
}
