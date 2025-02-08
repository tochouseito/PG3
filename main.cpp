#include "Utility.h"

// 基底クラス
class IShape {
public:
	virtual ~IShape() = default;
	virtual void Draw() const = 0;
	virtual float Size() const = 0;
protected:
	float size_ = 0.0f;
};

// 派生クラス
class Circle : public IShape {
public:
	void Draw() const override {
		CharOut("Circle Draw",Size());
	}
	float Size() const override {
		return PI * radius_ * radius_;
	}
private:
	float radius_ = 3.0f;
};

// 派生クラス
class Rectangle : public IShape {
public:
	void Draw() const override {
		CharOut("Rectangle Draw",Size());
	}
	float Size() const override {
		return width_ * height_;
	}
private:
	float width_ = 5.0f;
	float height_ = 3.0f;
};

int main() {

	std::unique_ptr<IShape> circle = std::make_unique<Circle>();
	std::unique_ptr<IShape> rectangle = std::make_unique<Rectangle>();

	circle->Draw();
	rectangle->Draw();

	return 0;
}
