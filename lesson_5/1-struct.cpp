#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>


struct Student {
  Student(std::string name,
          std::string surname,
          unsigned short course=1,
          std::string phystech_school="FEFM",
          bool is_academ=false):
  _name(name),
  _surname(surname),
  course(course),
  phystech_school(phystech_school),
  _is_academ(is_academ) {
    static unsigned int id = 1;

    personal_id = id++;
  }

  std::string full_name() const {
    return _name + " " + _surname;
  }

  bool in_academ() const {
    return _is_academ;
  }

  void print_info() const {
    int const width = 25;

    std::cout << std::setw(width) << std::left << "Name:" << _name << '\n'
              << std::setw(width) << std::left << "Surname:" << _surname << '\n'
              << std::setw(width) << std::left << "Course:" << course << '\n'
              << std::setw(width) << std::left << "ID:" << personal_id << '\n' << std::endl;
  }

  std::string _name;
  std::string _surname;
  unsigned short course;
  std::string phystech_school;
  unsigned int personal_id;
  bool _is_academ;
};


struct Botalka {
  Botalka(unsigned short count_of_seats=20):
  _count_of_seats(count_of_seats) {
  }

  void set_location(std::string location) {
    _location = location;
  }

  void came_student(Student const& student) {
    int is_here = is_student_here(student);
    if (is_here != -1) {
      std::cerr << "Student is already in " << _location <<"!\n" << '\n';
    } else if (vacancies_count() <= 0) {
      std::cerr << "Botalka in " << _location << " is crowded!\n" << '\n';
    } else {
      _students_id_list.push_back(student.personal_id);
    }
  }

  void left_student(Student const& student) {
    int is_here = is_student_here(student);
    if (is_here == -1) {
      std::cerr << "There are no student with ID " << student.personal_id << " in " << _location << '\n' << '\n';
    } else {
      _students_id_list.erase(std::begin(_students_id_list) + is_here);
    }
  }

  int is_student_here(Student const& student) const {
    for (size_t i = 0; i < _students_id_list.size(); i++) {
      if (_students_id_list.at(i) == student.personal_id) {
        return i;
      }
    }
    return -1;
  }

  int vacancies_count() const {
    return _count_of_seats - _students_id_list.size();
  }

  void print_info() const {
    int const width = 25;

    std::cout << std::setw(width) << std::left << "Location:" << _location << '\n'
              << std::setw(width) << std::left << "Count of seats:" << _count_of_seats << '\n'
              << std::setw(width) << std::left << "Number of vacancies:" << vacancies_count() << '\n'
              << std::setw(width) << std::left << "Students:" << '\n';
    for (auto& stud_id: _students_id_list) {
      std::cout << std::setw(width) << std::left << " " << stud_id << '\n';
    }

    std::cout << std::endl;
  }


  unsigned short _count_of_seats;
  std::vector<int> _students_id_list;
  std::string _location;
};


int main(int argc, char const *argv[]) {
  Student student1("Alexandr", "Ivanov", 2);
  Student student2("Gleb", "Lugovtsov", 2);
  Student student3("Maxim", "Korobkin", 3, "FRTK");
  Student student4("Alexey", "Dunaev", 5, "FAKT", true);

  // student1.print_info();
  // student2.print_info();
  // student3.print_info();
  student4.print_info();

  Botalka botalka1(30);
  Botalka botalka2(2);

  botalka1.set_location("GK");
  botalka2.set_location("8 dormitory");

  // botalka1.print_info();
  // botalka2.print_info();

  botalka2.came_student(student1);
  botalka2.came_student(student3);
  botalka2.came_student(student4);
  botalka2.came_student(student3);

  botalka2.print_info();

  botalka2.left_student(student2);
  botalka2.left_student(student1);

  botalka2.print_info();

  return 0;
}
