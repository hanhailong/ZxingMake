package com.wuba.zxing;

/**
 * Created by HanHailong on 16/9/14.
 */

public class QbarNative {

    static {
        System.loadLibrary("zxing");
    }

    /**
     * 解码
     *
     * @param bytes
     * @param width
     * @param height
     * @param cropLeft
     * @param cropTop
     * @param cropWidth
     * @param cropHeight
     * @param reverseHorizontal
     * @return
     */
    public native String decode(byte[] bytes, int width, int height, int cropLeft
            , int cropTop, int cropWidth, int cropHeight, boolean reverseHorizontal);

}
