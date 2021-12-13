#include "pch.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::AddObject(std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::CreateObject()
{
	std::shared_ptr<GameObject> object;
	object = std::make_shared<GameObject>("res/models/cube.obj", "res/shaders/basic.vert", "res/shaders/basic.frag", nullptr);
	AddObject(object);
}
