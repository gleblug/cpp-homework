#include <cctype>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <type_traits>

/*!
 *  @class String
 *
 *  @brief A custom String implementation
 *
 *  A custom C++ implementation of a String object for pedagogical purposes.
 *  Is efficient for specifying the length of your String and does not depend
 *  on the use of a NULL termination.
 *
 *  @invariant String data will always point to NULL or a valid address.
 *  @invariant String length will always indicate amount of allocated space.
 */

class String
{
private:

	char *       m_data;    /*!< The ASCII characters that comprise the String */
	std::size_t  m_length;  /*!< The number of characters allocated in data */

public:

	/*!
	 *  @brief Empty String Constructor.
	 *  @post String length is set equal to 0.
	 */
	String();

	/*!
	 *  @brief Single-character String Constructor.
	 *  @param[in] c A char literal.
	 *  @post String data equals @a c and String length equals 1.
	 */
	String(char c);

	/*!
	 *  @brief char* String Constructor
	 *  @param[in] c A char* null-terminated string.
	 *  @post String length equals @code{.cpp}strlen(c)@endcode.
	 *  @post String data equals @a c allocated values, except the null-terminator.
	 */
	String(const char * c_string);

	/*!
	 *  @brief Copy String Constructor
	 *  @param[in] s A String instance.
	 *  @post This String will be identical to String @a s.
	 */
	String(const String & other);

	/*!
	 *  @brief Move String Constructor
	 *  @param[in] s A String instance.
	 *  @post This String will be moved from String @a other.
	 */
	String(String && other);

	/*!
	 *  @brief Default String Destructor
	 *  @post String data is deleted.
	 */
	~String();

	/*!
	 *  @brief Swap two Strings.
	 *  @param[in] s A String instance.
	 *  @post This String will be swaped with String @a other.
	 */
	void swap(String & other);

	/*!
	 *  @brief String length.
	 *  @return Value in String @c length.
	 */
	std::size_t length() const;

	/*!
	 *  @brief String index of @a c.
	 *  @param[in] c A char literal.
	 *  @return The index of @a c in String, if exists; -1 otherwise.
	 */
	std::int64_t index(char c) const;

	/*!
	 *  @brief Converts lowercase alphabetic characters to uppercase.
	 *  @param[in] first Starting index of String to change case.
	 *  @param[in] last  Ending index of String to change case.
	 *  @pre @a first is less than or equal to @a last and @a last is less than
	 *       or equal to String length.
	 *  @post All lowercase alphabetic characters in String data greater than
	 *        or equal to @a first, but less than @a last are uppercase.
	 */
	void to_upper(std::size_t first, std::size_t last);

	/*!
	 *  @brief Converts uppercase alphabetic characters to lowercase.
	 *  @param[in] first Starting index of String to change case.
	 *  @param[in] last Ending index of String to change case.
	 *  @pre @a first is less than or equal to @a last and @a last is less than
	 *       or equal to String length.
	 *  @post All uppercase alphabetic characters in String data greater than
	 *        or equal to @a first, but less than @a last are lowercase.
	 */
	void to_lower(std::size_t first, std::size_t last);

	//@{
	/*!
	 *  @brief Stream operators.
	 *  @param so A stream object.
	 *  @param s  A String object.
	 *  @return Stream object containing String content.
	 */
	friend std::ostream & operator<< (std::ostream & stream, const String & string);
	friend std::istream & operator>> (std::istream & stream, String & string);
	//@}

	//@{
	/*!
	 *  @brief Access String character.
	 *  @param j Index value in String.
	 *  @pre @a j is less than String length.
	 *  @return character at @a j index of String data.
	 *  @throw int
	 */
	char   operator[] (std::size_t index) const;
	char & operator[] (std::size_t index);
	//@}

	/*!
	 *  @brief Sets String value.
	 *  @param[in] s A String object.
	 *  @return A String reference to *this.
	 *  @post String will be equivalent to @a s.
	 */
	String & operator= (const String & other);

	/*!
	 *  @brief Moves String value.
	 *  @param[in] other A String object.
	 *  @return A String reference to *this.
	 *  @post String will be moved from @a other.
	 */
	String & operator= (String && other);

	/*!
	 *  @brief Append to String.
	 *  @param[in] s A String object.
	 *  @return A String reference to *this.
	 *  @post String will equal the concatenation of itself with @a s.
	 */
	String & operator+= (const String & other);

	//@{
	/*!
	 *  @brief String concatenation (addition).
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return Copy of a String object.
	 *  @post The String will be the concatenation of @a lhs and @a rhs.
	 */
	friend String operator+ (const String & lhs, const String & rhs);
	friend String operator+ (const String & lhs, char           rhs);
	friend String operator+ (const String & lhs, const char *   rhs);
	friend String operator+ (char           lhs, const String & rhs);
	friend String operator+ (const char *   lhs, const String & rhs);

