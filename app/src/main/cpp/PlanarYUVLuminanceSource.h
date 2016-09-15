//
// Created by HailongHan on 16/9/15.
//

#ifndef ZXINGMAKE_PLANARYUVLUMINANCESOURCE_H
#define ZXINGMAKE_PLANARYUVLUMINANCESOURCE_H

#define THUMBNAIL_SCALE_FACTOR 2

#include <zxing/LuminanceSource.h>

using namespace zxing;
namespace qrviddec {
    class PlanarYUVLuminanceSource : public LuminanceSource {
        private :
        ArrayRef<char> yuvData;
        int dataWidth;
        int dataHeight;
        int left;
        int top;

        public:
        PlanarYUVLuminanceSource(ArrayRef<char> yuvData,int dataWidth,int dataHeight,int left,int top,int width,int height,bool reverseHorizontal);
        ~PlanarYUVLuminanceSource();
        
        ArrayRef<char> getRow(int y,ArrayRef<char> row) const;
        ArrayRef<char> getMatrix() const;
        bool isCropSupported() const;
        Ref<LuminanceSource> crop(int left, int top, int width, int height) const;
    };
}

#endif //ZXINGMAKE_PLANARYUVLUMINANCESOURCE_H
