#pragma once

#include <morda/widgets/Widget.hpp>

class WireSocket : virtual public morda::Widget{
	friend class WireArea;

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

protected:
	WireSocket(const stob::Node* chain);
	
	std::shared_ptr<WireSocket> getRemote();
public:

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
	
	/**
	 * @brief Connection event callback.
	 * The notification method is called only on one of the wire sockets.
	 * @param to - the wire socket it is connected to.
	 */
	virtual void onConnected(WireSocket& to){}
	
	/**
	 * @brief Disconnection event notification.
	 * The notification method is called only on one of the wire sockets.
	 * @param from - the wire socket it was disconnected from.
	 */
	virtual void onDisconnected(WireSocket& from){}
};
