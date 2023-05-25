#include "Brain.h"


Brain::Brain()
{
}

Brain::Brain(const Brain& brain)
{
}

Brain::Action Brain::Compute()
{
	// TEMPORARY
	switch (Eis::Random::UInt(0, 8))
	{
	case 0:
		return Action::None;
	case 1:
		return Action::MoveN;
	case 2:
		return Action::MoveS;
	case 3:
		return Action::MoveW;
	case 4:
		return Action::MoveE;
	case 5:
		return Action::MoveNW;
	case 6:
		return Action::MoveNE;
	case 7:
		return Action::MoveSW;
	case 8:
		return Action::MoveSE;
	}
}