#include <cmath>
#include <iostream>
#include <iomanip>

class Subject
{
protected:
    /// @brief Describe the loyalty of teacher from wikimipt.ru
    /// @return Teacher loyalty (1 to 5)
    virtual double teacher_loyalty() = 0;
    
    /// @brief Describe the complexity of homework in c.u.
    /// @return Value of complexity (0 to 1)
    virtual double complexity_of_homework() = 0;
    
    /// @brief Shows how many time we need to spend for this subject
    /// @return Necessary classes time in hours per week
    virtual double classes_time() = 0;

public:
    /// @brief Calculate hours per week to learn the subject
    /// @param assessment desired assessment (3 to 10) / 10
    /// @return Hours per week
    double labor_costs(int assessment)
    {
        return 4.15 * std::log10(assessment) * complexity_of_homework() * classes_time() * (1 / teacher_loyalty());
    }
};

class Math : public Subject
{
protected:
    virtual double complexity_of_homework() override
    {
        return 0.8;
    }

    virtual double classes_time() override
    {
        return 6;
    }

    virtual double teacher_loyalty() override
    {
        return 3;
    }
};

class Physics : public Subject
{
protected:
    virtual double complexity_of_homework() override
    {
        return 0.5;
    }

    virtual double classes_time() override
    {
        return 8;
    }

    virtual double teacher_loyalty() override
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
