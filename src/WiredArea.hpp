#pragma once

#include <morda/widgets/core/container/Container.hpp>

#include "OpenGL2ShaderColorPosLum.hpp"

class WiredArea : public morda::Container{
	struct Wire {
		morda::Vec2r begin;
		morda::Vec2r end;

		//TODO:
	};

	std::vector<Wire> wires;
	
public:
	WiredArea(const WiredArea&) = delete;
	WiredArea& operator=(const WiredArea&) = delete;
	
	WiredArea(const stob::Node* chain = nullptr);
	
	class WireSocket : virtual public morda::Widget{
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

		unsigned type;

		std::weak_ptr<WireSocket> connection;
		
	public:
		WireSocket(const WireSocket&) = delete;
		WireSocket& operator=(const WireSocket&) = delete;
		
		WireSocket(const stob::Node* chain = nullptr);

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
	};
	
	void render(const morda::Matr4r& matrix) const override;

private:

};

