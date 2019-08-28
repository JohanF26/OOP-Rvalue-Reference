#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "MyInt.hpp"
#include <initializer_list>
#include <string.h>
#include <stdio.h>
#include <chrono>

//Learned about chrono library from
//https://en.cppreference.com/w/cpp/chrono
//And implemented following examples

namespace cs540{

class Array{

private:
    MyInt* arrContents;
    int arrSize;

public:
    //constructor
    Array(): arrContents(nullptr), arrSize(0){}
    //constructor passing initializer list
    Array(std::initializer_list<MyInt> initList){
        arrSize = initList.size();
        arrContents = new MyInt[arrSize];
        auto it = initList.begin();
        int i = 0;
        while(it != initList.end()){
            arrContents[i] = *it;
            i++;
            it++;
        }
    }
    //copy constructor
    Array(Array &arr){
        arrSize = arr.arrSize;
        arrContents = new MyInt[arrSize];
        memcpy(arrContents, arr.arrContents, (arrSize*sizeof(MyInt)));
    }
    //move constructor, setting arr contents to nullptr afterwards
    Array(Array &&arr){
        arrSize = arr.arrSize;
        arrContents = arr.arrContents;
        arr.clear();
    }
    //function to clear the Array without deleting contents
    void clear(){
        arrSize = 0;
        arrContents = nullptr;
    }
    //clear the array deleting content
    void reset(){
        arrSize = 0;
        delete [] arrContents;
        arrContents = nullptr;
    }
    //copy assignment, handle self assignment
    Array& operator=(Array &arr){
        if(&arr == this){
            return *this;
        }
        if(arrContents != nullptr){
            delete [] arrContents;
        }
        arrSize = arr.arrSize;
        arrContents = new MyInt[arrSize];
        memcpy(arrContents, arr.arrContents, (arrSize*sizeof(MyInt)));
        return *this;
    }
    //move assignment
    Array& operator=(Array &&arr){
        if(&arr == this){
            return *this;
        }
        if(arrContents != nullptr){
            delete [] arrContents;
        }
        arrSize = arr.arrSize;
        arrContents = arr.arrContents;
        arr.clear();
        return *this;
    }
    friend std::ostream& operator<<(std::ostream &os, const Array &arr){
        int i = 0;
        while(i < arr.arrSize){
            if(i == arr.arrSize-1){
                os << arr.arrContents[i];
                break;
            }
            os << arr.arrContents[i] << ", ";
            i++;
        }
        return os;
    }
    //Destructor
    ~Array(){
        delete [] arrContents;
        arrContents = nullptr;
    }

    static void printDuration(std::chrono::time_point<std::chrono::system_clock> start, std::chrono::time_point<std::chrono::system_clock> end){
        std::chrono::duration<double, std::ratio<1, 1000 > > timeDuration = end - start;
        printf("\tElapsed: %fl ms\n", timeDuration.count());
    }

    //must be static since it is called as Array::move_performance_test
    static void move_performance_test(){
        Array testArr;
        testArr.arrContents = new MyInt[1000000];
        for(int i = 0; i < 1000000; i++){
            testArr.arrContents[i] = i;
        }

        std::chrono::time_point<std::chrono::system_clock> timeStart, timeEnd;

        //Copy Construc
        timeStart = std::chrono::system_clock::now();
        Array temp1{testArr};
        timeEnd = std::chrono::system_clock::now();
        printf("Copy Constructor:\n");
        printDuration(timeStart, timeEnd);

        //Move Construc
        timeStart = std::chrono::system_clock::now();
        Array temp2{std::move(testArr)};
        timeEnd = std::chrono::system_clock::now();
        printf("Move Constructor:\n");
        printDuration(timeStart, timeEnd);

        //Copy assign
        timeStart = std::chrono::system_clock::now();
        Array temp3;
        temp3 = temp2;
        timeEnd = std::chrono::system_clock::now();
        printf("Copy Assignment:\n");
        printDuration(timeStart, timeEnd);

        //Move assign
        timeStart = std::chrono::system_clock::now();
        Array temp4;
        temp4 = std::move(temp3);
        timeEnd = std::chrono::system_clock::now();
        printf("Move Assignment:\n");
        printDuration(timeStart, timeEnd);

    }

};

}



#endif
