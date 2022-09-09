// wrap_shared example
#include <iostream>
#include <memory>

#include "../pal/cpp/guarded.hpp"

struct screamer {
   screamer() { std::cout << "Creating screamer " << this << std::endl; }
  ~screamer() { std::cout << "Destroying screamer " << this << std::endl; }
};

std::ostream& operator<<(std::ostream& o, const screamer& scream)
{
  o << &scream;
  return (o);
}

void test_guarded_borrow () {

 //TODO: test with different threads

int ten(10);
int twenty(20);
int thirty(30);
screamer s1;

webserv::pal::cpp::guarded<int>  g1(ten);
webserv::pal::cpp::guarded<int *>  g6(new int(50));
webserv::pal::cpp::guarded<int>  g2(twenty);
webserv::pal::cpp::guarded<int>  g3(thirty);
webserv::pal::cpp::guarded<screamer>  g4(s1);
webserv::pal::cpp::guarded<screamer*>  g5(&s1);

std::cout << g1.get_borrow().getValue() << std::endl;
std::cout << g2.get_borrow().getValue() << std::endl;
std::cout << g3.get_borrow().getValue() << std::endl;
std::cout << g4.get_borrow().getValue() << std::endl;
std::cout << g5.get_borrow().getValue() << std::endl;
std::cout << *g6.get_borrow().getValue() << std::endl;




}