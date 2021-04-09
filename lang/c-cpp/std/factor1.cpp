#include <memory>

class Factor {
public:
  //Factor(const Factor&) = default;
  //Factor(Factor&&) = default;
  //Factor& operator=(const Factor&) = default;
  //Factor& operator=(Factor&&) = default;
  Factor(int data) {
    _data = std::make_unique<int>(data);
  }
  int* data() const { return _data.get(); }
private:
  //std::unique_ptr<int> _data; //this data remove default constructor
  std::shared_ptr<int> _data;
};

class Node {
public:
  Node(const Node& other) : _factor(other._factor) {
  }
private:
  Factor _factor;
};

int main(int argc, char **argv) {
}
