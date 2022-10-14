/*
Подход с использованием создания класса "ключа" (Key) внутри класса (Foo),
доступ к закрытым полям и методам которого мы хотим "приотрыть".

Этот способ позволяет выбрать, каким классам какой функционал будет доступен с
помощью посредника, так как создать экземпляр класса Foo::Key мы можем только
внутри дружественной сущности.

Источник: https://stackoverflow.com/questions/1609472/friend-class-with-limited-access
*/

class Foo {
public:
  class Key {
    friend class Bar;
    Key();
  };

  void A(Key key) { // Перегрузка функции
    A();
  }

private:
  int x;
  void A() {
    x++;
  };
  void B() {
    x--;
  };
};

class Bar {
  Bar() {
    Foo foo;
    Foo::Key key;

    foo.A(key);
    // foo.B(); -- доступа нет!
  }
};


int main(int argc, char const *argv[]) {

  // Foo::Key key; // ERROR: 'Foo::Key::Key()' is private within this context

  return 0;
}
