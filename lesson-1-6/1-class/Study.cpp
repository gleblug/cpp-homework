#include <iomanip>
#include <iostream>
#include "Study.hpp"


Student::Student(
  std::string const& name,
  std::string const& surname,
  unsigned int course,
  std::string phystech_school,
  bool is_academ
):
  m_name(name),
  m_surname(surname),
  m_course(course),
  m_phystech_school(phystech_school),
  m_is_academ(is_academ) {
    static unsigned int id = 1;

    personal_id = id++;
}

void Student::print_info() const {
  int const width = 25;

  std::cout << std::setw(width) << std::left << "Name:" << m_name << '\n'
            << std::setw(width) << std::left << "Surname:" << m_surname << '\n'
            << std::setw(width) << std::left << "Course:" << m_course << '\n'
            << std::setw(width) << std::left << "ID:" << personal_id << '\n' << std::endl;
}


Botalka::Botalka(
  unsigned int count_of_seats
):
  m_count_of_seats(count_of_seats)
{  }

void Botalka::came_student(Student const& student) {
  int place = student_place(student);
  if (place != -1) {
    std::cerr << "Student is already in " << m_location <<"!\n" << '\n';
  } else if (vacancies_count() <= 0) {
    std::cerr << "Botalka in " << m_location << " is crowded!\n" << '\n';
  } else {
    m_students_id_list.push_back(student.get_id());
  }
}

void Botalka::left_student(Student const& student) {
  int place = student_place(student);
  if (place == -1) {
    std::cerr << "There are no student with ID " << student.get_id() << " in " << m_location << '\n' << '\n';
  } else {
    m_students_id_list.erase(std::next(std::begin(m_students_id_list), place));
  }
}

int Botalka::student_place(Student const& student) const {
  for (size_t i = 0; i < std::size(m_students_id_list); i++) {
    if (m_students_id_list[i] == student.get_id()) {
      return i;
    }
  }
  return -1;
}

void Botalka::print_info() const {
  int const width = 25;

  std::cout << std::setw(width) << std::left << "Location:" << m_location << '\n'
            << std::setw(width) << std::left << "Count of seats:" << m_count_of_seats << '\n'
            << std::setw(width) << std::left << "Number of vacancies:" << vacancies_count() << '\n'
            << std::setw(width) << std::left << "Students:" << '\n';
  for (auto stud_id: m_students_id_list) {
    std::cout << std::setw(width) << std::left << " " << stud_id << '\n';
  }

  std::cout << std::endl;
}
