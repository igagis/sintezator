#pragma once

#include <morda/widgets/Container.hpp>


class WiredArea : public morda::Container{
	morda::real wireHalfWidth;
	std::uint32_t wireColor;
	std::uint32_t grabbedColor;
public:
	WiredArea(const WiredArea&) = delete;
	WiredArea& operator=(const WiredArea&) = delete;
	
	WiredArea(const stob::Node* chain);
	
	class WireSocket : virtual public morda::Widget{
		friend class WiredArea;
		
		unsigned groupId;
	public:
		enum class Outlet_e {
			LEFT,
			TOP,
			RIGHT,
			BOTTOM
		};
	private:
		Outlet_e outlet_v;

		std::weak_ptr<WireSocket> primary;
		std::shared_ptr<WireSocket> slave;
		
	public:
		WireSocket(const WireSocket&) = delete;
		WireSocket& operator=(const WireSocket&) = delete;
		
		WireSocket(const stob::Node* chain);

		/**
		 * @brief Alignment of wire out.
		 */
		decltype(outlet_v) outlet()const noexcept {
			return this->outlet_v;
		}

		void setOutlet(decltype(outlet_v) o) {
			this->outlet_v = o;
		}
		
		/**
		 * @brief Returns position and direction of the outlet.
		 * @return Array of two vectors. First is the position of the outlet within the widget.
		 *         Second is the unit vector of outlet wire direction.
		 */
		std::array<morda::Vec2r, 2> outletPos()const noexcept;

		void connect(const std::shared_ptr<WireSocket>& o = nullptr);
		void disconnect();
		
		bool onMouseButton(bool isDown, const morda::Vec2r& pos, morda::MouseButton_e button, unsigned pointerID) override;

		void onHoverChanged(unsigned pointerID) override;
	};
	
	void render(const morda::Matr4r& matrix) const override;

	void layOut() override;
	
	bool onMouseMove(const morda::Vec2r& pos, unsigned pointerID) override;

private:
	morda::Vec2r mousePos;
	
	std::shared_ptr<WireSocket> grabbedSocket;
	std::shared_ptr<WireSocket> hoveredSocket;
	
	std::list<std::shared_ptr<WireSocket>> sockets;

};

