//-----------------------------------------------------------------------------
namespace jl::ecs {
//-----------------------------------------------------------------------------

template<typename T>
inline size_t ConcreteComponentContainer<T>::getCount() const noexcept
{
	return m_container.size();
}
//-----------------------------------------------------------------------------

template<typename T>
inline T& ConcreteComponentContainer<T>::getByIdx(size_t _idx) noexcept
{
	return m_container[_idx];
}

template<typename T>
inline const T& ConcreteComponentContainer<T>::getByIdx(size_t _idx) const noexcept
{
	return m_container[_idx];
}

//-----------------------------------------------------------------------------

template<typename T>
inline T* ConcreteComponentContainer<T>::findById(EntityId _id) noexcept
{
	const T* result = static_cast<const ConcreteComponentContainer<T>*>(this)->findById(_id);
	return const_cast<T*>(result);
}

//-----------------------------------------------------------------------------

template<typename T>
inline const T* ConcreteComponentContainer<T>::findById(EntityId _id) const noexcept
{
	const T* result = nullptr;

	auto it = m_lookupTable.find(_id);
	if (it != m_lookupTable.end())
	{
		result = &getByIdx(it->second);
	}

	return result;
}

//-----------------------------------------------------------------------------

template<typename ... Args>
template<typename T>
inline ConcreteComponentContainer<T>& ComponentsContainer<Args...>::getContainer() noexcept
{
	static_assert(
		( ... || std::is_same_v<T, Args> ),
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<ConcreteComponentContainer<T>&>(*this);
}

template<typename ... Args>
template<typename T>
inline const ConcreteComponentContainer<T>& ComponentsContainer<Args...>::getContainer() const noexcept
{
	static_assert(
		( ... || std::is_same_v<T, Args> ),
		"ComponentsContainer doesn't containe components of specified type"
	);
	return static_cast<const ConcreteComponentContainer<T>&>(*this);
}

//-----------------------------------------------------------------------------
} // namespace jl::ecs
//-----------------------------------------------------------------------------
