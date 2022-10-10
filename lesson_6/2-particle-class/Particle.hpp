#include <string>
#include <map>

class Particle {
public:
  Particle(std::string const& name);

  void set_lifetime(double lifetime) {
    this->lifetime = lifetime;
  }
  auto get_lifetime() const {
    return lifetime;
  }

  void set_spin(double spin) {
    this->spin = spin;
  }
  auto get_spin() const {
    return spin;
  }

  void set_mass(double mass, std::string const& system_of_units);
  double get_mass(std::string const& system_of_units);

  void set_electrical_charge(double electrical_charge, std::string const& system_of_units);
  double get_electrical_charge(std::string const& system_of_units);

  void set_magnetic_moment(double magnetic_moment, std::string const& system_of_units);
  double get_magnetic_moment(std::string const& system_of_units);

  static std::map<std::string, double> si2cgs;

private:
  double input_converter(std::string type, double value, std::string system_of_units);
  double output_converter(std::string type, double value, std::string system_of_units);

  std::string name;

  double lifetime;
  double mass;
  double spin;
  double electrical_charge;
  double magnetic_moment;
};
