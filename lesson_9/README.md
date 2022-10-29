## Исключения

- Многоуровневость
- Эффективность
- Преобразования

`throw`, `try`, `catch`:
```cpp
try {
  throw 5;
}
catch(int e) {
  std::cerr << "Error " << e << '\n';
}
catch(...) {
  std::cerr << "Unknown error" << '\n';
}
```

`noexcept` -- помогает компилятору оптимизировать код
