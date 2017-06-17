package com.tuyou.tsd.common.v4l2;

import android.graphics.Rect;

/**
 * Created by XMD on 2017/5/15.
 */

public class V4L2CropCap {


    /**
     * Deﬁnes the window within capturing or output is possible,
     * this may exclude for example the horizontal and vertical blanking areas.
     * The cropping rectangle cannot exceed these limits.
     * Width and height are deﬁned in pixels,
     * the driver writer is free to choose origin and units of the coordinate system in the analog domain.
     */
    private final Rect bounds;
    /**
     * Default cropping rectangle,
     * it shall cover the "whole picture".
     * Assuming pixel aspect 1/1 this could be for example a 640 × 480 rectangle for NTSC,
     * a 768 × 576 rectangle for PAL and SECAM centered over the active picture area.
     * The same co-ordinate system as for bounds is used.
     */
    private final Rect defrect;

    /**
     * This is the pixel aspect (y / x) when no scaling is applied,
     * the ratio of the actual sampling frequency and the frequency required to get square pixels.
     * When cropping coordinates refer to square pixels,
     * the driver sets pixelaspect to 1/1.
     * Other common values are 54/59 for PAL and SECAM,
     * 11/10 for NTSC sampled according to [ITU601>].
     */
    private final V4L2Fract pixelaspect;

    public V4L2CropCap(Rect bounds, Rect defrect, V4L2Fract pixelaspect) {
        this.bounds = bounds;
        this.defrect = defrect;
        this.pixelaspect = pixelaspect;
    }

    @Override
    public String toString() {
        return "V4L2CropCap{" +
                "bounds=" + bounds +
                ", defrect=" + defrect +
                ", pixelaspect=" + pixelaspect +
                '}';
    }

    public Rect getBounds() {
        return bounds;
    }

    public Rect getDefrect() {
        return defrect;
    }

    public V4L2Fract getPixelaspect() {
        return pixelaspect;
    }
}
