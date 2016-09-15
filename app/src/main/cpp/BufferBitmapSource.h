//
// Created by HailongHan on 16/9/14.
//

#ifndef ZXINGMAKE_BUFFERBITMAPSOURCE_H
#define ZXINGMAKE_BUFFERBITMAPSOURCE_H

#include <zxing/LuminanceSource.h>
#include <stdio.h>
#include <stdlib.h>

using namespace zxing;

namespace qrviddec {

    class BufferBitmapSource : public LuminanceSource {

    private:
      ArrayRef<char> buffer;

    public:
      BufferBitmapSource(int inWidth, int inHeight, ArrayRef<char> buffer);
      ~BufferBitmapSource();

      ArrayRef<char> getRow(int y, ArrayRef<char> row) const;
      ArrayRef<char> getMatrix() const;
    };
}


#endif //ZXINGMAKE_BUFFERBITMAPSOURCE_H
