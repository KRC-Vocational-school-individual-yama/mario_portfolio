#pragma once

template<typename NAME>
struct Vec2 {
	NAME x, y;
	//void Add(const Vec2& _data) {
	//	this->x = this->x + _data.x;
	//	this->y = this->y + _data.y;
	//}
	//void Mul(const Vec2& _data) {
	//	this->x = this->x * _data.x;
	//	this->y = this->y * _data.y;
	//}

	template<typename NAME2>
	Vec2<NAME2>Cast() {
		Vec2<NAME2> ans;
		ans.x =  static_cast<NAME2>(this->x);
		ans.y =  static_cast<NAME2>(this->y);
		return ans;
	}

	/// <summary>
	/// Vec2＜typename＞のメンバ変数を全て0で返す
	/// </summary>
	/// <param name="x">　0</param>
	/// <param name="y">　0</param>
	/// <returns></returns>
	static inline Vec2<NAME>zero() {
		return Vec2<NAME>{0,0};
	}
};

template<typename NAME>
struct Circle {
	Vec2<NAME> pos;
	NAME radius;
};

template<typename T>
struct Square {
	Vec2<T> pos;
	Vec2<T> size;

	template<typename T2>
	void Cast() {
		Square<T2> ans;
		ans.pos = this->pos.Cast<T2>();
		ans.size = this->size.Cast<T2>();
	}
};