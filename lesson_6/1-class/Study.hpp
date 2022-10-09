#include <string>
#include <vector>

class Student {
public:
  Student(std::string name,
          std::string surname,
          unsigned short course=1,
          std::string phystech_school="FEFM",
          bool is_academ=false);

  std::string full_name() const;

  bool in_academ() const;

  void print_info() const;

  unsigned int get_id() const {
    return this->personal_id;
  }

private:
  std::string name;
  std::string surname;
  unsigned short course;
  std::string phystech_school;
  unsigned int personal_id;
  bool is_academ;
};


class Botalka {
public:
  Botalka(unsigned short count_of_seats=20);

  void set_location(std::string location) {
    this->location = location;
  }

  void came_student(Student const& student);

  void left_student(Student const& student);

  int is_student_here(Student const& student);

  int vacancies_count() const {
    return this->count_of_seats - this->students_id_list.size();
  }

  void print_info() const;

private:
  unsigned short count_of_seats;
  std::vector<unsigned int> students_id_list;
  std::string location;
};
