#include "Study.hpp"

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
