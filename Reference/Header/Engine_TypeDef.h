#pragma once
#ifndef Engine_Typedef_h__
#define Engine_Typedef_h__

namespace Engine
{
	typedef		bool						BOOL;

	typedef		signed char					_BYTE;
	typedef		unsigned char				UBYTE;

	typedef		wchar_t						TCHAR;

	typedef		signed short				SHORT;
	typedef		unsigned short				USHORT;

	typedef		signed int					INT;
	typedef		unsigned int				UINT;

	typedef		signed long					LONG;
	typedef		unsigned long				ULONG;

	typedef		float						FLOAT;
	typedef		double						DOUBLE;

	//typedef		D3DXVECTOR2					Vector2;
	//typedef		D3DXVECTOR3					Vector3;
	typedef		D3DXVECTOR4					Vector4;

	typedef		D3DXMATRIX					Matrix;

	struct Vector3Int;
	struct Vector3 : public D3DXVECTOR3
	{
	public:
		Vector3(void) = default;
		Vector3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
		~Vector3(void) = default;


		// 묵시적 형변환
		operator D3DXVECTOR3(void);
		operator Vector3Int(void);

		// 명시적 형변환
		D3DXVECTOR3 toDx(void) { return D3DXVECTOR3(x, y, z); }
		static D3DXVECTOR3 toDx(const Vector3& object) { return D3DXVECTOR3(object.x, object.y, object.z); }
		static Vector3 toVec3(const D3DXVECTOR3& object) { return Vector3(object.x, object.y, object.z); }

		// 가독성을 위한 정의
		static Vector3 zero() { return Vector3{ 0.0f, 0.0f, 0.0f }; }
		static Vector3 one() { return Vector3{ 1.0f, 1.0f, 1.0f }; }

