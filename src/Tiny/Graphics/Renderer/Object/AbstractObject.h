#ifndef TINY_GRAPHICS_ABSTRACTOBJECT_H
#define TINY_GRAPHICS_ABSTRACTOBJECT_H

namespace Tiny{ namespace Graphics{
	class AbstractObject {
	public:
		using Handle = UnsignedInt;

		AbstractObject(const AbstractObject&) = delete;
		AbstractObject& operator = (const AbstractObject&) = delete;

		AbstractObject(AbstractObject&& other) {
			std::swap(_handle, other._handle);
		}
		AbstractObject& operator = (AbstractObject&& other) {
			std::swap(_handle, other._handle);
		}

		virtual ~AbstractObject() = default;

	protected:
		AbstractObject() = default;

	private:
		Handle _handle;
	};
} }

#endif
