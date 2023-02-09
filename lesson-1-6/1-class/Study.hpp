#include <string>
#include <vector>

class Student {
public:
  Student(
    std::string const& name,
    std::string const& surname,
    unsigned int course=1,
    std::string phystech_school="FEFM",
    bool is_academ=false
  );

  const auto full_name() const {
    return m_name + " " + m_surname;
  }

  auto in_academ() const {
    return m_is_academ;
  }

  void print_info() const;

  auto get_id() const {
    return personal_id;
  }

private:
  std::string m_name;
  std::string m_surname;
  unsigned int m_course;
  std::string m_phystech_school;
  unsigned int personal_id;
  bool m_is_academ;
};

class Botalka {
public:
  Botalka(
    unsigned int count_of_seats=20
  );

  void set_location(std::string location) {
    m_location = location;
  }

  void came_student(Student const& student);

  void left_student(Student const& student);

  int student_place(Student const& student) const;

  int vacancies_count() const {
    return m_count_of_seats - std::size(m_students_id_list);
  }

  void print_info() const;

private:
  unsigned int m_count_of_seats;
  std::vector<unsigned int> m_students_id_list;
  std::string m_location;
};
