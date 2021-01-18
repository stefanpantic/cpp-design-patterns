#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/states.hpp>
#include <iostream>
#include <vector>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

// Transitions
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct PhoneThrownIntoWall {};

// States
struct PhoneStateMachine : public msm::front::state_machine_def<PhoneStateMachine>
{
	bool angry{false};

	struct OffTheHook : public msm::front::state<> {};
	struct Connecting : public msm::front::state<>
	{
		template <typename Event, typename FSM>
		void on_entry(const Event&, const FSM&)
		{
			std::cout << "Connecting..." << std::endl;
		} // on_exit
	};
	struct PhoneBeingDestroyed
	{
		template <typename Event, typename FSM, typename SourceState, typename TargetState>
		void operator()(const Event&, const FSM&, const SourceState&, const TargetState&)
		{
			std::cout << "Phone breaks into a million pieces..." << std::endl;
		}
	};
	struct CanDestroyPhone
	{

		template <typename Event, typename FSM, typename SourceState, typename TargetState>
		bool operator()(const Event&, const FSM& fsm, const SourceState&, const TargetState&)
		{
			return fsm.angry;
		}
	};
	struct Connected : public msm::front::state<> {};
	struct OnHold : public msm::front::state<> {};
	struct PhoneDestroyed : public msm::front::state<> {};

	struct transition_table : mpl::vector<
									msm::front::Row<OffTheHook, CallDialed, Connecting>,
									msm::front::Row<Connecting, CallConnected, Connected>,
									msm::front::Row<Connected, PlacedOnHold, OnHold>,
									msm::front::Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed, PhoneBeingDestroyed, CanDestroyPhone>
								>
	{};

	using initial_state = OffTheHook;
};

int main()
{
	std::vector<std::string> states{
		"Off The Hook",
		"Connecting",
		"Connected",
		"On Hold",
		"Phone Destroyed",
	};

	msm::back::state_machine<PhoneStateMachine> phone;
	auto info{[&phone, &states] ()
		{
			auto idx{phone.current_state()[0]};
			std::cout << "The phone is currently in state: " << states[idx] << std::endl;
		}};

	info();
	phone.process_event(CallDialed{});
	info();
	phone.process_event(CallConnected{});
	info();
	phone.process_event(PlacedOnHold{});
	info();
	phone.process_event(PhoneThrownIntoWall{});
	info();

	return 0;
}