	// friend String operator+ (String &&      lhs, String &&      rhs);
	// friend String operator+ (String &&      lhs, const String & rhs);
	// friend String operator+ (String &&      lhs, char           rhs);
	// friend String operator+ (String &&      lhs, const char *   rhs);
	// friend String operator+ (char           lhs, String &&      rhs);
	// friend String operator+ (const char *   lhs, String &&      rhs);
	// friend String operator+ (const String & lhs, String &&      rhs);

	//@}

	//@{
	/*!
	 *  @brief String equality
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs and @a rhs have the same length, and each
	 *          character in their String data are identical in both value
	 *          and index.
	 */
	friend bool operator== (const String & lhs, const String & rhs);
	friend bool operator== (const String & lhs, char           rhs);
	friend bool operator== (const String & lhs, const char *   rhs);
	friend bool operator== (char           lhs, const String & rhs);
	friend bool operator== (const char *   lhs, const String & rhs);
	//@}

	//@{
	/*!
	 *  @brief String inequality: Greater-than.
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs is in dictionary order (Capitals-first) to
	 *          @a rhs when comparing alphabetical characters or @a lhs is
	 *          greater in ASCII value to @a rhs, in corresponding String
	 *          data indices.
	 */
	friend bool operator> (const String & lhs, const String & rhs);
	friend bool operator> (const String & lhs, char           rhs);
	friend bool operator> (const String & lhs, const char *   rhs);
	friend bool operator> (char           lhs, const String & rhs);
	friend bool operator> (const char *   lhs, const String & rhs);
	//@}

	//@{
	/*!
	 *  @brief String non-equality
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs is not equal to @a rhs.
	 *  @see String::operator==
	 */
	friend bool operator!= (const String & lhs, const String & rhs);
	friend bool operator!= (const String & lhs, char           rhs);
	friend bool operator!= (const String & lhs, const char *   rhs);
	friend bool operator!= (char           lhs, const String & rhs);
	friend bool operator!= (const char *   lhs, const String & rhs);
	//@}

	//@{
	/*!
	 *  @brief String inequality: Less-than.
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs is neither equal to, nor greater-than @a rhs.
	 *  @see String::operator==,String::operator>
	 */
	friend bool operator< (const String & lhs, const String & rhs);
	friend bool operator< (const String & lhs, char           rhs);
	friend bool operator< (const String & lhs, const char *   rhs);
	friend bool operator< (char           lhs, const String & rhs);
	friend bool operator< (const char *   lhs, const String & rhs);
	//@}

	//@{
	/*!
	 *  @brief String inequality: Less-than or equal
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs is not greater-than @a rhs.
	 *  @see String::operator>
	 */
	friend bool operator<= (const String & lhs, const String & rhs);
	friend bool operator<= (const String & lhs, char           rhs);
	friend bool operator<= (const String & lhs, const char *   rhs);
	friend bool operator<= (char           lhs, const String & rhs);
	friend bool operator<= (const char *   lhs, const String & rhs);
	//@}

	//@{
	/*!
	 *  @brief String inequality: Greater-than or equal
	 *  @param[in] lhs The left-hand operand String or String convertable.
	 *  @param[in] rhs The right-hand operand String or String convertable.
	 *  @return True, if @a lhs is greater-than or equal to @a rhs.
	 *  @see String::operator>,String::operator==
	 */
	friend bool operator>= (const String & lhs, const String & rhs);
	friend bool operator>= (const String & lhs, char           rhs);
	friend bool operator>= (const String & lhs, const char *   rhs);
	friend bool operator>= (char           lhs, const String & rhs);
	friend bool operator>= (const char *   lhs, const String & rhs);
	//@}
};

String::String()
{

}

String::String(char c)
{

}

String::String(const char * c_string)
{

}

String::String(const String & other)
{

}

String::String(String && other)
{

}

String::~String()
{

}

void String::swap(String & other)
{

}

std::size_t String::length() const
{
	return m_length;
}

std::int64_t String::index(char c) const
{
	for (std::size_t i = 0; i < m_length; ++i)
		if (m_data[i] == c)
			return (std::int64_t)i;
	return -1;
}

void String::to_upper(std::size_t first, std::size_t last)
{
	if ((first >= last) || (last > m_length)) { /* error */ }

	for (std::size_t i = first; i < last; ++i)
		m_data[i] = (char)toupper(m_data[i]);
}

void String::to_lower(std::size_t first, std::size_t last)
{
	if ((first >= last) || (last > m_length)) { /* error */ }

	for (std::size_t i = first; i < last; ++i)
		m_data[i] = (char)tolower(m_data[i]);
}

