#pragma once
#include "Vector2.h"
#include "Math/Matrix33.h"
#include "Core/Serializable.h"

namespace jc
{
	struct Transform:public ISerializable
	{
		Vector2 position;
		float rotation{0};
		Vector2 scale{1};
		
		Vector2 localposition;
		float localrotation{ 0 };
		Vector2 localscale{ 1 };

		Matrix33 matrix;

		Transform() {}
		Transform(const Vector2& position, float rotation =0, float scale=1) : position{ position }, rotation{ rotation }, scale{ scale }{}

		void Update();
		void Update(const Matrix33 mx);

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
	};

}