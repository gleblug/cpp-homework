#include <iostream>
#include <string>
#include <vector>
#include <sstream>


class Array {
private:

  int *             m_data;
  size_t            m_length;
  std::vector<int>  m_vector;

public:

  // default constructor
  Array ();

  // users constructors
  Array (size_t length);

  Array (std::initializer_list<int> array);

  Array (const std::vector<int> & array);

  // copy constructor
  Array (const Array & other);

  // move constructor
  Array (Array && other);

  // destructor
  ~Array ();

  // stream operators
  friend std::ostream & operator<< (std::ostream & stream, const Array & array);
  friend std::istream & operator>> (std::istream & stream, Array & array);

  // index operator
  int   operator[] (size_t index) const;
  int & operator[] (size_t index);

  // sets Array value
  Array & operator= (const Array & other);

  // moves Array value
  Array & operator= (Array && other);

  // concatenation operator
  friend Array operator+ (const Array & lhs, const Array & rhs);

  size_t length () const;
};

Array::Array():
  m_length(0)
{

}

Array::Array(size_t length):
  m_data(new int [length]),
  m_length(length),
  m_vector(std::vector<int>(length))
{

}

Array::Array(std::initializer_list<int> array)
{
  m_length = std::distance(std::begin(array), std::end(array));
  m_vector = array;
  m_data = new int [m_length];
  for (size_t i = 0; i < m_length; i++)
  {
    m_data[i] = m_vector[i];
  }
}

Array::Array(const std::vector<int> & array)
{
  m_length = array.size();
  m_vector = array;
  m_data = new int [m_length];
  for (size_t i = 0; i < m_length; i++)
  {
    m_data[i] = m_vector[i];
  }
}

Array::Array(const Array & other)
{
  m_length = other.m_length;
  m_vector = other.m_vector;
  m_data = new int [m_length];
  for (size_t i = 0; i < m_length; i++)
  {
    m_data[i] = m_vector[i];
  }
}

Array::Array(Array && other)
{
  m_data = other.m_data;
  m_length = other.m_length;
  m_vector = std::move(other.m_vector);

  other.m_data = nullptr;
  other.m_length = 0;
}

Array::~Array()
{
  delete [] m_data;
}

std::ostream & operator<< (std::ostream & stream, const Array & array)
{
  for (size_t i = 0; i < array.m_length; i++) {
    stream << array.m_data[i] << ' ';
  }

  return stream;
}

std::istream & operator>> (std::istream & stream, Array & array)
{
  std::vector<int> buffer;
  std::string input;
  std::stringstream streamInput;
  int elem;

  std::getline(stream, input);

  streamInput << input;

  // Push every elem from streamInput to array as integer while it's not empty
  while (streamInput >> elem) {
    buffer.push_back(elem);
  }

  array = Array(buffer);

  return stream;
}

int Array::operator[] (size_t index) const
{
  if (index >= m_length) {
    std::cerr << "Index is bigger than array length." << '\n';
  }

  return m_data[index];
}

int & Array::operator[] (size_t index)
{
  if (index >= m_length) {
    std::cerr << "Index is bigger than array length." << '\n';
  }

  return m_data[index];
}

Array & Array::operator= (const Array & other)
{
  m_length = other.m_length;
  m_vector = other.m_vector;
  m_data = new int [m_length];
  for (size_t i = 0; i < m_length; i++)
  {
    m_data[i] = m_vector[i];
  }

  return (*this);
}

Array & Array::operator= (Array && other)
{
  m_data = other.m_data;
  m_length = other.m_length;
  m_vector = std::move(other.m_vector);

  other.m_data = nullptr;
  other.m_length = 0;

  return (*this);
}

Array operator+(const Array & lhs, const Array & rhs)
{
  size_t length = lhs.m_length + rhs.m_length;
  Array array(length);

  for (size_t i = 0; i < lhs.m_length; i++) {
    array.m_data[i] = lhs.m_data[i];
    array.m_vector[i] = lhs.m_vector[i];
  }

  for (size_t i = lhs.m_length; i < array.m_length; i++) {
    array.m_data[i] = rhs.m_data[i - lhs.m_length];
    array.m_vector[i] = rhs.m_vector[i - lhs.m_length];
  }

  return array;
}

size_t Array::length() const {
  return m_length;
}


int main(int argc, char const *argv[]) {
  Array a = {1, 2, 3, 4};
  Array b = {4, 6, 7};

  std::cout << a + b << '\n';

  Array c = std::move(b);

  std::cout << "length b = " << b.length() << '\n';
  std::cout << "c = " << c << '\n';

  return 0;
}
