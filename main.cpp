#include "Utility.h"

// 基底クラス
class Animal {
public:
	~Animal() = default;
    virtual void Speak() const = 0;
};

// 犬派生クラス
class Dog : public Animal {
public:
	void Speak() const override {
		CharOut("Dog: Woof!");
	}
};

// 猫派生クラス
class Cat : public Animal {
public:
	void Speak() const override {
		CharOut("Cat: Meow!");
	}
};

int main() {
	// 生成
    std::unique_ptr<Animal> dog = std::make_unique<Dog>();
	std::unique_ptr<Animal> cat = std::make_unique<Cat>();

	// 鳴く
	dog->Speak();
	cat->Speak();

    return 0;
}
