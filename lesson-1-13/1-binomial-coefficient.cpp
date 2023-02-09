using number = const unsigned int;

template <int n, int k>
struct Calculate_Binomial_Coefficient
{
    static number value = 
        Calculate_Binomial_Coefficient<n - 1, k>::value + 
        Calculate_Binomial_Coefficient<n - 1, k - 1>::value;
};

template <int n>
struct Calculate_Binomial_Coefficient<n, n>
{
    static number value = 1;
};

template <int n>
struct Calculate_Binomial_Coefficient<n, 0>
{
    static number value = 1;
};

template <int n, int k>
number Binomial_Coefficient = Calculate_Binomial_Coefficient<n, k>::value;


int main(int argc, char const *argv[])
{
    static_assert(Binomial_Coefficient<9, 1> == 9);

    static_assert(Binomial_Coefficient<12, 4> == 495);

    return 0;
}
