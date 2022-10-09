#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iterator>


struct Student {
  Student(std::string const& name,
          std::string const& surname,
          unsigned int course=1,
          std::string phystech_school="FEFM",
          bool is_academ=false):
  m_name(name),
  m_surname(surname),
  m_course(course),
  m_phystech_school(phystech_school),
  m_is_academ(is_academ) {
    static unsigned int id = 1;

    personal_id = id++;
  }

  const auto full_name() const {
    return m_name + " " + m_surname;
  }

  auto in_academ() const {
    return m_is_academ;
  }

  void print_info() const {
    int const width = 25;

    std::cout << std::setw(width) << std::left << "Name:" << m_name << '\n'
              << std::setw(width) << std::left << "Surname:" << m_surname << '\n'
              << std::setw(width) << std::left << "Course:" << m_course << '\n'
              << std::setw(width) << std::left << "ID:" << personal_id << '\n' << std::endl;
  }

  std::string m_name;
  std::string m_surname;
  unsigned int m_course;
  std::string m_phystech_school;
  unsigned int personal_id;
  bool m_is_academ;
};


struct Botalka {
  Botalka(unsigned int count_of_seats=20):
    m_count_of_seats(count_of_seats) {  }

  void set_location(std::string location) {
    m_location = location;
  }

  void came_student(Student const& student) {
    int place = student_place(student);
    if (place != -1) {
      std::cerr << "Student is already in " << m_location <<"!\n" << '\n';
    } else if (vacancies_count() <= 0) {
      std::cerr << "Botalka in " << m_location << " is crowded!\n" << '\n';
    } else {
      m_students_id_list.push_back(student.personal_id);
    }
  }

  void left_student(Student const& student) {
    int place = student_place(student);
    if (place == -1) {
      std::cerr << "There are no student with ID " << student.personal_id << " in " << m_location << '\n' << '\n';
    } else {
      m_students_id_list.erase(std::next(std::begin(m_students_id_list), place));
    }
  }
  // for (auto const& current_student_id: m_students_id_list) {

  int student_place(Student const& student) const {
    for (size_t i = 0; i < std::size(m_students_id_list); i++) {
      if (m_students_id_list[i] == student.personal_id) {
        return i;
      }
    }
    return -1;
  }

  int vacancies_count() const {
    return m_count_of_seats - std::size(m_students_id_list);
  }

  void print_info() const {
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


  unsigned int m_count_of_seats;
  std::vector<unsigned int> m_students_id_list;
  std::string m_location;
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
