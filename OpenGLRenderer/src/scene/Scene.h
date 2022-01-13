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

	const std::shared_ptr<GameObject> GetObjectAtIndex(int index) const 
	{ 
		if (index >= m_Objects.size())
		{
			return std::shared_ptr<GameObject>();
		}
		return m_Objects[index]; 
	}

	const std::vector<std::shared_ptr<GameObject>>& GetObjects() const { return m_Objects; }
};

