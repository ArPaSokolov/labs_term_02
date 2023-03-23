#include <iostream>
#include <bitset>
#include <vector>

template <size_t N> 
class MyVectorBool 
{
    std::bitset<N> data;
public:
    MyVectorBool(int n) : data(n) { }
    MyVectorBool() : data(0) { }
    MyVectorBool(const MyVectorBool& other) = default;
    MyVectorBool& operator=(const MyVectorBool& other) = default;
    friend std::ostream& operator<<(std::ostream& os, const MyVectorBool& v) {
        for (int i = v.data.size() - 1; i >= 0; --i) 
        {
            os << v.data[i];
        }
        return os;
    }
    void add_start(size_t k) 
    {
        data <<= 1;
        data |= std::bitset<N>(k & 1u);
    }
    void add_end(size_t k) 
    {
        data |= (std::bitset<N>(k & 1u) << data.count());
    }
    size_t size() const { return data.count(); }
    void erase(size_t i) { data = (data & ~(1ull << i)) | ((data >> (i + 1)) << i); }
    MyVectorBool operator+(const MyVectorBool& other) 
    {
        MyVectorBool result;
        std::bitset<N + 1> tmp(data.to_ulong() + other.data.to_ulong());
        result.data = tmp & ((1ull << N) - 1);
        return result;
    }
    bool operator[](size_t i) const { return data[i]; }
    bool& operator[](size_t i) { return data[i]; }
};

int main() {
    MyVectorBool<8> A(5u);
    MyVectorBool<3> B(3u);
    A.add_start(1u);
    B.add_end(7u);
    MyVectorBool<8> C = A + B;
    MyVectorBool<3> D = B + B;
    size_t index;
    std::cin >> index;
    C[index] = !C[index];
    C.erase(index);
    std::cout << "Hello world\n"_s * B.size();
    return 0;
}