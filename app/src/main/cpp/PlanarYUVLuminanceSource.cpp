//
// Created by HailongHan on 16/9/15.
//

#include "PlanarYUVLuminanceSource.h"
#include <iostream>

namespace qrviddec {

    PlanarYUVLuminanceSource::PlanarYUVLuminanceSource(ArrayRef<char> inYuvData,int inDataWidth,
    int inDataHeight,int inLeft,int inTop,int inWidth,int inHeight,bool reverseHorizontals)
    : LuminanceSource(inWidth,inHeight){
        
        if (inLeft + inWidth > inDataWidth || inTop + inHeight > inDataHeight) {
            throw "Crop rectangle does not fit within image data.";
        }
        
        yuvData = inYuvData;
        dataWidth = inDataWidth;
        dataHeight = inDataHeight;
        left = inLeft;
        top = inTop;
        
        if (reverseHorizontals) {
            reverseHorizontal(inWidth,inHeight);
        }
    }
    
    PlanarYUVLuminanceSource::~PlanarYUVLuminanceSource(){
    }
    
    ArrayRef<char> PlanarYUVLuminanceSource::getRow(int y,ArrayRef<char> row) const {
        if (y < 0 || y > getHeight()) {
            throw "Requested row is outside the image:"+y;
        }
        
        int width = getWidth();
        
        if (row == NULL) {
            char* p = new char[width];
            ArrayRef<char> tmp(p, width);
            row = tmp;
        }
    
        int offset = (y + top) * dataWidth + left;
        
        //进行拷贝
        for (int x = 0 ; x < width ; x ++){
            row[x] = yuvData[offset + x];
        }
        
        return row;
    }
    
    ArrayRef<char> PlanarYUVLuminanceSource::getMatrix() const {
        int width = getWidth();
        int height = getHeight();
        
        if (width == dataWidth && height == dataHeight) {
            return yuvData;
        }
        
        int area = width * height;
        
        ArrayRef<char> matrix(new char[area],area);
        
        int inputOffset = top * dataWidth + left;
        
        // If the width matches the full width of the underlying data, perform a single copy.
        if (width == dataWidth) {
            //进行拷贝
            for (int x = 0 ; x < area ; x ++) {
                matrix[x] = yuvData[inputOffset + x];
            }
            return matrix;
        }
        
        // Otherwise copy one cropped row at a time.
        for (int y = 0; y < height; y++) {
            int outputOffset = y * width;
            for (int x = 0 ; x < width ; x++) {
                matrix[outputOffset+x] = yuvData[inputOffset + x];
            }
            inputOffset += dataWidth;
        }
        
        return matrix;
    }
    
    bool PlanarYUVLuminanceSource::isCropSupported() const {
        return true;
    }
    
    Ref<LuminanceSource> PlanarYUVLuminanceSource::crop(int inLeft, int inTop, int width, int height) const {
        Ref<LuminanceSource> source(new PlanarYUVLuminanceSource(yuvData,dataWidth,dataHeight,left + inLeft,top + inTop,width,height,false));
        return source;
    }
    
    void PlanarYUVLuminanceSource::reverseHorizontal(int width , int height) const {
        ArrayRef<char> tempData = yuvData;

        for (int y = 0, rowStart = top * dataWidth + left; y < height; y++, rowStart += dataWidth) {
            int middle = rowStart + width / 2;
            for (int x1 = rowStart, x2 = rowStart + width - 1; x1 < middle; x1++, x2--) {
                unsigned char temp = tempData[x1];
                tempData[x1] = tempData[x2];
                tempData[x2] = temp;
            }
        }
        return;
    }
}
