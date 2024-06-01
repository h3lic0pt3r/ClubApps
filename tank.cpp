#include "new_tank.h"
#include <stddef.h>

template<typename T>
Tank<T>::Tank() {
    Resize(2);
}

template<typename T>
void Tank<T>::push_back(const T& new_ele) {
    if(size_cur >= size_max)
        Resize(size_max*2);                  //resizing extra to ensure quicker execution times
        
    m_data[size_cur] = new_ele;
        
    size_cur++;
}

template<typename T>
void Tank<T>::pop_back(){
    size_cur--;
    if(size_cur<=size_max*2)
        Resize(size_max/2);                  //resizing extra to ensure quicker execution times
}   

template<typename T>
T& Tank<T>::operator[](size_t index) {
    return m_data[index];
}

template<typename T>
const T& Tank<T>::at(size_t index) const {
    return m_data[index];
}

template<typename T>
size_t Tank<T>::size() const {
    return size_cur;
}

template<typename T>
void Tank<T>::Resize(size_t Size_Req) {
    T * new_null = new T[Size_Req];     //allocate a larger memory block

    if(Size_Req < size_cur)                 //check wheather the Tank is increasing in size or decreasing in size
        size_cur = Size_Req;

    for(size_t i = 0; i < size_cur; i++){   //copying all of the data on prev mem stack to the newly allocated one
        new_null[i] = m_data[i];
    }
    delete[] m_data;                      //freeing the memory of the redundant memblock
    m_data   = new_null;                //reassigning newly created memblock as the start pointer
    size_max = Size_Req;
}

template<typename U>
U accumulate(Tank<U>& tank_class){
    U total_sum = 0;
    for(size_t i = 0; i < tank_class.size(); i++){       //loop to iterate through the array and sum it up
        total_sum += tank_class[i];
    }

    return total_sum;
}