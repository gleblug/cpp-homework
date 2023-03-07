```cpp
int main(int argc, char const *argv[])
{
    std::vector<char> v;

    std::istream_iterator<char> it1(std::cin);
    std::istream_iterator<char> it2{};
    std::copy(it1, it2, std::back_inserter(v));

    std::ostream_iterator<char> out(std::cout, "\n");
    std::copy(v.cbegin(), v.cend(), out);

    return 0;
}
```

 

