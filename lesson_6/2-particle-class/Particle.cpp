#include "Particle.hpp"
#include <map>
#include <iostream>


Particle::Particle(std::string const& name):
  name(name)
{  }

void Particle::set_mass(double value, std::string const& system_of_units) {
  this->mass = input_converter("mass", value, system_of_units);
}
double Particle::get_mass(std::string const& system_of_units) {
  return output_converter("mass", this->mass, system_of_units);
}


void Particle::set_electrical_charge(double value, std::string const& system_of_units) {
  this->electrical_charge = input_converter("electrical_charge", value, system_of_units);
}
double Particle::get_electrical_charge(std::string const& system_of_units) {
  return output_converter("electrical_charge", this->electrical_charge, system_of_units);
}


void Particle::set_magnetic_moment(double value, std::string const& system_of_units) {
  this->magnetic_moment = input_converter("magnetic_moment", value, system_of_units);
}
double Particle::get_magnetic_moment(std::string const& system_of_units) {
  return output_converter("magnetic_moment", this->magnetic_moment, system_of_units);
}


std::map<std::string, double> Particle::si2cgs({
  {"mass", 1e3},
  {"electrical_charge", 3e9},
  {"magnetic_moment", 1e3}
});


double Particle::input_converter(std::string type, double value, std::string system_of_units) {
  if (system_of_units == "SI") {
    return value * Particle::si2cgs[type];
  } else if (system_of_units == "CGS") {
    return value;
  }

  std::cerr << "There is no one system of units with name " << system_of_units << '\n';
  return -1;
}

double Particle::output_converter(std::string type, double value_cgs, std::string system_of_units) {
  if (system_of_units == "SI") {
    return value_cgs / Particle::si2cgs[type];
  } else if (system_of_units == "CGS") {
    return value_cgs;
  }

  std::cerr << "There is no one system of units with name " << system_of_units << '\n';
  return -1;
}
