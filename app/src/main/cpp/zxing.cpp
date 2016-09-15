#include <jni.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <string>
#include <zxing/MultiFormatReader.h>
#include <zxing/Exception.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/DecodeHints.h>
#include "PlanarYUVLuminanceSource.h"

using namespace std;
using namespace zxing;
using namespace qrviddec;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_wuba_zxing_QbarNative_decode(JNIEnv *env, jobject instance,
                                                                 jbyteArray yuvData_,
                                                                 jint width, jint height,
                                                                 jint cropLeft, jint cropTop, jint cropWidth,
                                                                 jint cropHeight,
                                                                 jboolean reverseHorizontal) {
    jbyte *yuvData = env->GetByteArrayElements(yuvData_, NULL);

    std::string codeResult = "";
    try {
        // Convert the buffer to something that the library understands.
        ArrayRef<char> data((char*)yuvData, width*height);
        Ref<LuminanceSource> source (new PlanarYUVLuminanceSource(data, width, height,cropLeft,cropTop,cropWidth,cropHeight,reverseHorizontal));
        
        // Turn it into a binary image.
        Ref<Binarizer> binarizer (new HybridBinarizer(source));
        Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));

        // Tell the decoder to try as hard as possible.
        DecodeHints hints(DecodeHints::DEFAULT_HINT);
        hints.setTryHarder(true);
        
        // Perform the decoding.
        MultiFormatReader reader;
        reader.setHints(hints);
        Ref<Result> result(reader.decodeWithState(image));
        
        // Output the result.
        codeResult = result->getText()->getText();
        cout << result->getText()->getText() << endl;
    } catch (zxing::Exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    env->ReleaseByteArrayElements(yuvData_, yuvData, 0);

    return env->NewStringUTF(codeResult.c_str());
}
