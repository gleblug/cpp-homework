#include <cmath>
#include <iostream>
#include <iomanip>

template <class Derived>
class Subject
{
public:
    Derived *self()
    {
        return static_cast<Derived*>(this);
    }

    double labor_costs(int assessment)
    {
        return 4.15 * std::log10(assessment) 
            * self()->complexity_of_homework() 
            * self()->classes_time() 
            * (1 / self()->teacher_loyalty());
    }
};

class Math : public Subject <Math>
{
protected:
    friend Subject;

    double complexity_of_homework()
    {
        return 0.8;
    }

    double classes_time()
    {
        return 6;
    }

    double teacher_loyalty()
    {
        return 3;
    }
};

class Physics : public Subject <Physics>
{
protected:
    friend Subject;

    double complexity_of_homework() 
    {
        return 0.5;
    }

    double classes_time() 
    {
        return 8;
    }

    double teacher_loyalty() 
    {
        return 5;
    }
};

int main(int argc, char const *argv[])
{
    Math *math = new Math();
    Physics *physics = new Physics();

    int math_assessment;
    int physics_assessment;

    std::cout << "Enter the desired grade\nin math: ";
    std::cin >> physics_assessment;
    std::cout << "and physics: ";
    std::cin >> math_assessment;
    std::cout << std::endl;

    std::cout << std::setprecision(2) 
              << "You need to spend " << math->labor_costs(math_assessment)
              << " hours to math and " << physics->labor_costs(physics_assessment)
              << " hours to physics every week."
              << std::endl;

    return 0;
}
