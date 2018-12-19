#include "Tiny/Input/InputSystem.h"
#include "Tiny/Input/BaseInputEvent.h"
#include <assert.h>
#include "Tiny/Math/Tools.h"
#include "IronBranch/Utility/Log.h"

namespace Tiny { namespace Input {
	InputSystem::InputSystem()
		:_lastFrameInput{ 0, 0 }, _curFrameInput{ 0, 0 } {

	}

	void InputSystem::ProcessTouch() {
		if (_lastFrameInput.Empty()) {
			_clickSlots.Emit({ _curFrameInput.x, _curFrameInput.y, ClickEvent::ClickType::Press });
		}
		else {
			if (_curFrameInput == _lastFrameInput) {
				if (_lastFrameInput.isDragging) {
					_curFrameInput.isDragging = _lastFrameInput.isDragging;
					_dragSlots.Emit({ 0, 0, DragEvent::DragType::Drag });
				}
				/*
				else
					TODO: long press
				*/
			}
			else {
				_curFrameInput.isDragging = true;
					_dragSlots.Emit({ _curFrameInput.x - _lastFrameInput.x, _curFrameInput.y - _lastFrameInput.y, DragEvent::DragType::Drag });
			}
		}
		_lastFrameInput = _curFrameInput;
	}

	void InputSystem::ProcessTouchEnd() {
		if (!_lastFrameInput.Empty()) {
			if (_lastFrameInput.isDragging)
				_dragSlots.Emit({ 0.0, 0.0, DragEvent::DragType::Release });
			else
				_clickSlots.Emit({ _lastFrameInput.x, _lastFrameInput.y, ClickEvent::ClickType::Release });
		}
		_lastFrameInput = StandartInput();
	}
	
	void InputSystem::Update(double dt) {
		assert(_plat);
		_curFrameInput = _plat->GetStandartInputInfo();
		if (_curFrameInput.Empty())
			ProcessTouchEnd();
		else
			ProcessTouch();
	}
} }

