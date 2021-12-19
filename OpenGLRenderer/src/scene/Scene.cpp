#include "pch.h"
#include "Scene.h"


Scene::Scene()
{
	
}

Scene::~Scene()
{
}

void Scene::Render()
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		m_Objects[i]->Render();
	}
}

void Scene::AddObject(std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::CreateObject(bool empty)
{
	std::shared_ptr<GameObject> object;
	if (!empty)
	{
		object = std::make_shared<GameObject>();
	}
	else
	{
		object = std::make_shared<GameObject>();
	}

	AddObject(object);
}

void Scene::RemoveObject(int index)
{
	m_Objects[index].reset();
	m_Objects.erase(m_Objects.begin() + index);
}
