#include "Resources.hpp"

namespace acid
{
	Resources::Resources() :
		m_timerPurge(Time::Seconds(4.0f))
	{
	}

	void Resources::Update()
	{
		if (m_timerPurge.IsPassedTime())
		{
			m_timerPurge.ResetStartTime();

			for (auto it = m_resources.begin(); it != m_resources.end();)
			{
				if ((*it).second.use_count() <= 1)
				{
					it = m_resources.erase(it);
					continue;
				}

				++it;
			}
		}
	}

	std::shared_ptr<Resource> Resources::Find(const Metadata &metadata) const
	{
		for (const auto &[key, resource] : m_resources)
		{
			if (*key == metadata)
			{
				return resource;
			}
		}

		return nullptr;
		/*auto it = m_resources.find(metadata);

		if (it == m_resources.end())
		{
			return nullptr;
		}

		return it->second;*/
	}

	void Resources::Add(const Metadata &metadata, const std::shared_ptr<Resource> &resource)
	{
		if (Find(metadata) != nullptr)
		{
			return;
		}

		m_resources.emplace(metadata.Clone(), resource);
	}

	void Resources::Remove(const std::shared_ptr<Resource> &resource)
	{
		for (auto it = m_resources.begin(); it != m_resources.end(); ++it) // TODO: Clean remove.
		{
			if ((*it).second == resource)
			{
				m_resources.erase(it);
			}
		}
	}
}
