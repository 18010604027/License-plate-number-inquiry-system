#include"pch.h"
#include"Backgound.h"
Bitmap* _background;
void LoadBackgound(Image* imgBackground, CRect winrect)
{
	int imgwidth, imgheight;
	imgheight = imgBackground->GetHeight();
	imgwidth = imgBackground->GetWidth();
	if ((imgwidth / (double)imgheight) > (winrect.Width() / (double)winrect.Height()))
	{
		imgwidth = imgwidth * winrect.Height() / imgheight;
		imgheight = winrect.Height();
	}
	else
	{
		imgheight = imgheight * winrect.Width() / imgwidth;
		imgwidth = winrect.Width();
	}
	if (_background)
	{
		delete _background;
	}
	_background = new Bitmap(imgwidth, imgheight);
	Graphics g(_background);
	g.Clear(Color(255, 255, 255, 255));
	g.DrawImage(imgBackground, 0, 0, imgwidth, imgheight);
}