std::ostream & operator<< (std::ostream & stream, const String & string)
{
	for (std::size_t i = 0; i < string.length(); ++i)
		stream << string[i];

	return stream;
}

std::istream & operator>> (std::istream & stream, String & string)
{
	char * c = new char[1000];
	stream >> c;
	string = String(c);
	delete[] c;
	return stream;
}

char String::operator[] (std::size_t index) const
{
	if (index >= m_length) { /* error */ };
	return m_data[index];
}

char & String::operator[] (std::size_t index)
{
	if (index >= m_length) { /* error */ };
	return m_data[index];
}

String & String::operator= (const String & other)
{

}

String & String::operator= (String && other)
{

}

// #include <xstring>

String & String::operator+= (const String & other)
{
	std::size_t length = m_length + other.length();
	char *      string = new char[length];

	for (std::size_t i = 0; i < m_length; ++i)
		string[i] = m_data[i];

	for (std::size_t i = 0; i < other.length(); ++i)
		string[m_length + i] = other[i];

	delete m_data;
	m_length = length;
	m_data = string;

	return (*this);
}

String operator+ (const String & lhs, const String & rhs)
{
	return String(lhs) += rhs;
}

String operator+ (const String & lhs, char rhs)
{
	return String(lhs) += String(rhs);
}

String operator+ (const String & lhs, const char * rhs)
{
	return String(lhs) += String(rhs);
}

String operator+ (char lhs, const String & rhs)
{
	return String(lhs) += rhs;
}

String operator+ (const char * lhs, const String & rhs)
{
	return String(lhs) += rhs;
}

bool operator== (const String & lhs, const String & rhs)
{
	if (lhs.length() != rhs.length())
		return false; // optimization

	std::size_t length = lhs.length(), n = 0;
	while ((n < length) && (lhs[n] == rhs[n])) n++; // strcmp

	return (n == length);
}

bool operator== (const String & lhs, char rhs)
{
	return (lhs == String(rhs));
}

bool operator== (const String & lhs, const char * rhs)
{
	return (lhs == String(rhs));
}

bool operator== (char lhs, const String & rhs)
{
	return (String(lhs) == rhs);
}

bool operator== (const char * lhs, const String & rhs)
{
	return (String(lhs) == rhs);
}

bool operator> (const String & lhs, const String & rhs)
{
	std::size_t length = (lhs.length() < rhs.length()) ? lhs.length() : rhs.length(), n = 0;

	while ((n < length) && (lhs[n] == rhs[n])) n++;

	if (n == length)
		return (lhs.length() > rhs.length());

	if ((('A' <= lhs[n] && lhs[n] <= 'Z') || ('a' <= lhs[n] && lhs[n] <= 'z')) &&
		(('A' <= rhs[n] && rhs[n] <= 'Z') || ('a' <= rhs[n] && rhs[n] <= 'z')))
	{
		char A = lhs[n]; // (lhs[n] & ~32);
		char B = rhs[n]; // (rhs[n] & ~32);

		if (A != B) return (A > B);
	}

	return lhs[n] > rhs[n];
}

bool operator> (const String & lhs, char rhs)
{
	return (lhs > String(rhs));
}

bool operator> (const String & lhs, const char * rhs)
{
	return (lhs > String(rhs));
}

bool operator> (char lhs, const String & rhs)
{
	return (String(lhs) > rhs);
}

bool operator> (const char * lhs, const String & rhs)
{
	return (String(lhs) > rhs);
}

bool operator!= (const String & lhs, const String & rhs)
{
	return !(lhs == rhs);
}

bool operator!= (const String & lhs, char rhs)
{
	return !(lhs == rhs);
}

bool operator!= (const String & lhs, const char * rhs)
{
	return !(lhs == rhs);
}

bool operator!= (char lhs, const String & rhs)
{
	return !(lhs == rhs);
}

bool operator!= (const char * lhs, const String & rhs)
{
	return !(lhs == rhs);
}

