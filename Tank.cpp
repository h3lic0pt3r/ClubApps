template<typename U>
U accumulate(Tank<U>& tank_class){
    U total_sum =0;
    for(size_t i =0; i< tank_class.size() ; i++){       //loop to iterate through the array and sum it up
        total_sum+= tank_class[i];
    }

    return total_sum;
};

