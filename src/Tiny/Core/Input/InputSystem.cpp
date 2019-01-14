#include "Tiny/Core/Input/InputSystem.h"
#include "Tiny/Core/Input/InputEvent.h"
#include "Tiny/Math/Tools.h"
#include "IronBranch/Utility/Log.h"
#include <assert.h>

namespace Tiny { namespace Input {


	void StandardInputSystem::Update(double dt) {
		if (_standardInputs.Size()) {
			for (auto& input : _standardInputs) {
				Touch(input);
			}
		}
		else
			TouchEnd();

		_standardInputs.Clear();
	}

	void StandardInputSystem::Touch(const StandardInputs::Datum& input) {
		//IronBranch::Utility::Log::V("Standard Input x:{}, y{}, state:{}\n Last Input x::{}, y:{}, dragging:{}\n",
		//	input.x, input.y, (input.type == StandardDatum::Type::Press ? "press":"release"),
		//	_lastInput._input.x, _lastInput._input.y, (_lastInput._isDragging ? "True" : "False"));
		if (input.type == StandardInputs::Datum::Type::Press) {
			bool dragging = false;
			if (_lastInput.Empty()) {
				_clickSlots.Emit({ input.x, input.y, ClickEvent::Stage::Press });
			}
			else {
				if (_lastInput.Same(input)) {
					if (_lastInput._isDragging) {
						dragging = _lastInput._isDragging;;
						_dragSlots.Emit({ 0, 0, DragEvent::Stage::Drag });
					}
					/*
					else
						TODO: long press
					*/
				}
				else {
					dragging = true;
					if(!_lastInput._isDragging)
						_dragSlots.Emit({ input.x - _lastInput._input.x, input.y - _lastInput._input.y, DragEvent::Stage::Begin});
					_dragSlots.Emit({ input.x - _lastInput._input.x, input.y - _lastInput._input.y, DragEvent::Stage::Drag });
				}
			}
			_lastInput._input = input;
			_lastInput._isDragging = dragging;
		}
		else if (input.type == StandardInputs::Datum::Type::Release) {
			TouchEnd();
		}
	}

	void StandardInputSystem::TouchEnd() {
		if (!_lastInput.Empty()) {
			if (_lastInput._isDragging)
				_dragSlots.Emit({ 0.0, 0.0, DragEvent::Stage::Release });
			else
				_clickSlots.Emit({ _lastInput._input.x,  _lastInput._input.y, ClickEvent::Stage::Release });
		}
		_lastInput.Clear();
	}
} }

