#include <iostream>
#include <string>
#include <vector>


class Array {
private:

  std::vector<int>  m_vector;
  size_t            m_length;
  int               m_data[];

public:

  // default constructor
  Array ();

  // users constructors
  Array (size_t length);

  Array (const int array[]);

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
};

Array::Array()
{

}

Array::Array(size_t length)
{

}

Array::Array(const int array[])
{

}

Array::Array(const std::vector<int> & array)
{

}

Array::Array(const Array & other)
{

}

Array::Array(Array && other)
{

}

Array::~Array()
{

}

std::ostream & operator<< (std::ostream & stream, const Array & array)
{

}

std::istream & operator<< (std::istream & stream, Array & array)
{

}

int Array::operator[] (size_t index) const
{

}

int & Array::operator[] (size_t index)
{

}

Array & Array::operator= (const Array & other)
{

}

Array & Array::operator= (Array && other)
{

}

Array operator+(const Array & lhs, const Array & rhs)
{

}


int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
