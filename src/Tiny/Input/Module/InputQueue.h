#pragma once

#include "Tiny/Def.h"
#include "Tiny/Types.h"
#include "Tiny/Core/Service.h"

#include "IronBranch/Memory/Strategy/FreeList.h"
#include "IronBranch/Memory/AllocatorWrapper.h"

#include <list>
#include <string>

namespace Tiny{
    namespace Input{
        template<typename Datum>
        class InputQueue{
        public:
            explicit InputQueue(std::string tag, std::size_t maxSize)
            : _maxSize(maxSize)
            , _tag(tag){

            }

            ~InputQueue() = default;

            InputQueue(const InputQueue&) = default;
            InputQueue(InputQueue&& other) = default;
            InputQueue& operator=(InputQueue other){
                swap(*this, other);
                return *this;
            }

            friend void swap(InputQueue& a, InputQueue& b){
                std::swap(a._queue, b._queue);
                std::swap(a._maxSize, b._maxSize);
                std::swap(a._used, b._used);
                std::swap(a._tag, b._tag);
            }

            void Push(Datum data){
                //Service::Log().W("InputQueue {0} push, _used:{1}", _tag ,_used);
                if(_used >= _maxSize){
                    Service::Log().E("InputQueue {0} overflow! MaxQueueSize is {1}", _tag, _maxSize);
                    return;
                }
                _queue.push_back(data);
                _used++;
            }

            /*
                @brief  pop all cached data and clear all data.
            */
            std::list<Datum> Pop(){
                std::list<Datum> result;
                auto& iter = _queue.begin();
                while(iter != _queue.end()){
                    result.emplace_back(std::move(iter->data));
                    iter++;
                }
                _queue.clear();
				_used = 0;
                //Service::Log().W("InputQueue {0} clear, _used:{1}", _tag ,_used);
                return result;
            }

        private:
     //       struct Trait{
     //           union PlaceHolder{
     //               Datum data;
     //               void* _;
     //               PlaceHolder(const Datum& d)
     //               :data(d){

     //               }
					//PlaceHolder() = default;
     //           } _placeHolder;

     //           Trait(Datum data){
     //               new(&_placeHolder.data)Datum{data};
     //           }
     //       };
			union Trait {
				Datum data;
				void* _;
				Trait(const Datum& d)
					:data(d) {

				}
				Trait() = default;
			};

            std::list<Trait, IronBranch::Memory::STLAllocatorWrapper<IronBranch::Memory::FreeList, Trait>> _queue;
            std::size_t     _maxSize;
            std::size_t     _used;
            std::string     _tag;
        };
    }
}
