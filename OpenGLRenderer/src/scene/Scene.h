#pragma once
#include <scene/GameObject.h>
class Scene
{
private:
	std::vector<std::shared_ptr<GameObject>> m_Objects;
public:

	Scene();
	~Scene();

	void Render();

	void AddObject(std::shared_ptr<GameObject>& object);
	void CreateObject(bool empty = false);
	void RemoveObject(int index);
	void RemoveObject(UniversallyUniqueID id);

	const std::vector<std::shared_ptr<GameObject>>& GetObjects() const { return m_Objects; }
};

