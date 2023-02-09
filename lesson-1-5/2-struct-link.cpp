#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>


struct Lecture;

struct Student {
  Student(std::string const& name,  std::string const& surname, std::string const& group):
    m_name(name),
    m_surname(surname),
    m_group(group)
    {  }

  const auto full_name() const {
    return m_name + ' ' + m_surname;
  }

  void print_info() const;

  int lecture_index(Lecture const& lecture) const {
    const auto lect_iter = std::find(std::begin(list_of_lectures), std::end(list_of_lectures), &lecture);

    if (lect_iter != std::end(list_of_lectures)) {
      return lect_iter - std::begin(list_of_lectures);
    } else {
      return -1;
    }
  }

  std::string m_name;
  std::string m_surname;
  std::string m_group;
  std::vector<Lecture*> list_of_lectures;
};


struct Lecture {
  Lecture(std::string const& subject, std::string const& abstract):
    m_subject(subject),
    m_abstract(abstract)
    {  }

  int student_index(Student const& student) const {
    const auto stud_iter = std::find(std::begin(list_of_students), std::end(list_of_students), &student);

    if (stud_iter != std::end(list_of_students)) {
      return stud_iter - std::begin(list_of_students);
    } else {
      return -1;
    }
  }

  void print_info() const {
    const int width = 14;
    std::cout << std::setw(width) << std::left << "Subject:" << m_subject << '\n'
              << std::setw(width) << std::left << "Abstract:" << m_abstract << '\n'
              << std::setw(width) << std::left << "Students:" << '\n';
    for (Student* student: list_of_students) {
      std::cout << '\t' << std::setw(width) << std::left << (*student).full_name() << '\n';
    }
    std::cout << std::endl;
  }

  auto subject() const {
    return m_subject;
  }

  std::string m_subject;
  std::string m_abstract;
  std::vector<Student*> list_of_students;
};


void Student::print_info() const{
  const int width = 14;
  std::cout << std::setw(width) << std::left << "Full name:" << full_name() << '\n'
            << std::setw(width) << std::left << "Group:" << m_group << '\n'
            << std::setw(width) << std::left << "Lectures:" << '\n';
  for (Lecture* lecture: list_of_lectures) {
    std::cout << '\t'<< (*lecture).subject() << '\n';
  }
  std::cout << std::endl;
}

void connect(Student& student, Lecture& lecture) {
  int st_lecture_index = student.lecture_index(lecture);
  int lc_student_index = lecture.student_index(student);

  if (st_lecture_index == -1) {
    student.list_of_lectures.push_back(&lecture);
  }
  if (lc_student_index == -1) {
    lecture.list_of_students.push_back(&student);
  }
}

void disconnect(Student& student, Lecture& lecture) {
  int st_lecture_index = student.lecture_index(lecture);
  int lc_student_index = lecture.student_index(student);

  if (st_lecture_index != -1) {
    student.list_of_lectures.erase(std::next(std::begin(student.list_of_lectures), st_lecture_index));
  }

  if (lc_student_index != -1) {
    lecture.list_of_students.erase(std::next(std::begin(lecture.list_of_students), lc_student_index));
  }
}

int main(int argc, char const *argv[]) {
  Student ivan("Ivan", "Shvydkiy", "B01-201");
  Student maxim("Maxim", "Kotin", "B04-005");
  Student albina("Albina", "Morosheva", "B03-203");

  Lecture math("Mathematical analysis", "Some math quantors");
  Lecture physics("General physics", "Some physics stuff");
  Lecture infornatics("Informatics", "A lot of programming");
  Lecture english("English", "Learn new vocabulary and grammar");

  connect(ivan, math);
  connect(maxim, math);
  connect(albina, math);

  math.print_info();

  std::cout << "=============================="<< '\n';

  connect(ivan, physics);
  connect(ivan, english);

  ivan.print_info(); // OUT: Ivan

  std::cout << "=============================="<< '\n';

  disconnect(ivan, math);

  math.print_info();

  std::cout << "=============================="<< '\n';

  ivan.print_info();

  // mipt
  return 0;
}
