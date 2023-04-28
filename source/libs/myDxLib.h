#pragma once
#include<DxLib.h>
#include"common.h"

namespace DxLib {

	


	//Vec2<typename> operator達
	
	template<typename NAME>
	inline Vec2<NAME> operator +(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		Vec2<NAME> ans;
		ans.x = b.x+c.x;
		ans.y = b.y+c.y;
		return ans;
	}
	
	template<typename NAME>
	inline Vec2<NAME> operator +=(Vec2<NAME>& b, const Vec2<NAME>& c) {
		b.x += c.x;
		b.y += c.y;
		return b;
	}

	template<typename NAME>
	inline Vec2<NAME> operator -(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		Vec2<NAME> ans;
		ans.x = b.x - c.x;
		ans.y = b.y - c.y;
		return ans;
	}
	template<typename NAME>
	inline Vec2<NAME> operator -=(Vec2<NAME>& b, const Vec2<NAME>& c) {
		b.x -= c.x;
		b.y -= c.y;
		return b;
	}
	template<typename NAME>
	inline Vec2<NAME> operator *(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		Vec2<NAME> ans;
		ans.x = b.x * c.x;
		ans.y = b.y * c.y;
		return ans;
	}
	template<typename NAME>
	inline Vec2<NAME> operator *=(Vec2<NAME>& b, const Vec2<NAME>& c) {
		b.x *= c.x;
		b.y *= c.y;
		return b;
	}
	template<typename NAME>
	inline Vec2<NAME> operator /(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		Vec2<NAME> ans;
		ans.x = b.x / c.x;
		ans.y = b.y / c.y;
		return ans;
	}
	template<typename NAME>
	inline Vec2<NAME> operator /=(Vec2<NAME>& b, const Vec2<NAME>& c) {
		b.x /= c.x;
		b.y /= c.y;
		return b;
	}
	template<typename NAME>
	inline Vec2<NAME> operator %(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		Vec2<NAME> ans;
		ans.x = b.x % c.x;
		ans.y = b.y % c.y;
		return ans;
	}
	template<typename NAME>
	inline Vec2<NAME> operator %=(Vec2<NAME>& b, const Vec2<NAME>& c) {
		b.x %= c.x;
		b.y %= c.y;
		return b;
	}
	template<typename NAME>
	inline const bool operator ==(const Vec2<NAME>& b, const Vec2<NAME>& c) {
		return b.x==c.x&&b.y==c.y;
	}

	////Square<typename> operator達
	//
	//template<typename T2>
	//inline Square<T2> operator  +(const Square<T2>& b, const Square<T2>& c) {
	//	Square<T2> ans;
	//	ans.pos = b.pos+c.pos;
	//	ans.size = b.size + c.size;
	//	return ans;
	//}

	
	/// <summary>
	/// 四角が重なっているかどうか
	/// </summary>
	/// <param name="true　 ">重なっている</param>
	/// <param name="false　">重なっていない</param>
	/// <returns></returns>
	template<typename T>
	bool CheckSquareCollision(Square<T> p1,Square<T> p2) {
		bool up=false, down = false, left = false, right = false;
		if (p1.pos.x + p1.size.x	> p2.pos.x)				right = true;
		if (p1.pos.x				< p2.pos.x + p2.size.x)	left = true;
		
		if (p1.pos.y + p1.size.y	> p2.pos.y)				down = true;
		if (p1.pos.y 				< p2.pos.y+p2.size.y)	up = true;
		
		if (right && left && down && up)return true;

		return false;
	}

}