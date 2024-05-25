#include <stddef.h>

template<typename T>
class Tank
{
public:
    Tank(){
        Resize(2);
    }

    void push_back(const T& new_ele){
        if(size_cur>=size_max)
            Resize(size_max + size_max/2);                  //resizing extra to ensure quicker execution times
        
        m_data[size_cur] = new_ele;
        
        size_cur++;
    }

    void pop_back(){ Resize(size_cur--); }

    // const T& operator[](size_t index) const 
    // {
    //     return m_data[index];
    // }

    T& operator[](size_t index)                                 //adding function to access data via indexing
    {
        return m_data[index];
    }
    
    T at(size_t index) const {   return m_data[index];   }

    template<typename U>
    friend U accumulate(Tank<U>& tank_class);                  //using friend function to pass tank as an argument in itelf

    size_t size() const {  return size_cur;  }


private:
    T* m_data = nullptr; //0 index location of our tank

    size_t size_cur = 0;     //current number of elements in the Tank
    size_t size_max = 2; //max possible elements in the Tank with current memory space

private:
    void Resize(size_t Size_Req)
    {
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
    
};
