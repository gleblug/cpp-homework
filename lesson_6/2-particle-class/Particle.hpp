#include <string>

class Particle {
public:
  Particle(
    std::string const& name,
    double lifetime,
    double mass,
    double spin,
    double electrical_charge,
    double magnetic_moment
  );

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

  void set_mass(double mass, std::string const& SoU);
  auto get_mass(std::string const& SoU) const;

  void set_electrical_charge(double electrical_charge, std::string const& SoU);
  auto get_electrical_charge(std::string const& SoU) const;

  void set_magnetic_moment(double magnetic_moment, std::string const& SoU);
  auto get_magnetic_moment(std::string const& SoU) const;


private:
  std::string name;

  double lifetime;
  double mass;
  double spin;
  double electrical_charge;
  double magnetic_moment;

  static double si2sgc_mass;
  static double si2sgc_electrical_charge;
  static double si2cgs_magnetic_moment;
};
