#include <iostream>
#include <string>
#include <vector>
#include <iomanip>


struct Lecture;

struct Student {
  std::string full_name() const {
    return _name + ' ' + _surname;
  }

  void print_info();

  std::string _name;
  std::string _surname;
  std::string group;
  std::vector<Lecture*> list_of_lectures;
};


struct Lecture {
  void add_student(Student& student) {
    int index = student_index(student);
    if (index != -1) {
      std::cerr << student.full_name() << " already at a " << _subject << " lectures.\n" << std::endl;
    } else {
      student.list_of_lectures.push_back(this);
      list_of_students.push_back(&student);
    }
  }

  void kick_student(Student& student) {
    int index = student_index(student);
    if (index == -1) {
      std::cerr << student.full_name() << " doesn't attend " << _subject << " lectures.\n" << std::endl;
    } else {
      for (size_t i = 0; i < student.list_of_lectures.size(); i++) {
        if (student.list_of_lectures.at(i) == this) {
          student.list_of_lectures.erase(std::begin(student.list_of_lectures) + i);
          break;
        }
      }
      list_of_students.erase(std::begin(list_of_students) + index);
    }
  }

  int student_index(Student const& student) const {
    for (size_t i = 0; i < list_of_students.size(); i++) {
      if (list_of_students.at(i) == &student) {
        return i;
      }
    }

    return -1;
  }

  void print_info() const {
    const int width = 14;
    std::cout << std::setw(width) << std::left << "Subject:" << _subject << '\n'
              << std::setw(width) << std::left << "Abstract:" << _abstract << '\n'
              << std::setw(width) << std::left << "Students:" << '\n';
    for (Student* student: list_of_students) {
      std::cout << '\t' << std::setw(width) << std::left << (*student).full_name() << '\n';
    }
    std::cout << std::endl;
  }

  std::string subject() const {
    return _subject;
  }

  std::string _subject;
  std::string _abstract;
  std::vector<Student*> list_of_students;
};


void Student::print_info() {
  const int width = 14;
  std::cout << std::setw(width) << std::left << "Full name:" << full_name() << '\n'
            << std::setw(width) << std::left << "Group:" << group << '\n'
            << std::setw(width) << std::left << "Lectures:" << '\n';
  for (Lecture* lecture: list_of_lectures) {
    std::cout << '\t'<< (*lecture).subject() << '\n';
  }
  std::cout << std::endl;
}


int main(int argc, char const *argv[]) {
  std::vector<Student> mipt_students{
    {"Ivan", "Shvydkiy", "B01-201"},
    {"Maxim", "Kotin", "B04-005"},
    {"Petr", "Kovalsky", "M02-102"},
    {"Albina", "Morosheva", "B03-203"},
    {"Ekaterina", "Zaharova", "B04-107"},
  };

  std::vector<Lecture> mipt_lectures{
    {"Mathematical analysis", "Some math quantors"},
    {"General physics", "Some physics stuff"},
    {"Informatics", "A lot of programming"},
    {"English", "Learn new vocabulary and grammar"},
    {"PE", "The most important subject at MIPT"},
  };

  mipt_lectures.at(0).add_student(mipt_students.at(0));
  mipt_lectures.at(0).add_student(mipt_students.at(0));
  mipt_lectures.at(0).add_student(mipt_students.at(3));
  mipt_lectures.at(0).add_student(mipt_students.at(2));
  mipt_lectures.at(1).add_student(mipt_students.at(0));
  mipt_lectures.at(4).add_student(mipt_students.at(0));

  mipt_lectures.at(0).print_info();
  mipt_students.at(0).print_info();

  // mipt
  return 0;
}
