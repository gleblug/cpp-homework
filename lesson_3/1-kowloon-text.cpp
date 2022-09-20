/*
Эта программа предназначена для приведения текстов коулунских писателей к
удобному для издательств формату. Программа обладает встроенной системой
обработки ошибок в знаках пунктуации.

Программа распознаёт 10 знаков препинания и кавычки:
Запятая, точка, двоеточие, точка с запятой, многоточие, знак вопроса,
восклицательный знак, вопросительный и вослицательный знак (пример: "Что вы себе
позволяете?!"), скобки, тире (двойной дефис, окружённый пробелами:
"Московское метро -- крупнейшее в Европе.").

В случае появления некорректного знака препинания программа сообщает об этом
в отдельно выводе с указанием символа, который не подходит под перечисленные
выше критерии. В конечный вывод попадает неправильная, по мнению программы,
конструкция целиком (от первого до последнего пробела), пример:

in:
  "Рассветы на Арракисе прекрасны!.."

out:
  "Рассветы" "на" "Арракисе" "прекрасны" "!.."

  WARN: maybe wrong punctuation mark:
  19th character ==> "!.."
*/


#include <iostream>
#include <vector>
#include <string>
#include <array>

std::string userInput() {
  std::string text;

  std::cout << "Input a text fragment:" << std::endl;
  std::getline(std::cin, text);
  text += " ";

  std::cout << std::endl;

  return text;
}

void printOutput(std::vector<std::string> const &container) {
  std::cout << "Formatted text:" << std::endl;

  for (std::string const &word: container) {
     std::cout << "[" << word << "] ";
  }

  std::cout << '\n'<< std::endl;
}

void printWarnings(std::vector<std::array<std::string, 2>> const &warnings) {
  if (! warnings.empty()) {
    std::cout << "WARN: maybe wrong punctuation mark on:" << std::endl;

    for (std::array<std::string, 2> const &warning: warnings) {
      std::cout
        << warning.at(0) << " character --> \""
        << warning.at(1) << "\"" << std::endl;
    }
  }
}

bool punctuationMarkIsCorrect(std::string const &mark) {
  const std::vector<std::string> listOfMarks{
    "...",
    "?!",
    "--",
    ".",
    ",",
    ":",
    ";",
    "\"",
    "?",
    "!",
    "(",
    ")"
  };

  for (std::string const &availableMark: listOfMarks) {
    if (mark == availableMark) {
      return true;
    }
  }

  return false;
}

int main() {

  // Declaring variables
  std::string rawText;
  std::string buffer("");

  size_t counter(0);

  bool lastSymbolIsPunctMark(false);

  std::vector<std::string> outputContainer;
  std::vector<std::array<std::string, 2>> warningsContainer;


  // User input (raw text)
  rawText = userInput();

  // Main cycle
  for(char const &symbol: rawText){
    // Add 1 to counters
    counter++;

    switch (symbol) {
      case '.':
      case ',':
      case ':':
      case ';':
      case '"':
      case '?':
      case '!':
      case '(':
      case ')':
      case '-':
        // Проверка на пустоту буфера
        if (! buffer.empty()){
          // Является ли последний символ знаком препинания?
          if (lastSymbolIsPunctMark) {
            // Если да, добавляем его к буферу
            buffer += symbol;
          } else {
            // Последний сивол -- буква, смотрим, дефис ли это
            if (symbol == '-') {
              // Если да, добавляем его к слову (случай "старик-рыбак")
              buffer += symbol;
              // и делаем break
              break;
            } else {
              // Если это не дефис и в буфере лежит слово (проверили на этапе
              // lastSymbolIsPunctMark), отправляем его в вывод:
              outputContainer.push_back(buffer);
              // и помещаем в буфер символ.
              buffer = symbol;
            }
          }
        } else {
          buffer += symbol;
        }

        lastSymbolIsPunctMark = true;
        break;

      default:
        // Случай с буквой или пробелом:
        // Проверяем буфер на пустоту
        if (! buffer.empty()){
          if (lastSymbolIsPunctMark && (!punctuationMarkIsCorrect(buffer))) {
            // Если в буфере знак препинания и он некорректен, создаём запись об
            // ошибке, включающую индекс
            std::string warnIndex(std::to_string(counter - buffer.length()));
            std::array<std::string, 2> warning{warnIndex, buffer};

            warningsContainer.push_back(warning);
            outputContainer.push_back(buffer);
            buffer = "";
          } else if (symbol == ' ') {
            // Иначе проверяем пробел ли это
            // если да, пушим буфер в вывод и очищаем его
            outputContainer.push_back(buffer);
            buffer = "";
          } else {
            // если это буква, добавляем её к буферу
            buffer += symbol;
          }
        } else {
          if (symbol != ' ') {
            buffer += symbol;
          }
        }
        lastSymbolIsPunctMark = false;
        break;
    }
  }

  printOutput(outputContainer);

  printWarnings(warningsContainer);

  return 0;
}
