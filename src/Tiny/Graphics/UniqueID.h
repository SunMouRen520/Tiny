#ifndef _TINY_UNIQUEID_H
#define _TINY_UNIQUEID_H

#include <vector>
#include "Tiny/Core/Service.h"

namespace Tiny {
	namespace Graphics {
		template<typename T, std::size_t size>
		class UniqueID
		{
		public:
			UniqueID();
			~UniqueID();
			std::size_t operator()() { return ID; }
		private:
			std::size_t ID;
		private:
			static std::size_t uniqueid;
			static std::size_t maxSize;
			static std::vector<std::size_t> recycle;
		};

		template<typename T, std::size_t size>
		UniqueID<T, size>::UniqueID()
		{
			if (recycle.size() != 0)
			{
				ID = recycle.back();
				recycle.pop_back();
				return;
			}

			if (uniqueid >= maxSize)
			{
				Service::Log().E("uniqueid creation error");
				return;
			}

			ID = uniqueid++;
		}

		template<typename T, std::size_t size>
		UniqueID<T, size>::~UniqueID()
		{
			recycle.push_back(ID);
		}

		template<typename T, std::size_t size>
		std::size_t UniqueID<T, size>::uniqueid = 0;

		template<typename T, std::size_t size>
		std::size_t UniqueID<T, size>::maxSize = size;

		template<typename T, std::size_t size>
		std::vector<std::size_t> UniqueID<T, size>::recycle;
	}
}

#endif