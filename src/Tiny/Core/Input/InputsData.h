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

#ifdef TINY_PLATFORM_WINDOWS
		enum class KeyBoard {
			None = 0,

			KEY_A,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,

			f1,
			f2,
			f3,
			f4,
			f5,
			f6,
			f7,
			f8,
			f9,
			f10,
			f11,
			f12,

			ESC,
			TILDE,
			TAB,
			CAPSLOCK,
			LEFTSHIFT,
			LEFTCTRL,
			BACKSPACE,
			ENTER,
			LEFTBRACKET,
			RIGHTBRACKET,
			SEMICOLON,
			QUOTE,
			COMMA,
			PERIOD,
			SLASH,
			BACKSLASH,
		};

		/*
		  @brief	keyboard 
		*/
		struct KeyboardDatum {
			enum class Type {
				Press, 
				Rlease,
			};
			std::uint32_t keyboard; 
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
#endif

	}
}

#endif // !TINY_CORE_INPUT_INPUTS_DATA_H
