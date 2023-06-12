#include <iostream>
using namespace std;

class UserEntry {
  public:
    UserEntry():m_Name(""),m_Age(0){}
    UserEntry(std::string name, unsigned age):m_Name(name),m_Age(age) {}

    std::string GetName() const { return m_Name; }
    unsigned GetAge() const { return m_Age; }
  private:
    std::string m_Name;
    unsigned m_Age;
};

//template<size_t I> auto get (const UserEntry& u);
//template<> std::string get<0>(const UserEntry &u) { return u.GetName(); }
//template<> auto get<1>(const UserEntry &u) { return u.GetAge(); }



namespace std {
template<> struct tuple_size<UserEntry> : std::integral_constant<size_t,2> {};
template<> struct tuple_element<0, UserEntry> { using type = std::string; };
template<> struct tuple_element<1, UserEntry> { using type = unsigned; };

template<> auto get<0>(const UserEntry &u) { return u.GetName(); }
template<> auto get<1>(const UserEntry &u) { return u.GetAge(); }
}


int main() {
    //UserEntry userEntry("sunday", 1);
    //std::string name = get<0>(userEntry);
    //std::cout << "name:" << name << std::endl;
    return 0;
}
