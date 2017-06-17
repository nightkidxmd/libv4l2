package com.tuyou.tsd.common.v4l2;

/**
 * Created by XMD on 2017/5/15.
 */

public class V4L2Fract {
    public int numerator;
    public int denominator;

    public V4L2Fract(int numerator, int denominator) {
        this.numerator = numerator;
        this.denominator = denominator;
    }

    @Override
    public String toString() {
        return "V4L2Fract{" +
                "numerator=" + numerator +
                ", denominator=" + denominator +
                '}';
    }
}
