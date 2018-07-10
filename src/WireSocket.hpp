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

	void* userData_v = nullptr;
	
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
	
	virtual bool canConnectTo(const WireSocket& ws){
		return true;
	}
	
	virtual void onConnected(WireSocket& to);
	
	/**
	 * @brief Invoked when one socket is connected to another.
	 */
	std::function<void(WireSocket&, WireSocket&)> connected;
	
	
	virtual void onDisconnected(WireSocket& from);
	
	std::function<void(WireSocket&, WireSocket&)> disconnected;
	
	/**
	 * @brief Data for user use.
	 */
	void* userData = nullptr;
};
