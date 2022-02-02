#pragma once
#include <glm/glm.hpp>

// This is a pure abstract class. It will be used 
// as a base for the derived classes that will use
// FixedUpdate.

enum ShapeType
{
	PLANE = 0,
	CIRCLE,
	BOX,
	SHAPE_COUNT
};

class PhysicsObject
{
protected:
	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:
	virtual void FixedUpdate(glm::vec2 a_gravity,
		float a_timeStep) = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPosition() {};

	ShapeType GetShapeID() { return m_shapeID; }

	float GetElasticity() { return m_elasticity; }
	void SetElasticity(float a_elasticity) { m_elasticity = a_elasticity; }

protected:
	ShapeType m_shapeID;
	float m_elasticity;
	bool m_isKinematic;
};

