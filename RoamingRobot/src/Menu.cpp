#include <Menu.h>

AbstractMenu::AbstractMenu()
{
}

AbstractMenu::AbstractMenu(int WindowWidth, int WindowHeight)
{

}

void AbstractMenu::Click()
{
	m_bClicked = true;
}

void AbstractMenu::ResetClick()
{
	m_bClicked = false;
}
