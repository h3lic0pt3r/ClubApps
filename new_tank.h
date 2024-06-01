#ifndef NEW_TANK_H
#define NEW_TANK_H

#include <cstddef>

template<typename T>
class Tank
{
public:
    Tank();
    void push_back(const T& new_ele);
    void pop_back();
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    std::size_t size() const;

private:
    T* m_data = nullptr;
    std::size_t size_cur = 0;
    std::size_t size_max = 2;

    void Resize(std::size_t Size_Req);
};

#include "tank.cpp"

#endif // NEW_TANK_H    