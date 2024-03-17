#pragma once

#include <ruis/widgets/widget.hpp>

class WireSocket : virtual public ruis::widget{
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
	Outlet_e outlet_v = Outlet_e::BOTTOM;

	std::weak_ptr<WireSocket> primary;
	std::shared_ptr<WireSocket> slave;

public:
	WireSocket(const WireSocket&) = delete;
	WireSocket& operator=(const WireSocket&) = delete;

protected:
	WireSocket(const utki::shared_ref<ruis::context>& c, const tml::forest& desc);
	
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
	std::array<ruis::vector2, 2> outletPos()const noexcept;

	void connect(const std::shared_ptr<WireSocket>& o = nullptr);
	void disconnect();

	bool on_mouse_button(const ruis::mouse_button_event& event)override;

	void on_hovered_change(unsigned pointerID) override;
	
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
