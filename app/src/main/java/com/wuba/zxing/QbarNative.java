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
     * @param bytes             数据
     * @param width             数据宽度
     * @param height            数据高度
     * @param cropLeft
     * @param cropTop
     * @param cropWidth
     * @param cropHeight
     * @param isRotate          是否要旋转,true说明要处理的数据还没
     * @param reverseHorizontal
     * @return
     */
    public native String decode(byte[] bytes, int width, int height, int cropLeft
            , int cropTop, int cropWidth, int cropHeight, boolean isRotate, boolean reverseHorizontal);

}
