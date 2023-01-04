#pragma once

#include "box2d/b2_draw.h"

class B2DebugDraw : public b2Draw
{
public:
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
		// implement drawing code for polygons here
	}

	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override {
		// implement drawing code for solid polygons here
	}

	void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override {
		// implement drawing code for line segments here
	}

	void DrawTransform(const b2Transform& xf) override {
		// implement drawing code for transforms here
	}

	void DrawCircle(const b2Vec2& center, float radius, const b2Color& color) override {}

	void DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) override {}

	void DrawPoint(const b2Vec2& p, float size, const b2Color& color) override {}
};