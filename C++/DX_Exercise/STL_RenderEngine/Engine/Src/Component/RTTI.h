#pragma once

#include "Core.h"

// 상속 관계에 있는 클래스 간의
// 동적(실행중에) 형변환을 빠르게 하기 위해 사용하는 클래스.
namespace Ronnie
{
	// RunTime-Type-Information.
	// Reflection (리플렉션).
	// Java/C# - 변수 이름 얻어오기. 함수 이름 얻어오기.
	// UE4: Cast<Type>();
	class ENGINE_API RTTI
	{
	public:
		virtual const size_t& TypeIdInstance() const = 0;

		virtual RTTI* QueryInterface(const size_t id) const
		{
			return nullptr;
		}

		virtual bool Is(const size_t it) const
		{
			return false;
		}

		virtual bool Is(const std::string& name) const
		{
			return false;
		}

		template<typename T>
		T* As() const
		{
			if (Is(T::TypeIdClass()))
			{
				return (T*)this;
			}

			return nullptr;
		}
	};

#define RTTI_DECLARATIONS(Type, ParentType)													\
	public:																					\
		typedef ParentType Parent;															\
		static std::string TypeName() { return std::string(#Type); }						\
		virtual const size_t& TypeIdInstance() const { return Type::TypeIdClass(); }		\
		static const size_t& TypeIdClass() { return sRunTimeTypeId; }						\
		virtual RTTI* QueryInterface(const size_t id) const									\
		{																					\
			if (id == sRunTimeTypeId)														\
			{ return (RTTI*)this; }															\
			else																			\
			{ return Parent::QueryInterface(id); }											\
		}																					\
		virtual bool Is(const size_t id) const												\
		{																					\
			if (id == sRunTimeTypeId)														\
			{ return true; }																\
			else { return Parent::Is(id); }													\
		}																					\
		virtual bool Is(const std::string& name) const										\
		{																					\
			if (name == TypeName())															\
			{ return true; }																\
			else { return Parent::Is(name); }												\
		}																					\
	private:																				\
		static size_t sRunTimeTypeId;

#define RTTI_DEFINITIONS(Type) size_t Type::sRunTimeTypeId = (size_t)(&Type::sRunTimeTypeId);
}