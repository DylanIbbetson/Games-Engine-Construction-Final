#pragma once
class Rectangle
{
public:
	int left, right, top, bottom;

	//Rectangle() = default;
	Rectangle(int l = 0, int r = 0, int t = 0, int b = 0) : left(l), right(r), top(t), bottom(b){}
	

	int Width() const { return right - left; }
	int Height() const { return bottom - top; }

	void Translate(int dx, int dy)
	{
		left += dx;
		right += dx;
		top += dy;
		bottom += dy;
	}

	void ClipTo(const Rectangle& other)
	{
		if (left < other.left)
			left = other.left;

		if (right > other.right)
			right = other.right;

		if (top < other.top)
			top = other.top;

		if (bottom > other.bottom)
			bottom = other.bottom;

	}
};

