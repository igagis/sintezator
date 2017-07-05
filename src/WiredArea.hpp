#pragma once

#include <morda/widgets/core/container/Container.hpp>



class WiredArea : public morda::Container{
public:
	WiredArea(const WiredArea&) = delete;
	WiredArea& operator=(const WiredArea&) = delete;
	
	WiredArea(const stob::Node* chain = nullptr);
	
	class WireSocket : virtual public morda::Widget{
	public:
		enum class WireOut_e {
			LEFT,
			RIGHT,
			TOP,
			BOTTOM,
			CENTER
		};
	private:
		WireOut_e wireOut_v;
	public:
		WireSocket(const WireSocket&) = delete;
		WireSocket& operator=(const WireSocket&) = delete;
		
		WireSocket(const stob::Node* chain = nullptr);

		/**
		 * @brief Alignment of wire out.
		 */
		decltype(wireOut_v) wireOut()const noexcept {
			return this->wireOut_v;
		}

		void setWireOut(decltype(wireOut_v) wo) {
			this->wireOut_v = wo;
		}
	};
	
private:

};

