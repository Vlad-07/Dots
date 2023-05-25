#pragma once

#include <Eis.h>


class Brain
{
public:

	struct Inputs
	{
		int posX, posY;

		void operator =(const Inputs& ins)
		{
			posX = ins.posX;
			posY = ins.posY;
		}
	};

	enum Action
	{
		None = 0, MoveN, MoveS, MoveW, MoveE, MoveNW, MoveNE, MoveSW, MoveSE
	};

public:
	Brain();
	Brain(const Brain& brain);
	~Brain() = default;

	inline void SetInputs(const Inputs& inputs) { m_CurrentInputs = inputs; }

	Action Compute();

private:
	Inputs m_CurrentInputs;
	bool m_NewInputsAreSet;
};