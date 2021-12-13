#pragma once
#include <scene/GameObject.h>
class Scene
{
public:
	std::vector<std::shared_ptr<GameObject>> m_Objects;

	Scene();
	~Scene();

	void AddObject(std::shared_ptr<GameObject>& object);
	void CreateObject();
};

