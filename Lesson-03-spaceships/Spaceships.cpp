#include <iostream>
#include <memory>
#include <string>
#include <optional>

class Bitmap {
  std::string val;

 public:
  Bitmap(const std::string& val) : val(val) {
    std::cout << val << " bitmap loaded" << std::endl;
  }
  ~Bitmap() {
    std::cout << val << " bitmap unloaded" << std::endl;
  }
  void display() const { std::cout << val; }
};

struct Sprite {
  std::string name;
  std::shared_ptr<Bitmap> img;

  Sprite(std::optional<std::string> name) {
    if (name) {
      if (name->find("Spaceship") != std::string::npos) {
        img = std::make_shared<Bitmap>("<==>");
      } else {
        img = std::make_shared<Bitmap>("__");
      }
    } else {
      this->name = "default";
      img = std::make_shared<Bitmap>("#-#");
    }
    std::cout << this->name << " appeared: ";
    img->display();
    std::cout << std::endl;
  }
};

union Number {
  int n;
  float f;
  double d;
};

union Coord {
  int coords[2];
  struct Pos {
    int x, y;
  };
};

int main() {
  std::cout << "Create default\n";
  Sprite def(std::nullopt); // pass empty optional
  //Sprite def({}); // other way to pass empty
  {
    Sprite s1("Spaceship");
    {
      std::cout << "Create copy\n";
      Sprite s2(s1);
      std::cout << "Create other\n";
      Sprite s3("other");
    }
    std::cout << "Deleted copy\n";
  }
  std::cout << "Space should be empty\n";
}
