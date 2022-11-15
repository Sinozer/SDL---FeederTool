#include "Holder.h"
#include "Button.h"

#include "ApplicationManager.h"

Holder::Holder(bool isActive,
	int x, int y, int w, int h,
	int colorR, int colorG, int colorB, int colorA)
{
	this->active = isActive;
	this->setX(x);
	this->setY(y);
	this->setW(w);
	this->setH(h);
	this->setColorR(colorR);
	this->setColorG(colorG);
	this->setColorB(colorB);
	this->setColorA(colorA);
}

Holder::~Holder()
{

}

bool Holder::isActive()
{
	return this->active;
}
void Holder::setActive(bool isActive)
{
	this->active = isActive;
}

SDL_Rect& Holder::getRect()
{
	return this->rect;
}

Holder Holder::getParent()
{
	return this->parent;
}
void Holder::setParent(Holder* parent)
{
	this->parent = parent;
}

int Holder::getX()
{
	return this->rect.x;
}
void Holder::setX(int x)
{
	this->rect.x = x;
}

int Holder::getY()
{
	return this->rect.y;
}
void Holder::setY(int y)
{
	this->rect.y = y;
}

int Holder::getW()
{
	return this->rect.w;
}
void Holder::setW(int w)
{
	this->rect.w = w;
}

int Holder::getH()
{
	return this->rect.h;
}
void Holder::setH(int h)
{
	this->rect.h = h;
}

int Holder::getColorR()
{
	return this->colorR;
}
void Holder::setColorR(int colorR)
{
	if (colorR < 0) colorR = 0;
	else if (colorR > 255) colorR = 255;
	this->colorR = colorR;
}

int Holder::getColorG()
{
	return this->colorG;
}
void Holder::setColorG(int colorG)
{
	if (colorG < 0) colorG = 0;
	else if (colorG > 255) colorG = 255;
	this->colorG = colorG;
}

int Holder::getColorB()
{
	return this->colorB;
}
void Holder::setColorB(int colorB)
{
	if (colorB < 0) colorB = 0;
	else if (colorB > 255) colorB = 255;
	this->colorB = colorB;
}

int Holder::getColorA()
{
	return this->colorA;
}
void Holder::setColorA(int colorA)
{
	if (colorA < 0) colorA = 0;
	else if (colorA > 255) colorA = 255;
	this->colorA = colorA;
}

void Holder::handleEvents()
{
	if (!this->active) return;
	/*###### Holders ######*/
	for (auto i = this->holderList.list.begin(); i != this->holderList.list.end(); i++)
	{
		i->second.handleEvents();
	}
	/*###### Holders ######*/
	/*###### TextBoxs ######*/
	for (auto i = this->textBoxList.list.begin(); i != this->textBoxList.list.end(); i++)
	{
		i->second->handleEvents();
	}
	/*###### TextBoxs ######*/
	/*###### Buttons ######*/
	for (auto i = this->buttonList.list.begin(); i != this->buttonList.list.end(); i++)
	{
		i->second->handleEvents();
	}
	/*###### Buttons ######*/
}

void Holder::update()
{
	if (!this->active) return;
	/*###### Holders ######*/
	for (auto i = this->holderList.list.begin(); i != this->holderList.list.end(); i++)
	{
		//cout << i->first << endl;
		i->second.update();
	}
	/*###### Holders ######*/
	/*###### TextBoxs ######*/
	if (this->textBoxList.getLen() > 0)
	{
		for (auto i = this->textBoxList.list.begin(); i != this->textBoxList.list.end(); i++)
		{
			i->second->update();
		}
	}
	/*###### TextBoxs ######*/
	/*###### Buttons ######*/
	if (this->buttonList.getLen() > 0)
	{
		for (auto i = this->buttonList.list.begin(); i != this->buttonList.list.end(); i++)
		{
			i->second->update();
		}
	}
	/*###### Buttons ######*/
}

void Holder::render()
{
	if (!this->active) return;
	SDL_SetRenderDrawColor(ApplicationManager::application.getWindow()->renderer, this->colorR, this->colorG, this->colorB, this->colorA);
	SDL_RenderFillRect(ApplicationManager::application.getWindow()->renderer, &this->rect);

	/*###### Holders ######*/
	for (auto i = this->holderList.list.begin(); i != this->holderList.list.end(); i++)
	{
		i->second.render();
	}
	/*###### Holders ######*/
	/*###### TextBoxs ######*/
	if (this->textBoxList.getLen() > 0)
	{
		for (auto i = this->textBoxList.list.begin(); i != this->textBoxList.list.end(); i++)
		{
			i->second->render();
		}
	}
	/*###### TextBoxs ######*/
	/*###### Buttons ######*/
	if (this->buttonList.getLen() > 0)
	{
		for (auto i = this->buttonList.list.begin(); i != this->buttonList.list.end(); i++)
		{
			i->second->render();
		}
	}
	/*###### Buttons ######*/
}

/*###### Holder ######*/
Container<Holder>& Holder::getHolders()
{
	return this->holderList;
}

void Holder::createHolder(const char* name, bool isActive,
	int x, int y, int w, int h,
	int colorR, int colorG, int colorB, int colorA)
{
	this->holderList.add(name, Holder::Holder(isActive, x, y, w, h, colorR, colorG, colorB, colorA));
	this->holderList.getElement("name").setParent(this);
}
/*###### Holder ######*/

/*###### TextHolder ######*/
Container<TextBox*>& Holder::getTextBoxs()
{
	return this->textBoxList;
}

void Holder::createTextBox(const char* name,
	const char* text, bool isActive, bool isTitle,
	int x, int y, int w, int h,
	const char* vAlign, const char* hAlign,
	int colorR, int colorG, int colorB, int colorA)
{
	this->textBoxList.add(name, new TextBox(text, isActive, isTitle, x, y, w, h, vAlign, hAlign, colorR, colorG, colorB, colorA));
	this->textBoxList.getElement(name)->setParent(this);
}
/*###### TextHolder ######*/

/*###### Button ######*/
Container<Button*>& Holder::getButtons()
{
	return this->buttonList;
}

void Holder::createButton(const char* name, const char* text, function<void()> onClick,
	bool isActive, bool isTitle,
	int x, int y, int w, int h,
	const char* vAlign, const char* hAlign,
	int colorR, int colorG, int colorB, int colorA)
{
	this->buttonList.add(name, new Button(text, onClick, isActive, isTitle, x, y, w, h, vAlign, hAlign, colorR, colorG, colorB, colorA));
	this->buttonList.getElement(name)->setParent(this);
}
/*###### Button ######*/