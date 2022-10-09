#include <iomanip>
#include <iostream>
#include "Study.hpp"


Student::Student( std::string name,
                  std::string surname,
                  unsigned short course,
                  std::string phystech_school,
                  bool is_academ
                ):
name(name),
surname(surname),
course(course),
phystech_school(phystech_school),
is_academ(is_academ)
{
  static unsigned int id = 1;

  personal_id = id++;
}

std::string Student::full_name() const {
  return name + " " + surname;
}

bool Student::in_academ() const {
  return is_academ;
}

void Student::print_info() const {
  const int width = 25;

  std::cout << std::setw(width) << std::left << "Name:" << name << '\n'
            << std::setw(width) << std::left << "Surname:" << surname << '\n'
            << std::setw(width) << std::left << "Course:" << course << '\n'
            << std::setw(width) << std::left << "ID:" << personal_id << '\n' << std::endl;
}


Botalka::Botalka(unsigned short count_of_seats):
count_of_seats(count_of_seats) {  }

void Botalka::came_student(Student const& student) {
  int is_here = is_student_here(student);
  if (is_here != -1) {
    std::cerr << "Student is already in " << location <<"!\n" << '\n';
  } else if (vacancies_count() <= 0) {
    std::cerr << "Botalka in " << location << " is crowded!\n" << '\n';
  } else {
    students_id_list.push_back(student.get_id());
  }
}

void Botalka::left_student(Student const& student) {
  int is_here = is_student_here(student);
  if (is_here == -1) {
    std::cerr << "There are no student with ID " << student.get_id() << " in " << location << '\n' << '\n';
  } else {
    students_id_list.erase(std::begin(students_id_list) + is_here);
  }
}

int Botalka::is_student_here(const Student& student) {
  for (size_t i = 0; i < students_id_list.size(); i++) {
    if (students_id_list.at(i) == student.get_id()) {
      return i;
    }
  }
  return -1;
}

void Botalka::print_info() const {
  int const width = 25;

  std::cout << std::setw(width) << std::left << "Location:" << location << '\n'
            << std::setw(width) << std::left << "Count of seats:" << count_of_seats << '\n'
            << std::setw(width) << std::left << "Number of vacancies:" << vacancies_count() << '\n'
            << std::setw(width) << std::left << "Students:" << '\n';
  for (auto& stud_id: students_id_list) {
    std::cout << std::setw(width) << std::left << " " << stud_id << '\n';
  }

  std::cout << std::endl;
}
