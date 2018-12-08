# include <Siv3D.hpp> // OpenSiv3D v0.2.8

//http://www.ohshiro.tuis.ac.jp/~ohshiro/prog/game07_call_by_reference_pointer.html
Point Rotation2D(Point target, Point rotationCenter, double angle)
{
	double PI = 3.14159265358979323846;
	double theta = (angle / -180.0) * PI;
	target.y = -target.y; rotationCenter.y = -rotationCenter.y; // 数学座標と同じ様にするためにy座標値を反転
	
	Point pos;
	pos.x = (target.x - rotationCenter.x) * cos(theta) - (target.y - rotationCenter.y) * sin(theta) + rotationCenter.x;
	pos.y = -1.0 * ((target.x - rotationCenter.x) * sin(theta) + (target.y - rotationCenter.y) * cos(theta) + rotationCenter.y);
	return pos;
}

void Main()
{
	const ColorF backgroundColor(U"#454545");
	const ColorF foregroundColor(U"#e9e9e9");

	//Windowの生成
	Window::SetTitle(U"五度圏");
	Window::Resize(800, 800);
	Graphics::SetBackground(backgroundColor);	

	const String majorName[] = {U"C",U"F",U"B♭",U"E♭" ,U"A♭" ,U"D♭\nC♯" ,U"F♯\nG♭" ,U" B\nC♭" ,U"E" ,U"A" ,U"D",U"G" };
	const String minorName[] = { U"Am",U"Dm",U"Gm",U"Cm" ,U"Fm" ,U"B♭m\nA♯m" ,U"D♯m\nE♭m" ,U"G♯m\nA♭m" ,U"C♯m" ,U"F♯m" ,U"Bm",U"Em" };

	const Font majorFont(40, Typeface::Bold);
	const Font minorFont(15, Typeface::Bold);
	const Font infoFont(25);
	const Font infoSmallFont(15);

	const int pieStartDeg = 345;
	int pieOffsetDeg = 30;

	const int circleCenterSize = 20;
	const int circleSize = 300 + circleCenterSize;
	const int circleX = Window::Width() / 2;
	const int circleY = Window::Height() / 2;

	int mainDegOffset = 0;

	while (System::Update())
	{
		ClearPrint();

		Circle major(circleX, circleY, circleSize);
		Circle minor(circleX, circleY, circleSize / 2);
		Circle center(circleX, circleY, circleCenterSize);
		
		//#0
		major.drawPie(Radians(pieStartDeg), Radians(pieOffsetDeg), ColorF(U"#dadada"));
		minor.drawPie(Radians(pieStartDeg), Radians(pieOffsetDeg), ColorF(U"#dadada"));
		//#30
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 1), Radians(pieOffsetDeg), ColorF(U"#cacaca"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 1), Radians(pieOffsetDeg), ColorF(U"#cacaca"));
		//#60
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 2), Radians(pieOffsetDeg), ColorF(U"#aea29e"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 2), Radians(pieOffsetDeg), ColorF(U"#aea29e"));
		//#90
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 3), Radians(pieOffsetDeg), ColorF(U"#9a8b85"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 3), Radians(pieOffsetDeg), ColorF(U"#9a8b85"));
		//#120
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 4), Radians(pieOffsetDeg), ColorF(U"#aea29e"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 4), Radians(pieOffsetDeg), ColorF(U"#aea29e"));
		//#150
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 5), Radians(pieOffsetDeg), ColorF(U"#2954c1"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 5), Radians(pieOffsetDeg), ColorF(U"#6641a2"));
		//#180
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 6), Radians(pieOffsetDeg), ColorF(U"#ff6633"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 6), Radians(pieOffsetDeg), ColorF(U"#7a46c5"));
		//#210
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 7), Radians(pieOffsetDeg), ColorF(U"#f1ab31"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 7), Radians(pieOffsetDeg), ColorF(U"#6641a2"));
		//#240
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 8), Radians(pieOffsetDeg), ColorF(U"#f2ba5a"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 8), Radians(pieOffsetDeg), ColorF(U"#15e7ac"));
		//#270
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 9), Radians(pieOffsetDeg), ColorF(U"#f1ab31"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 9), Radians(pieOffsetDeg), ColorF(U"#12f3b4"));
		//#300
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 10), Radians(pieOffsetDeg), ColorF(U"#f2ba5a"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 10), Radians(pieOffsetDeg), ColorF(U"#15e7ac"));
		//#330
		major.drawPie(Radians(pieStartDeg + pieOffsetDeg * 11), Radians(pieOffsetDeg), ColorF(U"#cacaca"));
		minor.drawPie(Radians(pieStartDeg + pieOffsetDeg * 11), Radians(pieOffsetDeg), ColorF(U"#cacaca"));


		//中心を描画
		center.draw(backgroundColor);

		//音名を描画
		for(int i = 0; i < std::end(majorName) - std::begin(majorName); i++)
		{
			majorFont(majorName[i]).drawAt(Rotation2D(Point(circleX, circleY - circleSize + circleSize / 4), Point(circleX, circleY), (pieOffsetDeg * i) + mainDegOffset), Palette::Black);
			minorFont(minorName[i]).drawAt(Rotation2D(Point(circleX, circleY - circleSize / 2 + circleSize / 6), Point(circleX, circleY), (pieOffsetDeg * i) + mainDegOffset), Palette::Black);

		}
		
		//解説を描画
		infoFont(U"基調和音").drawAt(circleX, circleY - circleSize - 40, ColorF(U"#cacaca"));
		infoFont(U"トライトーン代理").drawAt(circleX, circleY + circleSize + 30, ColorF(U"#ff6633"));
		infoSmallFont(U"ダブル・ミクスチュア").drawAt(circleX, circleY + circleSize + 60, ColorF(U"#9f74dc"));
		infoFont(U"裏コード").drawAt(circleX + 180, circleY + circleSize + 10, ColorF(U"#5379d8"));
		infoFont(U"パ\nラ\nレ\nル\nマ\nイ\nナ\n丨").drawAt(circleX + circleSize + 40, circleY, ColorF(U"#aea29e"));
		infoFont(U"二\n次\nド\nミ\nナ\nン\nト").drawAt(circleX - circleSize - 30, circleY, ColorF(U"#f1ab31"));
		infoSmallFont(U"パ\nラ\nレ\nル\nメ\nジ\nャ\n丨").drawAt(circleX - circleSize - 60, circleY, ColorF(U"#15e7ac"));

		//回転の処理
		if(KeyRight.down())
		{
			mainDegOffset = mainDegOffset + pieOffsetDeg;
		}
		if(KeyLeft.down())
		{
			mainDegOffset = mainDegOffset - pieOffsetDeg;
		}
		
		/*if(KeySpace.down())
		{
			pieOffsetDeg = pieOffsetDeg * -1;
		}*/

		//枠線を描画
		center.drawFrame(0, 40, foregroundColor);
		center.drawFrame(2, 34, backgroundColor);
		major.drawFrame(3, 3, foregroundColor);
		minor.drawFrame(3, 3, foregroundColor);
		
		/*if(major.mouseOver() && !minor.mouseOver())
		{
			Print << U"Major: " << Cursor::Pos();
		}
		if(minor.mouseOver())
		{
			Print << U"Minor: " << Cursor::Pos();
		}*/
	}
}