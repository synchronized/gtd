#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::string;

class Observer;
class Subject {
   private:
    string mName;
    std::vector<std::shared_ptr<Observer>> observers;

   public:
    Subject(std::string name) : mName(name) {
        std::cout << "Subject:" << mName << " created" << std::endl;
    }
    void addObserver(std::shared_ptr<Observer> ob) { observers.push_back(ob); }

    ~Subject() { std::cout << "Subject:" << mName << " destroy" << std::endl; }
};

class Observer {
   private:
    string mName;
    std::weak_ptr<Subject> object;

   public:
    Observer(std::shared_ptr<Subject> obj, string name)
        : object(obj), mName(name) {
        std::cout << "Observer:" << mName << " created" << std::endl;
    }
    ~Observer() {
        std::cout << "Observer:" << mName << " destroy" << std::endl;
    }
};

int main() {
    auto sub_ptr = std::make_shared<Subject>("sub1");
    auto obs_ptr1 = std::make_shared<Observer>(sub_ptr, "obs1");
    auto obs_ptr2 = std::make_shared<Observer>(sub_ptr, "obs2");
    sub_ptr->addObserver(obs_ptr1);
    sub_ptr->addObserver(obs_ptr2);
    return 0;
}