		// 연산자 정의
		bool operator==(const Vector3& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z);
		}
		bool operator!=(const Vector3& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z);
		}
		bool operator>(const Vector3& other) const
		{
			return (x > other.x) && (y > other.y) && (z > other.z);
		}
		bool operator<(const Vector3& other) const
		{
			return (x < other.x) && (y < other.y) && (z < other.z);
		}
		bool operator>=(const Vector3& other) const
		{
			return (x >= other.x) && (y >= other.y) && (z >= other.z);
		}
		bool operator<=(const Vector3& other) const
		{
			return (x <= other.x) && (y <= other.y) && (z <= other.z);
		}

		Vector3 operator+(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}
		Vector3 operator-(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}
		Vector3 operator*(const float& i) const
		{
			return Vector3(x * i, y * i, z * i);
		}
		Vector3 operator/(const float& i) const
		{
			return Vector3(x / i, y / i, z / i);
		}

		void operator+=(const Vector3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}
		void operator-=(const Vector3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}
		void operator*=(const float& i)
		{
			x *= i;
			y *= i;
			z *= i;
		}
		void operator/=(const float& i)
		{
			x /= i;
			y /= i;
			z /= i;
		}



		// 벡터 내적
		float dot(const Vector3& other) const { return x * other.x + y * other.y + z + other.z; }
		static float dot(const Vector3& obj, const Vector3& sbj) { return obj.x * sbj.x + obj.y * sbj.y + obj.z + sbj.z; }

		// 선분의 법선 선분에 대한 반사벡터
		Vector3 reflect(const Vector3& other) const
		{
			float _dot = dot(other); // (R = V - 2 X (V dot N) X N)
			return Vector3(x - 2.0f * _dot * other.x, y - 2.0f * _dot * other.y, z - 2.0f * _dot * other.z);
		}
		static Vector3 reflect(const Vector3& object, const Vector3& subject)
		{
			float _dot = dot(object, subject);
			return Vector3(object.x - 2.0f * _dot * subject.x, object.y - 2.0f * _dot * subject.y, object.z - 2.0f * _dot * subject.z);
		}

		// 스칼라 값
		float magnitude() const { return std::sqrt(x * x + y * y + z * z); }
		static float magnitude(const Vector3& obj) { return std::sqrt(obj.x * obj.x + obj.y * obj.y + obj.z * obj.z); }

		// 두 점 사잉의 스칼라 값
		float distance(const Vector3& other) { return (*this - other).magnitude(); }
		static float distance(const Vector3& _Vec1, const Vector3& _Vec2) { return (_Vec1 - _Vec2).magnitude(); }

		// 단위벡터
		Vector3 normalize() const
		{
			float length = magnitude();
			return { x / length, y / length, z / length };
		}
		static Vector3 normalize(const Vector3& obj)
		{
			float length = obj.magnitude();
			return { obj.x / length, obj.y / length, obj.z / length };
		}

		// 방위각과 상승각에 대응하는 방향벡터
		static Vector3 direction(float azimuth, float elevation)
		{
			// azimuth: 방향각 (0 <= azimuth < 2π) / elevation: 경사각 (-π/2 <= elevation <= π/2)
			while (azimuth >= 0 && azimuth <= 360 && elevation >= 0 && elevation <= 360)
			{
				if (azimuth < 0) { azimuth += 360; }
				if (azimuth > 360) { azimuth -= 360; }
				if (elevation < 0) { elevation += 360; }
				if (elevation > 360) { elevation -= 360; }
			}

			return Vector3(std::cos(elevation) * std::cos(azimuth), std::cos(elevation) * std::sin(azimuth), std::sin(elevation));
		}
		static Vector3 direction(float pitchRadian, float yawRadian, float rollRadian)
		{
			float cosPitch = cosf(pitchRadian);
			Vector3 direction = Vector3{ cosf(yawRadian) * cosPitch, sinf(pitchRadian), sinf(yawRadian) * cosPitch };
			D3DXVec3Normalize(&direction, &direction);
			return direction;
		}
		static Vector3 direction(Vector3 rotationAngle)
		{
			return direction(D3DXToRadian(rotationAngle.x), D3DXToRadian(rotationAngle.y), D3DXToRadian(rotationAngle.z));
		}


		// 방위각에 대응하는 방향벡터
		static Vector3 drection2D(float azimuth) { return Vector3(std::cos(azimuth), std::sin(azimuth), 0.0f); }
		//static Vector3 drection2D(float azimuth) { return Vector3(std::cos(azimuth), 0.0f, std::sin(azimuth)); }

		static float angle2D(const Vector3& directionVec)
		{
			Vector3 normalVec = directionVec.normalize();
			float acosAng = acos(normalVec.x) * (180.0f / PI);
			if (normalVec.y < 0) { acosAng = 360.0f - acosAng; }
			return acosAng;
		}
		static float radian2D(const Vector3& directionVec)
		{
			Vector3 normalVec = directionVec.normalize();
			return acos(normalVec.x);
		}




		// 좌표를 기준으로 방위각과 상승각에 대응하는 방향벡터
		Vector3 forward(float azimuth, float elevation) { return *this + direction(azimuth, elevation).normalize(); }
		static Vector3 forward(Vector3 position, float azimuth, float elevation) { return position + direction(azimuth, elevation).normalize(); }

		// 벡터 외적
		Vector3 cross(const Vector3& other) const
		{
			return Vector3(
				y * other.z - z * other.y,
				z * other.x - x * other.z,
				x * other.y - y * other.x
			);
		}
		static Vector3 cross(const Vector3& obj, const Vector3& sbj)
		{
			return Vector3(
				obj.y * sbj.z - obj.z * sbj.y,
				obj.z * sbj.x - obj.x * sbj.z,
				obj.x * sbj.y - obj.y * sbj.x
			);
		}

		// 3차원 수직벡터(y축)
		Vector3 perpendicular() const { return cross(Vector3{ -z, y, x }); }
		static Vector3 perpendicular(const Vector3& obj) { return cross(obj, Vector3(-obj.z, obj.y, obj.x)); }
		// 2차원 수직벡터
		Vector3 perpendicular2D() const { return Vector3{ -z, y, x }; }
		static Vector3 perpendicular2D(const Vector3& obj) { return Vector3(-obj.z, obj.y, obj.x); }

	};

	struct Vector3Int
	{
	public:
		Vector3Int() : x(0), y(0), z(0) {}
		Vector3Int(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
		~Vector3Int() {}

		int x, y, z;

		// 묵시적 형변환
		operator D3DXVECTOR3();
		operator Vector3();

		// 명시적 형변환
		D3DXVECTOR3 toDx() { return D3DXVECTOR3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)); }
		static D3DXVECTOR3 toDx(const Vector3Int& object) { return D3DXVECTOR3(static_cast<float>(object.x), static_cast<float>(object.y), static_cast<float>(object.z)); }
		static Vector3Int toVec3(const D3DXVECTOR3& object) { return Vector3Int(static_cast<int>(object.x), static_cast<int>(object.y), static_cast<int>(object.z)); }

		//가독성을 위한 정의
		static Vector3Int zero() { return Vector3Int{ 0, 0, 0 }; }
		static Vector3Int one() { return Vector3Int{ 1, 1, 1 }; }

		// 연산자 정의
		bool operator==(const Vector3Int& other) const
		{
			return (x == other.x) && (y == other.y) && (z == other.z);
		}
		bool operator!=(const Vector3Int& other) const
		{
			return (x != other.x) || (y != other.y) || (z != other.z);
		}

		Vector3Int operator+(const Vector3Int& other) const
		{
			return Vector3Int(x + other.x, y + other.y, z + other.z);
		}
		Vector3Int operator-(const Vector3Int& other) const
		{
			return Vector3Int(x - other.x, y - other.y, z - other.z);
		}
		Vector3Int operator*(const int& i) const
		{
			return Vector3Int(x * i, y * i, z * i);
		}
		Vector3Int operator/(const int& i) const
		{
			return Vector3Int(x / i, y / i, z / i);
		}

		void operator+=(const Vector3Int& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;
		}
		void operator-=(const Vector3Int& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
		}
		void operator*=(const int& i)
		{
			x *= i;
			y *= i;
			z *= i;
		}
		void operator/=(const int& i)
		{
			x /= i;
			y /= i;
			z /= i;
		}
		void operator*=(const float& i)
		{
			x = (int)((float)x * i);
			y = (int)((float)y * i);
			z = (int)((float)z * i);
		}
		void operator/=(const float& i)
		{
			x = (int)((float)x / i);
			y = (int)((float)y / i);
			z = (int)((float)z / i);
		}

		// 벡터 내적
		float dot(const Vector3& other) const { return static_cast<float>(x * other.x + y * other.y + z + other.z); }
		static float dot(const Vector3& obj, const Vector3& sbj) { return static_cast<float>(obj.x * sbj.x + obj.y * sbj.y + obj.z + sbj.z); }

		// 스칼라값
		float magnitude() const { return std::sqrt(static_cast<float>(x * x + y * y + z * z)); }
		static float magnitude(const Vector3& obj) { return std::sqrt(static_cast<float>(obj.x * obj.x + obj.y * obj.y + obj.z * obj.z)); }

		// 두 점 사이의 스칼라값
		float distance(const Vector3Int& other) { return (*this - other).magnitude(); }
		static float distance(const Vector3Int& obj, const Vector3Int& sbj) { return (obj - sbj).magnitude(); }

	};


	inline Vector3::operator D3DXVECTOR3() { return D3DXVECTOR3(x, y, z); }
	inline Vector3::operator Vector3Int() { return Vector3Int(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)); }

	inline Vector3Int::operator D3DXVECTOR3() { return D3DXVECTOR3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z)); }
	inline Vector3Int::operator Vector3() { return Vector3Int(static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)); }




	struct Vector2Int;
	struct Vector2 : public D3DXVECTOR2
	{
	public:
		Vector2() = default;
		Vector2(float _x, float _y) { x = _x; y = _y; }
		~Vector2() = default;

		operator Vector2Int() const;
		Vector2Int toVec2Int() const;
		static Vector2Int toVec2Int(const Vector2& obj);


		bool operator==(const Vector2& other) const
		{
			return (x == other.x) && (y == other.y);
		}
		bool operator!=(const Vector2& other) const
		{
			return (x != other.x) || (y != other.y);
		}

		Vector2 operator+(const Vector2& other) const
		{
			return { x + other.x, y + other.y };
		}
		Vector2 operator-(const Vector2& other) const
		{
			return { x - other.x, y - other.y };
		}
		Vector2 operator*(const float& i) const
		{
			return { x * i, y * i };
		}
		Vector2 operator/(const int& i) const
		{
			return { x / i, y / i };
		}

		void operator+=(const Vector2& other)
		{
			x += other.x;
			y += other.y;
		}
		void operator-=(const Vector2& other)
		{
			x -= other.x;
			y -= other.y;
		}
		void operator*=(const float& i)
		{
			x *= i;
			y *= i;
		}
		void operator/=(const float& i)
		{
			x /= i;
			y /= i;
		}
		void operator=(const Vector2& other)
		{
			x = other.x;
			y = other.y;
		}

		//전위연산
		Vector2& operator++()
		{
			x++;
			y++;
			return *this;
		}
		// 후위연산
		Vector2 operator++(int)
		{
			Vector2 temp{ x, y };
			x++;
			y++;
			return temp;
		}

		Vector2& operator--()
		{
			x--;
			y--;
			return *this;
		}
		Vector2 operator--(int)
		{
			Vector2 temp{ x, y };
			x--;
			y--;
			return temp;
		}

		Vector2 absolute() // 좌표 절대값
		{
			return { abs(x) ,abs(y) };
		}
		static Vector2 absolute(const Vector2& obj) // 좌표 절대값
		{
			return { abs(obj.x) ,abs(obj.y) };
		}

		// 벡터 내적
		float dot(const Vector2& other) const
		{
			return x * other.x + y * other.y;
		}
		static float dot(const Vector2& obj, const Vector2& sbj)
		{
			return obj.x * sbj.x + obj.y * sbj.y;
		}

		// 벡터의 크기(스칼라)
		float magnitude() const
		{
			return static_cast<float>(std::sqrt(x * x + y * y));
		}
		static float magnitude(const Vector2& obj)
		{
			return static_cast<float>(std::sqrt(obj.x * obj.x + obj.y * obj.y));
		}

		// 두 좌표 간 상대 거리
		float distance(const Vector2& sbj)
		{
			Vector2 sum = *this - sbj;
			return sum.magnitude();
		}
		static float distance(const Vector2& _Vec1, const Vector2& _Vec2)
		{
			Vector2 sum = _Vec1 - _Vec2;
			return sum.magnitude();
		}

		// 수직 선분을 나타냄
		Vector2 perpendicular() const
		{
			return { -y, x };
		}
		static Vector2 perpendicular(const Vector2& obj)
		{
			return { -obj.y, obj.x };
		}

		// 단위 벡터 표현 (숫자 0~1로 범위 고정)
		Vector2 normalize() const
		{
			float length = (*this).magnitude();
			return { x / length, y / length };
		}
		static Vector2 normalize(const Vector2& obj)
		{
			float length = obj.magnitude();
			return { obj.x / length, obj.y / length };
		}

		// 실수 각도를 단위 벡터로 나타내줌
		static Vector2 getDirectionVector(float _angle)
		{
			return Vector2(std::cos(_angle), std::sin(_angle));
		}
		// 현재 각도의 전방을 알려줌
		Vector2 forward(float _rotation) const
		{
			Vector2 DirectionVec = getDirectionVector(_rotation);
			return Vector2(x * DirectionVec.x - y * DirectionVec.y, x * DirectionVec.y + y * DirectionVec.x);
		}

		static Vector2 reflect(const Vector2& velocity, const Vector2& normal)
		{
			Vector2 unitNormal = normal.normalize();
			return velocity - unitNormal * (2 * velocity.dot(unitNormal));
		}

		static float angle(const Vector2& directionVec)
		{
			Vector2 normalVec = directionVec.normalize();
			float acosAng = acos(normalVec.x) * (180.0f / PI);
			if (normalVec.y < 0) { acosAng = 360.0f - acosAng; }
			return acosAng;
		}





		static Vector2 zero() { return { 0.0f, 0.0f }; }
		static Vector2 one() { return { 1.0f, 1.0f }; }

	};

	struct Vector2Int
	{
	public:
		int x, y;

		Vector2Int(int _x, int _y) : x(_x), y(_y) {}

		Vector2 toVec2()
		{
			return { static_cast<float>(x), static_cast<float>(y) };
		}
		static Vector2 toVec2(const Vector2Int& obj)
		{
			return { static_cast<float>(obj.x), static_cast<float>(obj.y) };
		}

		Vector2Int absolute() // 좌표 절대값
		{
			return { (int)abs(x), (int)abs(y) };
		}
		static Vector2Int absolute(const Vector2& obj) // 좌표 절대값
		{
			return { (int)abs(obj.x), (int)abs(obj.y) };
		}

		operator Vector2() const;

		bool operator==(const Vector2Int& other) const
		{
			return (x == other.x) && (y == other.y);
		}
		bool operator!=(const Vector2Int& other) const
		{
			return (x != other.x) || (y != other.y);
		}

		Vector2Int operator+(const Vector2Int& other) const
		{
			return Vector2Int(x + other.x, y + other.y);
		}
		Vector2Int operator-(const Vector2Int& other) const
		{
			return Vector2Int(x - other.x, y - other.y);
		}
		Vector2Int operator*(const int& i) const
		{
			return Vector2Int(x * i, y * i);
		}
		Vector2Int operator/(const int& i) const
		{
			return Vector2Int(x / i, y / i);
		}

		void operator+=(const Vector2Int& other)
		{
			x += other.x;
			y += other.y;
		}
		void operator-=(const Vector2Int& other)
		{
			x -= other.x;
			y -= other.y;
		}
		void operator*=(const int& i)
		{
			x *= i;
			y *= i;
		}
		void operator/=(const int& i)
		{
			x /= i;
			y /= i;
		}
		void operator=(const Vector2Int& other)
		{
			x = other.x;
			y = other.y;
		}
		//전위연산
		Vector2Int& operator++()
		{
			x++;
			y++;
			return *this;
		}
		// 후위연산
		Vector2Int operator++(int)
		{
			Vector2Int temp{ x, y };
			x++;
			y++;
			return temp;
		}

		Vector2Int& operator--()
		{
			x--;
			y--;
			return *this;
		}
		Vector2Int operator--(int)
		{
			Vector2Int temp{ x, y };
			x--;
			y--;
			return temp;
		}


		// 벡터 내적
		int dot(const Vector2Int& other) const
		{
			return x * other.x + y * other.y;
		}
		static int dot(const Vector2Int& obj, const Vector2Int& sbj)
		{
			return obj.x * sbj.x + obj.y * sbj.y;
		}

		float magnitude() const
		{
			return static_cast<float>(std::sqrt(x * x + y * y));
		}
		static float magnitude(const Vector2Int& obj)
		{
			return static_cast<float>(std::sqrt(obj.x * obj.x + obj.y * obj.y));
		}

		// 수직 선분
		Vector2Int perpendicular() const
		{
			return { -y, x };
		}
		static Vector2Int perpendicular(const Vector2Int& obj)
		{
			return { -obj.y, obj.x };
		}

		static Vector2Int zero() { return { 0,0 }; }
		static Vector2Int one() { return { 1,1 }; }
	};



	inline Vector2Int Vector2::toVec2Int() const
	{
		return { static_cast<int>(x), static_cast<int>(y) };
	}
	inline Vector2Int Vector2::toVec2Int(const Vector2& obj)
	{
		return { static_cast<int>(obj.x), static_cast<int>(obj.y) };
	}

	inline Vector2::operator Vector2Int() const { return Vector2Int(static_cast<int>(x), static_cast<int>(y)); }
	inline Vector2Int::operator Vector2() const { return Vector2(static_cast<float>(x), static_cast<float>(y)); }








}


typedef Engine::Vector3 Vector3;
typedef Engine::Vector2 Vector2;




#endif // Engine_Typedef_h__