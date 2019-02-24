#pragma once

#include "Tiny/Macro.h"
#include "Tiny/Types.h"
#include "Tiny/Input/Interface/Data.h"

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

            friend void swap(InputQueue&& a, InputQueue&& b){
                std::swap(a._queue, b._queue);
                std::swap(a._maxSize, b._maxSize);
                std::swap(a._used, b._used);
                std::swap(a._tag, b._tag);
            }

            void Push(Datum data){
                if(_used >= maxSize){
                    Service.Log().E("InputQueue {0} overflow! MaxQueueSize is {1}", _tag, _maxSize);
                    return;
                }
                _queue.push_back(data);
                _used++;
            }

            std::list<Datum> Pop(){
                std::list<Datum> result;
                auto& iter = _queue.begin();
                std::size_t count = 0;
                while(iter != _queue.end() && count <= _used){
                    result.push_back(std::move(iter->_placeHolder.data));
                    count++;
                }
                _queue.clear();
                return result;
            }

        private:
            struct Trait{
                union PlaceHolder{
                    Datum data;
                    void* _;
                    PlaceHolder(const Datum& d)
                    :data(d){

                    }
                } _placeHolder;

                Trait(Datum data){
                    new(&_placeHolder.data){std::move(data);}
                }
            };
            std::list<Trait, IronBranch::Memory::STLAllocatorWrapper<IronBranch::Memory::FreeList, Trait>> _queue;
            std::size_t     _maxSize;
            std::size_t     _used;
            std::string     _tag;
        };

        struct KeyboardData{
            KEYBOARD    key;
            bool        pressed;
        };

        struct MouseBtnData{
            MOUSEBTN    btn;
            bool        pressed;
        };
    }
}
