#pragma once

#include <morda/widgets/core/container/Container.hpp>

#include "OpenGL2ShaderColorPosLum.hpp"

class WiredArea : public morda::Container{
	
public:
	WiredArea(const WiredArea&) = delete;
	WiredArea& operator=(const WiredArea&) = delete;
	
	WiredArea(const stob::Node* chain);
	
	class WireSocket : virtual public morda::Widget{
		friend class WiredArea;
	public:
		enum class Outlet_e {
			LEFT,
			RIGHT,
			TOP,
			BOTTOM,
			CENTER
		};

		enum class InOut_e {
			IN,
			OUT,
			INOUT
		};
	private:
		Outlet_e outlet_v;

		InOut_e inOut_v;

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

		void connect(const std::shared_ptr<WireSocket>& o = nullptr);
		void disconnect();
	};
	
	void render(const morda::Matr4r& matrix) const override;

	void layOut() override;

private:
	std::list<std::shared_ptr<WireSocket>> sockets;

};

