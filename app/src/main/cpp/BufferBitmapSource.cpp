//
// Created by HailongHan on 16/9/14.
//
// 参考资料
// http://wiki.ssrrsummerschool.org/doku.php?id=robocup2012:qrcode-cppexample
// http://stackoverflow.com/questions/17973641/how-to-decode-data-using-zxing-c
//

#include "BufferBitmapSource.h"
#include <iostream>

namespace qrviddec {

    BufferBitmapSource::BufferBitmapSource(int inWidth, int inHeight, ArrayRef<char> inBuffer)
        :LuminanceSource(inWidth,inHeight){
        buffer = inBuffer;
    }

    BufferBitmapSource::~BufferBitmapSource(){
    }

    ArrayRef<char> BufferBitmapSource::getRow(int y,ArrayRef<char> row) const {
        if (y < 0 || y >= height){
            fprintf(stderr, "ERROR, attempted to read row %d of a %d height image.\n", y, height);
            return NULL;
        }
        // WARNING: NO ERROR CHECKING! You will want to add some in your code.
        //if (row == NULL) row = new unsigned char[width];
        //for (int x = 0; x < width; x ++){
        //    row[x] = buffer[y*width+x];
        //}

        //if (row.empty()){
        //	  char* p = char[width];
        //	  ArrayRef<char> tmp(p, width);
        //	  row = tmp;
        //}
        if (!row)	{
        	  char* p = new char[width];
        	  ArrayRef<char> tmp(p, width);
        	  row = tmp;
        }
        for (int x = 0; x < width; x ++)
        {
        	row[x] = buffer[y*width+x];
        }

        return row;
    }

    ArrayRef<char> BufferBitmapSource::getMatrix() const {
        return buffer;
    }
}