//
//  Temp.h
//  com.nguyenhuy.mygame.planetap
//
//  Created by NguyenHuy on 1/28/16.
//
//

#ifndef __com_nguyenhuy_mygame_planetap__Temp__
#define __com_nguyenhuy_mygame_planetap__Temp__

#include <stdio.h>
#include "functional"
template <class T,int>
class myArray{
public:
    int numElements;
    T * data;
    myArray(T *data, int count);
    ~myArray();
    void add();
    void removeAt();
};
template <class T,int i>
myArray<T,i>::myArray(T *data, int count):data(data),numElements(count){
    
}
template <class T,int i>
void myArray<T,i>::removeAt(){}
template <class T,int i>
void myArray<T,i>::add(){}
std::function<void(int,int)> nh;
#endif /* defined(__com_nguyenhuy_mygame_planetap__Temp__) */
void (*fsdfsd)();