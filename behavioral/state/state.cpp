#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <vector>


enum class State
{
	OffTheHook,
	Connecting,
	Connected,
	OnHold,
};

inline std::ostream& operator<<(std::ostream& out, const State& s)
{
	switch(s)
	{
	case State::OffTheHook:
		out << "Off The Hook";
		break;
	case State::Connecting:
		out << "Connecting";
		break;
	case State::Connected:
		out << "Connected";
		break;
	case State::OnHold:
		out << "On Hold";
		break;
	default:
		throw std::runtime_error("Invalid state.");
	}

	return out;
}

enum class Trigger
{
	Dialed,
	HungUp,
	CallConnected,
	PlacedOnHold,
	TakenOffHold,
	LeftMessage,
};

inline std::ostream& operator<<(std::ostream& out, const Trigger& s)
{
	switch(s)
	{
	case Trigger::Dialed:
		out << "Dialed";
		break;
	case Trigger::HungUp:
		out << "Hung Up";
		break;
	case Trigger::CallConnected:
		out << "Call Connected";
		break;
	case Trigger::PlacedOnHold:
		out << "Placed On Hold";
		break;
	case Trigger::TakenOffHold:
		out << "Taken Off Hold";
		break;
	case Trigger::LeftMessage:
		out << "Left Message";
		break;
	default:
		throw std::runtime_error("Invalid state.");
	}

	return out;
}

int main()
{
	std::unordered_map<State, std::vector<std::pair<Trigger, State>>> state_machine;

	state_machine[State::OffTheHook] = {
		{Trigger::Dialed, State::Connecting},
	};

	state_machine[State::Connecting] = {
		{Trigger::HungUp, State::OffTheHook},
		{Trigger::CallConnected, State::Connected},
	};

	state_machine[State::Connected] = {
		{Trigger::LeftMessage, State::OffTheHook},
		{Trigger::HungUp, State::OffTheHook},
		{Trigger::PlacedOnHold, State::OnHold},
	};

	state_machine[State::OnHold] = {
		{Trigger::TakenOffHold, State::Connected},
		{Trigger::HungUp, State::OffTheHook},
	};

	auto current_state{State::OffTheHook};
	while(true)
	{
		std::cout << "The phone is currently in " << current_state << std::endl;
		std::cout << "Select a trigger: " << std::endl;;
		for(auto i = 0ull; i < std::size(state_machine[current_state]); ++i)
		{
			std::cout << "[" << i << "] " << state_machine[current_state][i].first << std::endl;
		}

		auto option{-1};
		std::cin >> option;
		if(option < 0 || option >= static_cast<int>(std::size(state_machine[current_state])))
		{
			std::cerr << "Invalid option, try again!" << std::endl;
			continue;
		}

		current_state = state_machine[current_state][option].second;
	}

	return 0;
}


