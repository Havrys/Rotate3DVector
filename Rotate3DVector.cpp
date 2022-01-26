/*Description
Rotate a vector around an axis in 3D space.
Input:

Ten reals:
1.The 3D coordinates of the vector.
2.The rotation angle in radians.
3.The 3D coordinates of a point of the axis.
4.The 3D coordinates of the direction vector of the axis.
The length of the direction vector is greater than 1e-8.

Output:
Three reals, the 3D coordinates of the vector after its rotation.*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

struct Vector {
	double x;
	double y;
	double z;

	void normalize()
	{
		double vectorLenght = std::sqrt(std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
		x /= vectorLenght;
		y /= vectorLenght;
		z /= vectorLenght;
	}

	Vector& operator+ (const Vector& rhs)  const {
		Vector res;
		res.x = rhs.x + this->x;
		res.y = rhs.y + this->y;
		res.z = rhs.z + this->z;
		return res;
	}

	Vector& operator- (const Vector& rhs) const {
		Vector res;
		res.x = this->x - rhs.x;
		res.y = this->y - rhs.y;
		res.z = this->z - rhs.z;
		return res;
	}

	Vector& operator* (const double& rhs) const {
		Vector res;
		res.x = this->x * rhs;
		res.y = this->y * rhs;
		res.z = this->z * rhs;
		return res;
	}
	friend std::ostream& operator<< (std::ostream& out, const Vector& v);
};

std::ostream& operator<< (std::ostream& out, const Vector& v)
{
	out << std::setprecision(8) << std::fixed << v.x << " " << v.y << " " << v.z;
	return out;
}

void rotate(Vector& rotate, Vector& point, Vector direction, double angle)
{
	direction.normalize();
	// change origin 
	Vector shifted = rotate - point;
	// rotate vector around x by alpha
	double d = std::sqrt(std::pow(direction.y, 2) + std::pow(direction.z, 2));
	double sina = 0;
	double cosa = 1;
	if (d != 0) {
		sina = direction.y / d;
		cosa = direction.z / d;
	}
	Vector rotx;
	rotx.x = shifted.x;
	rotx.y = shifted.y * cosa - shifted.z * sina;
	rotx.z = shifted.y * sina + shifted.z * cosa;
	// rotate vector around y by beta
	double cosb = d;
	double sinb = direction.x;
	Vector roty;
	roty.x = rotx.x * cosb - rotx.z * sinb;
	roty.y = rotx.y;
	roty.z = rotx.x * sinb + rotx.z * cosb;

	// rotate vector by angle
	double cosd = std::cos(angle);
	double sind = std::sin(angle);
	Vector rotz;
	rotz.x = roty.x * cosd - roty.y * sind;
	rotz.y = roty.x * sind + roty.y * cosd;
	rotz.z = roty.z;

	// rotate around y by - beta
	roty.x = rotz.x * cosb + rotz.z * sinb;
	roty.y = rotz.y;
	roty.z = -rotz.x * sinb + rotz.z * cosb;

	//rotate around x bu - alpha
	rotx.x = roty.x;
	rotx.y = roty.y * cosa + roty.z * sina;
	rotx.z = -roty.y * sina + roty.z * cosa;

	// shift it back
	rotate = rotx + point;
}

int main() {
	Vector vend;
	// input vector
	std::cin >> vend.x >> vend.y >> vend.z;
	Vector vbegin{ 0,0,0 };

	// input rotation angle
	double angle;
	std::cin >> angle;

	// input axis point
	Vector axisPoint;
	std::cin >> axisPoint.x >> axisPoint.y >> axisPoint.z;

	// input axis direction
	Vector direction;
	std::cin >> direction.x >> direction.y >> direction.z;

	rotate(vend, axisPoint, direction, angle);
	rotate(vbegin, axisPoint, direction, angle);
	Vector v = vend - vbegin;
	std::cout << v;
}
