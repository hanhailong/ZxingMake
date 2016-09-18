/*
 * Copyright (C) 2010 ZXing authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.dtr.zxing.decode;

import android.graphics.Rect;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;

import com.dtr.zxing.activity.CaptureActivity;
import com.wuba.zxing.QbarNative;
import com.wuba.zxing.R;

public class DecodeHandler extends Handler {

    private final CaptureActivity activity;
    private QbarNative mQbarNative;

    private boolean running = true;

    public DecodeHandler(CaptureActivity activity) {
        mQbarNative = new QbarNative();
        this.activity = activity;
    }

    @Override
    public void handleMessage(Message message) {
        if (!running) {
            return;
        }
        switch (message.what) {
            case R.id.decode:
                decode((byte[]) message.obj, message.arg1, message.arg2);
                break;
            case R.id.quit:
                running = false;
                Looper.myLooper().quit();
                break;
        }
    }

    /**
     * Decode the data within the viewfinder rectangle, and time how long it
     * took. For efficiency, reuse the same reader objects from one decode to
     * the next.
     *
     * @param data   The YUV preview frame.
     * @param width  The width of the preview frame.
     * @param height The height of the preview frame.
     */
    private void decode(byte[] data, int width, int height) {
        Rect rect = activity.getCropRect();
        long decodeStartTime = System.currentTimeMillis();
        String textResult = mQbarNative.decode(data, width, height
                , rect.left, rect.top, rect.width(), rect.height(), true, false);

        Handler handler = activity.getHandler();
        if (!TextUtils.isEmpty(textResult)) {
            // Don't log the barcode contents for security.
            if (handler != null) {
                long endTime = System.currentTimeMillis();
                Log.e("DecodeHandler", "解码时间为:" + (endTime - decodeStartTime));
                Message message = Message.obtain(handler, R.id.decode_succeeded, textResult);
                Bundle bundle = new Bundle();
//				bundleThumbnail(source, bundle);
                message.setData(bundle);
                message.sendToTarget();
            }
        } else {
            if (handler != null) {
                Message message = Message.obtain(handler, R.id.decode_failed);
                message.sendToTarget();
            }
        }

    }

}
