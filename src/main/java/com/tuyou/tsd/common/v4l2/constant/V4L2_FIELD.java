package com.tuyou.tsd.common.v4l2.constant;

/**
 * Created by XMD on 2017/5/16.
 */

public class V4L2_FIELD {
    /**
     * Applications request this ﬁeld order when any one of the
     * V4L2_FIELD_NONE,
     * V4L2_FIELD_TOP,
     * V4L2_FIELD_BOTTOM,
     * or V4L2_FIELD_INTERLACED
     * formats is acceptable.
     * Drivers choose depending on hardware capabilities
     * or e. g. the requested image size,
     * and return the actual ﬁeld order.
     * struct v4l2_buffer field can never be V4L2_FIELD_ANY.
     */
    public static final int V4L2_FIELD_ANY = 0;

    /**
     * Images are in progressive format,
     * not interlaced.
     * The driver may also indicate this order when it cannot distinguish between V4L2_FIELD_TOP and V4L2_FIELD_BOTTOM.
     */
    public static final int V4L2_FIELD_NONE = 1;

    /**
     * Images consist of the top ﬁeld only.
     */
    public static final int V4L2_FIELD_TOP = 2;

    /**
     * Images consist of the bottom ﬁeld only.
     * Applications may wish to prevent a device from capturing
     * interlaced images because they will have "comb" or "feathering" artefacts around moving objects.
     */
    public static final int V4L2_FIELD_BOTTOM = 3;

    /**
     * Images contain both ﬁelds,
     * interleaved line by line.
     * The temporal order of the ﬁelds (whether the top or bottom ﬁeld is ﬁrst transmitted) depends on the current video standard.
     * M/NTSC transmits the bottom ﬁeld ﬁrst, all other standards the top ﬁeld ﬁrst.
     */
    public static final int V4L2_FIELD_INTERLACED = 4;

    /**
     * Images contain both ﬁelds,
     * the top ﬁeld lines are stored ﬁrst in memory,
     * immediately followed by the bottom ﬁeld lines.
     * Fields are always stored in temporal order,
     * the older one ﬁrst in memory.
     * Image sizes refer to the frame, not ﬁelds.
     */
    public static final int V4L2_FIELD_SEQ_TB = 5;

    /**
     * Images contain both ﬁelds,
     * the bottom ﬁeld lines are stored ﬁrst in memory,
     * immediately followed by the top ﬁeld lines.
     * Fields are always stored in temporal order,
     * the older one ﬁrst in memory.
     * Image sizes refer to the frame,
     * not ﬁelds.
     */
    public static final int V4L2_FIELD_SEQ_BT = 6;

    /**
     *  The two ﬁelds of a frame are passed in separate buffers,
     *  in temporal order, i. e. the older one ﬁrst.
     *  To indicate the ﬁeld parity (whether the current ﬁeld is a top or bottom ﬁeld) the driver or application,
     *  depending on data direction,
     *  must set struct v4l2_buffer field to V4L2_FIELD_TOP or V4L2_FIELD_BOTTOM.
     *  Any two successive ﬁelds pair to build a frame.
     *  If ﬁelds are successive, without any dropped ﬁelds between them (ﬁelds can drop individually),
     *  can be determined from the struct v4l2_buffer sequence ﬁeld.
     *  Image sizes refer to the frame, not ﬁelds.
     *  This format cannot be selected when using the read/write I/O method.
     */
    public static final int V4L2_FIELD_ALTERNATE = 7;
}
