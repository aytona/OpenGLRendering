#include "SceneNode.h"
#pragma once
///////////////////////////////////////////////////////////////////////
//
// SceneNode.cpp
//
///////////////////////////////////////////////////////////////////////
using namespace std;

SceneNode::SceneNode(glm::mat4 aTransformation, float aScale)
{
	transformation = aTransformation;
	parent = nullptr;
	children = std::vector<SceneNode*>();
	scale = aScale;
	r = 1.0f;
	g = 1.0f;
	b = 1.0f;
}

void SceneNode::setColor(float R, float G, float B, float A)
{
	r = R;
	g = G;
	b = B;
    a = A;
}
void SceneNode::setParent(SceneNode* p)
{
	parent = p;
}

void SceneNode::addChild(SceneNode* child)
{
	children.push_back(child);
	(*child).setParent(this);

}

glm::mat4 SceneNode::getTransformationMatrix()
{
	return transformation;
}

std::vector<SceneNode*> SceneNode::getChildren()
{
	return children;
}
SceneNode* SceneNode::getParent()
{
	return parent;
}

void SceneNode::render()
{
	//Step One: getMyTransformation
	glm::mat4 transf = getTransformationMatrix();
	glm::vec3 myScale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(transf, myScale, rotation, translation, skew, perspective);

	//Step Two: glPushMatrix(My Transformation)
	glPushMatrix();
	glTranslatef(translation.x, translation.y, translation.z);

    float angle = 2 * acos(rotation.w);
    angle = angle * 180 / M_PI;
	float sqrtOfW = sqrt(1 - rotation.w * rotation.w);

    if (sqrtOfW != 0) {
        glRotatef(angle, rotation.x / sqrtOfW, rotation.y / sqrtOfW, rotation.z / sqrtOfW);
    }
	/*glRotatef(2 * acos(rotation.w), rotation.x / sqrtOfW, rotation.y / sqrtOfW, rotation.z / sqrtOfW);*/


	//Step Three: Draw myself
	glColor4f(r, g, b, a);
	draw(scale);


	//Step Four: Render My Children
	for (int i = 0; i < children.size(); i++)
	{
		SceneNode* tmp = children.at(i);
		(*tmp).render();
	}

	//Final Step: glPopMatrix()
	glPopMatrix();

	return;

}


