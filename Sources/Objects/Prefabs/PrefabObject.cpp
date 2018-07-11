#include "PrefabObject.hpp"

#include "Objects/GameObject.hpp"
#include "Helpers/FileSystem.hpp"

namespace fl
{
	PrefabObject::PrefabObject(const std::string &filename) :
		IResource(),
		m_filename(filename),
		m_fileJson(FileJson(filename))
	{
		if (!FileSystem::FileExists(filename))
		{
			FileSystem::CreateFile(filename);
		}

		m_fileJson.Load();
	}

	PrefabObject::~PrefabObject()
	{
	}

	void PrefabObject::Write(const GameObject &gameObject)
	{
		m_fileJson.Clear();

		for (auto &component : gameObject.GetComponents())
		{
			component->Write(m_fileJson.GetParent()->GetChild(component->GetName(), true));
		}
	}

	void PrefabObject::Save()
	{
		m_fileJson.Save();
	}
}