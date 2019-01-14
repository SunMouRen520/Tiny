#ifndef TINY_CORE_INPUT_INPUTS_DATA_H
#define TINY_CORE_INPUT_INPUTS_DATA_H

#include <cstddef>
#include <vector>

namespace Tiny {
	namespace Input {
		/*
			This file include the data structures which should be provided by underlying system accordingly.
		*/

		template<typename InnerDatum> class InputsTemplate {
		public:
			using Datum = InnerDatum;

			InputsTemplate() = default;

			void AddDatum(const Datum& datum) {
				_data.push_back(datum);
			}

			std::uint8_t Size() const{
				return (std::uint8_t)_data.size();
			}

			void Clear() {
				_data.clear();
			}

			auto begin() {
				return _data.begin();
			}

			auto begin() const{
				return _data.begin();
			}

			auto end() {
				return _data.end();
			}

			auto end() const{
				return _data.end();
			}

		private:
			std::vector<Datum> _data;
		};


		/*
		  @brief	Mouse left-button / touch
		*/
		struct StandardDatum {
			enum class Type {
				Press, 
				Release,
			};
			double x;
			double y;
			Type type;
		};

		using StandardInputs = InputsTemplate<StandardDatum>;
		/*
		  @brief	keyboard 
		*/
		struct KeyboardDatum {
			enum class Type {
				Press, 
				Rlease,
			};
			std::uint32_t keyboard; //using GLFW keyboard macro value
			Type type;
		};
		using KeyoardInputs = InputsTemplate<KeyboardDatum>;

		/*
		  @brief	Mouse scroll button
		*/
		struct ScrollDatum {
			double x;
			double y;
		};
		using ScrollInputs = InputsTemplate<ScrollDatum>;

	}
}

#endif // !TINY_CORE_INPUT_INPUTS_DATA_H