bool operator< (const String & lhs, const String & rhs)
{
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator< (const String & lhs, char rhs)
{
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator< (const String & lhs, const char * rhs)
{
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator< (char lhs, const String & rhs)
{
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator< (const char * lhs, const String & rhs)
{
	return !(lhs == rhs) && !(lhs > rhs);
}

bool operator<= (const String & lhs, const String & rhs)
{
	return !(lhs > rhs);
}

bool operator<= (const String & lhs, char rhs)
{
	return !(lhs > rhs);
}

bool operator<= (const String & lhs, const char * rhs)
{
	return !(lhs > rhs);
}

bool operator<= (char lhs, const String & rhs)
{
	return !(lhs > rhs);
}

bool operator<= (const char * lhs, const String & rhs)
{
	return !(lhs > rhs);
}

bool operator>= (const String & lhs, const String & rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

bool operator>= (const String & lhs, char rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

bool operator>= (const String & lhs, const char * rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

bool operator>= (char lhs, const String & rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

bool operator>= (const char * lhs, const String & rhs)
{
	return (lhs == rhs) || (lhs > rhs);
}

char main_menu()
{
	char result;

	std::cout << std::endl << std::endl;
	std::cout << std::endl << "  ~~~  String Simulator   ~~~  ";
	std::cout << std::endl;
	std::cout << "(0) Assign values to String s1, s2, and s3" << std::endl;
	std::cout << "(1) Upcase s1[0, 4] and Downcase s2[2, 4]" << std::endl;
	std::cout << "(2) Copy s2 into s5 and set s2 = s2 + s4" << std::endl;
	std::cout << "(3) Find 'c' in s5, -1 if not found." << std::endl;
	std::cout << "(4) Add 'fooBlah' to s1" << std::endl;
	std::cout << "(5) Add Random character to s4" << std::endl;
	std::cout << "(6) Insert String into s5" << std::endl;
	std::cout << "(7) Perform Logical Comparisons" << std::endl;
	std::cout << "(8) Display Currently Registered Strings" << std::endl;
	std::cout << "(9) Exit simulation" << std::endl << std::endl << std::endl;
	std::cout << "Enter a selection (0-9): ";

	std::cin >> result;

	return result;
}

void display_strings(const String & s1, const String & s2, const String & s3, const String & s4, const String & s5)
{
	std::cout << std::endl << "--- Current Registered Strings --- " << std::endl;
	std::cout << "                   Length  Content" << std::endl;
	std::cout << "        String s1:      " << s1.length() << "  " << s1 << std::endl;
	std::cout << "        String s2:      " << s2.length() << "  " << s2 << std::endl;
	std::cout << "        String s3:      " << s3.length() << "  " << s3 << std::endl;
	std::cout << "        String s4:      " << s4.length() << "  " << s4 << std::endl;
	std::cout << "        String s5:      " << s5.length() << "  " << s5 << std::endl;
}

void logical_tests(const String & s1, const String & s2, const String & s3, const String & s4, const String & s5)
{
	std::cout << std::endl << "*** Logical Tests ***" << std::endl;
	std::cout << "       s1 == s2?      " << ((s1 == s2) ? "True" : "False") << std::endl;
	std::cout << "       s1 != s2?      " << ((s1 != s2) ? "True" : "False") << std::endl;
	std::cout << "       s2 > s5?       " << ((s2 > s5) ? "True" : "False") << std::endl;
	std::cout << "       s4 < s2        " << ((s4 < s2) ? "True" : "False") << std::endl;
	std::cout << "       s1 <= fooBlah? " << ((s1 <= "fooBlah") ? "True" : "False") << std::endl;
	std::cout << "       s4 >= C        " << ((s4 >= 'C') ? "True" : "False") << std::endl;
}

int main(int argc, char ** argv)
{
	srand(unsigned(time(NULL)));

	bool flag = false;

	String s1, s2, s3;
	String s4('\0');
	String s5;

	std::cout << std::boolalpha;

	std::cout << std::is_copy_constructible_v < String > << std::endl;
	std::cout << std::is_copy_assignable_v < String > << std::endl;

	std::cout << std::is_move_constructible_v < String > << std::endl;
	std::cout << std::is_move_assignable_v < String > << std::endl;

	std::cout << std::is_trivially_assignable_v < String, String > << std::endl;
	std::cout << std::is_trivially_copyable_v < String > << std::endl;

	std::cout << std::is_trivially_copy_assignable_v < String > << std::endl;
	std::cout << std::is_trivially_copy_constructible_v < String > << std::endl;

	std::cout << std::is_trivially_move_assignable_v < String > << std::endl;
	std::cout << std::is_trivially_move_constructible_v < String > << std::endl;

	do
	{
		char c = (char)(rand() % 26 + 65);

		char choice = main_menu();

		switch (choice)
		{
		case '0': s1 = String("aLpHa"); s2 = "BraVo"; s3 = "charlie"; break;
		case '1': s1.to_upper(0, 4); s2.to_lower(2, 4); break;
		case '2': s5 = s2; s2 += s4; break;
		case '3': std::cout << std::endl << "Find 'c' in s5: " << s5.index('c'); break;
		case '4': s1 = s1 + "fooBlah"; break;
		case '5': s4[0] = c; break;
		case '6': std::cout << std::endl << "Enter String into s5" << std::endl; std::cout << "> "; std::cin >> s5; break;
		case '7': logical_tests(s1, s2, s3, s4, s5); break;
		case '8': display_strings(s1, s2, s3, s4, s5); break;
		case '9': flag = true; break;
		default: std::cout << "Invalid selection. Try again."; break;
		}

	} while (!flag);

	system("pause");

	return EXIT_SUCCESS;
}
