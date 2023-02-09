#include <string>
#include <map>

enum class System_of_units {
  SI,
  CGS
};

class Particle {
public:
  Particle(std::string const& name);

  void set_lifetime(double lifetime) {
    m_lifetime = lifetime;
  }
  auto get_lifetime() const {
    return m_lifetime;
  }

  void set_spin(double spin) {
    m_spin = spin;
  }
  auto get_spin() const {
    return m_spin;
  }

  void set_mass(double mass, System_of_units system_of_units);
  double get_mass(System_of_units system_of_units);

  void set_electrical_charge(double electrical_charge, System_of_units system_of_units);
  double get_electrical_charge(System_of_units system_of_units);

  void set_magnetic_moment(double magnetic_moment, System_of_units system_of_units);
  double get_magnetic_moment(System_of_units system_of_units);

  static std::map<std::string, double> si2cgs;

private:
  double input_converter(std::string type, double value, System_of_units system_of_units);
  double output_converter(std::string type, double value, System_of_units system_of_units);

  std::string name;

  double m_lifetime;
  double m_mass;
  double m_spin;
  double m_electrical_charge;
  double m_magnetic_moment;
};
