//#pragma once
//
//#include "julie/ecs/EntityId.hpp"
//
//#include <vector>
//#include <unordered_map>
//
////-----------------------------------------------------------------------------
//
//namespace jl::ecs {
//
////-----------------------------------------------------------------------------
//
//template<typename T>
//struct ConcreteComponentContainer
//{
//	std::vector<T> m_container;
//	std::unordered_map<EntityId, size_t> m_lookupTable;
//};
//
//template<typename T, typename ... Args>
//struct ComponentsContainer
//	: public ConcreteComponentContainer<T>
//	, public ComponentsContainer<Args...>
//{
//};
//
//template<typename T>
//struct ComponentsContainer<T> : public ConcreteComponentContainer<T>
//{
//};
//
////-----------------------------------------------------------------------------
//
//template<typename T>
//struct ConcreteComponentContainer
//{
//	std::vector<T>& m_container;
//	std::unordered_map<EntityId, size_t>& m_lookupTable;
//};
//
//template<typename T, typename ... Args>
//struct ComponentsContainer
//	: public ConcreteComponentContainer<T>
//	, public ComponentsContainer<Args...>
//{
//};
//
//template<typename T>
//struct ComponentsContainer<T> : public ConcreteComponentContainer<T>
//{
//};
//
////-----------------------------------------------------------------------------
//
//} // namespace jl::ecs
//
////-----------------------------------------------------------------------------
