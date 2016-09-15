#include <jni.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <fstream>
#include <string>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/Exception.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/DecodeHints.h>
#include "BufferBitmapSource.h"

using namespace std;
using namespace zxing;
using namespace zxing::qrcode;
using namespace qrviddec;

extern "C"
JNIEXPORT jstring JNICALL
Java_com_wuba_zxing_QbarNative_decode(JNIEnv *env, jobject instance, jbyteArray bytes_,
                                           jint width, jint height) {
    jbyte *bytes = env->GetByteArrayElements(bytes_, NULL);

    std::string codeResult = "";
    try {
        // Convert the buffer to something that the library understands.
        ArrayRef<char> data((char*)bytes, width*height);
        Ref<LuminanceSource> source (new BufferBitmapSource(width, height, data));
        // Turn it into a binary image.
        Ref<Binarizer> binarizer (new GlobalHistogramBinarizer(source));
        Ref<BinaryBitmap> image(new BinaryBitmap(binarizer));

        // Tell the decoder to try as hard as possible.
        DecodeHints hints(DecodeHints::DEFAULT_HINT);
        hints.setTryHarder(true);

        // Perform the decoding.
        QRCodeReader reader;
        Ref<Result> result(reader.decode(image, hints));

        // Output the result.
        codeResult = result->getText()->getText();
        cout << result->getText()->getText() << endl;
    } catch (zxing::Exception& e){
        cerr << "Error: " << e.what() << endl;
    }

    env->ReleaseByteArrayElements(bytes_, bytes, 0);

    return env->NewStringUTF(codeResult.c_str());
}